#include "linked_list.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LEN 256

Queue* lexer(char* sourceCode){
    
    // Creating the list of words.

    Queue* words = initialise_queue();
    char* word;
    int i,j = 0; // i refers to the word
    while(sourceCode[i] != '\0'){
        word = (char*) malloc(BUFFER_LEN);
        j = 0; // j refers to the position in the word.

        while(sourceCode[i] != ' ' && sourceCode[i] != '\n' && sourceCode[i] != '\0'){
            word[j] = sourceCode[i];
            i++;
            j++;
        }

        word[j] = '\0';
        j++;
        i++;

        push_queue(words,word,j*sizeof(char));
        free(word);
    }

    print_queue(words,print_string);
}

int main(int argc, char** argv){
    lexer("Hello World!\0");
}