// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.RedBlackTree.9e53bca141.h"
#include "CD2.h"

void som$RedBlackTree$9e53bca141$InsertResult$init$(struct som$RedBlackTree$9e53bca141$InsertResult* inst){
    inst->class$ = &som$RedBlackTree$9e53bca141$InsertResult$class$;
}
void som$RedBlackTree$9e53bca141$Entry$init$(struct som$RedBlackTree$9e53bca141$Entry* inst){
    inst->class$ = &som$RedBlackTree$9e53bca141$Entry$class$;
}
void som$RedBlackTree$9e53bca141$RedBlackTree$init$(struct som$RedBlackTree$9e53bca141$RedBlackTree* inst){
    inst->class$ = &som$RedBlackTree$9e53bca141$RedBlackTree$class$;
}
void som$RedBlackTree$9e53bca141$Node$init$(struct som$RedBlackTree$9e53bca141$Node* inst){
    inst->class$ = &som$RedBlackTree$9e53bca141$Node$class$;
}
struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$createNode(struct CD2$Vector2D * * key, uint8_t * value) {
    struct som$RedBlackTree$9e53bca141$Node * n;
    struct som$RedBlackTree$9e53bca141$Node * $t0;
    n = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$9e53bca141$Node));
    memset($t0,0,sizeof(struct som$RedBlackTree$9e53bca141$Node));
    n = $t0;
    som$RedBlackTree$9e53bca141$Node$init$($t0);
    (*n).key = (*key);
    (*n).value = (*value);
    (*n).color = 0;
    return n;
}

struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$treeMinimum(struct som$RedBlackTree$9e53bca141$Node * x) {
    struct som$RedBlackTree$9e53bca141$Node * current;
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

struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$Node$successor(void* this) {
    struct som$RedBlackTree$9e53bca141$Node* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * x;
    struct som$RedBlackTree$9e53bca141$Node * y;
    x = 0;
    y = 0;
    x = this$;
    if( ((void*)(*x).right != (void*)0) ) {
        return som$RedBlackTree$9e53bca141$treeMinimum((*x).right);
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

struct som$RedBlackTree$9e53bca141$RedBlackTree * som$RedBlackTree$9e53bca141$create(int32_t (*func)(struct CD2$Vector2D * *, struct CD2$Vector2D * *)) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree * t;
    struct som$RedBlackTree$9e53bca141$RedBlackTree * $t0;
    t = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$9e53bca141$RedBlackTree));
    memset($t0,0,sizeof(struct som$RedBlackTree$9e53bca141$RedBlackTree));
    t = $t0;
    som$RedBlackTree$9e53bca141$RedBlackTree$init$($t0);
    assert(((void*)func != (void*)0));
    (*t).compare = func;
    return t;
}

uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$put(void* this, struct CD2$Vector2D * * key, uint8_t * value) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    uint8_t newEntry;
    void* $t0;
    uint8_t (* $t1)(void*, struct CD2$Vector2D * *, uint8_t *, uint8_t *);
    newEntry = 0;
    return ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->putChecked, $t1($t0, &(*key), &(*value), &newEntry));
}

uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$putChecked(void* this, struct CD2$Vector2D * * key, uint8_t * value, uint8_t * newEntry) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$InsertResult insertionResult;
    struct som$RedBlackTree$9e53bca141$Node * x;
    struct som$RedBlackTree$9e53bca141$Node * y;
    void* $t0;
    void (* $t1)(void*, struct CD2$Vector2D * *, uint8_t *, struct som$RedBlackTree$9e53bca141$InsertResult *);
    void (* $t2)(void*, struct som$RedBlackTree$9e53bca141$Node *);
    memset(&insertionResult,0,sizeof(insertionResult));
    som$RedBlackTree$9e53bca141$InsertResult$init$(&insertionResult);
    x = 0;
    y = 0;
    ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->treeInsert, $t1($t0, &(*key), &(*value), &insertionResult));
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
                        ($t2 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, (*(*x).parent).parent));
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
                        ($t2 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, (*(*x).parent).parent));
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

uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$remove(void* this, struct CD2$Vector2D * * key) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * x;
    struct som$RedBlackTree$9e53bca141$Node * y;
    struct som$RedBlackTree$9e53bca141$Node * z;
    struct som$RedBlackTree$9e53bca141$Node * xParent;
    void* $t0;
    struct som$RedBlackTree$9e53bca141$Node * (* $t1)(void*, struct CD2$Vector2D * *);
    struct som$RedBlackTree$9e53bca141$Node * (* $t2)(void*);
    void (* $t3)(void*, struct som$RedBlackTree$9e53bca141$Node *, struct som$RedBlackTree$9e53bca141$Node *);
    x = 0;
    y = 0;
    z = 0;
    xParent = 0;
    z = ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*key)));
    if( ((void*)z == (void*)0) ) {
        return 0;
    } 
    if( (((void*)(*z).left == (void*)0) || ((void*)(*z).right == (void*)0)) ) {
        y = z;
    } else {
        y = ($t2 = ((struct som$RedBlackTree$9e53bca141$Node *)($t0 = &(*z)))->class$->successor, $t2($t0));
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
            ($t3 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t3($t0, x, xParent));
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
        ($t3 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t3($t0, x, xParent));
    } 
    return (*z).value;
}

uint8_t som$RedBlackTree$9e53bca141$RedBlackTree$get(void* this, struct CD2$Vector2D * * key) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * node;
    void* $t0;
    struct som$RedBlackTree$9e53bca141$Node * (* $t1)(void*, struct CD2$Vector2D * *);
    node = 0;
    node = ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*key)));
    if( ((void*)node == (void*)0) ) {
        return 0;
    } 
    return (*node).value;
}

