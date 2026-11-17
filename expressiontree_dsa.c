#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int top=-1;

char postfix[100];
struct Node{
    char w;
    struct Node* left;
    struct Node* right;
};

struct Node* stack[100];  // Stack is designed to contain nodes. So each element of stack contains a pointer to a node.

struct Node* pop(){
    struct Node* node=stack[top--];
    return node;
}

struct Node* push(char w,struct Node* lchild,struct Node* rchild){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->w=w;    // Here we don't use strcpy because we are only storing a single character. strcpy is used for strings, not single characters
    newNode->left=lchild;
    newNode->right=rchild;
    stack[++top]=newNode;
    return newNode;

}
void expressiontree(){    
    int i=0;   
    while (postfix[i]!='\0'){
        char c=postfix[i];
        switch (c){
            case '+':
            case '-':
            case '/':
            case '*':    // We do cases like this for operators because that way we can use a single left and right child definition. So the way it works is the below statements execute regardless of which operator is entered. The only condition for exeuction of those statements is that it has to be an operator.
                struct Node* rchild=pop();
                struct Node* lchild=pop();
                struct Node* new=push(c,lchild,rchild);
                break;
            default:
                struct Node* blank=push(c,NULL,NULL);
                break;

        }
        i=i+1;
    }
}

void preorder(struct Node* root){   // Used for displaying prefix
    if (root==NULL){
        return;
    }
    printf("%c",root->w);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node* root){   // Used for displaying infix
    if (root==NULL){
        return;
    }
    inorder(root->left);
    printf("%c",root->w);
    inorder(root->right);
}


int main(){
    printf("Enter postfix expression: ");
    fgets(postfix,100,stdin);
    postfix[strcspn(postfix,"\n")]='\0';
    printf("Expression you have entered is ");
    printf("%s",postfix);
    printf("\n");
    expressiontree();
    printf("Expression has been converted to expression tree \n");
    printf("Expression converted to prefix is: ");
    preorder(stack[top]);
    printf("\n");
    printf("Expression converted to infix is: ");
    inorder(stack[top]);
}

/* Read algorithm to understand but if you have any doubts but essentially whenever we read an operand, we create a node for it.
Whenever we read an operator, we pop two nodes from the stack and we create a new node with the operator.
The first node that gets popped will be right child of new node and the other node will be left child of new node.
Push the new node back onto the stack.
This process repeats until the final operator is read
At which point there will be only one element in the stack which will be pointer to root of the whole tree.
eg:

Symbol read	    Operation	                                                        Stack (bottom → top)
A	            Create node A and push	                                            A
B	            Create node B and push	                                            A, B
C	            Create node C and push	                                            A, B, C
*	            Pop C (right), B (left child).    Create * and push	                A, *
+	            Pop * (right child), A (left child).    Create + and push           +

Btw when we say stack contains A, what it actually means is the stack contains a pointer to node containing A and not A itself.

For example, when you push A, we
1. Create a node containing A using malloc().
2. Store the address of that node in the stack.
*/
