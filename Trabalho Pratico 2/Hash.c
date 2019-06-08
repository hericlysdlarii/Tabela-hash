#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tamHashT 101

typedef struct{
    char *Key;
} TabelaHash;

TabelaHash *criaTabela(const int Tamanho);
int Calculo(char *Key);
int calculaHash(char *Key);
int Colisoes(TabelaHash *tabela, char *Key);
void Inserir(TabelaHash *tabela, char *Key);
void Remover(TabelaHash *tabela, char *Key);
void Listar(FILE *Saida, TabelaHash *tabela, const int Tamanho);


int main(int argc, char const *argv[]){
    TabelaHash *Objeto;
    FILE *Entrada = fopen(argv[1], "r");
    FILE *Saida = fopen(argv[2], "w");

    int Teste, Linhas;
    char *flag = (char *)calloc(sizeof(char), 15);

    fscanf(Entrada, "%d", &Teste);
    printf(">> %d\n", Teste);
    for (int k = 0; k < Teste; k++){
        Objeto = criaTabela(tamHashT);
        fscanf(Entrada, "%d", &Linhas);
        for (int l = 0; l < Linhas; l++){
            fscanf(Entrada, "%s", flag);
            if (flag[0] == 'A'){
                Inserir(Objeto, &(flag[4]));
            }
            else{
                Remover(Objeto, &(flag[4]));
            }
        }
        Listar(Saida, Objeto, tamHashT);
    }

    fclose(Saida);
    fclose(Entrada);
    free(Objeto);

    return 0;
}

TabelaHash *criaTabela(const int Tamanho){
    TabelaHash *Temp = (TabelaHash *)calloc(sizeof(TabelaHash), Tamanho);

    for (int init = 0; init < Tamanho; init++){
        Temp[init].Key = (char *)calloc(sizeof(char), 15);
    }
    return Temp;
}

int Calculo(char *Key){
    int aux = 0;

    for (int i = 1; i <= strlen(Key); i++){
        aux += Key[i - 1] * i;
    }

    return aux * 19;
}

int calculaHash(char *Key){
    return Calculo(Key) % tamHashT;
}

int Colisoes(TabelaHash *tabela, char *Key){

    int hash, conta = 1;

    for (int i = 0; i <= 20; i++){
        hash = Calculo(Key) + (conta * conta) + (23 * conta);
        hash = hash % tamHashT;

        if (strlen(tabela[hash].Key) == 0){
            return hash;
        }
    }
    return -1; //Erro!
}

void Inserir(TabelaHash *tabela, char *Key){
    int hash = calculaHash(Key);

    if (strlen(tabela[hash].Key) == 0){
        strcpy(tabela[hash].Key, Key);
    }else if (strcmp(tabela[hash].Key, Key) == 0){
		puts("Key já inserida!");
   		}else{
   			hash = Colisoes(tabela, Key);
       	if (hash != (-1)){
            strcpy(tabela[hash].Key, Key);
        }
    }
}

void Remover(TabelaHash *tabela, char *Key){
    int hash = calculaHash(Key);

    if (strlen(tabela[hash].Key) != 0){
        if (strcmp(tabela[hash].Key, Key) == 0){
            printf("%s - Encontrado!\n", Key);
            strcpy(tabela[hash].Key, "");
            return;
        }else{
            int hash, conta = 1;

            for (int i = 0; i <= 20; i++){
                hash = Calculo(Key) + (conta * conta) + (23 * conta);
                hash = hash % tamHashT;

                if (strcmp(tabela[hash].Key, Key) == 0){
                    printf("%s - Encontrado!\n", Key);
                    strcpy(tabela[hash].Key, "");
                    return;
                }
            }
        }
    }

    printf("%s - Não existe!\n", Key);
    return;
}

void Listar(FILE *Saida, TabelaHash *tabela, const int Tamanho){
    int Count = 0;
    for (int i = 0; i < Tamanho; i++)
        if (strlen(tabela[i].Key) != 0)
            Count++;

    fprintf(Saida, "%d\n", Count);

    for (int i = 0; i < Tamanho; i++)
        if (strlen(tabela[i].Key) != 0)
            fprintf(Saida, "%d:%s\n", i, tabela[i].Key);
}
