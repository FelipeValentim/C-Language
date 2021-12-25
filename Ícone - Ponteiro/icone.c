#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "icone.h"
#define BITMAP 219
#define ESPACO 255

int qtdIcones = 0, flag = 0; //Vari�vel para determinar a quantidade de icones e uma flag para malloc e realloc

Icone *icone_cria(int tam)
{
    if(tam == 0)
    {
        return NULL;
    }

    Icone *ico = (Icone*) malloc(sizeof(Icone*)); // Aloca o �cone

    if(ico == NULL)
    {
        return NULL;
    }

    ico->tamanho = tam; // Armazena o tamanho

    ico->pixels = (short int**)malloc(tam*sizeof(short int*)); //Aloca os pixels

    for(int i = 0; i < tam; i++)
    {
        ico->pixels[i] = (short int*) malloc(tam*sizeof(short int*)); // Aloca a quantidade de colunas em cada linha
    }

    return ico;
}

void icone_libera_memoria(Icone *ic)
{
    for (int i = 0; i > icone_tam(ic); i++) //Libera a mem�ria dos pixels e do �cone
    {
        free(ic->pixels[i]);
    }
    free(ic->pixels);
    free(ic);
}

void icone_atribui(Icone *ponteiro, int linha, int coluna, int valor)
{
    if((linha > ponteiro->tamanho) || (coluna > ponteiro->tamanho)) // Se a as dimens�es forem maiores que o tamanho, retorna null
    {
        return;
    }
    ponteiro->pixels[linha][coluna] = valor; //Atribui o valor no pixel de linha e coluna espec�ficados
}

int icone_acessa(Icone *ic, int i, int j)
{
    if(i > ic->tamanho || j > ic->tamanho)
    {
        return 0;
    }
    return ic->pixels[i][j]; //Retorna o pixel referente a linha e coluna especificadas
}

int icone_tam(Icone *ic)
{
    return ic->tamanho;
}

void icone_preenche_aleatorio(Icone *ic)
{
    srand(time(NULL));
    for(int i = 0; i < ic->tamanho ; i++)
    {
        for(int j = 0; j < ic->tamanho; j++)
        {
            icone_atribui(ic, i, j, rand() % 2); //Percorre todas as linhas e colunas dos pixels e armazena um valor aleat�rio entre 0 e 1
        }
    }
    printf("Atribuindo valores, aguarde!\n");
    sleep(1);
}

void icone_imprime(Icone *ic)
{
    printf("Mostrando icone %dx%d: \n", icone_tam(ic), icone_tam(ic));
    printf("\n");
    for(int i = 0; i < icone_tam(ic); i++)
    {
        for(int j = 0; j < icone_tam(ic); j++) // Percorre todos os pixels do �cone
        {
            if(icone_acessa(ic, i, j) == 1) // Acessa o icone especificado como par�metro nas linhas e colunas. E se caso o valor for igual a 1, imprime 219 (BITMAP), caso contr�rio, imprime 255 (ESPA�O VAZIO)
            {
                printf("%c", BITMAP);
            }
            else
            {
                printf("%c", ESPACO);
            }
        }
        printf("\n");
    }
    printf("\n");
}

Icone* icone_copia(Icone *ic)
{
    Icone *novoIcone = icone_cria(icone_tam(ic)); // Aloca um novo icone

    for(int i = 0; i < icone_tam(ic); i++)
    {
        for(int j = 0; j < icone_tam(ic); j++) // Percorre todos os pixels do �cone
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ic, i, j)); // Chama a fun��o icone atribui, e armazena no novo icone criado o valor do outro icone a partir do �cone acessa
        }
    }
    qtdIcones++; // Aumenta a quantidade de �cones na vari�vel global
    return novoIcone;
}

Icone* icone_rotaciona(Icone *ic1)
{
    Icone *ic2 = icone_cria(icone_tam(ic1)); // Aloca um novo �cone
    for(int i = 0; i < icone_tam(ic2); i++)
    {
        for(int j = 0; j < icone_tam(ic2); j++)
        {
            icone_atribui(ic2, i, j, icone_acessa(ic1, icone_tam(ic1)-j-1, i)); //Atribui no novo icone o valor do outro icone na ultima posi��o menos o valor da coluna - 1. O -1 � devido ao tamanho j� que um vetor come�a em 0 e termina no tamanho -1.
        }
    }
    return ic2;
}

//Fun�oes para serem feitas

