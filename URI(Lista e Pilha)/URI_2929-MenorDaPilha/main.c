#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

typedef struct presente
{

    int grauDiversao;
    struct presente *proximo;

} Presente;

typedef struct pilha  // Faz o controle
{
    Presente *topo;
} Pilha;

void pilha_cria(Pilha *p);
void pilha_push(Pilha *p, int valor);
int pilha_min(Pilha* p);
void pilha_pop(Pilha* p);
void pilha_libera(Pilha *p);

void pilha_cria(Pilha *p)
{
    p->topo = 0;
}

void pilha_push(Pilha *p, int valor)
{
    Presente *novoPresente = (Presente*) malloc(sizeof(Presente)); // Cria novo elemento da pilha

    if(novoPresente == 0){
        return;
    }

    novoPresente->grauDiversao = valor;
    novoPresente->proximo = p->topo; //Elemento atual passa a ser o topo
    p->topo = novoPresente;
}

void pilha_pop(Pilha* p)
{
    Presente *topoPresente = p->topo;

    if (topoPresente == NULL) //Checa se o
    {
        printf("EMPTY\n");
        return; //não indica erro;
    }
    p->topo = topoPresente->proximo;
    free(topoPresente);
}

int pilha_min(Pilha* p)
{
    int valor;
    Presente *valorAuxiliar = p->topo;

    if (valorAuxiliar == NULL)
    {
        return -1; // Pilha vazia
    }

    valor = valorAuxiliar->grauDiversao;
    while (valorAuxiliar != NULL)
    {
        if (valorAuxiliar->grauDiversao < valor) // Compara o valor atual com o menor valor
        {
            valor = valorAuxiliar->grauDiversao;
        }
        valorAuxiliar = valorAuxiliar->proximo; // Passa para o próximo na pilha
    }
    return valor;
}

void pilha_libera (Pilha* p)
{
    Presente *t, *q = p->topo;
    while (q != NULL)
    {
        t = q->proximo; //Pega o próximo da pilha
        free(q); //Apaga o do topo
        q = t;
    }
}


void main()
{
    int valorPush, menorValor, numeroOperacoes, i;
    char operacao[5];
    Pilha p;

    scanf("%7d", &numeroOperacoes); //Vai pegar apenas os 7 primeiros dígitos (1 <= numeroOperacoes <= 1000000)
    numeroOperacoes = abs(numeroOperacoes); // Não deixa ser negativo

    pilha_cria(&p);

    for(i = 0; i < numeroOperacoes; i++)
    {
        do{
            scanf("%s", operacao);
        }while((strcasecmp(operacao, "PUSH") != 0) && (strcasecmp(operacao, "PUSH") == 0 && (strcasecmp(operacao, "PUSH") == 0)));

        if(strcasecmp(operacao, "PUSH") == 0)
        {
            scanf("%d", &valorPush);
            pilha_push(&p, valorPush);
        }
        else if(strcasecmp(operacao, "POP") == 0)
        {
            pilha_pop(&p);
        }
        else if(strcasecmp(operacao, "MIN") == 0)
        {
            menorValor = pilha_min(&p);
            if(menorValor != -1)
            {
                printf("%d\n", menorValor);
            }
            else
            {
                printf("EMPTY\n");
            }
        }
    }
}
