// Generated by Oberon+ IDE (Mono) 0.9.106 on 2024-07-13T01:26:30

#include "som.RedBlackTree.80265c2f3b.h"
#include "CD.h"

void som$RedBlackTree$80265c2f3b$InsertResult$init$(struct som$RedBlackTree$80265c2f3b$InsertResult* inst){
    inst->class$ = &som$RedBlackTree$80265c2f3b$InsertResult$class$;
    CD$Vector3D$init$((struct CD$Vector3D*)&inst->oldValue);
}
void som$RedBlackTree$80265c2f3b$Node$init$(struct som$RedBlackTree$80265c2f3b$Node* inst){
    inst->class$ = &som$RedBlackTree$80265c2f3b$Node$class$;
    CD$CallSign$init$((struct CD$CallSign*)&inst->key);
    CD$Vector3D$init$((struct CD$Vector3D*)&inst->value);
}
void som$RedBlackTree$80265c2f3b$Entry$init$(struct som$RedBlackTree$80265c2f3b$Entry* inst){
    inst->class$ = &som$RedBlackTree$80265c2f3b$Entry$class$;
    CD$CallSign$init$((struct CD$CallSign*)&inst->key);
    CD$Vector3D$init$((struct CD$Vector3D*)&inst->value);
}
void som$RedBlackTree$80265c2f3b$RedBlackTree$init$(struct som$RedBlackTree$80265c2f3b$RedBlackTree* inst){
    inst->class$ = &som$RedBlackTree$80265c2f3b$RedBlackTree$class$;
}
struct som$RedBlackTree$80265c2f3b$Node * som$RedBlackTree$80265c2f3b$createNode(struct CD$CallSign * key, struct CD$Vector3D * value) {
    struct som$RedBlackTree$80265c2f3b$Node * n;
    struct som$RedBlackTree$80265c2f3b$Node * $t0;
    n = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$80265c2f3b$Node));
    memset($t0,0,sizeof(struct som$RedBlackTree$80265c2f3b$Node));
    n = $t0;
    som$RedBlackTree$80265c2f3b$Node$init$($t0);
    (*(struct CD$CallSign *)&(*n).key) = (*(struct CD$CallSign *)&(*key));
    (*(struct CD$Vector3D *)&(*n).value) = (*(struct CD$Vector3D *)&(*value));
    (*n).color = 0;
    return n;
}

struct som$RedBlackTree$80265c2f3b$Node * som$RedBlackTree$80265c2f3b$treeMinimum(struct som$RedBlackTree$80265c2f3b$Node * x) {
    struct som$RedBlackTree$80265c2f3b$Node * current;
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

struct som$RedBlackTree$80265c2f3b$Node * som$RedBlackTree$80265c2f3b$Node$successor(void* this) {
    struct som$RedBlackTree$80265c2f3b$Node* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * x;
    struct som$RedBlackTree$80265c2f3b$Node * y;
    x = 0;
    y = 0;
    x = this$;
    if( ((void*)(*x).right != (void*)0) ) {
        return som$RedBlackTree$80265c2f3b$treeMinimum((*x).right);
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

struct som$RedBlackTree$80265c2f3b$RedBlackTree * som$RedBlackTree$80265c2f3b$create(int32_t (*func)(struct CD$CallSign *, struct CD$CallSign *)) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree * t;
    struct som$RedBlackTree$80265c2f3b$RedBlackTree * $t0;
    t = 0;
    $t0 = OBX$Alloc(sizeof(struct som$RedBlackTree$80265c2f3b$RedBlackTree));
    memset($t0,0,sizeof(struct som$RedBlackTree$80265c2f3b$RedBlackTree));
    t = $t0;
    som$RedBlackTree$80265c2f3b$RedBlackTree$init$($t0);
    assert(((void*)func != (void*)0));
    (*t).compare = func;
    return t;
}

struct CD$Vector3D som$RedBlackTree$80265c2f3b$RedBlackTree$put(void* this, struct CD$CallSign * key, struct CD$Vector3D * value) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    uint8_t newEntry;
    void* $t0;
    struct CD$Vector3D (* $t1)(void*, struct CD$CallSign *, struct CD$Vector3D *, uint8_t *);
    newEntry = 0;
    return ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->putChecked, $t1($t0, &(*(struct CD$CallSign *)&(*key)), &(*(struct CD$Vector3D *)&(*value)), &newEntry));
}

