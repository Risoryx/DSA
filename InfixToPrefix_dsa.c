#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
char infix[100];
char postfix[100];
char prefix[100];
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

void InfixtoPostfix(char w[]){
    int i=0,j=0;
    char c;
    while (w[i]!='\0'){
        c=w[i];
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

void InfixToPrefix(){
    char rev[100];                              // We reverse the infix expression while also flipping parentheses and then find postfix of that reversed expression. Taking reverse of that postfix gives us the infix expression.
    int j=0;
    int len=strlen(infix);
    for (int i=len-1;i>=0;i--){
        if (infix[i]=='('){
            rev[j]=')';
            j++;
        }
        else if (infix[i]==')'){
            rev[j]='(';
            j++;
        }
        else{
            rev[j]=infix[i];
            j++;
        }
    }
    rev[j]='\0';
    InfixtoPostfix(rev);          // Now in InfixToPostfix expression,j=0 so that means it essentially clears postfix array elements along the way and sets new null character at the end. It is upto the null character that printf and so on read.
    len=strlen(postfix);
    j=0;
    for (int i=len-1;i>=0;i--){
        prefix[j]=postfix[i];
        j++;
    }
    prefix[j]='\0';



}

int main(){
    printf("Enter infix expression: ");
    fgets(infix,100,stdin);
    infix[strcspn(infix,"\n")]='\0';
    InfixtoPostfix(infix);
    printf("Postfix expression is %s \n",postfix);
    top=-1;                                              // Don't do int top=-1 because that will just make a new local variable top. We need to edit the global variable top.
    //postfix[0]='\0'; also essentially clears the array but we don't really need to do this because of the j=0 in the InfixToPostfix function
    InfixToPrefix();
    printf("Prefix expression is %s \n",prefix);


}