#include "ineficiente.h"
#include <stdio.h>
#include <stdlib.h>

struct tlist {
    int valor;
    struct tlist *next;
};

struct tqueue {
    int valor;
    struct tqueue *next;
};

// ========= funções privadas

Tlist *node_lista(int valor){
    Tlist *node = (Tlist*)malloc(sizeof(Tlist));

    // Caso ocorrer um erro na alocação dinâmica, o programa será encerrado
    // gerando uma mensagem na saída de erro padrão.
    if(node == NULL){
        fprintf(stderr, "Erro ao alocar memória para lista\n");
        exit(1);
    }

    node->valor = valor;
    node->next = NULL;

    return node;
}

void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
// =========================


// ======== funções públicas
Tlist *gerar_lista(int *vetor, int tamanho_vetor){
    
    Tlist *head = NULL;
    Tlist *aux = NULL;

    for(int i=0; i<tamanho_vetor; i++){

        Tlist *node = node_lista(vetor[i]);
        if(head == NULL){
            head = node;
            aux = node;
        } else{
            aux->next = node;
            aux = node;
        }
    }

    return head;
}

/*
 * Primeiramente irá precorrer a lista encadeada calculando a quantidade de nodes. Depois, irá 
 * alocar o espaço de memória corretamente. E, por fim, percorrer novamente a lista encadeada 
 * adicionando os valores ao vetor
*/
int *gerar_vetor(Tlist *head){
    int tamanho_vetor = 0;
    int *vetor = NULL;

    for(Tlist *aux = head; aux != NULL; aux = aux->next){
        tamanho_vetor++;
    }

    vetor = (int *)malloc(tamanho_vetor * sizeof(int));

    if(vetor == NULL){
        fprintf(stderr, "Erro ao gerar vetor\n");
        exit(1);
    }

    int i=0;
    for(Tlist *aux = head; aux != NULL; aux = aux->next){
        vetor[i] = aux->valor;
        i++;
    }

    return vetor;
}

void exibir_vetor(int *vetor, int n){
    printf("{");
    for(int i=0; i<n-1; i++){
        printf("%d, ", vetor[i]);
    }
    printf("%d}\n", vetor[n-1]);
}

void exibir_lista(Tlist *head){
    if(head == NULL){
        printf("Lista vazia!\n");
        return;
    }

    Tlist *aux;    
    for(aux = head; aux->next != NULL; aux = aux->next){
        printf("%d -> ", aux->valor);
    }

    printf("%d\n", aux->valor);
}


void selectionsort(int *vetor, int tamanho_vetor){

    for(int i=0; i<tamanho_vetor - 1; i++){

        int menor = i;

        for(int j = i+1; j<tamanho_vetor; j++){
            if(vetor[menor] > vetor[j]){
                menor = j;
            }
        }
        troca(&vetor[menor], &vetor[i]);
    }
}


void liberar_memoria_lista(Tlist *head){
    Tlist *aux = head;

    while (aux != NULL){
        Tlist *prox = aux->next;
        free(aux);

        aux = prox;
    }
}

void liberar_memoria_vetor(int *vetor){
    free(vetor);
}