//AtividadeSortion
#include <stdio.h>
#include <string.h>

//cadastro com nome, idade e sexo.
//opções de ordenar por nome, idade ou sexo

#define MAX_CHAR 100
#define MAX 10

typedef struct pessoas{
    char nome[MAX_CHAR];
    int idade;
    char sexo;
} Pessoas;

int intercalar(Pessoas vetor[], int ini, int meio, int fim, int *global) {
    
    Pessoas auxiliar[MAX]; // vetor auxiliar
    int i = ini, j = meio + 1, k = 0; // índices dos vetores
    
    // intercala
    while(i <= meio && j <= fim) {
        switch(*global){
            case 1:
                int verifica;
                
                for(int n=0; vetor[i].nome[n]!='\0' || vetor[j].nome[n]!='\0';
                    n++){
                    if( *(vetor[i].nome+n) > *(vetor[j].nome+n) ){
                        verifica=0;
                        break;
                    } 
                    if( *(vetor[j].nome+n) > *(vetor[i].nome+n) ){
                        verifica=1;
                        break;
                    } 
                }
                
                if (verifica)
                    auxiliar[k++] = vetor[i++];
                else
                    auxiliar[k++] = vetor[j++];
            break;
            case 2:
                if (vetor[i].idade <= vetor[j].idade)
                    auxiliar[k++] = vetor[i++];
                else
                    auxiliar[k++] = vetor[j++];
            break;
            case 3:
                if (vetor[i].sexo <= vetor[j].sexo)
                    auxiliar[k++] = vetor[i++];
                else
                    auxiliar[k++] = vetor[j++];
            break;
            default:
            break;
        }
    }
    
    // copia resto de cada subvetor
    while (i <= meio) auxiliar[k++] = vetor[i++];
    while (j <= fim) auxiliar[k++] = vetor[j++];
    
    // copia de auxiliar para vetor
    for (i = ini, k=0; i <= fim; i++, k++)
    vetor[i] = auxiliar[k];
}

void ordenar_intercalacao(Pessoas vetor[], int ini, int fim, int *global) {
    int meio;
    if (ini < fim) {
        meio = (ini + fim) / 2;
        ordenar_intercalacao(vetor, ini, meio, global);
        ordenar_intercalacao(vetor, meio + 1, fim, global);
        intercalar(vetor, ini, meio, fim, global);
    }
}

int main() {
    Pessoas cadastrados[6];
    int opcao, *global;
    for(int i =0; i<6; i++){
        
        printf("\n-------Cadastro %i-------\n",i+1);
        printf("\nNome: ");
        fgets(cadastrados[i].nome, MAX_CHAR, stdin);
        
        //Deixa maiuscula a Inicial do nome
        if(*cadastrados[i].nome >= 97) *cadastrados[i].nome -= 32;
        
        //Pesquisei na internet a forma mais simples de retirar o \n
        strtok(cadastrados[i].nome, "\n");
        
        printf("Idade: ");
        scanf("%i", &cadastrados[i].idade);
        getchar();
        
        printf("Sexo (M/F): ");
        scanf("%c", &cadastrados[i].sexo);
        if(cadastrados[i].sexo >= 97) cadastrados[i].sexo -= 32;
        getchar();
    }

    while(1){
        printf("\n------Digite a Opção Desejada--------\n");
        printf("\n(1)Ordenar por nome\n");
        printf("(2)Ordenar por Idade\n");
        printf("(3)Ordenar por Sexo\n");
        printf("Qual deseja?\n -: ");
        scanf("%i",&opcao);
        printf("\n");
        
        if(opcao<1 || opcao>3){
            printf("\nVocê saiu!");
            break;
        }
        global = &opcao;
        
        ordenar_intercalacao(cadastrados, 0, 5, global);
        
        for(int i=0;i<6;i++){
            printf("-|-: %s, %i, %c\n",
                   cadastrados[i].nome,
                   cadastrados[i].idade,
                   cadastrados[i].sexo);
        }
    }
    return 0;
}