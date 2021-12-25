#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "estacionamento.h"

Carro* lista_cria(void)
{
    return NULL;
}

Carro* lista_insere(Carro* lista, char* placa, int prev_retirada)
{

    Carro* novo =(Carro*)malloc(sizeof(Carro));
    novo->prev_retirada = prev_retirada;
    strcpy(novo->placa, placa);
    novo->proximo = lista;
    return novo;
}

void pilha_cria(Pilha* p)
{
    p->topo = 0;
}

void pilha_push(Pilha* p, char* placa, int prev_retirada)
{
    Carro *novoCarro = (Carro*) malloc(sizeof(Carro)); // Cria novo elemento da pilha

    if(novoCarro == 0)
    {
        return;
    }

    novoCarro->prev_retirada = prev_retirada;
    strcpy(novoCarro->placa, placa);
    novoCarro->proximo = p->topo; //Elemento atual passa a ser o topo
    p->topo = novoCarro;
}

void pilha_pop(Pilha *p)
{
    Carro *topoPilha = p->topo;

    if (topoPilha == NULL) //Checa se o
    {
        printf("EMPTY\n");
        return; //não indica erro;
    }
    p->topo = topoPilha->proximo;
    free(topoPilha);
}

void cria_pilhas(Pilha* pilha)
{
    for(int i = 0; i < quantidadeFileiras; i++)
    {
        pilha_cria(&pilha[i]);
    }
}

void imprime_carro(Pilha* pilha)
{
    Carro* percorreFileira = pilha->topo;

    if(pilha->topo == NULL)
    {
        return;
    }
    while(percorreFileira != NULL)
    {
        printf("----%s-%2dh|", percorreFileira->placa, percorreFileira->prev_retirada);
        percorreFileira = percorreFileira->proximo;
    }
}

int garagem_conta(Pilha* pilha)
{
    int contador = 0;
    Carro* percorreFileira = pilha->topo;

    while(percorreFileira != NULL)
    {
        percorreFileira = percorreFileira->proximo;
        contador++;
    }
    return contador;
}

void imprime_rua(Carro* rua)
{
    printf("\nRua-> |");
    for(int i = 0; i < qtdVagasRua; i++)
    {
        if(rua != NULL)
        {
            printf("----%s-%2dh|", rua->placa, rua->prev_retirada);
            rua = rua->proximo;
        }
        else
        {
            printf("---------------|");
        }
    }
    printf("\n\n");
}

void imprime_garagem(Pilha *pilha, Carro* rua)
{
    int contador = 0;
    printf("\nSaída\n");
    for(int i = 0; i < quantidadeFileiras; i++)
    {
        contador = garagem_conta(&pilha[i]); //Conta quantos espaços tem de vagas em cada fileira(pilha)
        for(int j = 0; j < qtdVagasFileira; j++)
        {
            if(contador < qtdVagasFileira)
            {
                printf("---------------|"); // Vai colocando o espaço de garagem aonde não há carro
                contador++;
            }
            else
            {
                break;
            }
        }
        imprime_carro(&pilha[i]); // Vai imprimir todos os carros do índice
        printf("\n");
    }
    printf("\n");
    imprime_rua(rua);
}

int conta_fileira(Pilha* p)
{
    int tamanho = 0;
    Carro* percorreFileira = p->topo;
    if(p->topo == 0)
    {
        return 0;
    }
    else
    {
        while(percorreFileira != NULL)
        {
            tamanho++;
            percorreFileira = percorreFileira->proximo;
        }
    }
    return tamanho;
}

int conta_carros(Pilha* pilha)
{
    int tamanho = 0;
    for(int i = 0; i < quantidadeFileiras; i++)
    {
        tamanho += conta_fileira(&pilha[i]);
    }
    return tamanho;
}

int previsao_retirada(Pilha* pilha)
{
    Carro* topoPilha = pilha->topo;
    if(topoPilha == NULL)
    {
        return 0;
    }
    return topoPilha->prev_retirada;
}

int previsao_retirada_rua(Carro* rua){
    if(rua == NULL){
        return 0;
    }
    while(rua->proximo != NULL){
        rua = rua->proximo;
    }
    return rua->prev_retirada;
}

