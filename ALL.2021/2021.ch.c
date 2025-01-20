# include<stdio.h>
# include <stdlib.h>
struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node * newNode(int item)
{
    struct Node *temp =  (struct Node *)malloc(sizeof(struct Node));
    temp->data = item;
    temp->left =  NULL;
    temp->right = NULL;
    return temp;
}
void print(int p[], int level, int t){
    int i;
    for(i=t;i<=level;i++){
        printf("\n%d",p[i]);
    }
}
void check_paths_with_given_sum(struct Node * root, int da, int path[100], int level){

     if(root == NULL)
        return ;
    path[level]=root->data;
    int i;int temp=0;
    for(i=level;i>=0;i--){
        temp=temp+path[i];
        if(temp==da){
            print(path,level,i);
        }
    }
        check_paths_with_given_sum(root->left, da, path,level+1);
        check_paths_with_given_sum(root->right, da, path,level+1);

}
int main(){
    int par[100];
 struct Node *root = newNode(10);
    root->left = newNode(2);
    root->right = newNode(4);
    root->left->left = newNode(1);
    root->right->right = newNode(5);
    check_paths_with_given_sum(root, 9, par,0);


}
