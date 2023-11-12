#include "skiplist.h"
#include "utils.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct impl_sl {
    char word[MAX_WORD_LEN+1];
    char desc[MAX_DESC_LEN+1];
    size_t floor;
    struct impl_sl* next[SL_DEPTH];
};

// Retorna um inteiro entre [1, max]
int randint(int max) {
    int result = 1;

    while (result < max && (rand() > RAND_MAX / 2)) {
        result++;
    }

    return(result);
}

sl* sl_new(void) {
    srand(time(NULL)); // Reseta a seed 

    sl* new = xalloc(sizeof(sl)); // Xalloc zera tudo

    new->floor = SL_DEPTH; // Começa da posição mais alta
    return(new);
}

// apaga skiplist
void sl_free(sl* lst) {
    sl* cur = lst;
    sl* next = NULL;
    while (cur) {
        next = cur->next[0];
        free(cur);
        cur = next;
    }
}

// Procura o elemento 'word', se não encontrar retorna nulo
const char* sl_get(sl* lst, char word[MAX_WORD_LEN+1]) {
    sl* cur = lst;
    int level = lst->floor - 1;
    
    // Procura verbete
    while (cur != NULL && level >= 0) {
        if (cur->next[level] == NULL) {
            -- level;
        } else {
            int cmp = strcmp(cur->next[level]->word, word);
            if (cmp == 0) { // Achamos
                return strdup(cur->next[level]->desc); 
            } else if (cmp > 0) { // Desce
                level--;
            } else { // Continua no mesmo andar
                cur = cur->next[level];
            }
        }
    }

    // Não achamos :sob:
    return(NULL);
}

// Imprime todas as palavras que começam com *c*
_Bool sl_startswith(sl* lst, char c) {
    _Bool found = 0;
    // Procura todos os verbetes que começam com *c*
    while (lst != NULL) {
        if (lst->word[0] == c) {
            printf("%s %s\n", lst->word, lst->desc);
            found = 1;
        }
        lst = lst->next[0];
    }
    return found;
}
 
// Insere o novo elemento na lista, se new_only é falso, sobreescreve o valor antigo
void sl_ins(sl* lst, char word[MAX_WORD_LEN+1], char desc[MAX_DESC_LEN+1], _Bool new_only) {
    sl* prev[SL_DEPTH];
    sl* cur = lst;
    int level = lst->floor - 1;

    // Procura verbete
    while (cur != NULL && level >= 0) {
        prev[level] = cur;
        if (cur->next[level] == NULL) {
            level--;
        } else {
            int cmp = strcmp(cur->next[level]->word, word);
            if (cmp == 0) { // Palavras iguais
                if(new_only) return; 
                // Sobreescreve se new_only é false
                strcpy(cur->next[level]->desc, desc);
                return;
            } else if (cmp > 0) { // Desce um nivel
                level--;
            } else { // Continua no mesmo nivel
                cur = cur->next[level];
            }
        }
    }
    // Só adiciona se new_only é true
    if(!new_only) return;

    // Não está na skip list, precisamos criar um novo
    sl* new_entry = xalloc(sizeof(sl));
    new_entry->floor = randint(lst->floor);
    strcpy(new_entry->word, word);
    strcpy(new_entry->desc, desc);

    // Ponteiros nulos andares acima
    for (size_t i = SL_DEPTH - 1; i > new_entry->floor; -- i) { 
        new_entry->next[i] = NULL;
    }
    // Acerta ponteiros
    for (int i = new_entry->floor - 1; i >= 0; -- i) {
        new_entry->next[i] = prev[i]->next[i];
        prev[i]->next[i] = new_entry;
    }
}


// Apaga palavra da lista
_Bool sl_rem(sl* lst, char word[MAX_WORD_LEN+1]) {
    sl* prev[SL_DEPTH];
    sl* cur = lst;
    int level = lst->floor - 1;

    // Procura o nó anterior ao procurado
    int cmp = 1;
    while (cur != NULL && level >= 0) {
        prev[level] = cur;
        if (cur->next[level] == NULL) {
            level--;
        } else {
            cmp = strcmp(cur->next[level]->word, word);
            if (cmp >= 0) { // Desce um andar
                level--;
            } else { // Continua no mesmo andar
                cur = cur->next[level];
            }
        }
    }

    // Achamos o nó anterior ao procurado
    if (cur && !cmp) { 
        sl* guilt = cur->next[0];

        // Apaga o nó da lista
        for (int i = guilt->floor - 1; i >= 0; -- i) {
          prev[i]->next[i] = guilt->next[i];
        }
        // Liberte-o de seus pecados
        free(guilt);
        guilt = NULL;

        return 1;
    }

    return(0);
}
