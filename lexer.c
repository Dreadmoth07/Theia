#include "linked_list.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 256

typedef enum {
    TOKEN_NULL,
    // Operators
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_EXP,
    TOKEN_CON, // concatenate
    TOKEN_LEN, // length
    TOKEN_STO, // store
    TOKEN_OUT,
    TOKEN_IN,
    // Types
    TOKEN_INT,
    TOKEN_CHAR,
    TOKEN_BOOL,
    // Variable
    TOKEN_VARIABLE
} Token;

typedef struct {
    Token token;
    char name[BUFFER_LEN];
    void* value;
} Lex;

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

Queue* tokeniser(Queue* words){
    Lex* tok = (Lex*) malloc(sizeof(Lex));
    while(peek_queue(words)){
        strcpy(tok->name,"");
        tok->token=TOKEN_NULL;

        // check if a word is a known operator
        char* word = (char*)pop_queue(words);
        printf("%s",word);
        switch (*word)
        {
            case '+':
                tok->token = TOKEN_ADD;    
                break;
            case '-':
                tok->token=TOKEN_SUB;
                break;
            case '*':
                tok->token=TOKEN_MUL;
                break;
            case '/':
                tok->token=TOKEN_DIV;
                break;
            case '%':
                tok->token=TOKEN_MOD;
                break;
            case '^':
                tok->token=TOKEN_EXP;
                break;
            case ',':
                tok->token=TOKEN_CON;
                break;
            case '|':
                tok->token=TOKEN_LEN;
                break;
            case '=':
                tok->token=TOKEN_STO;
                break;
            case ':':
                tok->token=TOKEN_OUT;
                break;
            case '~':
                tok->token=TOKEN_IN;
                break;
        }
        
        // check if a word is a known data type (int, bool, string)
        // Since it is not necessarily a single-character word, we need to do string comparisons instead now.

        // Integers
        char* p=word;
        int v = strtol(word,&p,10);
        if(p != word){
            tok->token = TOKEN_INT;
            tok->value = &v;
        }
        // Booleans
        if(strcmp(word,"true")==0){
            tok->token=TOKEN_BOOL;
            p=malloc(sizeof(int));
            *p=1;
            tok->value=p;
        }
        else if(strcmp(word,"false")){
            tok->token=TOKEN_BOOL;
            p=malloc(sizeof(int));
            *p=0;
            tok->value=p;
        }

        // if neither is true, it must be a variable of some kind.
        if(tok->token == TOKEN_NULL){
            strcpy(tok->name,word);
            tok->token = TOKEN_VARIABLE;
        }

        free(word);
    }
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