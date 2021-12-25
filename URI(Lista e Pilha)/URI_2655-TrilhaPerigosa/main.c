#include <stdio.h>
#include <stdlib.h>

typedef struct monstros
{
    int tipoMonstro;
    struct monstros *proximo;
} Monstros;

Monstros* monstro_cria(void);
Monstros* monstro_insere(Monstros* monstro, int tipoMonstro);
int monstro_operacao_busca(Monstros* monstro, int cord1, int qtdLocalizacoes);
void monstro_operacao_troca(Monstros* monstro, int cord1);
void monstro_libera(Monstros* monstro);

Monstros* monstro_cria(void)
{
    return NULL;
}

Monstros* monstro_insere(Monstros* monstro, int tipoDoMonstro)
{
    Monstros *novoMonstro;

    Monstros* ant = NULL; //ponteiro para o primeiro elemento
    Monstros* p = monstro; //ponteiro para percorrer a lista

    //procura posição de inserção
    while (p != NULL)
    {
        ant = p;
        p = p->proximo;
    }

    //cria novo elemento
    novoMonstro = (Monstros*) malloc(sizeof(Monstros));
    novoMonstro->tipoMonstro = tipoDoMonstro;

    //encadeia elemento
    if (ant == NULL)  //insere o primeiro elemento
    {
        novoMonstro->proximo = monstro;
        monstro = novoMonstro;
    }
    else   //insere elemento no final da lista
    {
        novoMonstro->proximo = ant->proximo;
        ant->proximo = novoMonstro;
    }

    return monstro;
}

int monstro_operacao_busca(Monstros* monstro, int cord1, int qtdLocalizacoes)
{
    int qtdMonstrosDif = 1, cord2, monstroTemp, i;
    Monstros* temp1 = monstro;

    do
    {
        scanf("%d", &cord2);
    }
    while((cord2 < cord1) || (cord2 > qtdLocalizacoes));
    for(i = 0; i < cord1-1; i++)  // vai passando até  chegar na primeira loja
    {
        temp1 = temp1->proximo;
    }
    monstroTemp = temp1->tipoMonstro;

    for(i = 0; i <= cord2-cord1; i++)  // Percorre a quantidade sobrando de posições na lista (Ex: Se é loja 1 e 3, ele vai dar mais 2 next)
    {
        if(monstroTemp != temp1->tipoMonstro)
        {
            qtdMonstrosDif++;
        }
        temp1 = temp1->proximo;
    }
    return qtdMonstrosDif;
}

void monstro_operacao_troca(Monstros* monstro, int cord1)
{
    int monstroTemp, i;
    Monstros* temp1 = monstro;
    scanf("%d", &monstroTemp);
    for(i = 0; i < cord1-1; i++)
    {
        temp1 = temp1->proximo; //Vai passando para o próximo até encontrar a loja requerida
    }
    temp1->tipoMonstro = monstroTemp; //Altera o valor da loja dada como parâmetro
}

void monstro_libera(Monstros* monstro)
{
    Monstros *p = monstro, *t;
    while (p != NULL)
    {
        t = p->proximo; //guarda referência p/ próx. elemento
        free(p); //libera a memória apontada por p
        p = t; //faz p apontar para o próximo
    }
}

int main()
{
    Monstros* monstro;
    int tamanhoEstrada, quantidadeOperacoes, monstrosConhecidos, tipoMonstro, i, operacao, monstrosDiferentes, cord1;
    do
    {
        scanf("%d", &tamanhoEstrada);
    }
    while(tamanhoEstrada < 1);

    do
    {
        scanf("%d", &quantidadeOperacoes);
    }
    while((quantidadeOperacoes < 1) || (quantidadeOperacoes > 100000));

    do
    {
        scanf("%d", &monstrosConhecidos);
    }
    while((monstrosConhecidos < 1) || (monstrosConhecidos > 50));

    monstro = monstro_cria();
    for(i = 0; i < tamanhoEstrada; i++)
    {
        do
        {
            scanf("%d", &tipoMonstro);
        }
        while((tipoMonstro > monstrosConhecidos) || (tipoMonstro < 1));
        monstro = monstro_insere(monstro, tipoMonstro);
    }

    for(i = 0; i < quantidadeOperacoes; i++)
    {
        do
        {
            scanf("%d", &operacao);
        }
        while((operacao != 1) && (operacao != 2));

        do
        {
            scanf("%d", &cord1);
        }
        while((cord1 < 1) || (cord1 > tamanhoEstrada));

        if(operacao == 1)
        {
            monstrosDiferentes = monstro_operacao_busca(monstro, cord1, tamanhoEstrada);
            printf("%d\n", monstrosDiferentes);
        }
        else
        {
            monstro_operacao_troca(monstro, cord1);
        }
    }
    monstro_libera(monstro);

    return 0;
}
