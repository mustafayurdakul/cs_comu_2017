#include <stdio.h>
#include <stdlib.h>

struct node {
    int number;
    struct node *left;
    struct node *right;
};

struct binary_search_tree {
    struct node *root;
};

void create_binary_search_tree(struct binary_search_tree **tree) {
    *tree = (struct binary_search_tree *) malloc(sizeof(struct binary_search_tree));
    if (*tree == NULL) {
        printf("We can't allocate space in heap for binary search tree.\n");
        exit(1);
    }
    (*tree)->root = NULL;
}

int is_it_empty(struct binary_search_tree *tree) {
    if (tree->root == NULL) {
        return 1;
    } else {
        return 0;
    }
}

struct node *create_node(int number) {
    struct node *a = (struct node *) malloc(sizeof(struct node));
    if (a == NULL) {
        printf("We can't allocate space in heap for binary search tree.\n");
        exit(1);
    }
    a->number = number;
    a->left = NULL;
    a->right = NULL;
}

void add(struct binary_search_tree *tree, int number) {
    struct node *a = create_node(number);
    struct node *root = tree->root;
    struct node *back = NULL;

    while (root != NULL) {
        back = root;
        if (number < root->number) {
            root = root->left;
        } else if (number > root->number) {
            root = root->right;
        } else {
            return;
        }
    }

    if (tree->root == NULL) {
        tree->root = a;
    } else if (number < back->number) {
        back->left = a;
    } else if (number > back->number) {
        back->right = a;
    }
}

void inorder_h(struct node *root) {
    if (root == NULL) {
        return;
    }
    inorder_h(root->left);
    printf("%d   ", root->number);
    inorder_h(root->right);
}

void inorder(struct binary_search_tree *tree) {
    printf("Inorder: ");
    if (tree == NULL) {
        return;
    }
    inorder_h(tree->root);
    printf("\n");
}

void preorder_h(struct node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d   ", root->number);
    preorder_h(root->left);
    preorder_h(root->right);
}

void preorder(struct binary_search_tree *tree) {
    printf("Preorder: ");
    if (tree == NULL) {
        return;
    }
    preorder_h(tree->root);
    printf("\n");

}

void postorder_h(struct node *root) {
    if (root == NULL) {
        return;
    }
    postorder_h(root->left);
    postorder_h(root->right);
    printf("%d   ", root->number);
}

void postorder(struct binary_search_tree *tree) {
    printf("Postorder: ");
    if (tree == NULL) {
        return;
    }
    postorder_h(tree->root);
    printf("\n");
}

int node_counter(struct node *root) {

    if (root == NULL) {
        return 0;
    } else {
        return 1 + node_counter(root->left) + node_counter(root->right);
    }
}

int node_counter_not_leaf(struct node *root) {
    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return 0;
    } else {
        return 1 + node_counter_not_leaf(root->left) + node_counter_not_leaf(root->right);
    }
}

int leaf_counter(struct node *root) {

    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return 1;
    } else {
        return leaf_counter(root->left) + leaf_counter(root->right);
    }
}

void delete(struct binary_search_tree *tree, int number) {
    struct node *root = tree->root;
    struct node *parent = NULL;
    struct node *d1, *d2;
    int left = 0;
    while (root != NULL) {
        if (number < root->number) {
            parent = root;
            root = root->left;
            left = 1;
        } else if (number > root->number) {
            parent = root;
            root = root->right;
            left = 0;
        } else {
            break;
        }
    }
    if (root == NULL) {                         //Düğüm boş ise.
        return;
    } else if (root->left == NULL) {            //Silinen düğümün solu boş ise.
        if (parent == NULL) {
            return;
        } else {
            if (left == 1) {
                parent->left = root->right;
            } else {
                parent->right = root->right;
            }
        }
    } else if (root->right == NULL) {           //Silinen düğümün sağı boş ise.
        if (parent == NULL) {
            return;
        } else {
            if (left == 1) {
                parent->left = root->left;
            } else {
                parent->right = root->left;
            }
        }
    } else {                                    //Silinen düğümün her iki tarafı da dolu ise.
        d1 = root->right;
        d2 = NULL;
        while (d1->left == NULL) {              //Silinen düğümün sağının en soluna git.
            d2 = d1;                            //En sondaki düğüm silinen düğümün konumunu alır.
            d1 = d1->left;
        }
        if (d2 != NULL) {
            d2->left = d1->right;
            d1->right = root->right;
        }

        d1->left = root->right;
        if (parent == NULL) {
            tree->root = d1;
        } else {
            if (left == 1) {
                parent->left = d1;
            } else {
                parent->right = d1;
            }
        }
    }
}

void erase_binary_search_tree(struct node **root) {
    if (root != NULL) {
        erase_binary_search_tree(&(*root)->left);
        erase_binary_search_tree(&(*root)->right);
        free(*root);
    }
}

int main() {
    struct binary_search_tree *tree = NULL;
    create_binary_search_tree(&tree);
    add(tree, 200);
    add(tree, 25);
    add(tree, 75);
    add(tree, 20);
    add(tree, 35);
    add(tree, 98);
    add(tree, 99);
    add(tree, 500);
    add(tree, 400);
    add(tree, 300);
    add(tree, 210);
    add(tree, 375);
    add(tree, 30);
    add(tree, 173);
    erase_binary_search_tree(&tree->root);
    inorder(tree);
    preorder(tree);
    postorder(tree);
    printf("Node Counter Not Leafs: %d\n", node_counter_not_leaf(tree->root));
    printf("Leaf Counter: %d\n", leaf_counter(tree->root));

}
