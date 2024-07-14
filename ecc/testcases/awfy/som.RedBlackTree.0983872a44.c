// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.RedBlackTree.0983872a44.h"
#include "CD.h"
#include "som.Vector.e873043a5e.h"

void som$RedBlackTree$0983872a44$Node$init$(struct som$RedBlackTree$0983872a44$Node* inst){
    inst->class$ = &som$RedBlackTree$0983872a44$Node$class$;
    CD$Vector2D$init$((struct CD$Vector2D*)&inst->key);
}
void som$RedBlackTree$0983872a44$InsertResult$init$(struct som$RedBlackTree$0983872a44$InsertResult* inst){
    inst->class$ = &som$RedBlackTree$0983872a44$InsertResult$class$;
}
void som$RedBlackTree$0983872a44$RedBlackTree$init$(struct som$RedBlackTree$0983872a44$RedBlackTree* inst){
    inst->class$ = &som$RedBlackTree$0983872a44$RedBlackTree$class$;
}
void som$RedBlackTree$0983872a44$Entry$init$(struct som$RedBlackTree$0983872a44$Entry* inst){
    inst->class$ = &som$RedBlackTree$0983872a44$Entry$class$;
    CD$Vector2D$init$((struct CD$Vector2D*)&inst->key);
}
struct som$RedBlackTree$0983872a44$Node * som$RedBlackTree$0983872a44$createNode(struct CD$Vector2D * key, struct som$Vector$e873043a5e$Vector * * value) {
    struct som$RedBlackTree$0983872a44$Node * n;
    struct som$RedBlackTree$0983872a44$Node * $t0;
    n = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$0983872a44$Node));
    memset($t0,0,sizeof(struct som$RedBlackTree$0983872a44$Node));
    n = $t0;
    som$RedBlackTree$0983872a44$Node$init$($t0);
    (*(struct CD$Vector2D *)&(*n).key) = (*(struct CD$Vector2D *)&(*key));
    (*n).value = (*value);
    (*n).color = 0;
    return n;
}

struct som$RedBlackTree$0983872a44$Node * som$RedBlackTree$0983872a44$treeMinimum(struct som$RedBlackTree$0983872a44$Node * x) {
    struct som$RedBlackTree$0983872a44$Node * current;
    current = 0;
    current = x;
    while(1) {
        if( ((void*)(*current).left != (void*)0) ) {
            current = (*current).left;
        } else {
            break;
        }
    }
    return current;
}

struct som$RedBlackTree$0983872a44$Node * som$RedBlackTree$0983872a44$Node$successor(void* this) {
    struct som$RedBlackTree$0983872a44$Node* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * x;
    struct som$RedBlackTree$0983872a44$Node * y;
    x = 0;
    y = 0;
    x = this$;
    if( ((void*)(*x).right != (void*)0) ) {
        return som$RedBlackTree$0983872a44$treeMinimum((*x).right);
    } 
    y = (*x).parent;
    while(1) {
        if( (((void*)y != (void*)0) && ((void*)x == (void*)(*y).right)) ) {
            x = y;
            y = (*y).parent;
        } else {
            break;
        }
    }
    return y;
}

struct som$RedBlackTree$0983872a44$RedBlackTree * som$RedBlackTree$0983872a44$create(int32_t (*func)(struct CD$Vector2D *, struct CD$Vector2D *)) {
    struct som$RedBlackTree$0983872a44$RedBlackTree * t;
    struct som$RedBlackTree$0983872a44$RedBlackTree * $t0;
    t = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$0983872a44$RedBlackTree));
    memset($t0,0,sizeof(struct som$RedBlackTree$0983872a44$RedBlackTree));
    t = $t0;
    som$RedBlackTree$0983872a44$RedBlackTree$init$($t0);
    assert(((void*)func != (void*)0));
    (*t).compare = func;
    return t;
}

struct som$Vector$e873043a5e$Vector * som$RedBlackTree$0983872a44$RedBlackTree$put(void* this, struct CD$Vector2D * key, struct som$Vector$e873043a5e$Vector * * value) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    uint8_t newEntry;
    void* $t0;
    struct som$Vector$e873043a5e$Vector * (* $t1)(void*, struct CD$Vector2D *, struct som$Vector$e873043a5e$Vector * *, uint8_t *);
    newEntry = 0;
    return ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->putChecked, $t1($t0, &(*(struct CD$Vector2D *)&(*key)), &(*value), &newEntry));
}

