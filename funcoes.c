#include "funcoes.h"

void setup(char nomeDoArquivo[], int *palavras, int *letras){

  char tempString[40] = {0}; //string temporaria a qual armazena palavra do .txt

  FILE *bancoPalavras;

    //caso o .txt nao possa ser aberto
    if ( ( bancoPalavras = fopen( nomeDoArquivo, "r" ) ) == NULL ){

      printf( "BANCO DE PALAVRAS NAO PODE SER ABERTO\n" );

    }else{
      
      fscanf(bancoPalavras, "%d", palavras); //definiu a quantidade de palavras
      fscanf(bancoPalavras, "%s", tempString); //armazenou uma palavra do .txt em tempString

      int i=0; //loop para definir o numero de caracteres
      for(i=0; tempString[i] != '\0';i++){
      }
  
      *letras = i+1; //uma coluna a mais pra caber o '\0' de fim de string
    
    }
  
  fclose(bancoPalavras); //fecha arquivo .txt

}

void preencheTabela(char nomeDoArquivo[], int palavras, int letras, char tabela[][letras]){
  
  int linha, coluna;        //contadores
  char tempString[letras];  //armazena cada palavra do .txt
  
  FILE *bancoPalavras;

    //caso o .txt nao possa ser aberto
    if ( ( bancoPalavras = fopen( nomeDoArquivo, "r" ) ) == NULL ){
    
      printf( "BANCO DE PALAVRAS NAO PODE SER ABERTO\n" );

    }else{
      
      fscanf(bancoPalavras,"%d", tempString); //armazenou uma palavra do .txt em tempString

      //pecorre cada linha do .txt
      for(linha=0; linha < palavras; linha++ ){

        fscanf(bancoPalavras,"%s", tempString); //armazenou uma palavra do .txt em tempString

        //transfere carcteres da temString, incluindo '\0', para tabela de palavras na linha definida
        for(coluna = 0; coluna <= letras;coluna++){

          tabela[linha][coluna] = tempString[coluna];

        }

      }

    }

  fclose(bancoPalavras); //fechar arquivo .txt

}

int validaPalavra(int palavras, int letras, char chute[], char tabelaPalavras[][letras]){
  
  int letrasIguais = 0;  //Contador de letras iguais
  int c;                 //Contador pros For
  int strings = 0;       //Conta numero de palavras
  

  //conta o quantas letras digitadas
  for(c = 0; chute[c] != '\0'; c++){
  }

  //caso seja mais que as palavras do .txt
  if(c != letras - 1){
    
    printf("APENAS %d LETRAS!!\n", letras - 1);
      
    return 0; //Palavra digitada inválida

  }

  //Verifica se todos caracter são alfabéticos
  for(c = 0; chute[c] != '\0'; c++){
    
    //Caso isalph falso, existe diferente de alfabético
    if(!isalpha(chute[c])){
      
      printf("APENAS CARACTERES ALFABETICOS!!\n");
      
      return 0; //Palavra digitada inválida
      
    }
    
  }
  
  //Transforma letras maiuculas em minusculas
  for(c = 0; chute[c] != '\0'; c++){
    
    chute[c] = tolower(chute[c]);
    
  }
  
  //Enquanto haver palavras
  while(strings < palavras){
    
    //Verifica se palavra na linha da tabela eh igual ao chute
    for(c = 0; tabelaPalavras[strings][c] != '\0'; c++){
      
      //Caso uma letra seja diferente, a palavra eh diferente
      if(tabelaPalavras[strings][c] != chute[c]){
        
        letrasIguais = 0; //Zera contador de letras iguais
        strings++; //Incrementa strings     
        break; //Para o loop e vai pra proxima palavra do arquivo
        
       //Caso letras sejam iguais 
      }else{
        
        letrasIguais++; //Incrementa 1
        
      }
      
    }
    
    //Se todas letras forem iguas/palavras iguais são iguais
    if(letrasIguais != 0){
      
      return 1; //palavra igual encontrada
      
    }
    
  }
  
  printf("PALAVRA INVALIDA!!\n");
  
  return 0; //Palavra digitada inválida
  
}

void sorteiaPalavraChave(int palavras, int letras, char tabelaPalavras[][letras], char palavraSecreta[], int seed){
  
  int indicePalavraChave; //linha do arquivo de palavras sorteada para na qual pegar a palavra chave
  
  /*
   * time(NULL) retorna segundos desde 01/01/1970
   * time(NULL)/(24*3600) - ((2022 - 1970)*365) - (2022 - 1970)/4 = dia do ano
   * 
   */
  //int semente = (int) (time(NULL)/(24*3600) - ((2022 - 1970)*365) - (2022 - 1970)/4);
  srand(seed);
  indicePalavraChave = rand()%palavras + 1;

  //transfere palavra sorteiada da tabela de palavras para a string palavra secreta
  for(int coluna = 0; coluna <= letras; coluna++){

    palavraSecreta[coluna] = tabelaPalavras[indicePalavraChave][coluna];
  
  }
  
}

