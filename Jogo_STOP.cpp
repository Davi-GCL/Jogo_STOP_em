/*Jogo STOP Multiplayer local:
Tera uma tela de menu principal com selecao de 3 opcoes: 1-jogar, 2-regras ou 3-Sair
O usuario podera digitar o numero da opcao ou escrever a palavra chave

Depois de selecionar '1-jogar', exibira uma tela com opcoes de sortear uma letra ou entrar com uma letra escolhida
Em cada partida, a letra usada sera armazenada em uma array, e serao mostrados como letras ja usadas

Durante a partida o jogador devera preencher os campos, com o tipo de palavra INICIADA PELA LETRA ESCOLHIDA ou com 0, para as desconhecidas
Se for escrito uma palavra com a inicial diferente da LETRA, sera pedido que escreva novamente

TABELA:
  nome
  cor
  comida
  objeto
  animal
  cep
  famoso
  fsn

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <locale.h>

#define CTRS 24

char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz";
char alfabetoM[27] = {"ABCDEFHIJKLMNOPQRSTUVWXYZ"};

typedef struct array{
	int pass[8];
	char letra;
	char nome[CTRS], cor[CTRS], comida[CTRS], objeto[CTRS], animal[CTRS], cep[CTRS], famoso[CTRS], fsn[CTRS];	
	
}array;

//Funcao de gerar numero aleatorios nao repetidos
int aleatorio(int indice,int limite){	//(indice do vetor, numero maximo a ser gerado)
	int random[limite];
	int j, igual;
	int aux = 0;
    int i = 0;
	 
    srand(time(NULL));/*Funcao que define uma regra(semente) para a gerecao de numeros procedurais
    				  A funcao 'srand' esta recebendo o valor de 'time(NULL)' como parametro usado como semente
    				  A funcao 'time(NULL)' gera um numero diferente a cada inicializacao do programa
    				  (retorna o tempo, contado em segundos, desde 01/01/1970)
    				  */

    do{ //Executa o algoritmo pelo menos uma vez antes de verificar a condicao do 'while'
        
		random[i] = rand() % limite; // sorteia um número
        igual = 0;
        for(j = 0; j < i; j++){ // percorre a parte do vetor já preenchida
            if(random[j] == random[i])
                igual = 1; // número repetido
        }

        if(igual == 0) // significa que o elemento não se repetiu
            i++;
    }while(i < limite); // enquanto não for sorteado números diferentes

	return random[indice];
}

//Verifica se a letra informada ja foi usada anteriormente
int verificarHist(char letra, array papel[],int rodada){
	
	for(int i = 0;i <= rodada;i++){
		if(letra == papel[i].letra){
			return -1;
		}
	}
	return 0;
}

//Funcao para verificar se a palavra digitada e valida
int verificarVal(char auxS[], array papel[], int rodada){
	
	while(toupper(auxS[0]) != toupper(papel[rodada].letra) && strcmp(auxS, "0") != 0){
		printf("\nPalavra com letra nao correspondente!");
		gets(auxS);
		fflush(stdin);
	}
	
}

int verificarIndex(int index, array papel[], int rodada){
	int resultado = 0;

	for(int i = 0; i < 8; i++){
		if(index == papel[rodada].pass[i]){  //Se o index passado JA tiver sido passado para o vetor, sai da funcao retornando o valor 1
			resultado = 1; 
		}
	}
	
	//Se o index passado NUNCA tiver sido passado para o vetor, adiciona esse valor ao vetor na posicao correspondente('index 1' na posicao 1)	
	papel[rodada].pass[index] = index;
	
	return resultado;
}

//Função que mostra a tela do menu
int telaMenu(){
	int menu = 0;
	
	//system("color C7");
	system("cls");
	
	printf("\n");
	printf("\t\t");
	printf(" SSSSS  TTTTTTT  OOOOO  PPPPPP  \n");
	printf("\t\t");
	printf("SS        TTT   OO   OO PP   PP \n");
	printf("\t\t");
	printf(" SSSSS    TTT   OO   OO PPPPPP  \n");
	printf("\t\t");
	printf("     SS   TTT   OO   OO PP      \n");
	printf("\t\t");
	printf(" SSSSS    TTT    OOOO0  PP     \n");
	
	
	printf("                                      \n");
	printf("                     	 ______ \n");
	printf("                    	| MENU |\n");
	printf("                    	|______|\n");
	printf("                                      \n");
	
	printf("          	 __________________________ \n");
	printf("          	|    1 - INICIAR O JOGO    |\n");
	printf("          	|__________________________|\n");
	
	printf("          	 __________________________ \n");
	printf("          	|    2 - REGRAS            |\n");
	printf("          	|__________________________|\n");
	
	printf("          	 __________________________ \n");
	printf("          	|    3 - CRÉDITOS          |\n");
	printf("          	|__________________________|\n");
	
	printf("          	 __________________________ \n");
	printf("          	|    4 - FECHAR O JOGO     |\n");
	printf("          	|__________________________|\n");
	
	printf("\n>> ");
	scanf("%d",&menu);
	fflush(stdin);
	
	return menu;
}

