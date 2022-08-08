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

#define CTRS 24

char alfabeto[27] = "abcdefghijklmnopqrstuvwxyz";
char alfabetoM[27] = {"ABCDEFHIJKLMNOPQRSTUVWXYZ"};

typedef struct array{
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
        
		random[i] = rand() % limite; // sorteia um n�mero
        igual = 0;
        for(j = 0; j < i; j++){ // percorre a parte do vetor j� preenchida
            if(random[j] == random[i])
                igual = 1; // n�mero repetido
        }

        if(igual == 0) // significa que o elemento n�o se repetiu
            i++;
    }while(i < limite); // enquanto n�o for sorteado n�meros diferentes

	return random[indice];
}

//Verifica se a letra informada ja foi usada anteriormente
int verificar(char letra, array papel[],int limite ){
	
	for(int i = 0;i <= limite;i++){
		if(letra == papel[i].letra){
			return -1;
		}
	}
	return 0;
}

//Funcao para deixar a palavra em minusculo
char minus(char palavra[]){
	int i = 0;
	int largura = ( sizeof palavra ) / ( sizeof palavra[0] );
	
	for(i = 0; i < largura+1; i++){
		
		palavra[i] = tolower(palavra[i]);
			
	}
	
}

char tabela(char letra, array *papel, int param){

}

int main(){
	//Declaracao das variaveis
	int random, resp, auxInt, i;
	int rodada = 0;
	char auxC[7],auxS[CTRS];
	
	array papel[26];
	
	while(rodada == 0){
		//Reinicializacao das variaveis
		resp = 0;
		auxInt = 0;
		
		printf("Escolha: \n 1-Sortear a letra.\n 2-Digitar a letra.\n");
		scanf("%d",&resp);
		fflush(stdin);
		
		//Opcao responsavel por sortear a letra a ser usada na rodada
		if(resp == 1){
			
			do{
				random = aleatorio(rodada,26);  //A funcao aleatorio(indice,max) retorna um numero aleatorio, o 'int random' recebe o numero gerado
				auxC[0] = alfabeto[random]; //A variavel 'letra' recebe a letra que esta na posicao indice 'random'
				//memcpy(letra, &alfabeto[1], 1);
				
				auxC[0] = toupper(auxC[0]);
				
				auxInt = verificar(auxC[0], papel, rodada);
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
				
				auxC[0] = toupper(auxC[0]);
				
				auxInt = verificar(auxC[0], papel, rodada);
				
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
		
		system("pause");
		system("cls");
		
		printf("\nTabela:\n\n 1-Nome:\n\n 2-Cor:\n\n 3-Comida:\n\n 4-Objeto:\n\n 5-Animal:\n\n 6-CEP:\n\n 7-Famoso:\n\n 8-FSN:\n\n");
		printf("%c",papel[rodada].letra);
		
		printf("Digite a categoria ou numero a ser preenchida: ");
		gets(auxC); //Leitura da classe/numero
		fflush(stdin);
		
		//Condicao para preencher o campo de Nome
		if(strcmp(auxC, "nome") == 0 || auxC == "1"){
			
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].nome, auxS);
		}
		//Condicao para preenche o campo de Cor
		else if(strcmp(auxC, "cor") == 0 || auxC == "2"){
			
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].cor, auxS);	
		}
		//Condicao para preenche o campo de Comida
		else if(strcmp(auxC, "comida") == 0 || auxC == "3"){
			
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
		
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].comida, auxS);	
		}
		
		//Condicao para preenche o campo de Objeto
		else if(strcmp(auxC, "objeto") == 0 || auxC == "4"){
			
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].objeto, auxS);
		}
		
		//Condicao para preenche o campo de Animal
		else if(strcmp(auxC, "animal") == 0 || auxC == "5"){
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].animal, auxS);
		}
		
		//Condicao para preenche o campo de CEP
		else if(strcmp(auxC, "cep") == 0 || auxC == "6"){
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].cep, auxS);
		}
		//Condicao para preenche o campo de Famoso
		else if(strcmp(auxC, "famoso") == 0 || auxC == "7"){
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].famoso, auxS);
		}
		//Condicao para preenche o campo de F.S.N
		else if(strcmp(auxC, "fsn") == 0 || auxC == "8"){
			printf("%s >>",auxC);
			gets(auxS); //Leitura do substantivo
			
			
			while(toupper(auxS[0]) != papel[rodada].letra){
				printf("\nPalavra com letra nao correspondente!");
				scanf("%s",auxS);
				fflush(stdin);
			}
			
			strcpy(papel[rodada].fsn, auxS);
		}
		else{
			printf("Essa categoria nao existe!");
		}
		
		printf("Digitaste: %s, %s", auxC, auxS);
			
		rodada++;
	}
	
	return 0;
}

