#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} B_Tree;

B_Tree* new_node(int item) {
    B_Tree* node = (B_Tree*)malloc(sizeof(B_Tree));
    if (node == NULL) {
        exit(1);
    }
    node->key = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

B_Tree* insert(B_Tree* node, int key) {
    if (node == NULL)
        return new_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

bool compare_trees(B_Tree* tree1, B_Tree* tree2) {
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;

    return compare_trees(tree1->left, tree2->left) && compare_trees(tree1->right, tree2->right);
}

short count_unicue(B_Tree* trees[], int n) {
    int count = 0;
    bool is_unique[n];

    for (int i = 0; i < n; i++) {
        is_unique[i] = true;
        for (int j = 0; j < i; j++) {
            if (compare_trees(trees[i], trees[j])) {
                is_unique[i] = false;
                break;
            }
        }
        if (is_unique[i])
            count++;
    }

    return count;
}

void free_tree(B_Tree* node) {
    if (node == NULL)
        return;

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}
int main(int argc, char** argv) {
    int n, k;
    scanf("%d %d", &n, &k);
    B_Tree* trees[n];
    int val;
    for (int i = 0; i < n; i++) {
        trees[i] = NULL;
        for (int j = 0; j < k; j++) {
            scanf("%d", &val);
            trees[i] = insert(trees[i], val);
        }
    }
    int unique = count_unicue(trees, n);
    printf("%d\n", unique);

    for (int i = 0; i < n; i++) {
        free_tree(trees[i]);
    }

    return 0;
}