int main(){
	//Declaracao das variaveis
	int random, resp, auxInt, i;
	int rodada = 0, menu = 0;
	char auxC[7], auxS[CTRS];
	
	array papel[26];
	
	setlocale(LC_ALL,"portuguese");
	
	while(menu != 4){
		//https://www.alura.com.br/artigos/limpando-lixo-da-memoria-em-c
		memset(&papel, 0, sizeof(papel));	//(&variavel, 0, sizeof(SUA_STRUCT))
				
		menu = telaMenu();
		
		if(menu == 1){
			//Iniciando o jogo
			while(rodada <= 1){
				//Reinicializacao das variaveis
				resp = 0;
				auxInt = 0;
				
				system("cls");
				printf("Escolha: \n 1-Sortear a letra.\n 2-Digitar a letra.\n");
				scanf("%d",&resp);
				fflush(stdin);
				
				//Opcao responsavel por sortear a letra a ser usada na rodada
				if(resp == 1){
					
					do{
						random = aleatorio(rodada,26);  //A funcao aleatorio(indice,max) retorna um numero aleatorio, o 'int random' recebe o numero gerado
						auxC[0] = alfabeto[random]; //A variavel 'letra' recebe a letra que esta na posicao indice 'random'
						//memcpy(letra, &alfabeto[1], 1);				
						
						auxInt = verificarHist(auxC[0], papel, rodada);
						//printf("%d\n",auxInt);
						
						if(auxInt == 0){
							papel[rodada].letra = auxC[0];
							printf("\n LETRA SORTEADA: %c \n",papel[rodada].letra);
						}
		
						
					}while(auxInt!= 0);
		
				}
				//Opcao que recebe a letra digitada
				else if(resp == 2){
						
					do{
						auxInt = 0;
						
						printf("Digite a letra a ser usada: ");
						scanf("%s",auxC);
						fflush(stdin);
						
						auxInt = verificarHist(auxC[0], papel, rodada);
						
						if(auxInt == -1){
							printf("Essa letra ja foi usada!\n ");					
						}
						
						papel[rodada].letra = auxC[0];
						
					}while(auxInt != 0);
					
				}
				//Opcao de retornar para o menu
				else{
					break;
				}
				auxInt = 0;
				i = 0;
				
				//Laco de repeticao para iterar em cada formulario
				while(i < 8){
				
					system("pause");
					system("cls");
					
					printf("Apenas palavras com: %c",papel[rodada].letra);
					printf("\nTabela:\n\n 1-Nome:%s\n\n 2-Cor:%s\n\n 3-Comida:%s\n\n 4-Objeto:%s\n\n 5-Animal:%s\n\n 6-CEP:%s\n\n 7-Famoso:%s\n\n 8-FSN:%s\n\n", papel[rodada].nome, papel[rodada].cor, papel[rodada].comida, papel[rodada].objeto, papel[rodada].animal, papel[rodada].cep, papel[rodada].famoso, papel[rodada].fsn);
					
					//Leitura da categoria/numero
					printf("\nDigite a categoria ou numero a ser preenchida: ");
					gets(auxC); 
					//scanf()
					fflush(stdin);
					
					//Condicao para preencher o campo de Nome
					if(strcmp(auxC, "nome") == 0 || strcmp(auxC, "1") == 0){
						
						printf("Nome >>");
						gets(auxS); //Leitura do substantivo
						//scanf("%23[^\n]s",&auxS);
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						strcpy(papel[rodada].nome, auxS);
						
						//Verifica se essa categoria ja foi modificada antes, fazendo com oque as iteracoes so sejam contadas para categorias modificadas uma vez
						if(verificarIndex(0, papel, rodada) == 0){
							i++; 
						}
					}
					//Condicao para preenche o campo de Cor
					else if(strcmp(auxC, "cor") == 0 || strcmp(auxC, "2") == 0){
						
						printf("Cor >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].cor, auxS);	
						
						
						
						if(verificarIndex(1, papel, rodada) == 0){
							i++;
						}
					}
					//Condicao para preenche o campo de Comida
					else if(strcmp(auxC, "comida") == 0 || strcmp(auxC, "3") == 0){
						
						printf("Comida >>",auxC);
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
					
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].comida, auxS);
						
						if(verificarIndex(2, papel, rodada) == 0){
							i++;
						}	
					}
					
					//Condicao para preenche o campo de Objeto
					else if(strcmp(auxC, "objeto") == 0 || strcmp(auxC, "4") == 0){
						
						printf("Objeto >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].objeto, auxS);
						
						if(verificarIndex(3, papel, rodada) == 0){
							i++;
						}
					}
					
					//Condicao para preenche o campo de Animal
					else if(strcmp(auxC, "animal") == 0 || strcmp(auxC, "5") == 0){
						printf("Animal >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].animal, auxS);
						
						if(verificarIndex(4, papel, rodada) == 0){
							i++;
						}
					}
					
					//Condicao para preenche o campo de CEP
					else if(strcmp(auxC, "cep") == 0 || strcmp(auxC, "6") == 0){
						printf("CEP >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].cep, auxS);
						
						if(verificarIndex(5, papel, rodada) == 0){
							i++;
						}
					}
					//Condicao para preenche o campo de Famoso
					else if(strcmp(auxC, "famoso") == 0 || strcmp(auxC, "7") == 0){
						printf("Famoso >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].famoso, auxS);
		
						if(verificarIndex(6, papel, rodada) == 0){
							i++;
						}
					}
					//Condicao para preenche o campo de F.S.N
					else if(strcmp(auxC, "fsn") == 0 || strcmp(auxC, "8") == 0){
						printf("F.S.N >>");
						gets(auxS); //Leitura do substantivo
						fflush(stdin);
						
						verificarVal(auxS, papel, rodada);
						
						strcpy(papel[rodada].fsn, auxS);
						
						if(verificarIndex(7, papel, rodada) == 0){
							i++;
						}
					}
					else{
						printf("Essa categoria nao existe!");
					}
					
					printf("Digitaste: %s, %s", auxC, auxS);
					
				}
				
				rodada++;
			}
		}
		else if(menu == 2){
			//Regras
			
		}
		else if(menu == 3){
			//Creditos
			system("cls");
			printf("\n Desenvolvedor: Davi Gabriel \n");
			system("pause");
		}
		else{
			//Sair do jogo
			printf("Saindo do jogo...");
		}
		
	}

	return 0;
}

