# Skiplist
  O objetivo deste projeto é desenvolver os mecanismos de manipulação de um dicionário com definições de palavras ou expressões idiomáticas (verbetes) apresentadas pelos usuários. O seu dicionário deve suportar as operações de _inserção, remoção, alteração e busca_ de palavras, além da impressão de todos os verbetes iniciados por um caractere definido pelo usuário.


  A entrada do programa se dá pela definição da operação a ser realizada seguida por uma ou duas cadeias de caracteres, dependendo da operação requerida. As operações devem considerar a seguinte configuração de entrada.
  

* _insercao str1 str2_ : insere a palavra str1, com a definição str2, no dicionário;
* _alteracao str1 str2_ : altera a definição da palavra str1 para str2;
* _remocao str1_ : remove a palavra str1 do dicionário;
* _busca str1_ : imprime a definição da palavra str1;
* _impressao ch1_ : imprime todas as palavras iniciadas pelo caractere ch1 seguidas por suas respectivas definições em ordem alfabética. Cada palavra (com sua respectiva definição) deve ser impresso em uma linha diferente.


#### Note que há operações que operações de _alteração, remoção e busca_ de palavras inexistentes no dicionário e a _inserção_ de uma palavra repetida, o programa imprime “OPERACAO INVALIDA”. 


#### Caso não haja palavras iniciadas por ch1, imprime-se a mensagem “NAO HA PALAVRAS INICIADAS POR ch1”.

