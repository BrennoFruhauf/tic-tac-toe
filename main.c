#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Definindo booleanos e quantidade de players
#define TRUE 1
#define FALSE 0
#define PLAYERS 10

// Definindo a struct do jogador
struct dados_jogador {
  char nome[25];
  int vitoria, derrota, empate;
};

// Definindo variáveis globais
struct dados_jogador jogador[PLAYERS];
char tabuleiro[3][3];
char posicaoSigla[9][3] = {"ES", "CS", "DS", "EM", "CM", "DM", "EI", "CI", "DI"};
int id = -1;

// Registrando Funções Criadas após o MAIN
void limpar_tela();
void ordenarJogadores();
void exibirTabela();
void exibirJogoDaVelha();
void aguardar(float tempoEmSegundos);
int validarResposta(char resposta);
int validarSimbolo(char caracter);
int validarPosicao(char posicao[5]);

int main() {
  // Definindo a localização do idioma
   setlocale(LC_ALL, "Portuguese_Brazil");

  // Declarando variáveis locais do MAIN
  int jogando, jogadorUm, jogadorDois, option, validar, aux, quebrarLoop;
  char nome[25], simboloJogando, simboloJogadorUm, simboloJogadorDois, optionChar, posicao[5], resposta;
  // Indice de cada posição do tabuleiro de forma segmentada para logica da vitória
  int posTab[8][6] = {{0, 0, 0, 1, 0, 2},
                      {1, 0, 1, 1, 1, 2},
                      {2, 0, 2, 1, 2, 2},
                      {0, 0, 1, 0, 2, 0},
                      {0, 1, 1, 1, 2, 1},
                      {0, 2, 1, 2, 2, 2},
                      {0, 0, 1, 1, 2, 2},
                      {0, 2, 1, 1, 2, 0}};

  // Definindo semi loop para o jogo
  do {
    // Loop de validação do input
    do {
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
    switch (option) {

      case 1:
        for (int i = 0; i < 2; i++) {
          printf("Informe o nome dos jogadores:\n");
          printf("%d° Jogador: ", i + 1);
          fgets(nome, 25, stdin);
          fflush(stdin);
          limpar_tela();

          // Remove a quebra de linha da string
          nome[strlen(nome) - 1] = '\0';

          // Transforma o nome em uppercase
          aux = strlen(nome);
          for (int j = 0; j < aux; j++)
            nome[j] = toupper(nome[j]);

          // Compara o nome digitado com o nome armazenado
          aux = 0;
          for (int j = 0; j < PLAYERS; j++) {
            if (strcmp(nome, jogador[j].nome) == 0) {
              if (i == 0)
                jogadorUm = j;
              if (i == 1)
                jogadorDois = j;
              aux = 1;
            }
          }

          // Cadastrar um novo jogador
          if (aux == 0) {
            id += 1;
            if (id < PLAYERS) {
              if (i == 0) {
                jogadorUm = id;
                strcpy(jogador[id].nome, nome);
                jogador[id].vitoria = 0;
                jogador[id].derrota = 0;
                jogador[id].empate = 0;
              } if (i == 1) {
                jogadorDois = id;
                strcpy(jogador[id].nome, nome);
                jogador[id].vitoria = 0;
                jogador[id].derrota = 0;
                jogador[id].empate = 0;
              }
            }
          }
        }

        do {
          do {
            do {
              printf("Quem será o primeiro a jogar?\nDigite 1 para %s e 2 para %s", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
              printf("\nOpção: ");
              validar = scanf("%d", &option);
              fflush(stdin);
              limpar_tela();
            } while (validar != TRUE);

            // Escolher quem será o primeiro a jogar
            validar = FALSE;
            if (option == 1)
              validar = TRUE;
            else if (option == 2) {
              aux = jogadorUm;
              jogadorUm = jogadorDois;
              jogadorDois = aux;
              validar = TRUE;
            } else {
              printf("Opção inválida!\n");
              aguardar(3);
              limpar_tela();
            }
          } while (validar != TRUE);

          printf("Primeiro a jogar: %s\nSegundo a jogar: %s\n", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
          system("pause");
          limpar_tela();

          // O primeiro a jogar escolhe qual vai ser: O ou X
          do {
            printf("%s, qual deseja ser? X ou O (digite a letra)\n", jogador[jogadorUm].nome);
            printf("Quero ser: ");
            scanf("%c", &optionChar);
            optionChar = toupper(optionChar);
            fflush(stdin);
            limpar_tela();
          } while (validarSimbolo(optionChar) == FALSE);

          // Atribuição da escolha ao primeiro jogador e segundo
          if (optionChar == 'X') {
            simboloJogadorUm = 'X';
            simboloJogadorDois = 'O';
          } else {
              simboloJogadorUm = 'O';
              simboloJogadorDois = 'X';
            }

          // Inicialização da partida com tabuleiro limpo
          for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
              tabuleiro[y][x] = ' ';

          aux = -1;
          do {
            aux += 1;
            if (aux % 2 == 0) {
              jogando = jogadorUm;
              simboloJogando = simboloJogadorUm;
            } else {
              jogando = jogadorDois;
              simboloJogando = simboloJogadorDois;
            }
            if (aux < 9) {
              do {
                exibirJogoDaVelha();
                printf("\n");
                if (tabuleiro[0][0] == ' ')
                  printf("ES - Esquerda Superior\n");
                if (tabuleiro[0][1] == ' ')
                  printf("CS - Centro Superior\n");
                if (tabuleiro[0][2] == ' ')
                  printf("DS - Direita Superior\n");
                if (tabuleiro[1][0] == ' ')
                  printf("EM - Esquerda do Meio\n");
                if (tabuleiro[1][1] == ' ')
                  printf("CM - Centro do Meio\n");
                if (tabuleiro[1][2] == ' ')
                  printf("DM - Direita do Meio\n");
                if (tabuleiro[2][0] == ' ')
                  printf("EI - Esquerda Inferior\n");
                if (tabuleiro[2][1] == ' ')
                  printf("CI - Centro Inferior\n");
                if (tabuleiro[2][2] == ' ')
                  printf("DI - Direita Inferior\n");

                printf("\n%s, Digite a sigla para preencher a posição: ", jogador[jogando].nome);
                fgets(posicao, 5, stdin);
                fflush(stdin);
                limpar_tela();

                // Transformar o input em uppercase
                for (int i = 0; i < strlen(posicao); i++)
                  posicao[i] = toupper(posicao[i]);

                // Remove a quebra de linha
                posicao[strlen(posicao) - 1] = '\0';
              } while (validarPosicao(posicao) != TRUE);

              // Inserindo na posição digitada
              int y = 0, x = 0;
              for (int i = 0; i < 9; i++) {
                if (i == 3 || i == 6 ) {
                  y += 1;
                  x = 0;
                }
                if (strcmp(posicao, posicaoSigla[i]) == 0 && tabuleiro[y][x] == ' ')
                  tabuleiro[y][x] = simboloJogando;
                x += 1;
              }
            }

            quebrarLoop = 0;
            // Condição de vitória e adesão dos pontos
            for (int i = 0; i < 8; i++) {
              if ((tabuleiro[posTab[i][0]][posTab[i][1]] == tabuleiro[posTab[i][2]][posTab[i][3]] &&
              tabuleiro[posTab[i][2]][posTab[i][3]] == tabuleiro[posTab[i][4]][posTab[i][5]]) &&
              tabuleiro[posTab[i][0]][posTab[i][1]] != ' ') {
                if (tabuleiro[posTab[i][0]][posTab[i][1]] == 'X' && optionChar == 'X') {
                  printf("Jogador %s Venceu!\n", jogador[jogadorUm].nome);
                  jogador[jogadorUm].vitoria += 1;
                  jogador[jogadorDois].derrota += 1;
                  quebrarLoop = 1;
                }
                if (tabuleiro[posTab[i][0]][posTab[i][1]] == 'O' && optionChar == 'O') {
                  printf("Jogador %s Venceu!\n", jogador[jogadorUm].nome);
                  jogador[jogadorUm].vitoria += 1;
                  jogador[jogadorDois].derrota += 1;
                  quebrarLoop = 1;
                }
              }
            }

            if (quebrarLoop == 1) {
              exibirJogoDaVelha();
              aguardar(3);
              printf("\n");
              system("pause");
            }
          } while (aux < 9 && quebrarLoop != 1);

          if (aux == 9) {
            jogador[jogadorUm].empate += 1;
            jogador[jogadorDois].empate += 1;
            printf("\nEMPATE!");
            exibirJogoDaVelha();
            aguardar(3);
            printf("\n");
            system("pause");
          }
          limpar_tela();
          do {
            printf("Deseja continuar? (Digite S para sim ou N para não)\n");
            printf("Resposta: ");
            scanf("%c", &resposta);
            fflush(stdin);
            resposta = toupper(resposta);
            limpar_tela();
          } while (validarResposta(resposta) != TRUE);
        } while (resposta == 'S');
        limpar_tela();
        break;

      case 2:
        // Condional pra caso nao tenha nenhum jogador cadastrado
        if (id < 0) {
          printf("NENHUM PLACAR DISPONÍVEL!\n\n");
          aguardar(3);
        } else {
            exibirTabela();
            printf("\n");
            aguardar(3);
            printf("\n");
            system("pause");
          }
        limpar_tela();
        break;

      case 3:
        limpar_tela();
        break;

      default:
        printf("Opção Inválida!\n");
        aguardar(3);
        limpar_tela();
        break;
    }
  } while (option != 3);

  return 0;
}

// Função para limpar tela no Win ou Linux
void limpar_tela() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif // _WIN32
}

// Função para Aguardar um tempo
void aguardar(float tempoEmSegundos) {
  tempoEmSegundos /= 5;
  printf("\nAguarde");
  for (int i = 0; i < 5; i++) {
    Sleep(tempoEmSegundos * 1000);
    printf(" .");
  }
}

// Função para validar entrada do X ou O
int validarSimbolo(char caracter) {
  if (caracter == 'X' || caracter == 'O')
    return 1;
  else
    return 0;
}

// Função para validar resposta S ou N
int validarResposta(char resposta) {
  if (resposta == 'S' || resposta == 'N')
    return 1;
  else
    return 0;
}

// Função para validar preenchimento de posição
int validarPosicao(char posicao[5]) {
  int y = 0, x = 0;
  for (int i = 0; i < 9; i++) {
    if (i == 3 || i == 6 ) {
      y += 1;
      x = 0;
    }
    if (((strcmp(posicao, posicaoSigla[i]) == 0) && (tabuleiro[y][x] == ' ')) == TRUE)
      return 1;
    x += 1;
  }
  return 0;
}

// Função para exibir o tabuleiro do jogo da velha
void exibirJogoDaVelha() {
  printf("\nJOGO DA VELHA\n\n");
  printf(" %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
  printf("-----------\n");
  printf(" %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
  printf("-----------\n");
  printf(" %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

// Função para exibir a tabela do placar de todos jogadores registrados
void exibirTabela() {
  // Declaração de variaveis locais da função
  float porcentagemWin[PLAYERS], auxFloat;
  int ordemJogador[PLAYERS], aux;

  // Armazenar os dados de comparação e organização dos jogadores
  for (int i = 0; i <= id; i++) {
    ordemJogador[i] = (int) i;
    // Calcular a porcentagem de WIN em comparação a LOSE e DRAW
    porcentagemWin[i] = (float) jogador[i].vitoria * 100 / (jogador[i].vitoria + jogador[i].derrota + jogador[i].empate);
  }

  // Ordenação do melhor para o pior jogador
  for (int i = 0; i <= id; i++) {
    for (int j = i; j <= id; j++) {
      if (porcentagemWin[i] < porcentagemWin[j]) {
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
  for (int i = 0; i <= id; i++) {
    // Exibe a coluna POSIÇÃO
    sprintf(indiceString, "%d", i + 1);
    if (strlen(indiceString) == 1)
      printf("\n||      %d°     ||", i+1);
    else if (strlen(indiceString) == 2)
      printf("\n||     %d°     ||", i+1);

    // Armazena a diferença de caracteres entre a string e a coluna NOME
    difCaracteres = 28 - strlen(jogador[ordemJogador[i]].nome);

    // Exibe a coluna NOME
    if (difCaracteres % 2 != 0) {
      difCaracteres /= 2;
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < difCaracteres + j; k++)
          printf(" ");
        if (j == 0)
          printf("%s", jogador[ordemJogador[i]].nome);
      }
      printf("||");
    } else {
        difCaracteres /= 2;
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < difCaracteres; k++)
            printf(" ");
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
