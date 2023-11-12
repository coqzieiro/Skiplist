/* 
 * Implementação de uma Skip List
 * 
 * Autores: Guilherme Corrêa Torquato 
 *          Felipe da Costa Coqueiro 
 * 
 */

#ifndef SKIPLIST_H
    #define SKIPLIST_H

    // Profundidade máxima
    #define SL_DEPTH 11

    // Definições do problema
    #define MAX_WORD_LEN 50
    #define MAX_DESC_LEN 140

    typedef struct impl_sl sl;

    // Cria uma nova skip list e inicializa a seed do rand
    sl* sl_new(void);

    // Insere um elemento na skip list, se new_only for true, só insere se não existir
    void sl_ins(sl* lst, char word[MAX_WORD_LEN+1], char desc[MAX_DESC_LEN+1], _Bool new_only); 

    // Retorna um elemento da skip list, se não existir retorna NULL
    const char* sl_get(sl* lst, char word[MAX_WORD_LEN+1]); 

    // Remove um elemento da skip list, se não existir retorna false
    _Bool sl_rem(sl* lst, char word[MAX_WORD_LEN+1]); 

    // Imprime todos os elementos da skip list que começam com *c*
    _Bool sl_startswith(sl* lst, char c); 

    // Apaga a skip list
    void sl_free(sl* lst); 
#endif
