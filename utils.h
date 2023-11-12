#ifndef UTILS_H
    #define UTILS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // Função de ajuda, se a alocação deu errado, fecha o programa com o erro 69
    void* xalloc(size_t size){
        void* res = calloc(1, size);
        if(!res){ fputs("SHOOT!\n", stderr); exit(69); }
        return(res);
    }

    // Definição do strdup, cria uma nova string com o mesmo conteúdo
    char* strdup(const char *src) {
        char* dst = xalloc(strlen (src) + 1);  
        strcpy(dst, src);                      
        return(dst);                           
    }
#endif
