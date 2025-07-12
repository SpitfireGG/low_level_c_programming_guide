#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
} TREENODE;

TREENODE *CreateTree(int data)
{
    TREENODE *new_tree_node = malloc(sizeof(TREENODE));
    if (new_tree_node == NULL)
    {
        printf("%s\n", "Unable to create a new node");
        exit(1);
    }

    new_tree_node->left  = NULL;
    new_tree_node->right = NULL;
    new_tree_node->data  = data;
    return new_tree_node;
}

void print_tree(TREENODE *root, int level)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("    ");  // indentation 4 spaces
    }
    printf("-> %d\n", root->data);

    print_tree(root->left, level + 1);
}

void free_alloc(TREENODE *trn)
{
    if (trn == NULL)
    {
        return;
    }
    free_alloc(trn->left);
    free_alloc(trn->right);
    free(trn);
}

int main(void)
{
    TREENODE *tn1 = CreateTree(10);
    TREENODE *tn2 = CreateTree(11);
    TREENODE *tn3 = CreateTree(12);
    TREENODE *tn4 = CreateTree(13);
    TREENODE *tn5 = CreateTree(14);
    TREENODE *tn6 = CreateTree(15);
    TREENODE *tn7 = CreateTree(16);

    tn1->left  = tn2;
    tn1->right = tn3;
    tn2->left  = tn4;
    tn2->right = tn5;
    tn3->left  = tn6;
    tn3->right = tn7;

    printf("Tree traverse:\n\n");

    print_tree(tn1, 0);

    printf("\n");

    free_alloc(tn1);
    printf("Tree memory freed.\n");

    return 0;
}
