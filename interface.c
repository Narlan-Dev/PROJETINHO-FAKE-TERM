#include "interface.h"

char interface(){

    system("cls");

    char escolha = ' ';                             //armazena esecolha do usuario
    time_t tempo;                                   //guarda segundos desde 1970
    time(&tempo);                                   //preenche a variavel segundos
    
    //equanto nao for alfabetico
    while(!isalpha(escolha)){
        
        printf("\t==============================   \n");
        printf("\t      MENU FAKE TERM.OOO         \n");
        printf("\t============================== \n\n");

        printf("\t Enter [A] -> Jogar\n");
        printf("\t Enter [B] -> Ranking\n");
        printf("\t Enter [C] -> Regras\n");
        printf("\t Enter [D] -> Sair\n\n");
    
        printf("\t==============================   \n");
        printf("\t  %s", ctime(&tempo));    //imprime data no formato clássico
        printf("\t============================== \n\n");
    
        printf("\tPor favor Enter sua escolha: ");
        
        scanf("%1c", &escolha);
            
        system("cls");

    }   

    escolha = tolower(escolha); //deixa qualquer letra minuscula

    return escolha;

    system("cls");    

}

void jogo(){
    
    int loopPrincipal = 1;                              //loop para repetir o jogo
    char arquivo[] = "palavras.txt";                    //lista de palavras
    int nPalavras = 0;                                  //numero de palavras
    int *ptr_nPalavras = &nPalavras;                    //ponteiro pro numero de palavras
    int nLetras = 0;                                    //numero de letras
    int *ptr_nLetras = &nLetras;                        //ponteiro pro numero de letras
    int loopChute = 0;                                  //matem o loop caso palavra digitada inválida
    int tentativasMax = 6;                              //numero de tentativas do jogo
    int final = 0;                                      //determina se o jogo chegou ao final
    int tentativa = 0;                                  //conta o numero da tentativa atual
    double pontos = 0;                                  //guarda pontuacao do usuario
    double *ptr_pontos = &pontos;                       //ponteiro para os pontos
    char nomeJogador[MAXLETRAS];                        //armazena nome do jogador

    //Define quantas palavras tem o .txt e o numeros de letras das palavras
    setup(arquivo, ptr_nPalavras, ptr_nLetras);
    
    char tabelaPalavra[nPalavras][nLetras];             //armazena palavras do aquivo .txt
    char palavraChave[nLetras];                         //armazena palavra sorteada do arquivo
    char chute[40];                                     //palavra chutada pelo usuário
    char resultado[nLetras];                            //resultado da igualdade de letras em fomato de simbologia
    char listaChutes[tentativasMax][nLetras];           //armazena cada chute válido do usuário
    char listaResultados[tentativasMax][nLetras];       //armazena cada simbologia de posicao das letras
    int seed = 1;                                       //define o srand da função sorteia palavra

    preencheTabela(arquivo, nPalavras, nLetras, tabelaPalavra);

    sorteiaPalavraChave(nPalavras, nLetras, tabelaPalavra, palavraChave, seed);

    atualizaTabela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, chute, resultado);
        
    imprimeTela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, pontos);

    //enquanto não der game over fica repetindo
    while(loopPrincipal != 0){
        
        atualizaTabela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, chute, resultado);

        imprimeTela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, pontos);

        //fica repetindo até terminar as tentativas ou acertar a palvra chave
        while(!final){
            
            tentativa ++; //incrementa numero de tentativas

            //equanto valida palavra retonar 0, ou seja, palavra digitada invalida
            while(loopChute == 0){

                printf(" CHUTE: ");
                scanf("%s", chute);
                loopChute = validaPalavra(nPalavras, nLetras, chute, tabelaPalavra);
            
            }

            loopChute = 0; //caso tenha uma nova tentativa, possibilida entrada no loop anterior
            
            //caso checaPalavras retorne 1, o usuario acertou a palavra chave
            final = checaPalavra(chute, palavraChave, resultado, nLetras);

            contaPontos(ptr_pontos, tentativa, final);

            atualizaTabela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, chute, resultado);

            imprimeTela(tentativa, tentativasMax, nLetras, listaChutes, listaResultados, pontos);

            //finaliza o loop caso o numero de tentativa atinja o maximo pré-definido
            if(tentativa == tentativasMax)final = 1;

        }

        //caso tenham acabado as tentativas
        if(tentativa == tentativasMax){

            //caso tenha obtido alguma pontução, pede o nome e atualiza o ranking
            if(pontos != 0 && !checaPalavra(chute, palavraChave, resultado, nLetras)){
                
                printf("\nDIGITE SEU NOME:");
                scanf("%40s", nomeJogador);
                atualizaRanking(nomeJogador, pontos);
                loopPrincipal = 0;

            }else if (pontos == 0) loopPrincipal = 0; //sem pontos = game over

        }


        //sorteia uma nova palavra chave
        seed++;
        sorteiaPalavraChave(nPalavras, nLetras, tabelaPalavra, palavraChave, seed);

        final = 0; //para que volte a entrar no while interno novamente
        tentativa = 0; //zera as tentativas

        system("pause"); //presione para continuar e fechar o programa

    }

}

