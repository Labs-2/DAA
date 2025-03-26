#include <stdio.h>
#include <stdlib.h>
struct treenode {
    struct treenode *lchild;
    struct treenode *rchild;
    int weight;
};
struct treenode* least(struct treenode** list, int *size);
void insert(struct treenode** list, struct treenode* new_node, int *size);
struct treenode* TREE(int n, struct treenode** list);
void free_tree(struct treenode* root);

int main() {
    int n;
    printf("Enter the number of trees: ");
    scanf("%d", &n);

    struct treenode* list[n];
    for (int i = 0; i < n; i++) {
        list[i] = (struct treenode*)malloc(sizeof(struct treenode));
        list[i]->lchild = NULL;
        list[i]->rchild = NULL;
        printf("Enter the weight of tree %d: ", i + 1);
        scanf("%d", &list[i]->weight);
    }
    struct treenode* root = TREE(n, list);
    printf("The weight of the root of the merged tree is: %d\n", root->weight);
    free_tree(root);
    return 0;
}
struct treenode* least(struct treenode** list, int *size) {
    int min_index = 0;
    for (int i = 1; i < *size; i++) {
        if (list[i]->weight < list[min_index]->weight) {
            min_index = i;
        }
    }
    struct treenode* least_tree = list[min_index];
    for (int i = min_index; i < *size - 1; i++) {
        list[i] = list[i + 1];
    }
    (*size)--;
    return least_tree;
}
void insert(struct treenode** list, struct treenode* new_node, int *size) {
    int i = *size - 1;
    while (i >= 0 && list[i]->weight > new_node->weight) {
        list[i + 1] = list[i];
        i--;
    }
    list[i + 1] = new_node;
    (*size)++;
}
struct treenode* TREE(int n, struct treenode** list) {
    int size = n;
    for (int i = 1; i < n; i++) {
        struct treenode* pt = (struct treenode*)malloc(sizeof(struct treenode));
        pt->lchild = least(list, &size);
        pt->rchild = least(list, &size);
        pt->weight = pt->lchild->weight + pt->rchild->weight;
        insert(list, pt, &size);
    }
    return list[0];
}
void free_tree(struct treenode* root) {
    if (root != NULL) {
        free_tree(root->lchild);
        free_tree(root->rchild);
        free(root);
    }
}