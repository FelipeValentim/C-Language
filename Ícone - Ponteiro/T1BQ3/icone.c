#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include "icone.h"
#define BITMAP 219
#define ESPACO 255

int qtdIcones = 0, flag = 0; //Variável para determinar a quantidade de icones e uma flag para malloc e realloc

Icone *icone_cria(int tam)
{
    if(tam == 0)
    {
        return NULL;
    }

    Icone *ico = (Icone*) malloc(sizeof(Icone*)); // Aloca o ícone

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
    for (int i = 0; i > icone_tam(ic); i++) //Libera a memória dos pixels e do ícone
    {
        free(ic->pixels[i]);
    }
    free(ic->pixels);
    free(ic);
}

void icone_atribui(Icone *ponteiro, int linha, int coluna, int valor)
{
    if((linha > ponteiro->tamanho) || (coluna > ponteiro->tamanho)) // Se a as dimensões forem maiores que o tamanho, retorna null
    {
        return;
    }
    ponteiro->pixels[linha][coluna] = valor; //Atribui o valor no pixel de linha e coluna específicados
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
            icone_atribui(ic, i, j, rand() % 2); //Percorre todas as linhas e colunas dos pixels e armazena um valor aleatório entre 0 e 1
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
        for(int j = 0; j < icone_tam(ic); j++) // Percorre todos os pixels do ícone
        {
            if(icone_acessa(ic, i, j) == 1) // Acessa o icone especificado como parâmetro nas linhas e colunas. E se caso o valor for igual a 1, imprime 219 (BITMAP), caso contrário, imprime 255 (ESPAÇO VAZIO)
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
        for(int j = 0; j < icone_tam(ic); j++) // Percorre todos os pixels do ícone
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ic, i, j)); // Chama a função icone atribui, e armazena no novo icone criado o valor do outro icone a partir do ícone acessa
        }
    }
    qtdIcones++; // Aumenta a quantidade de ícones na variável global
    return novoIcone;
}

Icone* icone_rotaciona(Icone *ic1)
{
    Icone *ic2 = icone_cria(icone_tam(ic1)); // Aloca um novo ícone
    for(int i = 0; i < icone_tam(ic2); i++)
    {
        for(int j = 0; j < icone_tam(ic2); j++)
        {
            icone_atribui(ic2, i, j, icone_acessa(ic1, icone_tam(ic1)-j-1, i)); //Atribui no novo icone o valor do outro icone na ultima posição menos o valor da coluna - 1. O -1 é devido ao tamanho já que um vetor começa em 0 e termina no tamanho -1.
        }
    }
    return ic2;
}

//Funçoes para serem feitas

Icone** libera_memoria(Icone **ic) //Chamada de menu
{
    for(int i = 0; i < qtdIcones; i++) //Libera a memoria para cada ícone existente no programa a partir da variável global
    {
        icone_libera_memoria(ic[i]);
    }
    return ic;
}

void icone_preenche_usuario(Icone *ic) //Função para preenchimento do icone de forma manual
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
            while((valor != 0) && (valor != 1)); // Não deixará o usuário digitar valores diferentes de 0 e 1
            icone_atribui(ic, i, j, valor); //Atribui no pixel de linha e coluna no icone o valor digitado pelo usuário anteriormente
        }
    }
}

Icone** add_rotaciona(Icone **ico) //Sem uso
{
    int icone;
    printf("Qual icone deseja rotacionar?\n");
    mostrar_icones(ico);
    printf("\n-> ");
    scanf("%d", &icone);
    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); // Realoca o espaço para um novo icone
    ico[qtdIcones] = icone_rotaciona(ico[icone-1]); // Adiciona no próximo icone (qtdIcones sempre vai referenciar o próximo ícone no índice) o novo ícone rotacionado
    qtdIcones++;

    return ico;
}

int icone_simetrico(Icone *ic)
{
    for(int i = 0; i < icone_tam(ic); i++)
    {
        for(int j = i + 1; j < icone_tam(ic); j++) // + 1 para evitar redundância
        {
            if(icone_acessa(ic, i, j) != icone_acessa(ic, j, i)) // Checa se o valor da linha e coluna é igual ao valor nos índices contrários. (Ex: se pixels[0][1] é igual a pixels[1][0])
            {
                return 0; // Retorna 0 se não for simétrico
            }
        }
    }
    return 1; // Retorna 1 se for simétrico
}

