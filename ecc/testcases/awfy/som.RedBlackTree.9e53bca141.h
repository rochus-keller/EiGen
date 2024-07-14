#ifndef _SOM$REDBLACKTREE$9E53BCA141_
#define _SOM$REDBLACKTREE$9E53BCA141_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.d3c230b1e1.h"

// Declaration of module som.RedBlackTree(CD2.Vector2D,BOOLEAN)

struct CD2$Vector2D; // meta actual
struct som$RedBlackTree$9e53bca141$InsertResult$Class$;
struct som$RedBlackTree$9e53bca141$InsertResult;
struct som$RedBlackTree$9e53bca141$Entry$Class$;
struct som$RedBlackTree$9e53bca141$Entry;
struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$;
struct som$RedBlackTree$9e53bca141$RedBlackTree;
struct som$RedBlackTree$9e53bca141$Node$Class$;
struct som$RedBlackTree$9e53bca141$Node;
struct som$RedBlackTree$9e53bca141$InsertResult {
    struct som$RedBlackTree$9e53bca141$InsertResult$Class$* class$;
    uint8_t isNewEntry;
    struct som$RedBlackTree$9e53bca141$Node * newNode;
    uint8_t oldValue;
};

extern void som$RedBlackTree$9e53bca141$InsertResult$init$(struct som$RedBlackTree$9e53bca141$InsertResult*);
struct som$RedBlackTree$9e53bca141$Entry {
    struct som$RedBlackTree$9e53bca141$Entry$Class$* class$;
    struct CD2$Vector2D * key;
    uint8_t value;
};

extern void som$RedBlackTree$9e53bca141$Entry$init$(struct som$RedBlackTree$9e53bca141$Entry*);
struct som$RedBlackTree$9e53bca141$RedBlackTree {
    struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$* class$;
    struct som$RedBlackTree$9e53bca141$Node * root;
    int32_t (*compare)(struct CD2$Vector2D * *, struct CD2$Vector2D * *);
};

extern void som$RedBlackTree$9e53bca141$RedBlackTree$init$(struct som$RedBlackTree$9e53bca141$RedBlackTree*);
struct som$RedBlackTree$9e53bca141$Node {
    struct som$RedBlackTree$9e53bca141$Node$Class$* class$;
    struct CD2$Vector2D * key;
    uint8_t value;
    struct som$RedBlackTree$9e53bca141$Node * left;
    struct som$RedBlackTree$9e53bca141$Node * right;
    struct som$RedBlackTree$9e53bca141$Node * parent;
    int color;
};

extern void som$RedBlackTree$9e53bca141$Node$init$(struct som$RedBlackTree$9e53bca141$Node*);
struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$createNode(struct CD2$Vector2D * * key, uint8_t * value);
struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$treeMinimum(struct som$RedBlackTree$9e53bca141$Node * x);
struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$Node$successor(void* this);
struct som$RedBlackTree$9e53bca141$RedBlackTree * som$RedBlackTree$9e53bca141$create(int32_t (*func)(struct CD2$Vector2D * *, struct CD2$Vector2D * *));
uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$put(void* this, struct CD2$Vector2D * * key, uint8_t * value);
uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$putChecked(void* this, struct CD2$Vector2D * * key, uint8_t * value, uint8_t * newEntry);
uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$remove(void* this, struct CD2$Vector2D * * key);
uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$get(void* this, struct CD2$Vector2D * * key);
void som$RedBlackTree$9e53bca141$RedBlackTree$forEach(void* this, struct som$Interfaces$d3c230b1e1$ForEachInterface * fn);
struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$RedBlackTree$findNode(void* this, struct CD2$Vector2D * * key);
void som$RedBlackTree$9e53bca141$RedBlackTree$treeInsert(void* this, struct CD2$Vector2D * * key, uint8_t * value, struct som$RedBlackTree$9e53bca141$InsertResult * res);
void som$RedBlackTree$9e53bca141$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$9e53bca141$Node * x);
void som$RedBlackTree$9e53bca141$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$9e53bca141$Node * y);
void som$RedBlackTree$9e53bca141$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$9e53bca141$Node * x, struct som$RedBlackTree$9e53bca141$Node * xParent);
struct som$RedBlackTree$9e53bca141$InsertResult$Class$ {
    struct som$RedBlackTree$9e53bca141$InsertResult$Class$* super$;
};
extern struct som$RedBlackTree$9e53bca141$InsertResult$Class$ som$RedBlackTree$9e53bca141$InsertResult$class$;

struct som$RedBlackTree$9e53bca141$Entry$Class$ {
    struct som$RedBlackTree$9e53bca141$Entry$Class$* super$;
};
extern struct som$RedBlackTree$9e53bca141$Entry$Class$ som$RedBlackTree$9e53bca141$Entry$class$;

struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$ {
    struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$* super$;
    uint8_t (*put)(void* this, struct CD2$Vector2D * * key, uint8_t * value);
    uint8_t (*putChecked)(void* this, struct CD2$Vector2D * * key, uint8_t * value, uint8_t * newEntry);
    uint8_t (*remove)(void* this, struct CD2$Vector2D * * key);
    uint8_t (*get)(void* this, struct CD2$Vector2D * * key);
    void (*forEach)(void* this, struct som$Interfaces$d3c230b1e1$ForEachInterface * fn);
    struct som$RedBlackTree$9e53bca141$Node * (*findNode)(void* this, struct CD2$Vector2D * * key);
    void (*treeInsert)(void* this, struct CD2$Vector2D * * key, uint8_t * value, struct som$RedBlackTree$9e53bca141$InsertResult * res);
    void (*leftRotate)(void* this, struct som$RedBlackTree$9e53bca141$Node * x);
    void (*rightRotate)(void* this, struct som$RedBlackTree$9e53bca141$Node * y);
    void (*removeFixup)(void* this, struct som$RedBlackTree$9e53bca141$Node * x, struct som$RedBlackTree$9e53bca141$Node * xParent);
};
extern struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$ som$RedBlackTree$9e53bca141$RedBlackTree$class$;

struct som$RedBlackTree$9e53bca141$Node$Class$ {
    struct som$RedBlackTree$9e53bca141$Node$Class$* super$;
    struct som$RedBlackTree$9e53bca141$Node * (*successor)(void* this);
};
extern struct som$RedBlackTree$9e53bca141$Node$Class$ som$RedBlackTree$9e53bca141$Node$class$;

extern void som$RedBlackTree$9e53bca141$init$(void);
extern OBX$Cmd som$RedBlackTree$9e53bca141$cmd$(const char* name);
#endif
