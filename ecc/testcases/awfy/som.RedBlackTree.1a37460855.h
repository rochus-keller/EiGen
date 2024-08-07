#ifndef _SOM$REDBLACKTREE$1A37460855_
#define _SOM$REDBLACKTREE$1A37460855_

// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "OBX.Runtime.h"
#include "som.Interfaces.57f847cd33.h"

// Declaration of module som.RedBlackTree(CD2.CallSign,CD2.Vector3D)

struct CD2$CallSign; // meta actual
struct CD2$Vector3D; // meta actual
struct som$RedBlackTree$1a37460855$Entry$Class$;
struct som$RedBlackTree$1a37460855$Entry;
struct som$RedBlackTree$1a37460855$InsertResult$Class$;
struct som$RedBlackTree$1a37460855$InsertResult;
struct som$RedBlackTree$1a37460855$Node$Class$;
struct som$RedBlackTree$1a37460855$Node;
struct som$RedBlackTree$1a37460855$RedBlackTree$Class$;
struct som$RedBlackTree$1a37460855$RedBlackTree;
struct som$RedBlackTree$1a37460855$Entry {
    struct som$RedBlackTree$1a37460855$Entry$Class$* class$;
    struct CD2$CallSign * key;
    struct CD2$Vector3D * value;
};

extern void som$RedBlackTree$1a37460855$Entry$init$(struct som$RedBlackTree$1a37460855$Entry*);
struct som$RedBlackTree$1a37460855$InsertResult {
    struct som$RedBlackTree$1a37460855$InsertResult$Class$* class$;
    uint8_t isNewEntry;
    struct som$RedBlackTree$1a37460855$Node * newNode;
    struct CD2$Vector3D * oldValue;
};

extern void som$RedBlackTree$1a37460855$InsertResult$init$(struct som$RedBlackTree$1a37460855$InsertResult*);
struct som$RedBlackTree$1a37460855$Node {
    struct som$RedBlackTree$1a37460855$Node$Class$* class$;
    struct CD2$CallSign * key;
    struct CD2$Vector3D * value;
    struct som$RedBlackTree$1a37460855$Node * left;
    struct som$RedBlackTree$1a37460855$Node * right;
    struct som$RedBlackTree$1a37460855$Node * parent;
    int color;
};

extern void som$RedBlackTree$1a37460855$Node$init$(struct som$RedBlackTree$1a37460855$Node*);
struct som$RedBlackTree$1a37460855$RedBlackTree {
    struct som$RedBlackTree$1a37460855$RedBlackTree$Class$* class$;
    struct som$RedBlackTree$1a37460855$Node * root;
    int32_t (*compare)(struct CD2$CallSign * *, struct CD2$CallSign * *);
};

extern void som$RedBlackTree$1a37460855$RedBlackTree$init$(struct som$RedBlackTree$1a37460855$RedBlackTree*);
struct som$RedBlackTree$1a37460855$Node * som$RedBlackTree$1a37460855$createNode(struct CD2$CallSign * * key, struct CD2$Vector3D * * value);
struct som$RedBlackTree$1a37460855$Node * som$RedBlackTree$1a37460855$treeMinimum(struct som$RedBlackTree$1a37460855$Node * x);
struct som$RedBlackTree$1a37460855$Node * som$RedBlackTree$1a37460855$Node$successor(void* this);
struct som$RedBlackTree$1a37460855$RedBlackTree * som$RedBlackTree$1a37460855$create(int32_t (*func)(struct CD2$CallSign * *, struct CD2$CallSign * *));
struct CD2$Vector3D * som$RedBlackTree$1a37460855$RedBlackTree$put(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value);
struct CD2$Vector3D * som$RedBlackTree$1a37460855$RedBlackTree$putChecked(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value, uint8_t * newEntry);
struct CD2$Vector3D * som$RedBlackTree$1a37460855$RedBlackTree$remove(void* this, struct CD2$CallSign * * key);
struct CD2$Vector3D * som$RedBlackTree$1a37460855$RedBlackTree$get(void* this, struct CD2$CallSign * * key);
void som$RedBlackTree$1a37460855$RedBlackTree$forEach(void* this, struct som$Interfaces$57f847cd33$ForEachInterface * fn);
struct som$RedBlackTree$1a37460855$Node * som$RedBlackTree$1a37460855$RedBlackTree$findNode(void* this, struct CD2$CallSign * * key);
void som$RedBlackTree$1a37460855$RedBlackTree$treeInsert(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value, struct som$RedBlackTree$1a37460855$InsertResult * res);
void som$RedBlackTree$1a37460855$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$1a37460855$Node * x);
void som$RedBlackTree$1a37460855$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$1a37460855$Node * y);
void som$RedBlackTree$1a37460855$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$1a37460855$Node * x, struct som$RedBlackTree$1a37460855$Node * xParent);
struct som$RedBlackTree$1a37460855$Entry$Class$ {
    struct som$RedBlackTree$1a37460855$Entry$Class$* super$;
};
extern struct som$RedBlackTree$1a37460855$Entry$Class$ som$RedBlackTree$1a37460855$Entry$class$;

struct som$RedBlackTree$1a37460855$InsertResult$Class$ {
    struct som$RedBlackTree$1a37460855$InsertResult$Class$* super$;
};
extern struct som$RedBlackTree$1a37460855$InsertResult$Class$ som$RedBlackTree$1a37460855$InsertResult$class$;

struct som$RedBlackTree$1a37460855$Node$Class$ {
    struct som$RedBlackTree$1a37460855$Node$Class$* super$;
    struct som$RedBlackTree$1a37460855$Node * (*successor)(void* this);
};
extern struct som$RedBlackTree$1a37460855$Node$Class$ som$RedBlackTree$1a37460855$Node$class$;

struct som$RedBlackTree$1a37460855$RedBlackTree$Class$ {
    struct som$RedBlackTree$1a37460855$RedBlackTree$Class$* super$;
    struct CD2$Vector3D * (*put)(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value);
    struct CD2$Vector3D * (*putChecked)(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value, uint8_t * newEntry);
    struct CD2$Vector3D * (*remove)(void* this, struct CD2$CallSign * * key);
    struct CD2$Vector3D * (*get)(void* this, struct CD2$CallSign * * key);
    void (*forEach)(void* this, struct som$Interfaces$57f847cd33$ForEachInterface * fn);
    struct som$RedBlackTree$1a37460855$Node * (*findNode)(void* this, struct CD2$CallSign * * key);
    void (*treeInsert)(void* this, struct CD2$CallSign * * key, struct CD2$Vector3D * * value, struct som$RedBlackTree$1a37460855$InsertResult * res);
    void (*leftRotate)(void* this, struct som$RedBlackTree$1a37460855$Node * x);
    void (*rightRotate)(void* this, struct som$RedBlackTree$1a37460855$Node * y);
    void (*removeFixup)(void* this, struct som$RedBlackTree$1a37460855$Node * x, struct som$RedBlackTree$1a37460855$Node * xParent);
};
extern struct som$RedBlackTree$1a37460855$RedBlackTree$Class$ som$RedBlackTree$1a37460855$RedBlackTree$class$;

extern void som$RedBlackTree$1a37460855$init$(void);
extern OBX$Cmd som$RedBlackTree$1a37460855$cmd$(const char* name);
#endif