void libera_memoria(Icone **ic) //Chamada de menu
{
    for(int i = 0; i < qtdIcones; i++) //Libera a memoria para cada �cone existente no programa a partir da vari�vel global
    {
        icone_libera_memoria(ic[i]);
    }
}

Icone* icone_preenche_usuario(Icone *ic) //Fun��o para preenchimento do icone de forma manual
{
    int valor;
    for(int i = 0; i < icone_tam(ic) ; i++)
    {
        for(int j = 0; j < icone_tam(ic); j++)
        {
            do
            {
                printf("Qual valor voce quer no pixel[%d][%d] -> ", i+1, j+1);
                scanf("%d", &valor);
            }
            while((valor != 0) && (valor != 1)); // N�o deixar� o usu�rio digitar valores diferentes de 0 e 1
            icone_atribui(ic, i, j, valor); //Atribui no pixel de linha e coluna no icone o valor digitado pelo usu�rio anteriormente
        }
    }
    return ic;
}

Icone** add_rotaciona(Icone **ico) //Sem uso
{
    int icone;
    printf("Qual icone deseja rotacionar?\n");
    mostrar_icones(ico);
    printf("\n-> ");
    scanf("%d", &icone);
    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); // Realoca o espa�o para um novo icone
    ico[qtdIcones] = icone_rotaciona(ico[icone-1]); // Adiciona no pr�ximo icone (qtdIcones sempre vai referenciar o pr�ximo �cone no �ndice) o novo �cone rotacionado
    qtdIcones++;

    return ico;
}

int icone_simetrico(Icone *ic)
{
    for(int i = 0; i < icone_tam(ic); i++)
    {
        for(int j = i + 1; j < icone_tam(ic); j++) // + 1 para evitar redund�ncia
        {
            if(icone_acessa(ic, i, j) != icone_acessa(ic, j, i)) // Checa se o valor da linha e coluna � igual ao valor nos �ndices contr�rios. (Ex: se pixels[0][1] � igual a pixels[1][0])
            {
                return 0; // Retorna 0 se n�o for sim�trico
            }
        }
    }
    return 1; // Retorna 1 se for sim�trico
}

Icone** add_copia(Icone **ico)
{
    int icone;
    printf("Qual �cone gostaria de copiar?\n");
    mostrar_icones(ico);
    do
    {
        printf("\n-> ");
        scanf("%d", &icone);
    }
    while((icone < 1) || (icone > qtdIcones)); // N�o deixar o usu�rio digitar um �cone inexistente

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); //Realoca o espa�o para um novo �cone
    ico[qtdIcones] = icone_copia(ico[icone-1]); // Adiciona no pr�ximo icone o novo �cone copiado. O -1 em icone � por que o primeiro �cone � 1 ao inv�s de 0 no momento do printf.
                                                // Dessa forma se o usu�rio escolher o primeiro icone (icone 1), ao inv�s de ser icone[1] ser� o icone[0]
    return ico;
}

void checa_simetria(Icone **ic) //Chamada de menu
{
    for(int i = 0; i < qtdIcones ; i++)
    {
        printf("\n|%d|\n", i+1);
        if(icone_simetrico(ic[i]) == 1) { // Se o retorno for 1. Ir� printar que � sim�trico, caso contr�rio ir� printar que n�o �, e logo abaixo da mensagem vir� o �cone printado referente ao �ndice
            printf("Simetrico? -> Sim\n");
        } else{
            printf("Simetrico? -> Nao\n");
        }
        icone_imprime(ic[i]);
    }
}

