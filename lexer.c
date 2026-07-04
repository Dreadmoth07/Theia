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
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    // Types
    TOKEN_INT,
    TOKEN_STR,
    TOKEN_BOOL,
    // Variable
    TOKEN_VARIABLE
} Token;

typedef struct {
    Token token;
    char name[BUFFER_LEN];
    void* value;
} Lex;

void print_Lex(void*);

Queue* splitter(char* text){
    
    // Creating the list of words.

    Queue* words = initialise_queue();
    char* word;
    int i=0; // i refers to the word
    int j=0;  // j refers to the position in the word.

    while(text[i] != '\0'){
        word = (char*) malloc(BUFFER_LEN);
        j = 0;
        if(text[i]!='"'){
            while(text[i] != ' ' && text[i] != '\n' && text[i] != '\0'){
                word[j] = text[i];
                i++;
                j++;
            }
        }
        else if(text[i]=='"'){
            do{
                word[j] = text[i];
                i++;
                j++;
            }while((text[i] != '"' && text[i] != '\0'));
            i++;
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
    Queue* tokens = initialise_queue();
    Lex* tok = (Lex*) malloc(sizeof(Lex));
    while(peek_queue(words)){
        strcpy(tok->name,"");
        tok->token=TOKEN_NULL;

        // check if a word is a known operator
        char* word = (char*)pop_queue(words);
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
            case '$':
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
            case '&':
                tok->token=TOKEN_AND;
                break;
            case '|':
                tok->token=TOKEN_OR;
                break;
            case '`':
                tok->token=TOKEN_NOT;
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
        else if(strcmp(word,"false")==0){
            tok->token=TOKEN_BOOL;
            p=malloc(sizeof(int));
            *p=0;
            tok->value=p;
        }

        if(word[0]=='"'){
            tok->token=TOKEN_STR;
            p=(char*) malloc(BUFFER_LEN);

            int i=1;
            while(word[i]!='"' && word[i]!='\0')
                i++;
            word[i]='\0';

            strcpy(p,word+1);
            tok->value=p;
        }

        // if neither is true, it must be a variable of some kind.
        if(tok->token == TOKEN_NULL){
            strcpy(tok->name,word);
            tok->token = TOKEN_VARIABLE;
        }

        push_queue(tokens,tok,sizeof(Lex));

        free(word);
    }
    return tokens;
}

Queue* lexer(char* sourceCode){
    Queue* words = splitter(sourceCode);
    Queue* tokens = tokeniser(words);
    print_queue(tokens,print_Lex);
    return tokens;
}

int main(int argc, char** argv){
    char* source = (char*) malloc(BUFFER_LEN);
    printf("Enter Source Code: ");
    scanf("%[^\n]s",source); // ooh scanset specifier - this will only stop when it hits a newline.
    
    Queue* tokens = lexer(source);

    free(source);
}

void print_Lex(void* ptr){
    Lex* p = (Lex*) ptr;
    switch (p->token)
    {
    case TOKEN_ADD:
        printf("Addition");
        break;
    case TOKEN_SUB:
        printf("Subtraction");
        break;
    case TOKEN_MUL:
        printf("Multiplication");
        break;
    case TOKEN_DIV:
        printf("Division");
        break;
    case TOKEN_MOD:
        printf("Modulus");
        break;
    case TOKEN_EXP:
        printf("Exponentiation");
        break;
    case TOKEN_CON:
        printf("Concatenation");
        break;
    case TOKEN_LEN:
        printf("Length");
        break;
    case TOKEN_STO:
        printf("Storage");
        break;
    case TOKEN_AND:
        printf("Logical AND");
        break;
    case TOKEN_OR:
        printf("Logical OR");
        break;
    case TOKEN_NOT:
        printf("Logical NOT");
        break;
    case TOKEN_OUT:
        printf("Output");
        break;
    case TOKEN_IN:
        printf("Input");
        break;
    case TOKEN_STR:
        printf("String: %s",(char*)(p->value));
        break;
    case TOKEN_INT:
        printf("Int: %d",*(int*)(p->value));        
        break;
    case TOKEN_BOOL:
        printf("Bool: %d",*(int*)(p->value));
        break;
    case TOKEN_VARIABLE:
        printf("Variable. Name = %s",p->name);
        break;
    case TOKEN_NULL:
        printf("-------------NULL-------------");
        break;
    }
    printf("\n");
}