struct som$Vector$e873043a5e$Vector * som$RedBlackTree$0983872a44$RedBlackTree$putChecked(void* this, struct CD$Vector2D * key, struct som$Vector$e873043a5e$Vector * * value, uint8_t * newEntry) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$InsertResult insertionResult;
    struct som$RedBlackTree$0983872a44$Node * x;
    struct som$RedBlackTree$0983872a44$Node * y;
    void* $t0;
    void (* $t1)(void*, struct CD$Vector2D *, struct som$Vector$e873043a5e$Vector * *, struct som$RedBlackTree$0983872a44$InsertResult *);
    void (* $t2)(void*, struct som$RedBlackTree$0983872a44$Node *);
    memset(&insertionResult,0,sizeof(insertionResult));
    som$RedBlackTree$0983872a44$InsertResult$init$(&insertionResult);
    x = 0;
    y = 0;
    ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->treeInsert, $t1($t0, &(*(struct CD$Vector2D *)&(*key)), &(*value), &insertionResult));
    if( (!insertionResult.isNewEntry) ) {
        (*newEntry) = 0;
        return insertionResult.oldValue;
    } 
    x = insertionResult.newNode;
    while(1) {
        if( (((void*)x != (void*)(*this$).root) && ((*(*x).parent).color == 0)) ) {
            if( ((void*)(*x).parent == (void*)(*(*(*x).parent).parent).left) ) {
                y = (*(*(*x).parent).parent).right;
                if( (((void*)y != (void*)0) && ((*y).color == 0)) ) {
                    (*(*x).parent).color = 1;
                    (*y).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    x = (*(*x).parent).parent;
                } else {
                    if( ((void*)x == (void*)(*(*x).parent).right) ) {
                        x = (*x).parent;
                        ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, (*(*x).parent).parent));
                }
            } else {
                y = (*(*(*x).parent).parent).left;
                if( (((void*)y != (void*)0) && ((*y).color == 0)) ) {
                    (*(*x).parent).color = 1;
                    (*y).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    x = (*(*x).parent).parent;
                } else {
                    if( ((void*)x == (void*)(*(*x).parent).left) ) {
                        x = (*x).parent;
                        ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, (*(*x).parent).parent));
                }
            }
        } else {
            break;
        }
    }
    (*(*this$).root).color = 1;
    (*newEntry) = 1;
    return 0;
}

struct som$Vector$e873043a5e$Vector * som$RedBlackTree$0983872a44$RedBlackTree$remove(void* this, struct CD$Vector2D * key) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * x;
    struct som$RedBlackTree$0983872a44$Node * y;
    struct som$RedBlackTree$0983872a44$Node * z;
    struct som$RedBlackTree$0983872a44$Node * xParent;
    void* $t0;
    struct som$RedBlackTree$0983872a44$Node * (* $t1)(void*, struct CD$Vector2D *);
    struct som$RedBlackTree$0983872a44$Node * (* $t2)(void*);
    void (* $t3)(void*, struct som$RedBlackTree$0983872a44$Node *, struct som$RedBlackTree$0983872a44$Node *);
    x = 0;
    y = 0;
    z = 0;
    xParent = 0;
    z = ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*(struct CD$Vector2D *)&(*key))));
    if( ((void*)z == (void*)0) ) {
        return 0;
    } 
    if( (((void*)(*z).left == (void*)0) || ((void*)(*z).right == (void*)0)) ) {
        y = z;
    } else {
        y = ($t2 = ((struct som$RedBlackTree$0983872a44$Node *)($t0 = &(*z)))->class$->successor, $t2($t0));
    }
    if( ((void*)(*y).left != (void*)0) ) {
        x = (*y).left;
    } else {
        x = (*y).right;
    }
    if( ((void*)x != (void*)0) ) {
        (*x).parent = (*y).parent;
        xParent = (*x).parent;
    } else {
        xParent = (*y).parent;
    }
    if( ((void*)(*y).parent == (void*)0) ) {
        (*this$).root = x;
    } else {
        if( ((void*)y == (void*)(*(*y).parent).left) ) {
            (*(*y).parent).left = x;
        } else {
            (*(*y).parent).right = x;
        }
    }
    if( ((void*)y != (void*)z) ) {
        if( ((*y).color == 1) ) {
            ($t3 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t3($t0, x, xParent));
        } 
        (*y).parent = (*z).parent;
        (*y).color = (*z).color;
        (*y).left = (*z).left;
        (*y).right = (*z).right;
        if( ((void*)(*z).left != (void*)0) ) {
            (*(*z).left).parent = y;
        } 
        if( ((void*)(*z).right != (void*)0) ) {
            (*(*z).right).parent = y;
        } 
        if( ((void*)(*z).parent != (void*)0) ) {
            if( ((void*)(*(*z).parent).left == (void*)z) ) {
                (*(*z).parent).left = y;
            } else {
                (*(*z).parent).right = y;
            }
        } else {
            (*this$).root = y;
        }
    } else if( ((*y).color == 1) ) {
        ($t3 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t3($t0, x, xParent));
    } 
    return (*z).value;
}

