/*
 * This file is part of libFirm.
 * Copyright (C) 2012 University of Karlsruhe.
 */

/**
 * @file
 * @brief       implementation of set
 * @author      Markus Armbruster
 */

/*  This code is derived from:

    From: ejp@ausmelb.oz.AU (Esmond Pitt)
    Date: Tue, 7 Mar 1989 22:06:26 GMT
    Subject: v06i042: dynamic hashing version of hsearch(3)
    Message-ID: <1821@basser.oz>
    Newsgroups: comp.sources.misc
    Sender: msgs@basser.oz

    Posting-number: Volume 6, Issue 42
    Submitted-By: Esmond Pitt <ejp@ausmelb.oz.AU>
    Archive-name: dynamic-hash

    * Dynamic hashing, after CACM April 1988 pp 446-457, by Per-Ake Larson.
    * Coded into C, with minor code improvements, and with hsearch(3) interface,
    * by ejp@ausmelb.oz, Jul 26, 1988: 13:16;
 */

#include "pset.h"
#include "xmalloc.h"
#include "obst.h"
#include <assert.h>

#define SEGMENT_SIZE_SHIFT   8
#define SEGMENT_SIZE         (1 << SEGMENT_SIZE_SHIFT)
#define DIRECTORY_SIZE_SHIFT 8
#define DIRECTORY_SIZE       (1 << DIRECTORY_SIZE_SHIFT)
#define MAX_LOAD_FACTOR      4
# define SET pset
# define PMANGLE(pre) pre##_pset
# define MANGLEP(post) pset_##post
# define MANGLE(pre, post) pre##pset##post
# define EQUAL(cmp, elt, key, siz) (!(cmp) ((elt)->entry.dptr, (key)))

typedef struct element {
    struct element *chain;    /**< for chaining Elements */
    MANGLEP(entry)  entry;
} element_t, *segment_t;

struct SET {
    size_t p;             /**< Next bucket to be split */
    size_t maxp;          /**< upper bound on p during expansion */
    size_t nkey;          /**< current # keys */
    size_t nseg;          /**< current # segments */
    segment_t *dir[DIRECTORY_SIZE];
    MANGLEP(cmp_fun) cmp;     /**< function comparing entries */
    unsigned   iter_i;
    unsigned   iter_j;
    element_t *iter_tail;       /**< non-NULL while iterating over elts */
    element_t *free_list;       /**< list of free Elements */
    struct obstack obst;      /**< obstack for allocation all data */
};

pset *new_pset(pset_cmp_fun cmp, size_t nslots)
{
    if (nslots > SEGMENT_SIZE * DIRECTORY_SIZE) {
        nslots = DIRECTORY_SIZE;
    } else {
        /* Adjust nslots up to next power of 2, minimum SEGMENT_SIZE */
        size_t i = SEGMENT_SIZE;
        while (i < nslots)
            i <<= 1;
        nslots = i >> SEGMENT_SIZE_SHIFT;
    }

    SET *table = XMALLOC(SET);
    table->nseg      = table->p = table->nkey = 0;
    table->maxp      = nslots << SEGMENT_SIZE_SHIFT;
    table->cmp       = cmp;
    table->iter_tail = NULL;
    table->free_list = NULL;
    obstack_init(&table->obst);

    /* Make segments */
    for (size_t i = 0; i < nslots;  ++i) {
        table->dir[i] = OALLOCNZ(&table->obst, segment_t, SEGMENT_SIZE);
        table->nseg++;
    }

    return table;
}

void del_pset(pset *table)
{
    obstack_free(&table->obst, NULL);
    free(table);
}

int pset_default_ptr_cmp(const void *x, const void *y)
{
    return x != y;
}

/** Limit the hash value */
static inline unsigned limit_hash(SET const *table, unsigned const h)
{
    unsigned address = h & (table->maxp - 1);       /* h % table->maxp */
    if (address < (unsigned)table->p)
        address = h & ((table->maxp << 1) - 1); /* h % (2*table->maxp) */
    return address;
}