struct CD$Vector3D som$RedBlackTree$80265c2f3b$RedBlackTree$putChecked(void* this, struct CD$CallSign * key, struct CD$Vector3D * value, uint8_t * newEntry) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$InsertResult insertionResult;
    struct som$RedBlackTree$80265c2f3b$Node * x;
    struct som$RedBlackTree$80265c2f3b$Node * y;
    void* $t0;
    void (* $t1)(void*, struct CD$CallSign *, struct CD$Vector3D *, struct som$RedBlackTree$80265c2f3b$InsertResult *);
    void (* $t2)(void*, struct som$RedBlackTree$80265c2f3b$Node *);
    struct CD$Vector3D * $t3;
    memset(&insertionResult,0,sizeof(insertionResult));
    som$RedBlackTree$80265c2f3b$InsertResult$init$(&insertionResult);
    x = 0;
    y = 0;
    ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->treeInsert, $t1($t0, &(*(struct CD$CallSign *)&(*key)), &(*(struct CD$Vector3D *)&(*value)), &insertionResult));
    if( (!insertionResult.isNewEntry) ) {
        (*newEntry) = 0;
        return (*(struct CD$Vector3D *)&insertionResult.oldValue);
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
                        ($t2 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, (*(*x).parent).parent));
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
                        ($t2 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t2($t0, x));
                    } 
                    (*(*x).parent).color = 1;
                    (*(*(*x).parent).parent).color = 0;
                    ($t2 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t2($t0, (*(*x).parent).parent));
                }
            }
        } else {
            break;
        }
    }
    (*(*this$).root).color = 1;
    (*newEntry) = 1;
    return ($t3= &(struct CD$Vector3D){0}, $t3->class$ = &CD$Vector3D$class$, *$t3);
}

struct CD$Vector3D som$RedBlackTree$80265c2f3b$RedBlackTree$remove(void* this, struct CD$CallSign * key) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * x;
    struct som$RedBlackTree$80265c2f3b$Node * y;
    struct som$RedBlackTree$80265c2f3b$Node * z;
    struct som$RedBlackTree$80265c2f3b$Node * xParent;
    void* $t0;
    struct som$RedBlackTree$80265c2f3b$Node * (* $t1)(void*, struct CD$CallSign *);
    struct CD$Vector3D * $t2;
    struct som$RedBlackTree$80265c2f3b$Node * (* $t3)(void*);
    void (* $t4)(void*, struct som$RedBlackTree$80265c2f3b$Node *, struct som$RedBlackTree$80265c2f3b$Node *);
    x = 0;
    y = 0;
    z = 0;
    xParent = 0;
    z = ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*(struct CD$CallSign *)&(*key))));
    if( ((void*)z == (void*)0) ) {
        return ($t2= &(struct CD$Vector3D){0}, $t2->class$ = &CD$Vector3D$class$, *$t2);
    } 
    if( (((void*)(*z).left == (void*)0) || ((void*)(*z).right == (void*)0)) ) {
        y = z;
    } else {
        y = ($t3 = ((struct som$RedBlackTree$80265c2f3b$Node *)($t0 = &(*z)))->class$->successor, $t3($t0));
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
            ($t4 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t4($t0, x, xParent));
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
        ($t4 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->removeFixup, $t4($t0, x, xParent));
    } 
    return (*(struct CD$Vector3D *)&(*z).value);
}