void atualizaTabela(int tentativa, int tentativaMax, int letras, char listaChutes[][letras], char listaResultados[][letras], char chute[], char resultado[]){

  //se nao tiver nenhuma tentativa
  if(tentativa == 0){
      
    /*2 for aninhados para percorrer toda string bidimensional
    definindo cada posicao das duas listas como "*" */
    for(int linha = 0; linha < tentativaMax; linha++){
      
      for(int coluna = 0; coluna < letras - 1; coluna++){

        listaChutes[linha][coluna] = '*';
        listaResultados[linha][coluna] = '*';

      }
        
      listaChutes[linha][letras - 1] = '\0'; //define ultima posicao como terminador de string
      listaResultados[linha][letras - 1] = '\0'; //define ultima posicao como terminador de string         

    }

  }else{
      
    for(int coluna = 0; coluna < letras - 1; coluna++ ){

      listaChutes[(tentativa) - 1][coluna] = chute[coluna];
      listaResultados[(tentativa) - 1][coluna] = resultado[coluna];
    
    }

  }

}

void imprimeTela(int tentativa, int tentativasMax, int letras, char listaChutes[][letras], char listaResultados[][letras], double pontos){

  int contaLetrasCorretas = 0; //conta o numero de letras com posicao igual as da palavra chave

  system("cls");
  printf("\n");
  printf("=FAKE TERM.OOO=\t     __________L  E  G  E  N  D  A____________ \n"); //cabecalho do jogo

  /*2 for aninhados para percorrer toda string bidimensional
  verificando cada simbologia armazenada na lista de resultados*/
  for (int c = 0; c < tentativasMax; c++){
        
    for(int i=0; i < letras - 1; i++){
            
      if (listaResultados[c][i]=='!'){ 
      
        printf("<%c>", listaChutes[c][i]);

      }else if (listaResultados[c][i]=='$'){
      
        printf("[%c]", listaChutes[c][i]);
        contaLetrasCorretas++; //incrementa letras iguais

      }else{

        printf(" %c ", listaChutes[c][i]);

      }
            
    }

    //caso o chute nao tenha todas letras iguais a palavra chave
    if(contaLetrasCorretas != letras - 1){

      //zera o contador
      contaLetrasCorretas = 0;

    }
    
    //imprime a legenda para o jogo
    if (c==0) printf("\t    /                                         \\ ");
    if (c==1) printf("\t    | \"[a]\" - contem a letra nesta posicao.   |");
    if (c==2) printf("\t    | \"<a>\" - contem a letra noutra posicao.  |");
    if (c==3) printf("\t    | \" a \" - nao contem a letra.             |");
    if (c==4) printf("\t    \\_________________________________________/");
    if (c==5) printf("\t      Pontos: %.0lf", pontos);
    printf("\n"); //quebra de linha

  }

  //se o as todo chute estiver correto
  if(contaLetrasCorretas == letras - 1)printf("   PARABENS\n");

  //caso seja a ultima tentativa e nao acertou a palavra chave
  if(tentativa == tentativasMax && contaLetrasCorretas != letras - 1)printf("   GAME OVER\n");

}

int checaPalavra(char chute[], char palavraSecreta[], char resultado[], int letras){

  char copiaSecreta[letras - 1];    //armazena palavra secreta
  char copiaChute[letras - 1];      //armazena palavra secreta
  int i, c;                         //Contadores
  int letraIdentica = 0;            //contador de letras identicas

  /*Transfere palavra secreta e o chute para as strings copia
  define cada posicao do resultado como "*" */
  for(i = 0; i < letras - 1; i++){

    copiaSecreta[i] = palavraSecreta[i];
    copiaChute[i]  = chute[i];
    resultado[i] = '*';

  }

  for(i = 0; i < letras - 1; i++){

    for(c = 0; c < letras - 1; c++){

      //se achar caracter igual e posicao igual
      if(copiaChute[i] == copiaSecreta[c] && i == c){

        resultado[i] = '$';         //caracter na posicao correta
        letraIdentica++;            //conta caracters com mesma posicao
        copiaSecreta[c] = '*';      //nao testa a letra novamente
        copiaChute[i] = '!';        //nao testa a letra novamente     

      }
    
    }
  
  }

  for(i = 0; i < letras - 1; i++){

    for(c = 0; c < letras - 1; c++){

      //se achar caracter igual e posicao diferente
      if(copiaChute[i] == copiaSecreta[c] && i != c){

        resultado[i] = '!';          //caracter na posicao errada
        copiaSecreta[c] = '*';       //nao testa a letra novamente
        copiaChute[i] = '!';         //nao testa a letra novamente

      }
    
    }
  
  }

  if(letraIdentica == letras - 1)return 1; //todas letras iguais e na posicao correta
  else return 0; //todas letras nao sao iguais ou nao estao na posicao correta

}

void contaPontos(double *pontos, int tentativa, int final){

  double parametro = 0.999;         //parametro que subitrai o valor da tentativa
  double parametro2 = 4;            //parametro que soma o valor obtido do log     
  double baseLog = 0.5;             //define a base do log com 1/2
  double constante = 1125;          //constante multiplicativa
  
  /*se nao acertar a palavra secreta retorna 0, se acertar 
  calcula os pontos, de acordo com a tentativa com o 
  parametro multiplicativo da funcao log, e 
  incrementa nos pontos anteriores*/
  if(final != 0)*pontos = *pontos + ((log2(tentativa - parametro)/log2(baseLog)) + parametro2) * constante;

}