Icone** add_copia(Icone **ico)
{
    int icone;
    printf("Qual ícone gostaria de copiar?\n");
    mostrar_icones(ico);
    do
    {
        printf("\n-> ");
        scanf("%d", &icone);
    }
    while((icone < 1) || (icone > qtdIcones)); // Não deixar o usuário digitar um ícone inexistente

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); //Realoca o espaço para um novo ícone
    ico[qtdIcones] = icone_copia(ico[icone-1]); // Adiciona no próximo icone o novo ícone copiado. O -1 em icone é por que o primeiro ícone é 1 ao invés de 0 no momento do printf.
                                                // Dessa forma se o usuário escolher o primeiro icone (icone 1), ao invés de ser icone[1] será o icone[0]
    return ico;
}

Icone **checa_simetria(Icone **ic) //Chamada de menu
{
    for(int i = 0; i < qtdIcones ; i++)
    {
        printf("\n|%d|\n", i+1);
        if(icone_simetrico(ic[i]) == 1) { // Se o retorno for 1. Irá printar que é simétrico, caso contrário irá printar que não é, e logo abaixo da mensagem virá o ícone printado referente ao índice
            printf("Simetrico? -> Sim\n");
        } else{
            printf("Simetrico? -> Nao\n");
        }
        icone_imprime(ic[i]);
    }
    return ic;
}

Icone** criar_icones(Icone **ico) //Chamada de menu
{
    int j, k, adicionarIcones;

    do
    {
        printf("\nQuantidade de icones para criar/adicionar -> ");
        scanf("%d", &adicionarIcones);
    }
    while(adicionarIcones < 1); // Não deixa o usuário digitar 0 ícones
    printf("\n");
    if(flag == 0) // Essa flag irá dar o malloc caso seja a primeira vez do usuário ao selecionar a opção de criar ícones, caso não seja, irá dar realloc
    {
        ico = (Icone**)malloc(adicionarIcones*sizeof(Icone*));
        flag = 1;
    }
    else
    {
        ico = (Icone**)realloc(ico, (adicionarIcones+qtdIcones)*sizeof(Icone*));
    }                             // adicionarIcones é referente ao valor atual que o usuário quer adicionar, enquanto qtdIcones é a quantidade total de ícones criados até aquele momento. Por isso a soma


    for(int i = qtdIcones; i < qtdIcones+adicionarIcones; i++) // Vai iniciar o percurso a partir do próximo ícone, caso n tenha adicionado ainda, qtdIcones é 0.
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

        ico[i] = icone_cria(k); // Cria um novo ícone com o tamanho referente

        switch(j) // Caso o usuário digite 1 irá preencher de forma aleatório, caso 2 o usuário preencherá manualmente
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

Icone** mostrar_icones(Icone **ico) //Chamada de menu
{
    for(int i = 0; i < qtdIcones ; i++) // Irá mostrar cada ícone referente ao indice do for
    {
        printf("\n|%d|\n", i+1);
        icone_imprime(ico[i]);
    }
    return ico;
}

Icone* reajusta_icone(Icone *ico) // Reajusta o ícone após apagar. Caso você tenha, por exemplo, 3 ícones e decida apagar o primeiro, essa função irá pegar o último ícone e passar para o lugar do primeiro, para os ícones
{                                 // continuarem na ordem que estava e não retornar null na hora de printar eles
    Icone *novoIcone = icone_cria(icone_tam(ico)); // Cria um novo ícone no mesmo lugar do ícone excluido

    for(int i = 0; i < icone_tam(novoIcone); i++)
    {
        for(int j = 0; j < icone_tam(novoIcone); j++)
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ico, i, j)); // Armazena nesse novo ícone, o valor referente ao último ícone
        }
    }
    icone_libera_memoria(ico); // Agora libera todo o espaço desse último ícone

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

    if(qtdIcones == 0) // Um if para evitar que o programa faça realloc multiplicando por 0
    {
        ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*));
    }
    else
    {
        ico = (Icone**)realloc(ico, qtdIcones*sizeof(Icone*));
    }

    if(icone-1 == qtdIcones) // Caso o ícone selecionado seja o último, ele apenas irá apagar ele já que não há problemas com retornar nulo por diminuir qtdIcones, caso não seja, irá apagar e tbm fazer os reajustes
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
    int reflexo, escolha;
    Icone *novoIcone = icone_cria(icone_tam(ico)); // Aloca um novo ícone
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
                icone_atribui(novoIcone, i, j, icone_acessa(ico, i, icone_tam(ico)-1-j)); // Atribui no novo icone o valor do outro ícone. Com os valores da linha e coluna referentes pela última coluna menos 1 menos
            }                                                                             // a quantidade de colunas que passou. Ex: Em um ícone de tamanho 6, Atribui em pixels[2][5] o valor de pixels[2][0]
        }
    }
    else  // Calcular reflexo vertical
    {
        for(int i = 0; i < icone_tam(ico); i++)
        {
            for(int j = 0; j < icone_tam(ico); j++)
            {
                icone_atribui(novoIcone, j, i, icone_acessa(ico, icone_tam(ico)-1-j, i)); // Mesma coisa do outro, porém trocando a linha pela coluna do for para fazer o vertical
            }
        }
    }

    printf("\n|Icone nao refletido|\n"); // Imprime o ícone não refletido e o refletido
    icone_imprime(ico);
    printf("\n|Icone refletido|\n");
    icone_imprime(novoIcone);

    do
    {
        printf("Deseja salvar? ( 1 - Sim | 2 - Nao ) -> ");
        scanf("%d", &escolha);
    }
    while((escolha != 1) && (escolha != 2));
    if(escolha == 1) // Se o usuário escolher salvar, ele apenas aumentará o valor de ícones e retornará o novo icone, caso contrário irá libera o espaço do novo ícone que já havia sido criado
    {
        qtdIcones++;
        return novoIcone;
    }
    else
    {
        icone_libera_memoria(novoIcone);
    }
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

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); //Realoca para mais 1 ícone
    ico[qtdIcones] = reflexo(ico[icone-1]); // Armazena no próximo ícone o valor refletido do ícone escolhido

    return ico;
}

