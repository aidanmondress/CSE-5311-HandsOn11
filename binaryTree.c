/*
 * binaryTree.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Aidan Mondress
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
} node;

node* makeNode(int data)
{
    node* n = (node*)malloc(sizeof(node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node* insertNode(node* n, int data)
{
    if(n == NULL)
    	return makeNode(data);
    if (data < n->data)
        n->left = insertNode(n->left, data);
    else if (data > n->data)
        n->right = insertNode(n->right, data);
    return n;
}

node* minNode(node* n)
{
    node* i = n;
    while(i && i->left != NULL)
        i = i->left;
    return i;
}

node* removeNode(node* root, int data)
{
    if(root == NULL)
        return root;
    if(data < root->data)
        root->left = removeNode(root->left, data);
    else if(data > root->data)
        root->right = removeNode(root->right, data);
    else
    {
        if(root->left == NULL)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* temp = minNode(root->right);
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }
    return root;
}

void printOrder(node* root)
{
    if (root != NULL)
    {
        printOrder(root->left);
        printf("%d \n", root->data);
        printOrder(root->right);
    }
}

node* search(node* root, int key)
{
    if(root == NULL || root->data == key)
       return root;
    else if(root->data < key)
       return search(root->right, key);
    else if(root->data > key)
           return search(root->left, key);
}

int main()
{
    node* root = NULL;
    root = insertNode(root, 63);
    root = insertNode(root, 21);
    root = insertNode(root, 6);
    root = insertNode(root, 40);
    root = insertNode(root, 91);
    root = insertNode(root, 74);
    root = insertNode(root, 16);
    root = insertNode(root, 19);
    root = insertNode(root, 33);
    root = insertNode(root, 85);

    printf("Full tree traversal: \n");
    printOrder(root);

    root = removeNode(root, 40);
    printf("Full tree traversal (After 40 deletion): \n");
    printOrder(root);

    root = removeNode(root, 63);
    printf("Full tree traversal (After 63 deletion): \n");
    printOrder(root);

    root = removeNode(root, 19);
    printf("Full tree traversal (After 19 deletion): \n");
    printOrder(root);

    int searchVal = 74;
    node* result = search(root, searchVal);
    if (result != NULL)
        printf("\n%d found in the tree!\n", searchVal);
    else
        printf("\n%d NOT found in the tree!\n", searchVal);
    return 0;
}
