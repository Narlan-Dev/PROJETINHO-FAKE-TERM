#include "ranking.h"
void atualizaRanking(char novoNome[MAXLETRAS], double novoPonto){
  

  char arquivoNome[] = "ranking.txt";                      //armazena nome do arquivo
  int linha = 0;

  char listaNomes[11][MAXLETRAS+1] = {0};
  //adiciona o nome novo no final da lista de nomes
  strcpy(listaNomes[10], novoNome);

  int listaPontos[11];

  //o mesmo pra lista de pontuacoes
  listaPontos[10] = novoPonto;
  
  
  FILE *rankingPtr;
  
  char stringBuffer[MAXLETRAS+1];
  int intBuffer = 0;
  
  //com 'r+' abre tanto pra leitura quanto pra escrita
  if (( rankingPtr = fopen( arquivoNome, "r+")) == NULL){
      
      printf( "\n\tBANCO DE RANKING NAO PODE SER ABERTO\n" );
    
  }else{
      while(!feof(rankingPtr))  {
          fscanf(rankingPtr,"%s", stringBuffer);
            strcpy(listaNomes[linha], stringBuffer);
      
            fscanf(rankingPtr," %d", &intBuffer);
            listaPontos[linha] = intBuffer;
            
            linha++;
            
        }

        //volta pro inicio do arquivo antes das
        //operacoes de escrita
        rewind(rankingPtr);
        

        
        // loop para comparar as pontuacoes de duas em duas
        //e colocar maior na frente
        for (int i = 0; i < 11; i++){
            for (int j = i+1; j < 11; j++){
                if(listaPontos[i]<listaPontos[j]){
                    //coloca a pontuacao maior na frente
                    intBuffer=listaPontos[i];
                    listaPontos[i]=listaPontos[j];
                    listaPontos[j]=intBuffer;

                    //troca os nomes pra acompanhar os pontos
                    strcpy(stringBuffer, listaNomes[i]);
                    strcpy(listaNomes[i], listaNomes[j]);
                    strcpy(listaNomes[j], stringBuffer);
                }
            }
        }
        //sobreescreve o ranking.txt com as 10 pontuações mais altas da maior pra menor
        for(linha = 0; linha < 9; linha++) fprintf(rankingPtr,"%s %d\n", listaNomes[linha], listaPontos[linha]);
        fprintf(rankingPtr,"%s %d", listaNomes[9], listaPontos[9]);
        
        fclose(rankingPtr);
        
    }
  }