void som$RedBlackTree$9e53bca141$RedBlackTree$forEach(void* this, struct som$Interfaces$d3c230b1e1$ForEachInterface * fn) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * current;
    struct som$RedBlackTree$9e53bca141$Entry e;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$9e53bca141$Entry *);
    struct som$RedBlackTree$9e53bca141$Node * (* $t2)(void*);
    current = 0;
    memset(&e,0,sizeof(e));
    som$RedBlackTree$9e53bca141$Entry$init$(&e);
    if( ((void*)(*this$).root == (void*)0) ) {
        return ;
    } 
    current = som$RedBlackTree$9e53bca141$treeMinimum((*this$).root);
    while(1) {
        if( ((void*)current != (void*)0) ) {
            e.key = (*current).key;
            e.value = (*current).value;
            ($t1 = ((struct som$Interfaces$d3c230b1e1$ForEachInterface *)($t0 = &(*fn)))->class$->apply, $t1($t0, &e));
            current = ($t2 = ((struct som$RedBlackTree$9e53bca141$Node *)($t0 = &(*current)))->class$->successor, $t2($t0));
        } else {
            break;
        }
    }
}

struct som$RedBlackTree$9e53bca141$Node * som$RedBlackTree$9e53bca141$RedBlackTree$findNode(void* this, struct CD2$Vector2D * * key) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * current;
    int32_t comparisonResult;
    current = 0;
    comparisonResult = 0;
    current = (*this$).root;
    while(1) {
        if( ((void*)current != (void*)0) ) {
            comparisonResult = (*this$).compare(&(*key), &(*current).key);
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

void som$RedBlackTree$9e53bca141$RedBlackTree$treeInsert(void* this, struct CD2$Vector2D * * key, uint8_t * value, struct som$RedBlackTree$9e53bca141$InsertResult * res) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * x;
    struct som$RedBlackTree$9e53bca141$Node * y;
    struct som$RedBlackTree$9e53bca141$Node * z;
    int32_t comparisonResult;
    x = 0;
    y = 0;
    z = 0;
    comparisonResult = 0;
    x = (*this$).root;
    while(1) {
        if( ((void*)x != (void*)0) ) {
            y = x;
            comparisonResult = (*this$).compare(&(*key), &(*x).key);
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
    z = som$RedBlackTree$9e53bca141$createNode(&(*key), &(*value));
    (*z).parent = y;
    if( ((void*)y == (void*)0) ) {
        (*this$).root = z;
    } else {
        if( ((*this$).compare(&(*key), &(*y).key) < 0) ) {
            (*y).left = z;
        } else {
            (*y).right = z;
        }
    }
    (*res).isNewEntry = 1;
    (*res).newNode = z;
}

void som$RedBlackTree$9e53bca141$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$9e53bca141$Node * x) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * y;
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

void som$RedBlackTree$9e53bca141$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$9e53bca141$Node * y) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * x;
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

void som$RedBlackTree$9e53bca141$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$9e53bca141$Node * x, struct som$RedBlackTree$9e53bca141$Node * xParent) {
    struct som$RedBlackTree$9e53bca141$RedBlackTree* this$ = this;
    struct som$RedBlackTree$9e53bca141$Node * w;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$9e53bca141$Node *);
    w = 0;
    while(1) {
        if( (((void*)x != (void*)(*this$).root) && (((void*)x == (void*)0) || ((*x).color == 1))) ) {
            if( ((void*)x == (void*)(*xParent).left) ) {
                w = (*xParent).right;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
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
                        ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, w));
                        w = (*xParent).right;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).right != (void*)0) ) {
                        (*(*w).right).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
                    x = (*this$).root;
                    xParent = (*x).parent;
                }
            } else {
                w = (*xParent).left;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
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
                        ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, w));
                        w = (*xParent).left;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).left != (void*)0) ) {
                        (*(*w).left).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$9e53bca141$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
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

struct som$RedBlackTree$9e53bca141$InsertResult$Class$ som$RedBlackTree$9e53bca141$InsertResult$class$ = { 
    0,
};

struct som$RedBlackTree$9e53bca141$Entry$Class$ som$RedBlackTree$9e53bca141$Entry$class$ = { 
    0,
};

struct som$RedBlackTree$9e53bca141$RedBlackTree$Class$ som$RedBlackTree$9e53bca141$RedBlackTree$class$ = { 
    0,
    som$RedBlackTree$9e53bca141$RedBlackTree$put,
    som$RedBlackTree$9e53bca141$RedBlackTree$putChecked,
    som$RedBlackTree$9e53bca141$RedBlackTree$remove,
    som$RedBlackTree$9e53bca141$RedBlackTree$get,
    som$RedBlackTree$9e53bca141$RedBlackTree$forEach,
    som$RedBlackTree$9e53bca141$RedBlackTree$findNode,
    som$RedBlackTree$9e53bca141$RedBlackTree$treeInsert,
    som$RedBlackTree$9e53bca141$RedBlackTree$leftRotate,
    som$RedBlackTree$9e53bca141$RedBlackTree$rightRotate,
    som$RedBlackTree$9e53bca141$RedBlackTree$removeFixup,
};

struct som$RedBlackTree$9e53bca141$Node$Class$ som$RedBlackTree$9e53bca141$Node$class$ = { 
    0,
    som$RedBlackTree$9e53bca141$Node$successor,
};

static int initDone$ = 0;
void som$RedBlackTree$9e53bca141$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Interfaces$d3c230b1e1$init$();
}
OBX$Cmd som$RedBlackTree$9e53bca141$cmd$(const char* name) {
    if( name == 0 ) return som$RedBlackTree$9e53bca141$init$;
    return 0;
}
