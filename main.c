#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Definição de True e False
#define TRUE 1
#define FALSE 0

// Define a quantidade máxima de jogadores
#define PLAYERS 10

// Definindo a struct do jogador
struct dados_jogador
{
  char nome[25];
  int vitoria, derrota, empate;
};

// Definindo variáveis globais
struct dados_jogador jogador[PLAYERS];
int id = -1;

int main()
{
  // Registrando Funções Criadas após o MAIN
  void limpar_tela();
  void ordenarJogadores();
  void exibirTabela();
  void aguardar(float tempoEmSegundos);

  // Definindo a localização do idioma
   setlocale(LC_ALL, "Portuguese_Brazil");

  // Declarando variáveis do MAIN
  int jogadorUm, jogadorDois, option, validar;

  // Definindo semi loop para o jogo
  do
  {
    // Loop de validação do input
    do
    {
      // Menu principal do jogo
      printf("1 - Iniciar um novo jogo\n");
      printf("2 - Ver placar\n");
      printf("3 - Sair\n");
      printf("\nOpção: ");
      validar = scanf("%d", &option);
      fflush(stdin);
      limpar_tela();
      // Verificando se o que foi digitado e um número
    } while (validar != TRUE);

    // Definindo a funcionalidade das opções do menu principal
    switch (option)
    {
      case 1:
        // Incrementa sempre que iniciar um novo jogo para cadastrar um novo jogador
          id += 1;
          if (id < PLAYERS)
          {
            for (int i = 0; i < 2; i++)
            {
              if (i == 0)
                jogadorUm = id;
              else
                jogadorDois = id;
              printf("Informe o nome dos jogadores:\n");
              printf("%d° Jogador: ", i + 1);
              fgets(jogador[id].nome, 25, stdin);
              fflush(stdin);
              // Remove a quebra de linha da string
              jogador[id].nome[strlen(jogador[id].nome) - 1] = '\0';
              // Inicializa WIN, LOSE e DRAW em zero
              jogador[id].vitoria = rand() % 10;
              jogador[id].derrota = rand() % 10;
              jogador[id].empate = rand() % 10;
              limpar_tela();
              if (i == 0)
                id += 1;
            }

            // Escolha de quem irá começar primeiro
          } else
            {
              id = PLAYERS - 1;
              printf("Limite máximo de cadastro atingido!\n");
              aguardar(0.5);
              limpar_tela();
            }

        limpar_tela();
        break;

      case 2:
        // Condional pra caso nao tenha nenhum jogador cadastrado
        if (id < 0)
        {
          printf("NENHUM PLACAR DISPONÍVEL!\n\n");
          aguardar(0.5);
        } else
          {
            exibirTabela();
            printf("\n");
            aguardar(0.5);
            printf("\n");
            system("pause");
          }
        limpar_tela();
        break;

      case 3:
        limpar_tela();
        break;

      default:
        printf("Opção Inválida\n");
        aguardar(0.5);
        limpar_tela();
        break;
    }
  } while (option != 3);

  return 0;
}

// Função para limpar tela no Win ou Linux
void limpar_tela()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif // _WIN32
}

// Função para Aguardar um tempo
void aguardar(float tempoEmSegundos)
{
  printf("\nAguarde");
  for (int i = 0; i < 5; i++)
  {
    Sleep(tempoEmSegundos * 1000);
    printf(" .");
  }
}

// Função para exibir a tabela do placar de todos jogadores registrados
void exibirTabela()
{
  // Declaração de variaveis locais da função
  float porcentagemWin[PLAYERS], auxFloat;
  int ordemJogador[PLAYERS], aux;

  // Armazenar os dados de comparação e organização dos jogadores
  for (int i = 0; i <= id; i++)
  {
    ordemJogador[i] = (int) i;
    // Calcular a porcentagem de WIN em comparação a LOSE e DRAW
    porcentagemWin[i] = (float) jogador[i].vitoria * 100 / (jogador[i].vitoria + jogador[i].derrota + jogador[i].empate);
  }

  // Ordenação do melhor para o pior jogador
  for (int i = 0; i <= id; i++)
  {
    for (int j = i; j <= id; j++)
    {
      if (porcentagemWin[i] < porcentagemWin[j])
      {
        auxFloat = porcentagemWin[i];
        porcentagemWin[i] = porcentagemWin[j];
        porcentagemWin[j] = auxFloat;

        aux = ordemJogador[i];
        ordemJogador[i] = ordemJogador[j];
        ordemJogador[j] = aux;
      }
    }
  }

  char indiceString[4];
  int difCaracteres = 0;
  // Inicia a Exibição da Tabela
  printf("==================================================================================\n");
  printf("||   Posição   ||            Nome            ||   Win   ||   Lose   ||   Draw   ||\n");
  printf("==================================================================================");
  for (int i = 0; i <= id; i++)
  {
    // Exibe a coluna POSIÇÃO
    sprintf(indiceString, "%d", i + 1);
    if (strlen(indiceString) == 1)
      printf("\n||      %d°     ||", i+1);
    else if (strlen(indiceString) == 2)
      printf("\n||     %d°     ||", i+1);

    // Armazena a diferença de caracteres entre a string e a coluna NOME
    difCaracteres = 28 - strlen(jogador[ordemJogador[i]].nome);

    // Exibe a coluna NOME
    if (difCaracteres % 2 != 0)
    {
      difCaracteres /= 2;
      for (int j = 0; j < 2; j++)
      {
        for (int k = 0; k < difCaracteres + j; k++)
        {
          printf(" ");
        }
        if (j == 0)
          printf("%s", jogador[ordemJogador[i]].nome);
      }
      printf("||");
    } else
      {
        difCaracteres /= 2;
      for (int j = 0; j < 2; j++)
      {
        for (int k = 0; k < difCaracteres; k++)
        {
          printf(" ");
        }
        if (j == 0)
          printf("%s", jogador[ordemJogador[i]].nome);
      }
      printf("||");
      }

    char resultado[7];
    // Exibe a coluna WIN
    sprintf(resultado, "%d", jogador[ordemJogador[i]].vitoria);
    if (strlen(resultado) == 1)
      printf("    %d    ||", jogador[ordemJogador[i]].vitoria);
    else if (strlen(resultado) == 2)
      printf("   %d    ||", jogador[ordemJogador[i]].vitoria);

    // Exibe a coluna LOSE
    sprintf(resultado, "%d", jogador[ordemJogador[i]].derrota);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[ordemJogador[i]].derrota);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[ordemJogador[i]].derrota);

    // Exibe a coluna DRAW
    sprintf(resultado, "%d", jogador[ordemJogador[i]].empate);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[ordemJogador[i]].empate);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[ordemJogador[i]].empate);
  }
  printf("\n==================================================================================");
}
