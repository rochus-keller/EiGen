#ifndef _SOM$REDBLACKTREE$14446907C4_
#define _SOM$REDBLACKTREE$14446907C4_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.d1517c3aa3.h"

// Declaration of module som.RedBlackTree(CD.Vector2D,som.Vector(CD.Motion).Vector)

struct CD$Vector2D;
struct CD$Vector2D; // meta actual
struct som$Vector$e0832c0c14$Vector; // meta actual
struct som$RedBlackTree$14446907c4$InsertResult$Class$;
struct som$RedBlackTree$14446907c4$InsertResult;
struct som$RedBlackTree$14446907c4$Node$Class$;
struct som$RedBlackTree$14446907c4$Node;
struct som$RedBlackTree$14446907c4$RedBlackTree$Class$;
struct som$RedBlackTree$14446907c4$RedBlackTree;
struct som$RedBlackTree$14446907c4$Entry$Class$;
struct som$RedBlackTree$14446907c4$Entry;
struct som$RedBlackTree$14446907c4$InsertResult {
    struct som$RedBlackTree$14446907c4$InsertResult$Class$* class$;
    uint8_t isNewEntry;
    struct som$RedBlackTree$14446907c4$Node * newNode;
    struct som$Vector$e0832c0c14$Vector * oldValue;
};

extern void som$RedBlackTree$14446907c4$InsertResult$init$(struct som$RedBlackTree$14446907c4$InsertResult*);
struct som$RedBlackTree$14446907c4$Node {
    struct som$RedBlackTree$14446907c4$Node$Class$* class$;
    struct /*CD$Vector2D*/ { void* class$; double x; double y; } key;
    struct som$Vector$e0832c0c14$Vector * value;
    struct som$RedBlackTree$14446907c4$Node * left;
    struct som$RedBlackTree$14446907c4$Node * right;
    struct som$RedBlackTree$14446907c4$Node * parent;
    int color;
};

extern void som$RedBlackTree$14446907c4$Node$init$(struct som$RedBlackTree$14446907c4$Node*);
struct som$RedBlackTree$14446907c4$RedBlackTree {
    struct som$RedBlackTree$14446907c4$RedBlackTree$Class$* class$;
    struct som$RedBlackTree$14446907c4$Node * root;
    int32_t (*compare)(struct CD$Vector2D *, struct CD$Vector2D *);
};

extern void som$RedBlackTree$14446907c4$RedBlackTree$init$(struct som$RedBlackTree$14446907c4$RedBlackTree*);
struct som$RedBlackTree$14446907c4$Entry {
    struct som$RedBlackTree$14446907c4$Entry$Class$* class$;
    struct /*CD$Vector2D*/ { void* class$; double x; double y; } key;
    struct som$Vector$e0832c0c14$Vector * value;
};

extern void som$RedBlackTree$14446907c4$Entry$init$(struct som$RedBlackTree$14446907c4$Entry*);
struct som$RedBlackTree$14446907c4$Node * som$RedBlackTree$14446907c4$createNode(struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value);
struct som$RedBlackTree$14446907c4$Node * som$RedBlackTree$14446907c4$treeMinimum(struct som$RedBlackTree$14446907c4$Node * x);
struct som$RedBlackTree$14446907c4$Node * som$RedBlackTree$14446907c4$Node$successor(void* this);
struct som$RedBlackTree$14446907c4$RedBlackTree * som$RedBlackTree$14446907c4$create(int32_t (*func)(struct CD$Vector2D *, struct CD$Vector2D *));
struct som$Vector$e0832c0c14$Vector * som$RedBlackTree$14446907c4$RedBlackTree$put(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value);
struct som$Vector$e0832c0c14$Vector * som$RedBlackTree$14446907c4$RedBlackTree$putChecked(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value, uint8_t * newEntry);
struct som$Vector$e0832c0c14$Vector * som$RedBlackTree$14446907c4$RedBlackTree$remove(void* this, struct CD$Vector2D * key);
struct som$Vector$e0832c0c14$Vector * som$RedBlackTree$14446907c4$RedBlackTree$get(void* this, struct CD$Vector2D * key);
void som$RedBlackTree$14446907c4$RedBlackTree$forEach(void* this, struct som$Interfaces$d1517c3aa3$ForEachInterface * fn);
struct som$RedBlackTree$14446907c4$Node * som$RedBlackTree$14446907c4$RedBlackTree$findNode(void* this, struct CD$Vector2D * key);
void som$RedBlackTree$14446907c4$RedBlackTree$treeInsert(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value, struct som$RedBlackTree$14446907c4$InsertResult * res);
void som$RedBlackTree$14446907c4$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$14446907c4$Node * x);
void som$RedBlackTree$14446907c4$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$14446907c4$Node * y);
void som$RedBlackTree$14446907c4$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$14446907c4$Node * x, struct som$RedBlackTree$14446907c4$Node * xParent);
struct som$RedBlackTree$14446907c4$InsertResult$Class$ {
    struct som$RedBlackTree$14446907c4$InsertResult$Class$* super$;
};
extern struct som$RedBlackTree$14446907c4$InsertResult$Class$ som$RedBlackTree$14446907c4$InsertResult$class$;

struct som$RedBlackTree$14446907c4$Node$Class$ {
    struct som$RedBlackTree$14446907c4$Node$Class$* super$;
    struct som$RedBlackTree$14446907c4$Node * (*successor)(void* this);
};
extern struct som$RedBlackTree$14446907c4$Node$Class$ som$RedBlackTree$14446907c4$Node$class$;

struct som$RedBlackTree$14446907c4$RedBlackTree$Class$ {
    struct som$RedBlackTree$14446907c4$RedBlackTree$Class$* super$;
    struct som$Vector$e0832c0c14$Vector * (*put)(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value);
    struct som$Vector$e0832c0c14$Vector * (*putChecked)(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value, uint8_t * newEntry);
    struct som$Vector$e0832c0c14$Vector * (*remove)(void* this, struct CD$Vector2D * key);
    struct som$Vector$e0832c0c14$Vector * (*get)(void* this, struct CD$Vector2D * key);
    void (*forEach)(void* this, struct som$Interfaces$d1517c3aa3$ForEachInterface * fn);
    struct som$RedBlackTree$14446907c4$Node * (*findNode)(void* this, struct CD$Vector2D * key);
    void (*treeInsert)(void* this, struct CD$Vector2D * key, struct som$Vector$e0832c0c14$Vector * * value, struct som$RedBlackTree$14446907c4$InsertResult * res);
    void (*leftRotate)(void* this, struct som$RedBlackTree$14446907c4$Node * x);
    void (*rightRotate)(void* this, struct som$RedBlackTree$14446907c4$Node * y);
    void (*removeFixup)(void* this, struct som$RedBlackTree$14446907c4$Node * x, struct som$RedBlackTree$14446907c4$Node * xParent);
};
extern struct som$RedBlackTree$14446907c4$RedBlackTree$Class$ som$RedBlackTree$14446907c4$RedBlackTree$class$;

struct som$RedBlackTree$14446907c4$Entry$Class$ {
    struct som$RedBlackTree$14446907c4$Entry$Class$* super$;
};
extern struct som$RedBlackTree$14446907c4$Entry$Class$ som$RedBlackTree$14446907c4$Entry$class$;

extern void som$RedBlackTree$14446907c4$init$(void);
extern OBX$Cmd som$RedBlackTree$14446907c4$cmd$(const char* name);
#endif
