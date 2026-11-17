#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char word[50];
    struct Node* next;
};

struct Node* createNode(struct Node* root,char w[]){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word,w);
    newNode->next=NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root,char w[]){
    if (root==NULL){
        root=createNode(root,w);

    }
    else{
        struct Node* temp=root;
        while (temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=createNode(root,w);
    }
    return root;
}


struct Node* findAndReplace(struct Node* root,char w1[],char w2[]){
    struct Node* temp=root;
    int c;
    while (temp!=NULL){                                         // while(temp->next!=NULL) would be wrong because that way it wouldn't let us access last node
        c=strcmp(temp->word,w1);
        if (c==0){
            strcpy(temp->word,w2);
            printf("Word was successfully replaced \n");
            break;
        }
        temp=temp->next;
    }
    if (temp==NULL){
        printf("Word was not found \n");
    }
    return root;
} 


void display(struct Node* root){
    struct Node* temp=root;
    while (temp!=NULL){
        printf("%s ",temp->word);
        temp=temp->next;
    }
    printf(" \n");
}

int main(){
    printf("Enter sentence: ");
    char sentence[100];
    fgets(sentence,100,stdin);
    sentence[strcspn(sentence,"\n")]='\0';     // strcspn will effectively return index of \n character, and using array indexing we modify it to replace it with null character. So instead of 'hello\n\0', it becomes 'hello\0'.
    char* tok;              //strtok returns a char pointer
    tok=strtok(sentence," ");
    struct Node* sen=NULL;    //   
    while (tok!=NULL){
        sen=insertNode(sen,tok);
        tok=strtok(NULL," ");
    }
    do{
        printf("1. Display sentence \n");
        printf("2. Replace Word \n");
        printf("3.Exit \n");
        int choice;
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();                     // We do this so \n gets removed from buffer because if it were in buffer and we do fgets, fgets would immediately with it storing just \n(newline).
        switch(choice){
            case 1:
                display(sen);
                break;
            case 2:
                printf("Enter word to find: ");
                char w1[100];
                fgets(w1,100,stdin);
                w1[strcspn(w1,"\n")]='\0';                // The \n needs to be in double quotes and not single quotes. Refer to bottom if you want to learn why.
                printf("Enter word to replace it with: ");
                char w2[100];
                fgets(w2,100,stdin);
                w2[strcspn(w2,"\n")]='\0';
                sen=findAndReplace(sen,w1,w2);
                break;
            case 3:
                printf("Program was successfully terminated \n");
                return 0;
            default:
                printf("Invaild choice \n");
                break;
        }
    }
    while (1);

}


/* char *strtok(char *str, const char *delim);
str: The string you want to split.
delim: The delimiter(s) used to split the string.
Return value: A char * pointing to the next token.
Returns NULL when there are no more tokens.
char str[] = "Hello World C Programming";

char *token = strtok(str, " ");
strtok() searches for the first space.
Replaces that space with '\0'.
Returns a pointer to the beginning of "Hello".
Conceptually, the original string becomes: Hello\0World C Programming

The next call: token = strtok(NULL, " ");
Tells strtok() to continue from where it previously stopped.
It remembers its position internally.

char *token = strtok(str, " ");
printf("%s", token);

You don't need to dereference it using *token when printing a string.
Why?
- token points to the first character of the token.
- %s expects a pointer to a character array.
- So you pass token directly.

The end condition is when strtok() returns NULL
eg:
char str[] = "Apple,Orange,Banana";

char *token = strtok(str, ",");

while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ",");
}

A token is a sequence of characters between delimiters.

strtok() considers there to be no more tokens when it has searched the remaining string and cannot find another non-empty sequence of characters separated by the specified delimiters.

But how does it know?

strtok() internally remembers where it stopped in the original string.

When it reaches the terminating '\0' of the original string, it knows there are no more characters to tokenize, so it returns NULL.

You don't have to define this condition yourself. strtok() handles it internally.

Btw, this NULL is different from Null character '\0'.
*/

// Single quotes ' ' represent a single character. Double quotes " " represent a string (a character array terminated by '\0'). Keep this in mind