Icone** criar_icones(Icone **ico) //Chamada de menu
{
    int j, k, adicionarIcones;

    do
    {
        printf("\nQuantidade de icones para criar/adicionar -> ");
        scanf("%d", &adicionarIcones);
    }
    while(adicionarIcones < 1); // N�o deixa o usu�rio digitar 0 �cones
    printf("\n");
    if(flag == 0) // Essa flag ir� dar o malloc caso seja a primeira vez do usu�rio ao selecionar a op��o de criar �cones, caso n�o seja, ir� dar realloc
    {
        ico = (Icone**)malloc(adicionarIcones*sizeof(Icone*));
        flag = 1;
    }
    else
    {
        ico = (Icone**)realloc(ico, (adicionarIcones+qtdIcones)*sizeof(Icone*));
    }                             // adicionarIcones � referente ao valor atual que o usu�rio quer adicionar, enquanto qtdIcones � a quantidade total de �cones criados at� aquele momento. Por isso a soma


    for(int i = qtdIcones; i < qtdIcones+adicionarIcones; i++) // Vai iniciar o percurso a partir do pr�ximo �cone, caso n tenha adicionado ainda, qtdIcones � 0.
    {
        do{
            printf("Insira o tamanho do icone %d em pixels (Ex: 4, 8, 10, etc.) -> ", i+1);
            scanf("%d", &k);
        }while(k < 1);
        do
        {
            printf("Quer definir o icone %d como aleatorio ou personalizado? (1 - Aleatorio | 2 - Personalizado) -> ", i+1);
            scanf("%d", &j);
        }
        while((j != 1) && (j != 2));

        ico[i] = icone_cria(k); // Cria um novo �cone com o tamanho referente

        switch(j) // Caso o usu�rio digite 1 ir� preencher de forma aleat�rio, caso 2 o usu�rio preencher� manualmente
        {
        case 1:
            icone_preenche_aleatorio(ico[i]);
            break;
        case 2:
            icone_preenche_usuario(ico[i]);
            break;
        }
        printf("\n");
    }
    qtdIcones += adicionarIcones;
    return ico;
}

void mostrar_icones(Icone **ico) //Chamada de menu
{
    for(int i = 0; i < qtdIcones ; i++) // Ir� mostrar cada �cone referente ao indice do for
    {
        printf("\n|%d|\n", i+1);
        icone_imprime(ico[i]);
    }
}

Icone* reajusta_icone(Icone *ico) // Reajusta o �cone ap�s apagar. Caso voc� tenha, por exemplo, 3 �cones e decida apagar o primeiro, essa fun��o ir� pegar o �ltimo �cone e passar para o lugar do primeiro, para os �cones
{                                 // continuarem na ordem que estava e n�o retornar null na hora de printar eles
    Icone *novoIcone = icone_cria(icone_tam(ico)); // Cria um novo �cone no mesmo lugar do �cone excluido

    for(int i = 0; i < icone_tam(novoIcone); i++)
    {
        for(int j = 0; j < icone_tam(novoIcone); j++)
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ico, i, j)); // Armazena nesse novo �cone, o valor referente ao �ltimo �cone
        }
    }
    icone_libera_memoria(ico); // Agora libera todo o espa�o desse �ltimo �cone

    return novoIcone; // Retorna o novo icone
}

Icone** icone_remove(Icone **ico) //Chamada de menu
{
    int icone;
    printf("Qual icone gostaria de remover? ");
    mostrar_icones(ico);
    do
    {
        printf("\n-> ");
        scanf("%d", &icone);
    }
    while((icone < 1) || (icone > qtdIcones));

    qtdIcones--;

    if(qtdIcones == 0) // Um if para evitar que o programa fa�a realloc multiplicando por 0
    {
        ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*));
    }
    else
    {
        ico = (Icone**)realloc(ico, qtdIcones*sizeof(Icone*));
    }

    if(icone-1 == qtdIcones) // Caso o �cone selecionado seja o �ltimo, ele apenas ir� apagar ele j� que n�o h� problemas com retornar nulo por diminuir qtdIcones, caso n�o seja, ir� apagar e tbm fazer os reajustes
    {
        icone_libera_memoria(ico[icone-1]);
    }
    else
    {
        icone_libera_memoria(ico[icone-1]);
        ico[icone-1] = reajusta_icone(ico[qtdIcones]);
    }

    return ico;
}

Icone* reflexo(Icone *ico)
{
    int reflexo;
    Icone *novoIcone = icone_cria(icone_tam(ico)); // Aloca um novo �cone
    do
    {
        printf("Reflexo horizontal ou vertical? (1 - Horizontal | 2 - Vertical) -> ");
        scanf("%d", &reflexo);
    }
    while((reflexo != 1) && (reflexo != 2));

    if(reflexo == 1)  // Calcular reflexo horizontal
    {
        for(int i = 0; i < icone_tam(ico); i++)
        {
            for(int j = 0; j < icone_tam(ico); j++)
            {
                icone_atribui(novoIcone, i, j, icone_acessa(ico, i, icone_tam(ico)-1-j)); // Atribui no novo icone o valor do outro �cone. Com os valores da linha e coluna referentes pela �ltima coluna menos 1 menos
            }                                                                             // a quantidade de colunas que passou. Ex: Em um �cone de tamanho 6, Atribui em pixels[2][5] o valor de pixels[2][0]
        }
    }
    else  // Calcular reflexo vertical
    {
        for(int i = 0; i < icone_tam(ico); i++)
        {
            for(int j = 0; j < icone_tam(ico); j++)
            {
                icone_atribui(novoIcone, j, i, icone_acessa(ico, icone_tam(ico)-1-j, i)); // Mesma coisa do outro, por�m trocando a linha pela coluna do for para fazer o vertical
            }
        }
    }

    printf("\n|Icone nao refletido|\n"); // Imprime o �cone n�o refletido e o refletido
    icone_imprime(ico);
    printf("\n|Icone refletido|\n");
    icone_imprime(novoIcone);

    IconeSalva(novoIcone);

    return novoIcone;
}

