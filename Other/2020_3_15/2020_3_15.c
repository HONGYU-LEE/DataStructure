#include<stdio.h>
#include<malloc.h>
typedef char DATATYPE;
typedef struct Tree
{
    DATATYPE data;
    struct Tree* right;
    struct Tree* left;
}Tree;

Tree* treeBulid(char* str, int* i)
{
    if('#' == str[*i])
    {
        ++(*i);
        return NULL;
    }

    
    Tree* node = (Tree*)malloc(sizeof(Tree));
    node->data = str[*i];
    ++(*i);
    
    node->left = treeBulid(str, i);
    node->right = treeBulid(str, i);
    
    return node;
}

Tree* inorderTravel(Tree* root)
{
    if(!root)
        return NULL;
    
    inorderTravel(root->left);
    printf("%c ", root->data);
    inorderTravel(root->right);
}

int main()
{
    char str[100];
    int i = 0;
    scanf("%s", str);
    
    Tree* tree = treeBulid(str, &i);
    inorderTravel(tree);
    return 0;
}
