#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Jogo para teste de memória
		- Entrada: semente para função aleatória e dificuldade do jogo (Fácil, Intermediário ou Avançado)
		- São mostrados vetores com números aleatórios para o jogador, com número e tamanho variando com a dificuldade. O jogador então
		deve, após o vetor ser apagado da tela, reproduzi-lo. Recebendo uma pontuação pelo acerto ou erro.
*/

//		Funções de manipulação do array dado
	//Recebem: tamanho e ponteiro pro array já alocado
	void arrayCreation(int size, int* array)
	{	//Coloca dentro do array os números aleatórios
		for (int i = 0; i < size; i++)
			array[i] = rand() % 10;
	}

	void arrayRead(int size, int* array)
	{	//Lê o array digitado
		for (int i = 0; i < size; i++)
			scanf("%d", &array[i]);
	}

	void arrayPrint(int size, int* array)
	{	//Escreve o array na tela
		for (int i = 0; i < size; i++)
			printf("%d ", array[i]);
	}

	int arrayCompare(int size, int* array1, int* array2)
	{	//Compara os dois arrays e retorna a quantidade de diferenças
		int diff = 0;
		for (int i = 0; i < size; i++)
		{
			if(array1[i] != array2[i])
				diff++;
		}
		return diff;
	}

//		Função de manipulação de tempo e console
	void waitAndErase(int seconds, int spaces)
	{	//Recebe um tempo em segundos e quantidade de espaços, após o tempo, apaga a quantidade de espaços dada
					fflush(stdout);

					printf("\r");

					for(int i = 0; i < spaces; i++)
						printf(" ");

					sleep(seconds);

					printf("\r");
	}

//		Função de manipulação de pontos
	int scoreSet(int maxScore, int numFail)
	{	//Recebe a pontuação máxima da rodada e o numero de erros, calcula e retorna a pontuação
		if(maxScore >= 10 * numFail)
		{
			maxScore -= 10 * numFail;
		}else
			maxScore = 0;
		return maxScore;
	}

//		Funções de acerto e erro
	int wrongAnswer(int currentScore, int maxScore, int chancesLeft)
	{	//Recebe pontuação atual e máxima da rodada e chances que faltam
		//Calcula chances que faltam e pontuação até agora
		printf("\nIncorreto!\n");
		chancesLeft -= 1;
		printf("Tentativas disponiveis: %d\n", chancesLeft);
		printf("Pontuacao: %d\n", currentScore + maxScore);
		return chancesLeft;
	}

	int correctAnswer(int currentScore, int maxScore, int chancesLeft)
	{	//Recebe pontuação atual e máxima da rodada e chances que faltam
		//Calcula a pontuação do jogador
		printf("\nCorreto!\n");
		printf("Tentativas disponiveis: %d\n", chancesLeft);
		currentScore += maxScore;
		printf("Pontuacao: %d\n", currentScore);
		return currentScore;
	}

//		Função do Game Loop
	void gameLoop(int* array1, int* array2, int size, int waitTime, int games)
	{	//Recebe ponteiros pros arrays usados no jogo, tamanho do array, tempo de espera e quantos jogos haverão
		int chances = 3, score = 0;
		int correct, maxScore;
		for (int i = 0; i < games; i++)							//Laço principal, pra rodar 3 vezes o jogo
		{
			maxScore = 10 * size;								//Reset da pontuação máxima por rodada
			correct = 0;										//Reset do marcador de saída do loop
			arrayCreation(size, array1);						//Coloca valores no array
			while((correct == 0) && (chances > 0)) 				//Verifica se pode continuar o jogo
			{
				printf("Sequencia #%d:\n", i+1);
				arrayPrint(size, array1);						//Print o array criado
				waitAndErase(waitTime, 2 * size);				//Espera e apaga a string printada
				arrayRead(size, array2);						//Lê os palpites

				if(arrayCompare(size, array1, array2) != 0)		//Laço pra caso erro, ajusta pontuação e roda resposta errada
				{	
					maxScore = scoreSet(maxScore, arrayCompare(size, array1, array2));
					chances = wrongAnswer(score, maxScore, chances);
				}else											//Laço para o acerto prepara nova rodada e roda resposta certa
				{
					correct = 1;
					score = correctAnswer(score, maxScore, chances);
				}
			}
			if(chances == 0)
			{													//Laço para acabar o programa, caso o usuário tenha falhado
				printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
				return;
			}
		}	
		printf("Otima memoria! Parabens!!!");
	}

int main(int argc, char const *argv[])
{
	int  seed;
	char dificuldade;
	int  tamanho, tempoEspera, jogos;

	scanf("%d %c", &seed, &dificuldade);
	
	srand(seed);

	switch(dificuldade)
	{
		case 'F':
			tamanho = 5;
			tempoEspera = 5;
			jogos = 3;
			int seq1[5];									//Declaração dos vetores da sequência a ser gerada e
			int guess1[5];									//do vetor de chutes
			gameLoop(seq1, guess1, tamanho, tempoEspera, jogos);
		break;

		case 'I':
			tamanho = 7;
			tempoEspera = 7;
			jogos = 4;
			int seq2[7];
			int guess2[7];
			gameLoop(seq2, guess2, tamanho, tempoEspera, jogos);
		break;

		case 'A':
			tempoEspera = 10;
			tamanho = 9;
			jogos = 5;
			int seq3[9];
			int guess3[9];
			gameLoop(seq3, guess3, tamanho, tempoEspera, jogos);
		break;

		default:
			return 1;
		break;
	}
	return 0;
}