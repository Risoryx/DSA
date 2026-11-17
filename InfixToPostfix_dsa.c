#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
char infix[100];
char postfix[100];
int top=-1;

void push(char c){
    if (top<99){
        stack[++top]=c;
    }
    else{
        printf("Stack overflow \n");
    }
}

char pop(){
    if (top==-1){
        printf("Stack underflow \n");
    }
    else{
    char item=stack[top--];
    return item;}
}

char peek(){
    if (top==-1){
        printf("Nothing in stack \n");
    }
    else{
    char item;
    item=stack[top];
    return item;
    }
}

int precedence(char op){
    switch(op){
        case '+':
            return 1;
        case '-':
            return 1;
        case '/':
            return 2;
        case '*':
            return 2;
        default:
            return 0;
    }
}

void InfixtoPostfix(){
    int i=0,j=0;
    char c;
    while (infix[i]!='\0'){
        c=infix[i];
        if (!isspace(c)){
            switch(c){
                case '(':
                    push(c);
                    break;
                case ')':
                    while (top!=-1 && peek()!='('){                     // It pops everything and adds it to postfix until it encounters '('. We do not want to add '(' to postfix
                        postfix[j++]=pop();
                        }
                    if (top!=-1){
                    pop();                                             // Used to pop '('. We do not want to add it to postfix so we simply pop it.
                    }                                                    
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    while (top!=-1 && precedence(stack[top])>=precedence(c)){
                        postfix[j++]=pop();
                    }
                    push(c);
                    break;
                default:
                    postfix[j++]=c;
                    break;
            }
        }
        i++;
    }
    while (top!=-1){
        postfix[j++]=pop();
    }
    postfix[j]='\0';                             // Adds '\0' at end of postfix string. Without '\0', functions like printf("%s", postfix) wouldn't know where the string ends. They might continue reading beyond the actual expression.
}

int main(){
    printf("Enter infix expression: ");
    fgets(infix,100,stdin);
    infix[strcspn(infix,"\n")]='\0';
    InfixtoPostfix();
    printf("Postfix expression is %s \n",postfix);
}