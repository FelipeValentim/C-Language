#include <stdio.h>
#include <stdlib.h>
#include "icone.c"

int main()
{
    Icone **ico;
    int opt = 0;
    do{
        do{
            printf("O que deseja fazer?\n");
            printf("1- Criar novos icones\n");
            printf("2- Mostrar icones\n");
            printf("3- Remover icone\n");
            printf("4- Criar reflexo do icone\n");
            printf("5- Copiar icone\n");
            printf("6- Adicionar duplica/quadruplica\n");
            printf("7- Checar simetria dos icones\n");
            printf("8- Sair\nEscolha -> ");
            scanf("%d", &opt);
            system("cls");
            if((qtdIcones < 1 ) && (opt != 1)  && (opt > 1) && (opt < 8)){ //Apenas visual
                printf("Sem icones registrados. Adicione pelo menos um!\n\n"); //Printa a mensagem caso selecione uma das op��es que envolve a exist�ncia de pelo menos um icone
            }
        }while((qtdIcones < 1) && (opt != 1) && (opt != 8)); //Loop que repete at� que o usu�rio adicione pelo menos 1 icone
        switch(opt)
        {
        case 1:
            ico = criar_icones(ico);
            break;
        case 2:
            mostrar_icones(ico);
            break;
        case 3:
            ico = icone_remove(ico);
            break;
        case 4:
            ico = add_reflexo(ico);
            break;
        case 5:
            ico = add_copia(ico);
            break;
        case 6:
            ico = add_duplicado(ico);
            break;
        case 7:
            checa_simetria(ico);
            break;
        case 8:
            libera_memoria(ico);
            exit(0);
        }
    } while(opt != 8);
    return 0;
}
