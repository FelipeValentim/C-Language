#ifndef ESTACIONAMENTO_H_INCLUDED
#define ESTACIONAMENTO_H_INCLUDED
#define FALSE 0
#define TRUE 1

int quantidadeFileiras, qtdVagasRua, qtdVagasFileira, indexSequencia = FALSE;

typedef struct carro
{
    char placa[8];
    int prev_retirada;
    struct carro *proximo;
} Carro;

typedef struct pilha  // Faz o controle
{
    Carro *topo;
} Pilha;

Carro* lista_cria(void);
void pilha_cria(Pilha* p);
void pilha_push(Pilha* p, char* placa, int prev_retirada);
void pilha_pop(Pilha *p);
void cria_pilhas(Pilha* pilha);
void imprime_carro(Pilha* pilha);
void imprime_rua(Carro* rua);
void imprime_garagem(Pilha *pilha, Carro* rua);
int conta_fileira(Pilha* p);
int conta_carros(Pilha* pilha);
int previsao_retirada(Pilha* pilha);
int busca_recomendado(Pilha* pilha, Carro* rua);
Carro* apaga_ultimo(Carro* rua);
int procura_placa(Pilha* fileira, char* placa, int retorno);
int percorre_fileiras(Pilha* fileira, char* placa);
void insere_carro(Pilha* pilha, Carro* rua);
int busca_indice(Pilha* pilha, char* placa);
void imprime_sequencia(Pilha* pilha, Carro* rua);
void carro_remove(Pilha *fileira, Carro* rua, char* placa, Pilha *pilha);
void push_copia(Pilha* pilha1, Pilha* pilha2);
void libera_pilha(Pilha* fileira);
void libera_todas_pilhas(Pilha* fileira);
void retira_carro_sem_sequencia(Pilha* pilha, Carro* rua);
void retira_carro_com_sequencia(Pilha* pilha, Carro* rua);
Carro* rearruma_rua(Carro* lista, char* placa, int prev_retirada);
void rearruma(Pilha* fileira, Carro* rua);
void rearruma_garagem(Pilha* pilha, Carro* rua);


#endif // ESTACIONAMENTO_H_INCLUDED
