# Amazon-Engineering-Challenge---EDB2
Código fonte do programa desenvolvido para a atividade e instruções para rodar e usá-lo.

Autor: Henri Felipe Tomaz Bezerra Costa

Este programa visa simular as árvores AVL e LLRB. Ele permite fazer operações em ambas e visualizar suas rotações e o balanceamento final da árvore.

Programa escrito em C, testado e compilado no Windows 11. (funcionou perfeitamente aqui)

Instruções para uso: 
Ao executar o programa, ele pede para que o usuário escolha uma das árvores, digite 1 no terminal para AVL e 2 para a Rubro Negra LLRB.

Após isso, o usuário será apresentado com um menu. O programa conta com 8 opções no menu, sendo elas:
1. Inserir elemento - *Exemplo de uso: 1 -> enter -> 15 -> enter*
2. Remover elemento - *Exemplo de uso: 2 -> enter -> 20 -> enter*
3. Buscar elemento - *Exemplo de uso: 3 -> enter -> 10 -> enter*
4. Exibir percurso em ordem (crescente)
5. Visualizar estrutura da árvore
6. Alternar visualização automática
7. Trocar tipo de árvore - *Exemplo de uso: 7 -> enter -> 2 -> enter*
8. Sair e fechar o programa.

Para realizar essas funções basta digitar o número dela no terminal e apertar enter.

Siga as instruções dadas em cada função

De modo geral, as funções de 1 a 3 requerem que o usuário digite o número que ele quer para fazer uma operação na árvore. Basta digitar o número da operação que o programa pedirá ao usuário uma entrada, então digite o número desejado e aperte enter.

A função 4 imprime na tela os elementos da árvore em ordem crescente

A função 5 permite ao usuário ver a estrutura completa da árvore, ela aparecerá dessa forma:
  30 (alt:1)
20 (alt:2)
   10 (alt:1)

Alt indica a altura do nó, percebe-se que nessa árvore o 20 é a raiz, o 30 é o filho direito e o 10 é o filho esquerdo. 

A função 6 permite ativar ou desativar a visualização automática da árvore após cada operação, ou seja, caso o usuário queira, ele só verá a árvore quando utilizar a função 5. A função 6 já começa ativada por padrão.

A função 7 permite ao usuário trocar de um tipo de árvore para outro, igual a quando inicializa-se o programa. Após a troca, a árvore antiga fica guardada na memória.

A função 8 encerra o programa.

*PARA COMPILAR*: 

Basta fazer o download do arquivo.exe e executá-lo, caso contrário é possível compilar o arquivo.c
./edbamazon no terminal

Para compilar o arquivo.c é necessário que o usuário tenha instalado um compilador de código C.

Com isso, digite no terminal:

gcc edbv3.c -o edbamazon -Wall
./edbamazon

ou 

gcc -std=c99 edbv3.c -o edbamazon -Wall
./edbamazon


Algumas decisões de implementação:
1. A inserção e a remoção foram implementadas de forma recursiva na avl e LLRB
2. A função de inserção retorna um ponteiro booleano *inserido indicando se a chave já existia e bloqueia duplicatas
3. Visualização por Cores ANSI na LLRB
4. Menu interativo
5. toggle de visualização
6. implementação de contador de rotações por totalRotacoesAVL e arvore->rotacoes para facilitar contagem
7. tratamento de erros com print de mensagens
