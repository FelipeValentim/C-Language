#include <stdio.h>
#include <stdlib.h>

typedef struct numeros
{
    int valor;
    struct numeros *proximo;
}Numeros;

int indice;

Numeros* lista_cria(void);
Numeros* lista_insere (Numeros* numero, int val);
Numeros* busca_elemento(Numeros* numero, int v);
void lista_retira (Numeros* numero, int val, int tam);
void lista_libera(Numeros* numero);

//fun��o de cria��o: retorna uma lista vazia
Numeros* lista_cria(void)
{
    return NULL;
}

//inser��o no in�cio: retorna a lista atualizada
Numeros* lista_insere (Numeros* numero, int val)
{
    Numeros* novoNumero;

    Numeros* ant = NULL; //ponteiro para o primeiro elemento
    Numeros* p = numero; //ponteiro para percorrer a lista

    //procura posi��o de inser��o
    while ((p != NULL)  && (p->valor < val))
    {
        ant = p;
        p = p->proximo;
    }

    //cria novo elemento
    novoNumero = (Numeros*) malloc(sizeof(Numeros));
    novoNumero->valor = val;

    //encadeia elemento
    if (ant == NULL)  //insere o primeiro elemento
    {
        novoNumero->proximo = numero;
        numero = novoNumero;
    }
    else   //insere elemento no final da lista
    {
        novoNumero->proximo = ant->proximo;
        ant->proximo = novoNumero;
    }
    return numero;
}

Numeros* busca_elemento(Numeros* numero, int v){
    indice = 0;
    while(numero != NULL)
    {
        indice++;
        if (numero->valor == v){
            return numero;
        }
        numero = numero->proximo;
    }
    indice = 0;
    return NULL; //N�o achou o elemento
}

void lista_retira (Numeros* numero, int val, int tam)
{
    Numeros* temp1 = numero;
    Numeros* temp2;
    int contaLista = 1, conta = 1, contador = 0;

    do{
        while((temp1 != NULL) && (contaLista < tam)){
            contador++; // Contador auxiliar para remover a cada 2, 3, 4, 5, etc.
            contaLista++; // Conta a quantidade de itens da lista

            if(contador == conta){ //Checa se o contador � igual ao valor de posi��o de exclus�o. Ex: Se conta � igual a 3, o contador ir� adicionar +1, +1, +1 e a� sim passar� pelo if
                temp2 = temp1->proximo;
                temp1->proximo = temp2->proximo;
                free(temp2); //deleta temp2
                contador = 0; // Reseta contador
                tam--; // Diminui a vari�vel de tamanho da lista at� ele ser menor que contaLista
            }
            temp1 = temp1->proximo; // Passa para o pr�ximo elemento da lista
            busca_elemento(numero, val); //Busca o elemento para saber o seu �ndice
        }
        temp1 = numero; //Atualiza a lista temp1
        contaLista = 1;
        conta++; // Contador de controle para determinar se ir� remover a cada 3, 4, 5, etc. Aumenta a cada vez que percorre toda a lista
        contador = 0; // Reseta novamente o contador
    }while(indice >= conta);
}

void lista_libera(Numeros* numero){
    Numeros *p = numero, *t;
    while (p != NULL)
    {
        t = p->proximo; //guarda refer�ncia p/ pr�x. elemento
        free(p); //libera a mem�ria apontada por p
        p = t; //faz p apontar para o pr�ximo
    }
}

int main(){
    int n, m, ni, i;

    Numeros* numero;//declara uma lista n�o inicializada
    do{
        scanf("%d", &n);
        if((n > 305000) || (n < 1)){
            break;
        }
        numero = lista_cria();   //cria e inicializa lista como vazia
        for(i = 1; i <= n; i++){
            do{
                scanf("%d", &ni);
            }while((ni < 1) || (ni > 305000));
            numero = lista_insere(numero, ni);
        }

        do{
            scanf("%d", &m);
        }while((m < 1) || (m > 305000));

        lista_retira(numero, m, n);

        if(busca_elemento(numero, m) != NULL){
            printf("Y\n");
        }else{
            printf("N\n");
        }
        lista_libera(numero);
    }while(1);

    return 0;
}