int busca_recomendado(Pilha* pilha, Carro* rua)
{
    int indice = 0, maiorDiferenca, diferenca;

    maiorDiferenca = previsao_retirada_rua(rua) - previsao_retirada(&pilha[0]);

    for(int i = 1; i < quantidadeFileiras; i++)
    {
        diferenca = previsao_retirada_rua(rua) - previsao_retirada(&pilha[0]);
        if(diferenca > maiorDiferenca)
        {
            indice = i;
        }
        maiorDiferenca = diferenca;

    }
    return indice;
}

Carro* apaga_ultimo(Carro* rua)
{
    if(rua->proximo == NULL)
    {
        return NULL;
    }
    else
    {
        Carro* ultimo = rua->proximo;
        Carro* penultimo = rua;

        while(ultimo->proximo != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->proximo;
        }
        penultimo->proximo = NULL;
        return ultimo;
    }
}

int procura_placa(Pilha* fileira, char* placa, int retorno)
{
    Carro* percorreFileira = fileira->topo;

    if(percorreFileira == NULL)
    {
        return retorno;
    }

    while(percorreFileira != NULL)
    {
        if(strcasecmp(percorreFileira->placa, placa) == 0)
        {
            retorno = TRUE;
            return retorno;
        }
        percorreFileira = percorreFileira->proximo;
    }
    return retorno;
}

int percorre_fileiras(Pilha* fileira, char* placa)
{
    int retorno = FALSE;
    for(int i = 0; i < quantidadeFileiras; i++)
    {
        retorno = procura_placa(&fileira[i], placa, retorno);
    }
    return retorno;
}

void insere_carro(Pilha* pilha, Carro* rua)
{
    char placa[8];
    int escolha, fileira, recomendado, previsao_retirada;

    if(conta_carros(pilha) >= quantidadeFileiras*qtdVagasFileira)
    {
        return;
    }

    do
    {
        imprime_garagem(pilha, rua);
        printf("Diga a placa do carro (7 algorismos e/ou letras) -> ");
        scanf("%s", placa);
    }
    while(percorre_fileiras(pilha, placa) || strlen(placa) > 7 || strlen(placa) < 7);  // Placa existente

    do
    {
        printf("Diga a previsão de retirada em horas (Ex: 5, 7, 10, etc. Máximo de 24 e mínimo de 1)-> ");
        scanf("%d", &previsao_retirada);
    }
    while(previsao_retirada < 1 || previsao_retirada > 24);

    rua = lista_insere(rua, placa, previsao_retirada);

    recomendado = busca_recomendado(pilha, rua);

    rua = apaga_ultimo(rua);

    pilha_push(&pilha[recomendado], "-CARRO-", previsao_retirada);
    rua = lista_insere(rua, placa, previsao_retirada);

    imprime_garagem(pilha, rua);
    do
    {
        printf("Deseja inserir na posição recomendada ('CARRO') ou em outra fileira? (1 - Recomendada | 2 - Outra fileira) -> ");
        scanf("%d", &escolha);
    }
    while(escolha != 1 && escolha != 2);


    pilha_pop(&pilha[recomendado]);
    rua = apaga_ultimo(rua);

    if(escolha == 1)
    {
        pilha_push(&pilha[recomendado], placa, previsao_retirada);
    }
    else
    {
        do
        {
            printf("Diga a fileira -> ");
            scanf("%d", &fileira);
        }
        while(fileira < 1 || fileira > quantidadeFileiras || conta_fileira(&pilha[fileira-1]) >= qtdVagasFileira);
        pilha_push(&pilha[fileira-1], placa, previsao_retirada);
    }

}

int busca_indice(Pilha* pilha, char* placa)
{
    Carro* percorreFileira = pilha->topo;

    while(percorreFileira != NULL)
    {
        if(strcasecmp(percorreFileira->placa, placa) == 0)
        {
            return TRUE;
        }
        percorreFileira = percorreFileira->proximo;
    }
    return FALSE;
}

void carro_remove(Pilha *fileira, Carro* rua, char* placa, Pilha *pilha)
{
    Carro* percorreFileira = fileira->topo;

    do
    {
        percorreFileira = fileira->topo;
        rua = lista_insere(rua, percorreFileira->placa, percorreFileira->prev_retirada);
        pilha_pop(fileira);
    }
    while(strcasecmp(percorreFileira->placa, placa) != 0);
    imprime_garagem(pilha, rua);
    rua = rua->proximo;
    while(rua != NULL)
    {
        pilha_push(fileira, rua->placa, rua->prev_retirada);
        rua = apaga_ultimo(rua);
    }
    imprime_garagem(pilha, rua);
}

