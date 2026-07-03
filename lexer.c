#include "linked_list.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN 256

Queue* splitter(char* text){
    
    // Creating the list of words.

    Queue* words = initialise_queue();
    char* word;
    int i=0; // i refers to the word
    int j=0;  // j refers to the position in the word.

    while(text[i] != '\0'){
        word = (char*) malloc(BUFFER_LEN);
        j = 0;
        while(text[i] != ' ' && text[i] != '\n' && text[i] != '\0'){
            word[j] = text[i];
            i++;
            j++;
        }

        word[j] = '\0';
        j++;
        i++;

        push_queue(words,word,j*sizeof(char));
        free(word);
    }

    return words;
}

Queue* lexer(char* sourceCode){
    Queue* words = splitter(sourceCode);
    Queue* tokens = tokeniser(words);
}

int main(int argc, char** argv){
    char* source = (char*) malloc(BUFFER_LEN);
    printf("Enter Source Code: ");
    scanf("%[^\n]s",source); // ooh scanset specifier - this will only stop when it hits a newline.
    
    Queue* words = lexer(source);

    free(source);
}