struct som$Vector$e873043a5e$Vector * som$RedBlackTree$0983872a44$RedBlackTree$get(void* this, struct CD$Vector2D * key) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * node;
    void* $t0;
    struct som$RedBlackTree$0983872a44$Node * (* $t1)(void*, struct CD$Vector2D *);
    node = 0;
    node = ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*(struct CD$Vector2D *)&(*key))));
    if( ((void*)node == (void*)0) ) {
        return 0;
    } 
    return (*node).value;
}

void som$RedBlackTree$0983872a44$RedBlackTree$forEach(void* this, struct som$Interfaces$6b0df483d0$ForEachInterface * fn) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * current;
    struct som$RedBlackTree$0983872a44$Entry e;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$0983872a44$Entry *);
    struct som$RedBlackTree$0983872a44$Node * (* $t2)(void*);
    current = 0;
    memset(&e,0,sizeof(e));
    som$RedBlackTree$0983872a44$Entry$init$(&e);
    if( ((void*)(*this$).root == (void*)0) ) {
        return ;
    } 
    current = som$RedBlackTree$0983872a44$treeMinimum((*this$).root);
    while(1) {
        if( ((void*)current != (void*)0) ) {
            (*(struct CD$Vector2D *)&e.key) = (*(struct CD$Vector2D *)&(*current).key);
            e.value = (*current).value;
            ($t1 = ((struct som$Interfaces$6b0df483d0$ForEachInterface *)($t0 = &(*fn)))->class$->apply, $t1($t0, &e));
            current = ($t2 = ((struct som$RedBlackTree$0983872a44$Node *)($t0 = &(*current)))->class$->successor, $t2($t0));
        } else {
            break;
        }
    }
}

struct som$RedBlackTree$0983872a44$Node * som$RedBlackTree$0983872a44$RedBlackTree$findNode(void* this, struct CD$Vector2D * key) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * current;
    int32_t comparisonResult;
    current = 0;
    comparisonResult = 0;
    current = (*this$).root;
    while(1) {
        if( ((void*)current != (void*)0) ) {
            comparisonResult = (*this$).compare(&(*(struct CD$Vector2D *)&(*key)), &(*(struct CD$Vector2D *)&(*current).key));
            if( (comparisonResult == 0) ) {
                return current;
            } else if( (comparisonResult < 0) ) {
                current = (*current).left;
            } else {
                current = (*current).right;
            }
        } else {
            break;
        }
    }
    return 0;
}

void som$RedBlackTree$0983872a44$RedBlackTree$treeInsert(void* this, struct CD$Vector2D * key, struct som$Vector$e873043a5e$Vector * * value, struct som$RedBlackTree$0983872a44$InsertResult * res) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * x;
    struct som$RedBlackTree$0983872a44$Node * y;
    struct som$RedBlackTree$0983872a44$Node * z;
    int32_t comparisonResult;
    x = 0;
    y = 0;
    z = 0;
    comparisonResult = 0;
    x = (*this$).root;
    while(1) {
        if( ((void*)x != (void*)0) ) {
            y = x;
            comparisonResult = (*this$).compare(&(*(struct CD$Vector2D *)&(*key)), &(*(struct CD$Vector2D *)&(*x).key));
            if( (comparisonResult < 0) ) {
                x = (*x).left;
            } else if( (comparisonResult > 0) ) {
                x = (*x).right;
            } else {
                (*res).isNewEntry = 0;
                (*res).oldValue = (*x).value;
                (*x).value = (*value);
                return ;
            }
        } else {
            break;
        }
    }
    z = som$RedBlackTree$0983872a44$createNode(&(*(struct CD$Vector2D *)&(*key)), &(*value));
    (*z).parent = y;
    if( ((void*)y == (void*)0) ) {
        (*this$).root = z;
    } else {
        if( ((*this$).compare(&(*(struct CD$Vector2D *)&(*key)), &(*(struct CD$Vector2D *)&(*y).key)) < 0) ) {
            (*y).left = z;
        } else {
            (*y).right = z;
        }
    }
    (*res).isNewEntry = 1;
    (*res).newNode = z;
}

void som$RedBlackTree$0983872a44$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$0983872a44$Node * x) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * y;
    y = 0;
    y = (*x).right;
    (*x).right = (*y).left;
    if( ((void*)(*y).left != (void*)0) ) {
        (*(*y).left).parent = x;
    } 
    (*y).parent = (*x).parent;
    if( ((void*)(*x).parent == (void*)0) ) {
        (*this$).root = y;
    } else {
        if( ((void*)x == (void*)(*(*x).parent).left) ) {
            (*(*x).parent).left = y;
        } else {
            (*(*x).parent).right = y;
        }
    }
    (*y).left = x;
    (*x).parent = y;
}

