#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node{
        int coeff;
        int expo;
        struct Node* next;
};

struct Node* createNode(struct Node* head,int co,int ex){
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        newNode->coeff=co;
        newNode->expo=ex;
        newNode->next=NULL;
        return newNode;
}

struct Node* insertNode(struct Node* head,int co,int ex){   //Keep in mind, in this I have not accounted for coefficients with same exponents being entered multiple times
        struct Node* ptr=createNode(head,co,ex);
        if (head==NULL || (ptr->expo) > (head->expo)){
            ptr->next=head;
            head=ptr;
        }
        else{
            struct Node* temp=head;
            while (temp->next!=NULL && ((temp->next->expo) > (ptr->expo))){
                temp=temp->next;
            }
            ptr->next=temp->next;
            temp->next=ptr;
                
            }
        return head;
}

struct Node* addition(struct Node* head1,struct Node* head2, struct Node* sum){
    struct Node* ptr1=head1;
    struct Node* ptr2=head2;
    while (ptr1!=NULL && ptr2!=NULL){
        if (ptr1->expo==ptr2->expo){
            int co=ptr1->coeff + ptr2->coeff;
            int ex=ptr1->expo;
            sum=insertNode(sum,co,ex);
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
        else if(ptr1->expo > ptr2->expo){
            int co=ptr1->coeff;
            int ex=ptr1->expo;
            sum=insertNode(sum,co,ex);
            ptr1=ptr1->next;
        }
        else {
            int co=ptr2->coeff;
            int ex=ptr2->expo;
            sum=insertNode(sum,co,ex);
            ptr2=ptr2->next;}
        }
    while (ptr1!=NULL){                    //This only happens when ptr2 reaches ending
            int co=ptr1->coeff;
            int ex=ptr1->expo;
            sum=insertNode(sum,co,ex);
            ptr1=ptr1->next;
    }
    while (ptr2!=NULL){                   //This only happens when ptr1 reaches ending
            int co=ptr2->coeff;
            int ex=ptr2->expo;
            sum=insertNode(sum,co,ex);
            ptr2=ptr2->next;
    }
    return sum;
}

//Honestly I should have made a display function instead of manually printing everytime.

int main(){
    struct Node* poly1=NULL;    // Don't forget to initialise pointer as NULL. Otherwise you will run into issues.
    int n1;
    printf("Enter no of values you want in poly1");
    scanf("%d",&n1);
    for (int i=0;i<n1;i++){
        int co,ex;
        printf("Enter coefficient: ");
        scanf("%d",&co);
        printf("Enter exponent: ");
        scanf("%d",&ex);
        poly1=insertNode(poly1,co,ex);
    }
    printf("Polynomial 1 \n");
    
    struct Node* temp1=poly1;
    while (temp1!=NULL){
        printf("%dx^%d ",temp1->coeff,temp1->expo);
        if (temp1->next!=NULL){                     //We only print '+' as long as the term we are printing before it isn't the last term.
            printf("+ ");           
        }
            temp1=temp1->next;
        }
    printf("\n");
     
    struct Node* poly2=NULL;
    int n2;
    printf("Enter no of values you want in poly 2: ");
    scanf("%d",&n2);
    for (int i=0;i<n2;i++){
        int co,ex;
        printf("Enter coefficient: ");
        scanf("%d",&co);
        printf("Enter exponent: ");
        scanf("%d",&ex);
        poly2=insertNode(poly2,co,ex);
    }
    printf("Polynomial 2 \n");
    
    temp1=poly2;
    while (temp1!=NULL){
        printf("%dx^%d ",temp1->coeff,temp1->expo);
        if (temp1->next!=NULL){
            printf("+ ");
        }
            temp1=temp1->next;
        }
    printf(" \n");
    

    struct Node* result=NULL;
    result=addition(poly1,poly2,result);
    temp1=result;
    while (temp1!=NULL){
        printf("%dx^%d ",temp1->coeff,temp1->expo);
        if (temp1->next!=NULL){
            printf("+ ");
        }
            temp1=temp1->next;
        }


    }