void ranking(){

    system("cls");
    
    char amrNome[MAXLETRAS + 1];                                 //armazena nomes dos usuários
    char arquivoNome[] = "ranking.txt";                      //armazena nome do arquivo
    int pontos;                                             //armazena pontos

    FILE *rankingPtr;                                        //ponteiro para rakingPtr

        //caso n possa ser aberto o arquivo
        if (( rankingPtr = fopen( arquivoNome, "r")) == NULL){

            printf( "\n\tBANCO DE RANKING NAO PODE SER ABERTO\n" );

        }else{

            printf("\n\tTOP 10");
            printf("\n\tPLAYER NAME \t\t\t\t\tPONTOS\n\n");     //imprime cabecalho
            //fscanf(rankingPtr, "%s%d", amrNome, &pontos);     //escaneia e armazena .txt

            //enquanto arquivo .txt n terminar
            while(!feof(rankingPtr)){
                
                fscanf(rankingPtr, "%s %d", amrNome, &pontos);     //escaneia e armazena .txt
                printf("\t%-41s\t%-10d\n", amrNome, pontos);       //imprime .txt

            }

        }

    fclose(rankingPtr);                                       //fecha aquivo .txt

    printf("\n");
    system("pause");

}

void regras(){

    system("cls");

    printf("\t ___________R  E  G  R  A  S _____________ \n");
    printf("\t/                                         \\ \n");
    printf("\t| Ache a palavra certa em 6 tentativas, d |\n");
    printf("\t| epois de cada tentativa, as pecas mostr |\n");
    printf("\t| am o quao perto voce esta.              |\n");
    printf("\t|                                         |\n");
    printf("\t| As palavras podem ter letras repitidas. |\n");
    printf("\t|                                         |\n");
    printf("\t| [C] O R N O                             |\n");
    printf("\t|                                         |\n");
    printf("\t| A letra \"C\" faz parte da palavra e esta |\n");
    printf("\t| na posicao correta.                     |\n");
    printf("\t|                                         |\n");
    printf("\t| T E <R> N O                             |\n");
    printf("\t|                                         |\n");
    printf("\t| A letra \"R\" faz parte da palavra mas em |\n");
    printf("\t| outra posicao.                          |\n");
    printf("\t|                                         |\n");
    printf("\t| G A L H o                               |\n");
    printf("\t|                                         |\n");
    printf("\t| A letra \"O\" nao faz parte da palavra    |\n");
    printf("\t|                                         |\n");
    printf("\t| A cada acerto uma certa pontuacao eh de |\n");
    printf("\t| finida a partir do numero de tentativas |\n");
    printf("\t| , e o jogo eh reiniciado, ate perder.   |\n");
    printf("\t|                                         |\n");
    printf("\t| 1A Tentativa: 10000  pontos             |\n");
    printf("\t| 2A Tentativa: 5000   pontos             |\n");
    printf("\t| 3A Tentativa: 2000   pontos             |\n");
    printf("\t| 4A Tentativa: 800    pontos             |\n");
    printf("\t| 5A Tentativa: 200    pontos             |\n");
    printf("\t| 6A Tentativa: 100    pontos             |\n");
    printf("\t|                                         |\n");
    printf("\t| Por fim, se garantir algum ponto, antes |\n");
    printf("\t| do termino das tentativas, seu nome sera|\n");
    printf("\t| salvo na lista de raking.               |\n");
    printf("\t\\_________________________________________/\n\n");
    
    system("pause");

}