void som$RedBlackTree$0983872a44$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$0983872a44$Node * y) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * x;
    x = 0;
    x = (*y).left;
    (*y).left = (*x).right;
    if( ((void*)(*x).right != (void*)0) ) {
        (*(*x).right).parent = y;
    } 
    (*x).parent = (*y).parent;
    if( ((void*)(*y).parent == (void*)0) ) {
        (*this$).root = x;
    } else {
        if( ((void*)y == (void*)(*(*y).parent).left) ) {
            (*(*y).parent).left = x;
        } else {
            (*(*y).parent).right = x;
        }
    }
    (*x).right = y;
    (*y).parent = x;
}

void som$RedBlackTree$0983872a44$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$0983872a44$Node * x, struct som$RedBlackTree$0983872a44$Node * xParent) {
    struct som$RedBlackTree$0983872a44$RedBlackTree* this$ = this;
    struct som$RedBlackTree$0983872a44$Node * w;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$0983872a44$Node *);
    w = 0;
    while(1) {
        if( (((void*)x != (void*)(*this$).root) && (((void*)x == (void*)0) || ((*x).color == 1))) ) {
            if( ((void*)x == (void*)(*xParent).left) ) {
                w = (*xParent).right;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
                    w = (*xParent).right;
                } 
                if( ((((void*)(*w).left == (void*)0) || ((*(*w).left).color == 1)) && (((void*)(*w).right == (void*)0) || ((*(*w).right).color == 1))) ) {
                    (*w).color = 0;
                    x = xParent;
                    xParent = (*x).parent;
                } else {
                    if( (((void*)(*w).right == (void*)0) || ((*(*w).right).color == 1)) ) {
                        (*(*w).left).color = 1;
                        (*w).color = 0;
                        ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, w));
                        w = (*xParent).right;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).right != (void*)0) ) {
                        (*(*w).right).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
                    x = (*this$).root;
                    xParent = (*x).parent;
                }
            } else {
                w = (*xParent).left;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
                    w = (*xParent).left;
                } 
                if( ((((void*)(*w).right == (void*)0) || ((*(*w).right).color == 1)) && (((void*)(*w).left == (void*)0) || ((*(*w).left).color == 1))) ) {
                    (*w).color = 0;
                    x = xParent;
                    xParent = (*x).parent;
                } else {
                    if( (((void*)(*w).left == (void*)0) || ((*(*w).left).color == 1)) ) {
                        (*(*w).right).color = 1;
                        (*w).color = 0;
                        ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, w));
                        w = (*xParent).left;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).left != (void*)0) ) {
                        (*(*w).left).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$0983872a44$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
                    x = (*this$).root;
                    xParent = (*x).parent;
                }
            }
        } else {
            break;
        }
    }
    if( ((void*)x != (void*)0) ) {
        (*x).color = 1;
    } 
}

struct som$RedBlackTree$0983872a44$Node$Class$ som$RedBlackTree$0983872a44$Node$class$ = { 
    0,
    som$RedBlackTree$0983872a44$Node$successor,
};

struct som$RedBlackTree$0983872a44$InsertResult$Class$ som$RedBlackTree$0983872a44$InsertResult$class$ = { 
    0,
};

struct som$RedBlackTree$0983872a44$RedBlackTree$Class$ som$RedBlackTree$0983872a44$RedBlackTree$class$ = { 
    0,
    som$RedBlackTree$0983872a44$RedBlackTree$put,
    som$RedBlackTree$0983872a44$RedBlackTree$putChecked,
    som$RedBlackTree$0983872a44$RedBlackTree$remove,
    som$RedBlackTree$0983872a44$RedBlackTree$get,
    som$RedBlackTree$0983872a44$RedBlackTree$forEach,
    som$RedBlackTree$0983872a44$RedBlackTree$findNode,
    som$RedBlackTree$0983872a44$RedBlackTree$treeInsert,
    som$RedBlackTree$0983872a44$RedBlackTree$leftRotate,
    som$RedBlackTree$0983872a44$RedBlackTree$rightRotate,
    som$RedBlackTree$0983872a44$RedBlackTree$removeFixup,
};

struct som$RedBlackTree$0983872a44$Entry$Class$ som$RedBlackTree$0983872a44$Entry$class$ = { 
    0,
};

static int initDone$ = 0;
void som$RedBlackTree$0983872a44$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Interfaces$6b0df483d0$init$();
}
OBX$Cmd som$RedBlackTree$0983872a44$cmd$(const char* name) {
    if( name == 0 ) return som$RedBlackTree$0983872a44$init$;
    return 0;
}