Icone* duplica(Icone *ico, int escolha)
{
    int valor;
    Icone *novoIcone;
    if(escolha == 1) // Se o usuário escolheu a opção de duplicar, o valor irá ser 2 e as outras etapas serão feitas em base desse valor, como alocação e o próprio acesso ao ícone a ser duplicado/quadruplicado
    {
        valor = 2;
        novoIcone = icone_cria(icone_tam(ico)*valor);
    }
    else // Se escolheu a de quadruplicar irá ser 4
    {
        valor = 4;
        novoIcone = icone_cria(icone_tam(ico)*valor);
    }
    for(int i = 0; i < icone_tam(novoIcone); i++)
    {
        for(int j = 0; j < icone_tam(novoIcone); j++)
        {
            icone_atribui(novoIcone, i, j, icone_acessa(ico, i/valor, j/valor)); // O programa atribuir ao novo icone o valor referente a posição de linha e coluna divido pelo valor escolhido. Ou seja, se o usuário escolheu
        }                                                                       // duplicar um ícone 3x3. O programa irá atribuir em pixels[0][0] o valor de pixels[0/2][0/2], atribuirá em pixels[0][1] o do pixels[0][1/2], sendo
    }                                                                           // que 1/2 irá dar 0. Ou seja, ele irá atribuir normalmente no ícone aumentado, mas irá acessar o mesmo valor (do ícone normal) 2 ou 4 vezes (dependendo da opção) para de fato passar para o próximo

    printf("\n|Icone nao duplicado/quadruplicado|\n");
    icone_imprime(ico);
    printf("\n|Icone duplicado/quadruplicado|\n");
    icone_imprime(novoIcone);

    do
    {
        printf("Deseja salvar? ( 1 - Sim | 2 - Nao ) -> ");
        scanf("%d", &escolha);
    }
    while((escolha != 1) && (escolha != 2));

    if(escolha == 1)  // Se o usuário escolher salvar, ele apenas aumentará o valor de ícones e retornará o novo icone, caso contrário irá libera o espaço do novo ícone que já havia sido criado
    {
        qtdIcones++;
        return novoIcone;
    }
    else
    {
        icone_libera_memoria(novoIcone);
    }
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

    ico = (Icone**)realloc(ico, (qtdIcones+1)*sizeof(Icone*)); // Realoca o espaço para um novo ícone

    ico[qtdIcones] = duplica(ico[icone-1], escolha); // Armazena no próximo ícone o valor multiplicado do ícone escolhido e tbm passa por parâmetro a escolha do usuário referente a duplicar e quadruplicar

    return ico;
}
