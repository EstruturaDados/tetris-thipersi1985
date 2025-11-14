#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

//criação da estrutura do elemento
typedef struct {        
    char nome[4];
    int id;
} Peca;

//tamanho máximo da fila
#define MAX 5 

//criação da estrutura da fila
typedef struct {
    Peca itens[MAX];
    int inicio, fim, total;
} Fila;

//inicialização da fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

//verificação da fila (se estão cheias ou vazias)
int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

//inserindo elemento na fila; primeiro testa se a fila já está cheia. 
void inserir (Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir!\n");
        return;
    }
    
    f->itens[f->fim] = p; //insere o elemento 'p' no final
    f->fim = (f->fim + 1) % MAX; //lógica circular; ela aponta pro próximo elemento.
    f-> total++;    //incrementa a fila ao inserir a peça 
}

//removendo elemento na fila; primeiro testa se a fila já está vazia.
void remover (Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover!\n");
        return;
    }
    
    *p = f->itens[f->inicio]; //armazena o item a ser removido
    f->inicio = (f->inicio + 1) % MAX; //lógica circular; ela atualiza o índice do início do array.
    f-> total--; //decrementa a fila ao remover a peça
}

//exibir a fila
void mostrarFila(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = 0; i < f->total; i++, idx++)
    {
        printf("[%s, %d]", f->itens[idx].nome, idx);
    }
    printf("\n");
}

//função para limpar o buffer de entrada
void limparBuffer() {     
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//declaração e utilização no main()
int main() {
    Fila f;     //instanciando um elemento 'f' na struct 'Fila'
    inicializarFila(&f);  //Inicializando a fila
    int opcao; //variável que será usada no menu de opções abaixo

do {
        printf("BEM-VINDO AO JOGO TETRIS\n");
        printf("=========================\n");
        printf("1 - Jogar Peça\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("=========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();     // Limpa o '/n' deixado pelo scanf.

        // processamento das opções
        switch (opcao) {
            case 1:
                Peca removida;
                remover(&f, &removida);
                printf("Última peça removida: %s\n", removida.nome);
                mostrarFila(&f); //mostra a fila após remoção da peça
                // a pausa abaixo é crucial para que o usuário veja a lista antes do próximo loop limpar a tela.
                printf("\nPressione enter para continuar...");
                getchar();
            break; 
            case 2:
                Peca pecas[] = {{"I"},{"O"},{"L"},{"T"}};           //definindo a lista de peças
                int total_pecas = sizeof(pecas) / sizeof(pecas[0]); //conta o número total de peças na lista de peças
                srand(time(NULL));                                  //inicializa o gerador de números aleatórios
                int indice_aleatorio = rand() % total_pecas;        //gera um índice aleatório
                inserir(&f,pecas[indice_aleatorio]);                //chama a função inserir, passando a peça gerada aleatoriamente
                mostrarFila(&f);
                // a pausa abaixo é crucial para que o usuário veja a lista antes do próximo loop limpar a tela.
                printf("\nPressione enter para continuar...");
                getchar();
            break;
            case 0:
                printf("saindo do jogo...");
            break;
            default:
                printf("Você escolheu uma opção inválida. Tente novamente!\n");
            break;
        }
    } while (opcao !=0);

return 0;

}