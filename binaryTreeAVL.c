/*
 * binaryTreeAVL.c
 *
 *  Created on: Apr 2, 2024
 *      Author: Aidan Mondress
 */

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int h;
    struct node* left;
    struct node* right;
};

struct node* root = NULL;

struct node* makeNode(int data)
{
    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->left = NULL;
    new->right = NULL;
    new->data = data;

    return new;
}

int findHeight(struct node* root)
{
    if(root == NULL)
        return 0;
    int heightL = findHeight(root->left);
    int heightR = findHeight(root->right);

    return(heightL > heightR) ? (heightL + 1) : (heightR + 1);
}

int balanceFactor(struct node* root)
{
    if(root == NULL)
        return 0;
    int heightL = findHeight(root->left);
    int heightR = findHeight(root->right);

    return heightL - heightR;
}

struct node* rotateLeft(struct node* root)
{
    struct node* childR = root->right;
    root->right = childR->left;
    childR->left = root;
    root->h = findHeight(root);
    childR->h = findHeight(childR);

    return childR;
}

struct node* rotateRight(struct node* root)
{
    struct node* childL = root->left;
    root->left = childL->right;
    childL->right = root;
    root->h = findHeight(root);
    childL->h = findHeight(childL);

    return childL;
}

struct node* insertNode(struct node* root, int data)
{
    if(root == NULL)
        return makeNode(data);
    if(data > root->data)
        root->right = insertNode(root->right, data);
    else if(data < root->data)
        root->left = insertNode(root->left, data);
    else if(data == root->data)
        return root;

    root->h = findHeight(root);
    int bf = balanceFactor(root);

    if(data < root->left->data && bf > 1)
        return rotateRight(root);
    if(data > root->right->data && bf < -1)
        return rotateLeft(root);

    if(data > root->left->data && bf > 1)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if(data < root->right->data && bf < -1)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    else
    	return root;
}

struct node* removeNode(struct node* root, int data)
{
    if(root == NULL)
        return root;

    int cmp;
    if(cmp > 0)
    	root->right = removeNode(root->right, data);
    else if((cmp = data - root->data) < 0)
    	root->left = removeNode(root->left, data);
    else
    {
        if(root->left == NULL)
        {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = root->right;
        while(temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = removeNode(root->right, temp->data);
    }

    root->h = findHeight(root);
    int bf = balanceFactor(root);

    if(balanceFactor(root->left) >= 0 && bf > 1)
        return rotateRight(root);
    if(balanceFactor(root->right) <= 0 && bf < -1)
        return rotateLeft(root);

    if(balanceFactor(root->left) < 0 && bf > 1)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if(balanceFactor(root->right) > 0 && bf < -1)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    else
    	return root;
}

struct node* search(struct node* root, int key)
{
    if(root == NULL || key == root->data)
        return root;
    if(key < root->data)
        return search(root->left, key);
    else if(key > root->data)
        return search(root->right, key);
}

void printOrder(struct node* root)
{
    if(root == NULL)
        return;

    printOrder(root->left);
    printf("%d ", root->data);
    printOrder(root->right);
}

int main()
{
    struct node* searchVal;

    root = insertNode(root, 5);
    printf("\nFull tree traversal:\n");
    printOrder(root);
    printf("\n");

    root = insertNode(root, 8);
    printf("\nFull tree traversal:\n");
    printOrder(root);
    printf("\n");

    root = insertNode(root, 19);
    printf("\nFull tree traversal:\n");
    printOrder(root);
    printf("\n");

    root = removeNode(root, 8);
    printf("\nFull tree traversal:\n");
    printOrder(root);
    printf("\n");

    searchVal = search(root, 5);
    if(searchVal == NULL)
        printf("NOT FOUND!\n");
    else
        printf("Data Found.\n");
    return 0;
}