/**
 * Returns non-zero if the number of elements in
 * the set is greater then number of segments * MAX_LOAD_FACTOR
 */
static inline int loaded(SET *table)
{
    return ++table->nkey > (table->nseg << SEGMENT_SIZE_SHIFT) * MAX_LOAD_FACTOR;
}

/**
 * Expand the hash-table: the algorithm is split, so on every
 * insert, only ONE segment is rehashed!
 *
 * table->p contains the current segment to split
 * after all segments were split, table->p is set to zero and
 * table->maxp is duplicated.
 */
static void expand_table(SET *table)
{
    if (table->maxp + table->p >= (DIRECTORY_SIZE << SEGMENT_SIZE_SHIFT))
        return;

    /* Locate the bucket to be split */
    size_t     OldSegmentDir   = table->p >> SEGMENT_SIZE_SHIFT;
    segment_t *OldSegment      = table->dir[OldSegmentDir];
    size_t     OldSegmentIndex = table->p & (SEGMENT_SIZE - 1);

    /* Expand address space; if necessary create a new segment */
    size_t NewAddress      = table->maxp + table->p;
    size_t NewSegmentDir   = NewAddress >> SEGMENT_SIZE_SHIFT;
    size_t NewSegmentIndex = NewAddress & (SEGMENT_SIZE - 1);
    if (NewSegmentIndex == 0) {
        table->dir[NewSegmentDir] = OALLOCNZ(&table->obst, segment_t, SEGMENT_SIZE);
        table->nseg++;
    }
    segment_t *NewSegment = table->dir[NewSegmentDir];

    /* Adjust state variables */
    table->p++;
    if (table->p == table->maxp) {
        table->maxp <<= 1;  /* table->maxp *= 2 */
        table->p      = 0;
    }

    /* Relocate records to the new bucket */
    element_t **Previous  = &OldSegment[OldSegmentIndex];
    element_t  *Current   = *Previous;
    element_t **LastOfNew = &NewSegment[NewSegmentIndex];
    *LastOfNew = NULL;
    while (Current != NULL) {
        if (limit_hash(table, Current->entry.hash) == NewAddress) {
            /* Move to new chain */
            *LastOfNew = Current;
            *Previous  = Current->chain;
            LastOfNew  = &Current->chain;
            Current    = Current->chain;
            *LastOfNew = NULL;
        } else {
            /* Leave on old chain */
            Previous = &Current->chain;
            Current  = Current->chain;
        }
    }
}

void *_pset_search(pset *table, const void *key, unsigned hash, _pset_action action)
{
    assert(table);
    assert(key);

    /* Find collision chain */
    unsigned    h               = limit_hash(table, hash);
    unsigned    segment_index   = h & (SEGMENT_SIZE-1);
    segment_t  *current_segment = table->dir[h >> SEGMENT_SIZE_SHIFT];
    assert(current_segment != NULL);
    segment_t   q               = current_segment[segment_index];

    /* Follow collision chain */
    MANGLEP(cmp_fun) cmp = table->cmp;
    while (q && !EQUAL(cmp, q, key, size)) {
        q = q->chain;
    }

    if (!q && (action != MANGLE(_,_find))) { /* not found, insert */
        assert(!table->iter_tail && "insert an element into a set that is iterated");

        if (table->free_list) {
            q                = table->free_list;
            table->free_list = q->chain;
        } else {
            q = OALLOC(&table->obst, element_t);
        }
        q->entry.dptr = (void *)key;
        q->chain                       = current_segment[segment_index];
        q->entry.hash                  = hash;
        current_segment[segment_index] = q;

        if (loaded(table)) {
            /* does not affect q */
            expand_table(table);
        }
    }

    if (!q)
        return NULL;
    if (action == _pset_hinsert)
        return &q->entry;
    return q->entry.dptr;
}


