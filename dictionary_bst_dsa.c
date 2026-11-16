#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node{
    char word[50];
    char meaning[50];
    struct Node* left;
    struct Node* right;

};

struct Node* createNode(char w[],char m[]){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word,w);
    strcpy(newNode->meaning,m);
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root,char w[],char m[]){
    
    if (root==NULL){
        root=createNode(w,m);

    }
    else{
        int c=strcmp(w,root->word);
        if (c==0){
            printf("Word already exists \n");
        }
        else if(c<0){
            root->left=insertNode(root->left,w,m);

        }
        else{
            root->right=insertNode(root->right,w,m);
        }
    }
    return root;   // The prior recursion calls are resolved 
}

/* Recursion Explanation
1. First recursive call:

insertNode(Mango, "Avocado", "Meaning")

Mango is not NULL. strcmp("Avocado", "Mango") returns a negative value, so we execute:

Mango->left = insertNode(Apple, "Avocado", "Meaning");

2. Second recursive call:

insertNode(Apple, "Avocado", "Meaning")

Apple is not NULL. strcmp("Avocado", "Apple") returns a positive value, so we execute:

Apple->right = insertNode(NULL, "Avocado", "Meaning");

3. Third recursive call:

insertNode(NULL, "Avocado", "Meaning")

Now root is NULL, so we execute:

return createNode("Avocado", "Meaning");

A new Avocado node is created and returned.

4. We return to the second recursive call.

Remember, we were executing:

Apple->right = insertNode(NULL, w, m);

The recursive call returned the newly created Avocado node. Therefore, Apple->right is assigned Avocado.

Then we execute return root, which returns Apple.

5. We return to the first recursive call.

We were executing:

Mango->left = insertNode(Apple, w, m);

The recursive call returned Apple. Therefore, Mango->left is assigned Apple.

Then we execute return root, which returns Mango.

6. Finally, we return to main():

root = insertNode(root, w, m);

The function returns Mango, so the original root is preserved.

The final tree is:

Mango
/
Apple

Avocado

Essentially, the recursive calls go down the tree (Mango → Apple → NULL), and the return values travel back up (Avocado → Apple → Mango), reconnecting the pointers along the way.*/

void display(struct Node* root){

    if (root == NULL) {
        return;
    }
    display(root->left);
    printf("%s : %s \n",root->word,root->meaning);
    display(root->right);}


struct Node* search(struct Node* root,char w[]){
    if (root==NULL){
        printf("Word not found \n");
    }
    else{
        int c=strcmp(w,root->word);
        if (c<0){
            search(root->left,w);
        }
        else if(c>0){
            search(root->right,w);
        }
        else{
            printf("Meaning: %s \n",root->meaning);
        }
    }
}

int main(){
    struct Node* dict=NULL;
    do{
        printf("1. Add word to dictionary \n");
        printf("2. Search word \n");
        printf("3. Print all words \n");
        printf("4. Exit \n");
        int choice;
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
                char w[50];
                char m[50];
                printf("Enter word: ");
                scanf("%s",&w);
                printf("Enter meaning: ");
                scanf("%s",&m);
                dict=insertNode(dict,w,m);
                break;
            case 2:
                char sw[50];
                printf("Enter word to search for: ");
                scanf("%s",&sw);
                search(dict,sw);
                break;
            case 3:
                display(dict);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice \n");
                break;
        }
    }
    while (1);
}