void push_copia(Pilha* pilha1, Pilha* pilha2)
{
    Carro* percorre = pilha1->topo;

    while (percorre != NULL)
    {
        pilha_push(pilha2, percorre->placa, percorre->prev_retirada);
        percorre = percorre->proximo;
    }
}

void copia_fileira(Pilha* fileira1, Pilha* fileira2)
{

    pilha_cria(fileira2);

    for(int i = 0; i < quantidadeFileiras; i++)
    {
        push_copia(&fileira1[i], &fileira2[i]);
    }
}

void libera_pilha(Pilha* fileira)
{
    Carro *percorreFileira = fileira->topo;
    while (percorreFileira != NULL)
    {
        pilha_pop(fileira);
        percorreFileira = fileira->topo;
    }
}

void libera_todas_pilhas(Pilha* fileira)
{
    for(int i = 0; i < quantidadeFileiras; i++)
    {
        libera_pilha(&fileira[i]);
    }
}


void retira_carro(Pilha* pilha, Carro* rua)
{
    Pilha* fileiraAuxiliar = (Pilha*)malloc(quantidadeFileiras*sizeof(Pilha));
    cria_pilhas(fileiraAuxiliar);

    int i = 0;
    char placa[8];
    imprime_garagem(pilha, rua);

    if(pilha == NULL)
    {
        return;
    }

    do
    {
        printf("Diga a placa do carro que gostaria de retirar -> ");
        scanf("%s", placa);
    }
    while(!percorre_fileiras(pilha, placa));

    for(i = 0; i < quantidadeFileiras; i++)
    {
        if(busca_indice(&pilha[i], placa) == TRUE)
        {
            break;
        }
        if(i == quantidadeFileiras)
        {
            break;
        }
    }
    carro_remove(&pilha[i], rua, placa, pilha);


}

void retira_carro_sem_sequencia(Pilha* pilha, Carro* rua)
{
    if(conta_carros(pilha) <= 0)
    {
        return;
    }
    indexSequencia = FALSE; // Não vai apresentar as pausas das sequências
    retira_carro(pilha, rua);
}

Carro* rearruma_rua(Carro* lista, char* placa, int prev_retirada)
{
    Carro* novo;
    Carro* ant = NULL; //ponteiro para elemento anterior
    Carro* p = lista; //ponteiro para percorrer a lista
    while (p != NULL && p->prev_retirada > prev_retirada)
    {
        ant = p;
        p = p->proximo;
    }
    novo = (Carro*) malloc(sizeof(Carro));
    strcpy(novo->placa, placa);
    novo->prev_retirada = prev_retirada;
    if (ant == NULL)  //insere elemento no início
    {
        novo->proximo = lista;
        lista = novo;
    }
    else   //insere elemento no meio da lista
    {
        novo->proximo = ant->proximo;
        ant->proximo = novo;
    }
    return lista;
}

void rearruma(Pilha* fileira, Carro* rua)
{
    Carro* percorreFileira = fileira->topo;

    if(percorreFileira == NULL)
    {
        return;
    }

    while(percorreFileira != NULL)
    {
        rua = rearruma_rua(rua, percorreFileira->placa, percorreFileira->prev_retirada);
        pilha_pop(fileira);
        percorreFileira = fileira->topo;
    }
    while(rua != NULL)
    {
        pilha_push(fileira, rua->placa, rua->prev_retirada);
        free(rua);
        rua = rua->proximo;
    }
}

void rearruma_garagem(Pilha* pilha, Carro* rua)
{
    int resposta;

    if(conta_carros(pilha) <= 0)
    {
        return;
    }
    Pilha* fileiraAuxiliar = (Pilha*)malloc(quantidadeFileiras*sizeof(Pilha));
    cria_pilhas(fileiraAuxiliar);

    copia_fileira(pilha, fileiraAuxiliar);
    rearruma(fileiraAuxiliar, rua);

    imprime_garagem(fileiraAuxiliar, rua);

    do
    {
        printf("Deseja efetivar? (1 - Sim | 2 - Não) -> ");
        scanf("%d", &resposta);
    }
    while(resposta != 1 && resposta != 2);

    if(resposta == 1)
    {
        for(int i = 0; i < quantidadeFileiras; i++)
        {
            rearruma(&pilha[i], rua);
        }
    }
    libera_todas_pilhas(fileiraAuxiliar);

    imprime_garagem(pilha, rua);
}