struct CD$Vector3D som$RedBlackTree$80265c2f3b$RedBlackTree$get(void* this, struct CD$CallSign * key) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * node;
    void* $t0;
    struct som$RedBlackTree$80265c2f3b$Node * (* $t1)(void*, struct CD$CallSign *);
    struct CD$Vector3D * $t2;
    node = 0;
    node = ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->findNode, $t1($t0, &(*(struct CD$CallSign *)&(*key))));
    if( ((void*)node == (void*)0) ) {
        return ($t2= &(struct CD$Vector3D){0}, $t2->class$ = &CD$Vector3D$class$, *$t2);
    } 
    return (*(struct CD$Vector3D *)&(*node).value);
}

void som$RedBlackTree$80265c2f3b$RedBlackTree$forEach(void* this, struct som$Interfaces$b3330a6a65$ForEachInterface * fn) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * current;
    struct som$RedBlackTree$80265c2f3b$Entry e;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$80265c2f3b$Entry *);
    struct som$RedBlackTree$80265c2f3b$Node * (* $t2)(void*);
    current = 0;
    memset(&e,0,sizeof(e));
    som$RedBlackTree$80265c2f3b$Entry$init$(&e);
    if( ((void*)(*this$).root == (void*)0) ) {
        return ;
    } 
    current = som$RedBlackTree$80265c2f3b$treeMinimum((*this$).root);
    while(1) {
        if( ((void*)current != (void*)0) ) {
            (*(struct CD$CallSign *)&e.key) = (*(struct CD$CallSign *)&(*current).key);
            (*(struct CD$Vector3D *)&e.value) = (*(struct CD$Vector3D *)&(*current).value);
            ($t1 = ((struct som$Interfaces$b3330a6a65$ForEachInterface *)($t0 = &(*fn)))->class$->apply, $t1($t0, &e));
            current = ($t2 = ((struct som$RedBlackTree$80265c2f3b$Node *)($t0 = &(*current)))->class$->successor, $t2($t0));
        } else {
            break;
        }
    }
}

struct som$RedBlackTree$80265c2f3b$Node * som$RedBlackTree$80265c2f3b$RedBlackTree$findNode(void* this, struct CD$CallSign * key) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * current;
    int32_t comparisonResult;
    current = 0;
    comparisonResult = 0;
    current = (*this$).root;
    while(1) {
        if( ((void*)current != (void*)0) ) {
            comparisonResult = (*this$).compare(&(*(struct CD$CallSign *)&(*key)), &(*(struct CD$CallSign *)&(*current).key));
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

void som$RedBlackTree$80265c2f3b$RedBlackTree$treeInsert(void* this, struct CD$CallSign * key, struct CD$Vector3D * value, struct som$RedBlackTree$80265c2f3b$InsertResult * res) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * x;
    struct som$RedBlackTree$80265c2f3b$Node * y;
    struct som$RedBlackTree$80265c2f3b$Node * z;
    int32_t comparisonResult;
    x = 0;
    y = 0;
    z = 0;
    comparisonResult = 0;
    x = (*this$).root;
    while(1) {
        if( ((void*)x != (void*)0) ) {
            y = x;
            comparisonResult = (*this$).compare(&(*(struct CD$CallSign *)&(*key)), &(*(struct CD$CallSign *)&(*x).key));
            if( (comparisonResult < 0) ) {
                x = (*x).left;
            } else if( (comparisonResult > 0) ) {
                x = (*x).right;
            } else {
                (*res).isNewEntry = 0;
                (*(struct CD$Vector3D *)&(*res).oldValue) = (*(struct CD$Vector3D *)&(*x).value);
                (*(struct CD$Vector3D *)&(*x).value) = (*(struct CD$Vector3D *)&(*value));
                return ;
            }
        } else {
            break;
        }
    }
    z = som$RedBlackTree$80265c2f3b$createNode(&(*(struct CD$CallSign *)&(*key)), &(*(struct CD$Vector3D *)&(*value)));
    (*z).parent = y;
    if( ((void*)y == (void*)0) ) {
        (*this$).root = z;
    } else {
        if( ((*this$).compare(&(*(struct CD$CallSign *)&(*key)), &(*(struct CD$CallSign *)&(*y).key)) < 0) ) {
            (*y).left = z;
        } else {
            (*y).right = z;
        }
    }
    (*res).isNewEntry = 1;
    (*res).newNode = z;
}

void som$RedBlackTree$80265c2f3b$RedBlackTree$leftRotate(void* this, struct som$RedBlackTree$80265c2f3b$Node * x) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * y;
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

void som$RedBlackTree$80265c2f3b$RedBlackTree$rightRotate(void* this, struct som$RedBlackTree$80265c2f3b$Node * y) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * x;
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

void som$RedBlackTree$80265c2f3b$RedBlackTree$removeFixup(void* this, struct som$RedBlackTree$80265c2f3b$Node * x, struct som$RedBlackTree$80265c2f3b$Node * xParent) {
    struct som$RedBlackTree$80265c2f3b$RedBlackTree* this$ = this;
    struct som$RedBlackTree$80265c2f3b$Node * w;
    void* $t0;
    void (* $t1)(void*, struct som$RedBlackTree$80265c2f3b$Node *);
    w = 0;
    while(1) {
        if( (((void*)x != (void*)(*this$).root) && (((void*)x == (void*)0) || ((*x).color == 1))) ) {
            if( ((void*)x == (void*)(*xParent).left) ) {
                w = (*xParent).right;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
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
                        ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, w));
                        w = (*xParent).right;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).right != (void*)0) ) {
                        (*(*w).right).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, xParent));
                    x = (*this$).root;
                    xParent = (*x).parent;
                }
            } else {
                w = (*xParent).left;
                if( ((*w).color == 0) ) {
                    (*w).color = 1;
                    (*xParent).color = 0;
                    ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
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
                        ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->leftRotate, $t1($t0, w));
                        w = (*xParent).left;
                    } 
                    (*w).color = (*xParent).color;
                    (*xParent).color = 1;
                    if( ((void*)(*w).left != (void*)0) ) {
                        (*(*w).left).color = 1;
                    } 
                    ($t1 = ((struct som$RedBlackTree$80265c2f3b$RedBlackTree *)($t0 = &(*this$)))->class$->rightRotate, $t1($t0, xParent));
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

