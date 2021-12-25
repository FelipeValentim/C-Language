/*
    @autor: Felipe;
    @data: 07/05/2021;
    @nome: Compras em Fdl;
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct loja
{
    int preco;
    struct loja *proximo;
} Loja;

Loja* loja_cria(void);
Loja* loja_insere(Loja* loja, int val);
void loja_operacao(Loja* loja, int operacao, int qtdLojas);
void loja_libera(Loja* loja);

Loja* loja_cria(void)
{
    return NULL;
}

Loja* loja_insere(Loja* loja, int val)
{
    Loja *novaLoja;

    Loja* ant = NULL; //ponteiro para o primeiro elemento
    Loja* p = loja; //ponteiro para percorrer a lista

    //procura posição de inserção
    while (p != NULL)
    {
        p = p->proximo;
    }

    //cria novo elemento
    novaLoja = (Loja*) malloc(sizeof(Loja));
    novaLoja->preco = val;

    //encadeia elemento
    if (p == NULL)  //insere o primeiro elemento
    {
        novaLoja->proximo = loja;
        loja = novaLoja;
    }
    else   //insere elemento no final da lista
    {
        novaLoja->proximo = ant->proximo;
        p->proximo = novaLoja;
    }

    return p;
}

void loja_operacao(Loja* loja, int operacao, int qtdLojas)
{
    int i, j, *precoLoja, maiorDiferenca = 0, lojaPos, loja2Pos, preco;

    Loja* temp1 = loja;
    do
    {
        scanf("%d", &lojaPos);
    }
    while((lojaPos < 1) || (lojaPos > qtdLojas));

    if(operacao == 1)  // Checa se a operação é 1 ou 2
    {
        do
        {
            scanf("%d", &preco);
        }
        while((preco < 1) || (preco > 100000));

        for(i = 0; i < lojaPos-1; i++)
        {
            temp1 = temp1->proximo; //Vai passando para o próximo até encontrar a loja requerida
        }
        temp1->preco = preco; //Altera o valor da loja dada como parâmetro
        return;

    }
    else
    {
        do
        {
            scanf("%d", &loja2Pos); //Lê a posição da segunda loja
        }
        while((loja2Pos < lojaPos) || (loja2Pos > qtdLojas));
        precoLoja = (int*)malloc((loja2Pos-lojaPos+1)*sizeof(int));

        for(i = 0; i < lojaPos-1; i++)  // vai passando até  chegar na primeira loja
        {
            temp1 = temp1->proximo;
        }
        for(i = 0; i <= loja2Pos-lojaPos; i++)  // Percorre a quantidade sobrando de posições na lista (Ex: Se é loja 1 e 3, ele vai dar mais 2 next)
        {
            precoLoja[i] = temp1->preco;
            temp1 = temp1->proximo;
        }
        for(i = 0; i <= loja2Pos-lojaPos; i++)  // Compara cada um da diferença dos preços em absoluto (positivo) para saber qual o maior
        {
            for(j = 1+i; j <= loja2Pos-lojaPos; j++)
            {
                if(maiorDiferenca < abs(precoLoja[i]-precoLoja[j])) //Compara a diferença atual com a maior diferença anterior
                {
                    maiorDiferenca = abs(precoLoja[i]-precoLoja[j]);
                }
            }
        }
        printf("%d\n", maiorDiferenca);
        free(precoLoja);
        return;
    }
}

void loja_libera(Loja* loja)
{
    Loja *p = loja, *t;
    while (p != NULL)
    {
        t = p->proximo; //guarda referência p/ próx. elemento
        free(p); //libera a memória apontada por p
        p = t; //faz p apontar para o próximo
    }
}

void imprime(Loja* loja){
    while(loja){
        printf("\n%d\n", loja->preco);
        loja = loja->proximo;
    }
}

int main ()
{
    int n, precoLoja, i, q, operacao;
    Loja* loja;
    do
    {
        do
        {
            scanf("%d", &n);
        }
        while(n > 100000);

        if(n < 1)
        {
            break;
        }

        loja = loja_cria();

        for(i = 1; i <= n; i++)
        {
            do
            {
                scanf("%d", &precoLoja);
            }
            while((precoLoja > 100000) || (precoLoja < 1));
            loja = loja_insere(loja, precoLoja);
        }
        imprime(loja);
        scanf("%d", &q);
        for(i = 0; i < q; i++)
        {
            do
            {
                scanf("%d", &operacao);
            }
            while((operacao != 1) && (operacao != 2));
            loja_operacao(loja, operacao, n);
        }
        loja_libera(loja);
    }
    while(n != EOF);

    return 0;
}
