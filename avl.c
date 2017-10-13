#include<stdio.h>
#include<stdlib.h>
/* Node template */
struct node
{
struct node *left;
int data;
struct node *right;
int height;
};
/* Get a new node */
struct node* get_newnode(int key)
{
struct node *new_node=(struct node *)malloc(sizeof(struct node));
new_node->left=NULL;
new_node->data=key;
new_node->right=NULL;
new_node->height=1;
return new_node;
}
/* Helper function to find height */
int height(struct node* node)
{
if(node==NULL)
return 0;
else
return node->height;
}
/* To return maximum height among the childeren */
int max_height(struct node *left_child,struct node *right_child)
{
return (height(left_child)>height(right_child))?height(left_child):height(right_child);
}
/* Helper Function to perform Left Rotate */
struct node* left_rotate(struct node* curr_node)
{
struct node *new_root=curr_node->right;
struct node *temp=new_root->left;
new_root->left=curr_node;
curr_node->right=temp;
/* Update height */
curr_node->height=1+max_height(curr_node->left,curr_node->right);
return new_root;
}
/*Helper Function to Right node */
struct node* right_rotate(struct node* curr_node)
{
struct node *new_root=curr_node->left;
struct node *temp=new_root->right;
new_root->right=curr_node;
curr_node->left=temp;
/* Update height*/
curr_node->height=max_height(curr_node->left,curr_node->right);
return new_root;
}
/* Node insertion functio */
struct node* insert(struct node* curr_root,int key)
{
signed int balance_factor;
if(curr_root==NULL)
{
return get_newnode(key);
}
/* Insert at Left Child*/
if(key<curr_root->data)
curr_root->left=insert(curr_root->left,key);
/*Insert at Right Child*/
if(key>curr_root->data)
curr_root->right=insert(curr_root->right,key);
/*Update Height*/
curr_root->height=1+max_height(curr_root->left,curr_root->right);
/* Get balance Factor and do balancing */
balance_factor=height(curr_root->left)-height(curr_root->right);
/* Right Right rotate case */
if(balance_factor>1 && key < (curr_root->left)->data)
return right_rotate(curr_root);
/*Left Left rotate case */
if(balance_factor<-1 && key > (curr_root->right)->data)
return left_rotate(curr_root);
/* Left Right rotate */
if(balance_factor>1 && key < (curr_root->left)->data)
{
curr_root->left=left_rotate(curr_root->left);
return right_rotate(curr_root);
}
/* Right Left Rotate */
if(balance_factor<-1 && key > (curr_root->right)->data)
{
curr_root->right=right_rotate(curr_root->right);
return left_rotate(curr_root);
}
return curr_root;
}
/* Pre order traversal */
void preorder(struct node* root)
{
if(root)
{
printf("%d",root->data);
preorder(root->left);
preorder(root->right);
}
}
struct node *root=NULL;
/* Main function */
int main()
{
int element;
while(1)
{
printf("\n Enter the element to be inserted : ");
scanf("%d" ,&element);
root=insert(root,element);
printf( " \n \t PRE ORDERED TREE \n");
preorder(root);
}
}