struct som$RedBlackTree$80265c2f3b$InsertResult$Class$ som$RedBlackTree$80265c2f3b$InsertResult$class$ = { 
    0,
};

struct som$RedBlackTree$80265c2f3b$Node$Class$ som$RedBlackTree$80265c2f3b$Node$class$ = { 
    0,
    som$RedBlackTree$80265c2f3b$Node$successor,
};

struct som$RedBlackTree$80265c2f3b$Entry$Class$ som$RedBlackTree$80265c2f3b$Entry$class$ = { 
    0,
};

struct som$RedBlackTree$80265c2f3b$RedBlackTree$Class$ som$RedBlackTree$80265c2f3b$RedBlackTree$class$ = { 
    0,
    som$RedBlackTree$80265c2f3b$RedBlackTree$put,
    som$RedBlackTree$80265c2f3b$RedBlackTree$putChecked,
    som$RedBlackTree$80265c2f3b$RedBlackTree$remove,
    som$RedBlackTree$80265c2f3b$RedBlackTree$get,
    som$RedBlackTree$80265c2f3b$RedBlackTree$forEach,
    som$RedBlackTree$80265c2f3b$RedBlackTree$findNode,
    som$RedBlackTree$80265c2f3b$RedBlackTree$treeInsert,
    som$RedBlackTree$80265c2f3b$RedBlackTree$leftRotate,
    som$RedBlackTree$80265c2f3b$RedBlackTree$rightRotate,
    som$RedBlackTree$80265c2f3b$RedBlackTree$removeFixup,
};

static int initDone$ = 0;
void som$RedBlackTree$80265c2f3b$init$(void) {
    if(initDone$) return; else initDone$ = 1;
    som$Interfaces$b3330a6a65$init$();
}
OBX$Cmd som$RedBlackTree$80265c2f3b$cmd$(const char* name) {
    if( name == 0 ) return som$RedBlackTree$80265c2f3b$init$;
    return 0;
}
