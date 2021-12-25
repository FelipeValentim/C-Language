#ifndef ICONE_H_INCLUDED
#define ICONE_H_INCLUDED

typedef struct _icone
{
    short int **pixels; // matriz representando imagem do �cone
    int tamanho; // n�mero de linhas e colunas da matriz da imagem
} Icone;

Icone *icone_cria(int tam);
//Essa fun��o deve alocar um �cone (n�o se esque�a de alocar espa�o para os pixels e testar se ocorreu
//erro) e retornar um ponteiro para a estrutura alocada.

void icone_libera_memoria(Icone *ic);
//Essa fun��o deve liberar toda a mem�ria associada ao �cone.

void icone_atribui(Icone *ic, int i, int j, int v);
//Essa fun��o deve atribuir um valor 'v' ao elemento na posi��o (i, j) do �cone

int icone_acessa(Icone *ic, int i, int j);
//Essa fun��o deve retornar o elemento na posi��o (i, j) do �cone

int icone_tam (Icone *ic);
//Essa fun��o deve retornar o n�mero de linhas e colunas do �cone

void icone_preenche_aleatorio(Icone *ic);
//Essa fun��o deve atribuir valores �1� a pixels aleat�rios do �cone.

void icone_imprime(Icone *ic);
//Essa fun��o deve imprimir o �cone na tela de forma semelhante a um bitmap

Icone* icone_copia(Icone *ic);
//Essa fun��o deve alocar e retornar um �cone contendo uma c�pia do �cone recebido como par�metro.

Icone* icone_rotaciona(Icone *ic1);
//Essa fun��o deve criar um �cone (use icone_cria!) e colocar nesse �cone o resultado da rota��o de ic1
//de 90 graus no sentido hor�rio.

Icone** criar_icones(Icone **ico);

void libera_memoria(Icone **ic);

Icone* icone_preenche_usuario(Icone *ic);

void mostrar_icones(Icone **ico);

Icone** add_rotaciona(Icone **ico);

int icone_simetrico(Icone *ic);

void checa_simetria(Icone **ic);

Icone** add_copia(Icone **ico);

Icone** icone_remove(Icone **ico);

Icone* reajusta_icone(Icone *ico);

Icone** add_reflexo(Icone **ico);

Icone* reflexo(Icone *ico);

Icone** add_duplicado(Icone **ico);

Icone* duplica(Icone *ico, int escolha);

void IconeSalva(Icone *ico);

#endif // ICONE_H_INCLUDED
