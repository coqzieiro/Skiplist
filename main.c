#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

enum opcode {
    INS,
    REM,
    ALT,
    GET, 
    ALL,
    NOP
};

// Transforma uma string em um opcode, type-safety
enum opcode op(const char* str){
    if(!strcmp("insercao", str)) return INS;
    if(!strcmp("alteracao", str)) return ALT;
    if(!strcmp("remocao", str)) return REM;
    if(!strcmp("busca", str)) return GET;
    if(!strcmp("impressao", str)) return ALL;

    return(NOP);
}

// Função de ajuda para verificar se uma palavra existe na skiplist
_Bool exists(sl* lst, char* word){
    const char* got = sl_get(lst, word);

    if(got){
        free((char*)got);
        return(1);
    }
    return(0);
}

int main(void){
    char opstr[10]; // Operação tem 10 caracteres no máximo
    char word[MAX_WORD_LEN+1];
    char desc[MAX_DESC_LEN+1];

    char c;

    int ignore;

    // Cria skiplist
    sl* lst = sl_new();

    // Pega operação
    while(scanf("%s", opstr) != EOF){
        switch(op(opstr)){
            case INS:
            ignore = scanf("%s %[^\n]s", word, desc);
            
            if(exists(lst, word)) puts("OPERACAO INVALIDA");
            else sl_ins(lst, word, desc, 1);
            break;
            case ALT:
            ignore = scanf("%s %[^\n]s", word, desc);
            
            if(!exists(lst, word)) puts("OPERACAO INVALIDA");
            else sl_ins(lst, word, desc, 0);
            break;
            case REM:
            ignore = scanf("%s", word);
            if(!sl_rem(lst, word)) puts("OPERACAO INVALIDA");
            break;
            case GET:
            ignore = scanf("%s", word);
                {
                    const char* got = sl_get(lst, word);
                    if(!got){
                        puts("OPERACAO INVALIDA");
                        break;
                    }
                    printf("%s %s\n", word, got);
                    free((char*)got);
                }
            break;
            case ALL:
            ignore = scanf(" %c", &c);
            if(!sl_startswith(lst, c)) printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
            break;
            case NOP:
            // No-op
            break;
        }
    }

    // Apaga skiplist
    sl_free(lst);
    return ignore ^ ignore;
}
