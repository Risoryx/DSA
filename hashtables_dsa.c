#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int size=100;
char hash[100][50];    // Row indicates no of strings .Column indicates max length of string.

int hashfunction(char w[]){
    int sum=0;
    for (int i=0;w[i]!='\0';i++){
        sum=sum+w[i];
    }
    int hashing=sum%size;
    return hashing;
}

void insert(char w[]){
    int pos=hashfunction(w);
    if (hash[pos][0]=='\0'){
        strcpy(hash[pos],w);
    }
    else {
        pos=(pos+1)%size;
        while (hash[pos][0]!='\0'){
            pos=(pos+1)%size;
        }
        strcpy(hash[pos],w);

    }

}

int search(char w[]){
    int key=0;
    for (int i=0;i<size;i++){
        if (strcmp(w,hash[i])==0){
            key=1;
            break;
        }
    }
    
    return key;
}

void suggest(char word[]){
    char temp[50];
    int len=strlen(word);

    printf("Suggestions:\n");

    // 1. REPLACEMENT
    for (int i=0; i<len; i++){                     //The objective is to replace every character with every possible lowercase alphabet letter.  Outer loop (i) decides WHICH character position to replace. Inner loop (c) decides WHAT character to replace it with.
        for (char c='a'; c<='z'; c++){
            strcpy(temp,word);                     // Why do we call strcpy() every time?  Because we want to start with the original word for every new attempt.  Otherwise, the modifications from the previous iteration could remain. After trying all 26 letters, the inner loop finishes.
            temp[i]=c;

            if (search(temp)){
                printf("%s\n",temp);
            }
        }
    }

    // 2. INSERTION
    for (int i=0; i<=len; i++){                   // The reason we do i<=len is because we can also insert after final character
        for (char c='a'; c<='z'; c++){
            strcpy(temp,word);

            memmove(temp+i+1,temp+i,len-i+1);            // memmove(destination, source, number_of_bytes);   It copies the specified number of bytes from source to destination.   eg: memmove(temp + 2, temp + 1, 4);    Lets break it down: temp + 2: Destination starts at index 2. temp + 1: Source starts at index 1. 4: Copy 4 bytes.  Essentially, we're shifting everything from index 1 onwards one position to the right.
                                                         // We do len-i+1 instead of just len-i because we also need to shift the null character to the right!
            temp[i]=c;

            if (search(temp)){
                printf("%s\n",temp);
            }
        }
    }

    // 3. DELETION
    for (int i=0; i<len; i++){
        strcpy(temp,word);

        memmove(temp+i,temp+i+1,len-i);

        if (search(temp)){
            printf("%s\n",temp);
        }
    }
}

int main(){
    char dict[][50] = {
        "apple",
        "mango",
        "cat",
        "cot",
        "coat",
        "bat",
        "car",
        "dog",
        "banana",
        "orange"
    };

    int n = sizeof(dict) / sizeof(dict[0]);

    // Insert all dictionary words into the hash table
    for (int i = 0; i < n; i++){
        insert(dict[i]);
    }

    char word[50];

    printf("Enter a word: ");
    scanf("%s", word);

    if (search(word)){
        printf("Correct spelling! Word found in dictionary.\n");
    }
    else{
        printf("Word not found in dictionary.\n");
        suggest(word);
    }

    return 0;
}


//Your spell checker only checks corrections that require one insertion, one deletion, or one replacement. It doesn't check whether a word merely sounds or looks similar.