Icone** add_reflexo(Icone **ico) //Chamada de menu
{
    int icone;
    printf("Qual icone gostaria de criar um reflexo?\n");
    mostrar_icones(ico);
    do
    {
        printf("\n-> ");
        scanf("%d", &icone);
    }
    while((icone < 1) || (icone > qtdIcones));

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); //Realoca para mais 1 �cone
    ico[qtdIcones] = reflexo(ico[icone-1]); // Armazena no pr�ximo �cone o valor refletido do �cone escolhido

    return ico;
}

Icone* duplica(Icone *ico, int escolha)
{
    int valor;
    Icone *novoIcone;
    if(escolha == 1) // Se o usu�rio escolheu a op��o de duplicar, o valor ir� ser 2 e as outras etapas ser�o feitas em base desse valor, como aloca��o e o pr�prio acesso ao �cone a ser duplicado/quadruplicado
    {
        valor = 2;
        novoIcone = icone_cria(icone_tam(ico)*valor);
    }
    else // Se escolheu a de quadruplicar ir� ser 4
    {
        valor = 4;
        novoIcone = icone_cria(icone_tam(ico)*valor);
    }
    for(int i = 0; i < icone_tam(novoIcone); i++)
    {
        for(int j = 0; j < icone_tam(novoIcone); j++)
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ico, i/valor, j/valor)); // O programa atribuir ao novo icone o valor referente a posi��o de linha e coluna divido pelo valor escolhido. Ou seja, se o usu�rio escolheu
        }                                                                       // duplicar um �cone 3x3. O programa ir� atribuir em pixels[0][0] o valor de pixels[0/2][0/2], atribuir� em pixels[0][1] o do pixels[0][1/2], sendo
    }                                                                           // que 1/2 ir� dar 0. Ou seja, ele ir� atribuir normalmente no �cone aumentado, mas ir� acessar o mesmo valor (do �cone normal) 2 ou 4 vezes (dependendo da op��o) para de fato passar para o pr�ximo

    printf("\n|Icone nao duplicado/quadruplicado|\n");
    icone_imprime(ico);
    printf("\n|Icone duplicado/quadruplicado|\n");
    icone_imprime(novoIcone);

    IconeSalva(novoIcone);

    return novoIcone;
}

Icone** add_duplicado(Icone **ico) //Chamada de menu
{
    int icone, escolha;
    printf("Qual icone gostaria de duplicar/quadruplicar?");
    mostrar_icones(ico);
    do
    {
        printf("\n-> ");
        scanf("%d", &icone);
    }
    while((icone < 1) || (icone > qtdIcones));

    do
    {
        printf("Deseja duplicar ou quadruplicar? ( 1 - Duplicar | 2 - Quadruplicar ) -> ");
        scanf("%d", &escolha);
    }
    while((escolha != 1) && (escolha != 2));

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); // Realoca o espa�o para um novo �cone

    ico[qtdIcones] = duplica(ico[icone-1], escolha); // Armazena no pr�ximo �cone o valor multiplicado do �cone escolhido e tbm passa por par�metro a escolha do usu�rio referente a duplicar e quadruplicar

    return ico;
}

void IconeSalva(Icone *novoIcone){
    int escolha;
    do
    {
        printf("Deseja salvar? ( 1 - Sim | 2 - Nao ) -> ");
        scanf("%d", &escolha);
    }
    while((escolha != 1) && (escolha != 2));

    if(escolha == 1)  // Se o usu�rio escolher salvar, ele apenas aumentar� o valor de �cones e retornar� o novo icone, caso contr�rio ir� libera o espa�o do novo �cone que j� havia sido criado
    {
        qtdIcones++;
    }
    else
    {
        icone_libera_memoria(novoIcone);
    }
}
