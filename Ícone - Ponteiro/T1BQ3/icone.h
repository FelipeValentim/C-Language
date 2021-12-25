#ifndef ICONE_H_INCLUDED
#define ICONE_H_INCLUDED

typedef struct _icone
{
    short int **pixels; // matriz representando imagem do ícone
    int tamanho; // número de linhas e colunas da matriz da imagem
} Icone;

Icone *icone_cria(int tam);
//Essa função deve alocar um ícone (não se esqueça de alocar espaço para os pixels e testar se ocorreu
//erro) e retornar um ponteiro para a estrutura alocada.

void icone_libera_memoria(Icone *ic);
//Essa função deve liberar toda a memória associada ao ícone.

void icone_atribui(Icone *ic, int i, int j, int v);
//Essa função deve atribuir um valor 'v' ao elemento na posição (i, j) do ícone

int icone_acessa(Icone *ic, int i, int j);
//Essa função deve retornar o elemento na posição (i, j) do ícone

int icone_tam (Icone *ic);
//Essa função deve retornar o número de linhas e colunas do ícone

void icone_preenche_aleatorio(Icone *ic);
//Essa função deve atribuir valores “1” a pixels aleatórios do ícone.

void icone_imprime(Icone *ic);
//Essa função deve imprimir o ícone na tela de forma semelhante a um bitmap

Icone* icone_copia(Icone *ic);
//Essa função deve alocar e retornar um ícone contendo uma cópia do ícone recebido como parâmetro.

Icone* icone_rotaciona(Icone *ic1);
//Essa função deve criar um ícone (use icone_cria!) e colocar nesse ícone o resultado da rotação de ic1
//de 90 graus no sentido horário.

Icone** criar_icones(Icone **ico);

Icone** libera_memoria(Icone **ic);

void icone_preenche_usuario(Icone *ic);

Icone** mostrar_icones(Icone **ico);

Icone** add_rotaciona(Icone **ico);

int icone_simetrico(Icone *ic);

Icone **checa_simetria(Icone **ic);

Icone** add_copia(Icone **ico);

Icone** icone_remove(Icone **ico);

Icone* reajusta_icone(Icone *ico);

Icone** add_reflexo(Icone **ico);

Icone* reflexo(Icone *ico);

Icone** add_duplicado(Icone **ico);

Icone* duplica(Icone *ico, int escolha);

#endif // ICONE_H_INCLUDED
