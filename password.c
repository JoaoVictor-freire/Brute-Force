#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_LETRAS 26
#define ASCII_A 65
#define QUANT_PROC 10

char* encrypt(const char* str, int tamanho) {
    char* str_result = (char*) malloc(sizeof(char)*tamanho);
    for (int i = 0; i < tamanho; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            int chave = str[i] - ASCII_A;
            str_result[i] = (str[i] - ASCII_A + chave) % NUM_LETRAS + ASCII_A;
        }
    }
    return str_result;
}


int main(void){
    int origin_pid;
    int *clone_pid;
    int index = -1;

    origin_pid = getpid(); // Armazenando o pid do processo original
    clone_pid = (int*) malloc(sizeof(int) * QUANT_PROC); // criando um array para os pid's dos processos que serão criados


    //Fazendo a clonagem de processos onde apenas o processo pai se clona e armazenando o indice de cada processo filho.
    for(int i = 0; i < QUANT_PROC; i++){

        if(origin_pid == getpid()){
            clone_pid[i] = fork();
            if(getpid() != origin_pid){
                index = i;
                break;
            } 
        }

    }
  

    if(getpid() != origin_pid){

        char encrypted[QUANT_PROC][5];
        char teste[] = {"AAAA"};
        char way_proc[50];

        //Passando para o 'way_proc' o caminho até chegar no arquivo, o sprintf faz com que cada processo pegue o arquivo referente ao sei index.
        sprintf(way_proc, "/home/joaovf/Documents/senhas/encrypted/%d.txt", index);

        //Abrindo o arquivo txt e verificando se ele foi corretamente lido.
        FILE* password = fopen(way_proc, "r");
        if(password == NULL){
            fprintf(stderr, "Erro ao abrir arquivo %s.\n", way_proc);
        }

        //Lendo as strings do arquivo enquanto não for o final do mesmo, e armazenando as mesmas no Array 'encrypted'
       int n = 0;
       while(!feof(password)){
        fscanf(password, "%s", encrypted[n]);
        n++;
       }

        char result[5]; //variavel criada para guardar a string 'teste' após ser encryptada
    
        /*
            Este laço duplo de for ira percorrer todas as Strigns do meu array 'encrypted' -> referente ao valor 'i'.
            A váriavel 'k' serve para indicar em qual indice estamos da string, por isso ela encerra quando k = 4. Pois se k = 4 já encontramos a senha desencryptada.
            Por fim, o laço que usa a váriavel 'j' servirá para percorrer a ASCII list de 'A' até 'Z'.
        */
        int k = 0;
        for(int i = 0; i < QUANT_PROC; i++){

            for(int j = 0; j < 26; j++){

                strcpy(result, encrypt(teste,5)); //encryptando a cada repetição, pois a string 'teste' está mudando o valor de seus indices até achar o correto.

                if(result[k] == encrypted[i][k]){
                    encrypted[i][k] = teste[k]; // Alocando as letras desencryptadas no local onde elas estavam encryptadas
                    k++; // Passa para o próximo indice
                    j = 0; // Volta a testar todas a letras, começando do 'A'
                }else{
                teste[k] += 1; // Passando de 'A' à 'Z'
                }

                if(k == 4) break;

            }
  
            //resetando a string 'teste' e a variável 'k' para podermos recomeçar na string seguinte.
            k = 0;
            strcpy(teste, "AAAA");
        }

        usleep(index * 10000); //fazendo que cada processo espere para que o processo anterior exiba primeiro.
        for(int i = 0; i < QUANT_PROC; i++){
            printf("[File %d] -> Encrypted key: %s / Decrypted key: %s\n", index ,encrypt(encrypted[i], 5), encrypted[i]);
            if(i == 9) printf("\n");
        }
        
        
        fclose(password);
    
    }

    if(getpid() == origin_pid) sleep(1); // Processo original espera 1 segundo para que dê tempo dos filhos printarem na tela.

    free(clone_pid);
    return 0;
}