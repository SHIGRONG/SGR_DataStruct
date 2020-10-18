//
//  test04.c
//  test
//
//  Created by sgr on 2020/9/26.
//  Copyright © 2020 lzb. All rights reserved.
//
//题目：http://cslibrary.stanford.edu/110/BinaryTrees.html
#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct node
{
    Data data;
    struct node * left;
    struct node * right;
}node;

node* newNode(Data data)
{
    node* p = malloc(sizeof(node));
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//使用递归方法
node * insert(node * root,Data data)
{
    if(root == NULL)
    {
        return newNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }else
    {
        root->right = insert(root->right, data);
    }
    return root;
}


//使用循环方法

/*
node * insert01(node* root,Data data)
{
    node* p = root;
    if(root == NULL)
    {
        root = newNode(data);
        return root;
    }
    
    
    while (p)
    {
        if(data < p->data)
        {
            if(p->left == NULL)
            {
                p->left = newNode(data);
                break;
            }
            
            p = p->left;
        }
        else
        {
            if(p->right == NULL)
            {
                p->right = newNode(data);
                break;
            }
            
            p = p->right;
        }
            
    }
    
    return root;
}
*/

node * insert01(node* root,Data data)
{
    node* p = root,*p2 = p;
    if(p == NULL)
    {
        p = newNode(data);
        return p;
    }
    
    
    while (p)
    {
        p2 = p;
        if(data < p->data)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
            
    }
    
    if(data < p2->data)
    {
        p2->left = newNode(data);
    }
    else
    {
        p2->right = newNode(data);
    }
    
    return root;
}


struct node* build123b()
{
    node * root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);
    return root;
}

struct node* build123c()
{
    node * root = NULL;
    insert(root, 2);
    insert(root, 1);
    insert(root, 3);
    return root;
}


/* ************************************************ */

int size(node * root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    return size(root->left)+size(root->right)+1;
}
/*
int size02(node * root)
{
    if (root == NULL)
    {
        return 0;
    }
    return size(root->left)+size(root->right)+1;
}
 */
/* ************************************************ */
int maxDepth(node * root)
{
    int l,r;
    if(root == NULL)
        return 0;
    l = maxDepth(root->left);
    r = maxDepth(root->right);
    return l>r ? l+1:r+1;
}
/* ************************************************ */

int minValue(node * root)
{
    while (root->left)
    {
        root = root->left;
    }
    
    return root->data;
}


int maxValue(node *root)
{
    while (root->right) {
        root = root->right;
    }
    
    return root->data;
}
/* ************************************************ */
void printTree(node* root)//左根右
{
    if(root == NULL)
    {
        return;
    }
    printTree(root->left);
    printf("%d   ",root->data);
    printTree(root->right);
}

/* ************************************************ */
void printPostorder(node * root)//左右根
{
    if (root == NULL)
    {
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d  ",root->data);
}
/* ************************************************ */
int hasPathSum(node * root,int sum)
{
    if (root == NULL)
    {
        return sum == 0;
    }
    
    return hasPathSum(root->left,sum - root->data) | hasPathSum(root->right,sum - root->data);
}
/* ************************************************ */
void printPathsRecur(node * root,int* path,int length)
{
    int i;
    if (root == NULL)
    {
        for (i = 0; i < length; i++)
        {
            printf("%d  ",path[i]);
        }
        printf("\n");
    }
    path[length] = root->data;
    printPathsRecur(root->left, path, length+1);
    printPathsRecur(root->right, path, length+1);
}
void printPaths(node *root)
{
    int path[200];
    printPathsRecur(root,path,0);
}
/* ************************************************ */
void mirror(node *root)
{
    node* temp = NULL;
    
    if (root == NULL)
    {
        return;
    }
    mirror(root->left);
    mirror(root->right);
    
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

/* ************************************************ */
void doubleTree(node *root)
{
    node* temp = NULL;
    if (root == NULL)
    {
        return;
    }
    doubleTree(root->left);
    doubleTree(root->right);
    
    
    temp = newNode(root->data);
    temp->left = root->left;
    root->left = temp;
    
}

/* ************************************************ */
int sameTree(node* a,node* b)
{
    if (a == NULL && b == NULL)
    {
        return 1;
    }
    else if(a != NULL && b != NULL)
    {
        return a->data == b->data && sameTree(a->left, b->left) && sameTree(a->right, b->right);
    }
    else
        return 0;
}
/* ************************************************ */

//int countTrees


/* ************************************************ */

int isBST(node* root)
{
    if (root == NULL)
    {
        return 1;
    }
    
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    
    if (root->data > maxValue(root->right) && root->data < minValue(root->left))
    {
        return isBST(root->left) && isBST(root->right);
    }
    
    else
    {
      return 0;
    }
}

/* ************************************************ */

int isBSTRecur(node* root, int min, int max)
{
    if (root == NULL)
    {
        return 1;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    
    if (root->left->data < min && root->right->data > max)
    {
        return isBSTRecur(root->left, root->left->data, max) && isBSTRecur(root->right, min, root->right->data);
    }
    
    return 0;
}

int isBST02(node* root)
{
    return isBSTRecur(root, root->data, root->data);
}

/* ************************************************ */

node * append(node *a,node *b)
{
    if (a == NULL)
    {
        return b;
    }
    if (b == NULL)
    {
        return a;
    }
    
    b->left = a;
    b->right = a->right;
    a->right->left = b;
    a->right = b;
    
    return a;
}


node * treeToList(node * root)
{
    node* right,*left;
    if (root == NULL)
    {
        return NULL;
    }
    right = treeToList(root->left);
    left = treeToList(root->right);
    
    root->left = root;
    root->right = root;
    
    right = append(right, root);
    right = append(right, left);
    
    return right;
}

/* ************************************************ */
