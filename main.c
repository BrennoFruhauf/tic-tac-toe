#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Defini��o de True e False
#define TRUE 1
#define FALSE 0

// Define a quantidade m�xima de jogadores
#define PLAYERS 10

// Definindo a struct do jogador
struct dados_jogador
{
  char nome[25];
  int vitoria, derrota, empate;
};

// Definindo vari�veis globais
struct dados_jogador jogador[PLAYERS];
int id = -1;

int main()
{
  // Registrando Fun��es Criadas ap�s o MAIN
  void limpar_tela();
  void exibirTabela();
  // Definindo a localiza��o do idioma
   setlocale(LC_ALL, "Portuguese_Brazil");

  // Declarando variaveis do MAIN
  int jogadorUm, jogadorDois, option, validar;

  // Definindo semi loop para o jogo
  do
  {
    // Loop de validacao do input
    do
    {
      // Menu principal do jogo
      printf("1 - Iniciar um novo jogo\n");
      printf("2 - Ver placar\n");
      printf("3 - Sair\n");
      printf("\nOp��o: ");
      validar = scanf("%d", &option);
      fflush(stdin);
      limpar_tela();
      // Verificando se o que foi digitado e um numero
    } while (validar != TRUE);

    // Definindo a funcionalidade das opcoes do menu principal
    switch (option)
    {
      case 1:
        for (int i = 0; i < 2; i++)
        {
          // Incrementa sempre que for cadastrar um novo jogador
          id += 1;
          if (i == 0)
            jogadorUm = id;
          else
            jogadorDois = id;
          printf("Informe o nome dos jogadores:\n");
          printf("%d Jogador: ", i + 1);
          fgets(jogador[id].nome, 25, stdin);
          fflush(stdin);
          // Remove a quebra de linha da string
          jogador[id].nome[strlen(jogador[id].nome) - 1] = '\0';
          limpar_tela();
        }

        limpar_tela();
        break;

      case 2:
        // Condional pra caso nao tenha nenhum jogador cadastrado
        if (id < 0)
        {
          printf("NENHUM PLACAR DISPON�VEL!\n\n");
          printf("Aguarde");
          for (int i = 0; i < 5; i++)
          {
            Sleep(500);
            printf(" .");
          }
        } else
          {
            exibirTabela();
            printf("\n");
            system("pause");
          }
        limpar_tela();
        break;

      case 3:
        limpar_tela();
        break;

      default:
        printf("Opcao Invalida\n\n");
        printf("Aguarde");
        for (int i = 0; i < 5; i++)
        {
          Sleep(500);
          printf(" .");
        }
        limpar_tela();
        break;
    }
  } while (option != 3);

  return 0;
}

// Fun��o para limpar tela no Win ou Linux
void limpar_tela()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif // _WIN32
}


// Fun��o para exibir a tabela do placar de todos jogadores registrados
void exibirTabela()
{
  char indiceString[4];
  int difCaracteres = 0;
  printf("==================================================================================\n");
  printf("||   Posi��o   ||            Nome            ||   Win   ||   Lose   ||   Draw   ||\n");
  printf("==================================================================================");
  for (int i = 0; i <= id; i++)
  {
    // Exibe a coluna POSI��O
    sprintf(indiceString, "%d", i + 1);
    if (strlen(indiceString) == 1)
      printf("\n||      %d�     ||", i+1);
    else if (strlen(indiceString) == 2)
      printf("\n||     %d�     ||", i+1);

    difCaracteres = 28 - strlen(jogador[i].nome);

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
          printf("%s", jogador[i].nome);
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
          printf("%s", jogador[i].nome);
      }
      printf("||");
      }

    // Exibe os Resultados
    char resultado[4];
    sprintf(resultado, "%d", jogador[i].vitoria);
    if (strlen(resultado) == 1)
      printf("    %d    ||", jogador[i].vitoria);
    else if (strlen(resultado) == 2)
      printf("   %d    ||", jogador[i].derrota);

    sprintf(resultado, "%d", jogador[i].derrota);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[i].derrota);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[i].derrota);

    sprintf(resultado, "%d", jogador[i].empate);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[i].empate);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[i].empate);
  }
  printf("\n==================================================================================");
}