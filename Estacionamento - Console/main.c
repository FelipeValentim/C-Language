#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.c"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op;

    do
    {
        printf("Diga a quantidade fileiras no estacionamento -> ");
        scanf("%d", &quantidadeFileiras);
    }
    while(quantidadeFileiras < 1);

    Pilha *estacionamento = (Pilha*)malloc((qtdVagasFileira)*sizeof(Pilha));
    Carro* rua = lista_cria();

    do
    {
        printf("Diga a quantidade de vagas em cada fileira no estacionamento -> ");
        scanf("%d", &qtdVagasFileira);
    }
    while(qtdVagasFileira < 1);


    do
    {
        printf("Diga a quantidade de carros na rua (no mínimo igual ao de vagas na fileira) -> ");
        scanf("%d", &qtdVagasRua);
    }
    while(qtdVagasRua < qtdVagasFileira);

    cria_pilhas(estacionamento);

    system("cls");
    do
    {
        printf("[1] - Inserir carro\n");
        printf("[2] - Mostrar garagem\n");
        printf("[3] - Retirar carro\n");
        printf("[4] - Rearrumação\n");
        printf("\nResposta -> ");
        scanf("%d", &op);
        getchar();
        system("cls");
        switch(op)
        {
        case 1:
            insere_carro(estacionamento, rua);
            break;
        case 2:
            imprime_garagem(estacionamento, rua);
            break;
        case 3:
            retira_carro_sem_sequencia(estacionamento, rua);
            break;
        case 4:
            rearruma_garagem(estacionamento, rua);
            break;
        }
    }
    while(op != 6);
    libera_todas_pilhas(estacionamento);
    return 0;
}
