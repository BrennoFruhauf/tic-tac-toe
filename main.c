// Declarando bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Definindo booleanos e quantidade de players
#define TRUE 1
#define FALSE 0
#define PLAYERS 2

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
void exibirLogo();
void aguardar(float tempoEmSegundos);
int validarResposta(char resposta);
int validarSimbolo(char caracter);
int validarPosicao(char posicao[5]);

int main() {
  // Definindo a localização do idioma
   setlocale(LC_ALL, "Portuguese_Brazil");

  // Declarando variáveis locais do MAIN
  int jogando, jogadorUm, jogadorDois, option, validar, aux, quebrarLoop, encerrar, igual;
  char nome[25], simboloJogando, simboloJogadorUm, simboloJogadorDois, optionChar, posicao[5], resposta, simbolo[] = {'X', 'O'};
  // Indice de cada posição do tabuleiro de forma segmentada para logica da vitória
  int posTab[8][6] = {{0, 0, 0, 1, 0, 2},
                      {1, 0, 1, 1, 1, 2},
                      {2, 0, 2, 1, 2, 2},
                      {0, 0, 1, 0, 2, 0},
                      {0, 1, 1, 1, 2, 1},
                      {0, 2, 1, 2, 2, 2},
                      {0, 0, 1, 1, 2, 2},
                      {0, 2, 1, 1, 2, 0}};
  exibirLogo();
  limpar_tela();
  // Definindo semi loop para o jogo
  do {

    // Loop de validação do input
    do {
      // Abrindo o arquivo e exibindo
      FILE *arq = fopen("logo/logo0.txt", "r");
      char txt[200];
      while(fgets(txt, sizeof(txt), arq) != NULL)
        printf("%s", txt);
      // Menu principal do jogo
      printf("\n\n\n\t\t\t\t\t     1 - Iniciar um novo jogo\n");
      printf("\t\t\t\t\t     2 - Ver placar\n");
      printf("\t\t\t\t\t     3 - Sair\n");
      printf("\n\t\t\t\t\t     Opção: ");
      // Scanf retorna Falso caso o valor digitado não seja um número e armazena em validar
      validar = scanf("%d", &option);
      fflush(stdin);
      limpar_tela();
      // Verificando se o que foi digitado e um número
    } while (validar != TRUE);

    // Definindo a funcionalidade das opções do menu principal
    switch (option) {

      case 1:
        for (int i = 0; i < 2; i++) {
          if (id < PLAYERS - 1)
            printf("\nInforme o nome do jogador:\n");
          else
            printf("\nInforme um nome de jogador já cadastrado:\n");
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

          aux = 0;
          igual = FALSE;
          // Verifica se existe o jogador registrado
          for (int j = 0; j < PLAYERS; j++) {
            // Compara a string digitada com a armazenada
            if (strcmp(nome, jogador[j].nome) == 0) {
              // Se existir a mesma string o id do jogador é inserido
              if (i == 0)
                jogadorUm = j;
              if (i == 1)
                jogadorDois = j;
              aux = 1;
              igual = TRUE;
            }
          }

          encerrar = 0;
          // Cadastra um novo jogador caso a verificação não encontre nada
          if (aux == 0 && id < PLAYERS - 1) {
            // Incrementa sempre que vai criar um jogador novo
            id += 1;
            // Verifica se atingiu o número máximo de jogadores registrados
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

            // ID se torna o tamanho do array de jogadores quando recebe o cadastro do ultimo jogador
            if (id == PLAYERS - 1)
              id = PLAYERS;
            // Se a quantidade atingiu o máximo e for inserido um nome diferente dos cadastrados é encerrado a partida
          } else if (id == PLAYERS &&  igual == FALSE) {
              printf("\nPartida Encerrada devido número de jogadores cadastrados ter chegado ao máximo!\n");
              encerrar = 1;
              aguardar(5);
              limpar_tela();
              break;
          }
        }

        // Sai do Caso 1 e volta para o menu principal
        if (encerrar == 1)
          break;

        do {
          do {
            do {
              // Escolha de quem será o primeiro a jogar
              printf("\nQuem será o primeiro a jogar?\nDigite 1 para %s e 2 para %s", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
              printf("\nOpção: ");
              validar = scanf("%d", &option);
              fflush(stdin);
              limpar_tela();
            } while (validar != TRUE);

            // Validação da resposta e alteração do primeiro e segundo jogador dependendo da resposta
            validar = FALSE;
            if (option == 1)
              validar = TRUE;
            else if (option == 2) {
              aux = jogadorUm;
              jogadorUm = jogadorDois;
              jogadorDois = aux;
              validar = TRUE;
            } else {
              printf("\nOpção inválida!\n");
              aguardar(3);
              limpar_tela();
            }
          } while (validar != TRUE);

          // Exibe a ordem de jogar
          printf("\nPrimeiro a jogar: %s\nSegundo a jogar: %s\n\n", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
          system("pause");
          limpar_tela();

          do {
            // O primeiro a jogar escolhe qual vai ser: O ou X
            printf("\n%s, qual deseja ser? X ou O (digite a letra)\n", jogador[jogadorUm].nome);
            printf("Quero ser: ");
            scanf("%c", &optionChar);
            optionChar = toupper(optionChar);
            fflush(stdin);
            limpar_tela();
            // Função para validação da escolha
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
            // Verificação, quando for par é a vez do primeiro jogador e impar do segundo jogador
            if (aux % 2 == 0) {
            // Realiza a alteração de quem é a vez dos jogadores
              jogando = jogadorUm;
              simboloJogando = simboloJogadorUm;
            } else {
              jogando = jogadorDois;
              simboloJogando = simboloJogadorDois;
            }
            // Verifica quantas jogadas ocorreram, se for menor ou igual a 9 jogadas, é exibido as opções e permitido continuar
            if (aux < 9) {
              do {
                // Função que exibe a situação do tabuleiro
                exibirJogoDaVelha();
                printf("\n");
                // Exibe as opções permitidas e não preenchidas
                if (tabuleiro[0][0] == ' ')
                  printf("\t\t\t\t\t     ES - Esquerda Superior\n");
                if (tabuleiro[0][1] == ' ')
                  printf("\t\t\t\t\t     CS - Centro Superior\n");
                if (tabuleiro[0][2] == ' ')
                  printf("\t\t\t\t\t     DS - Direita Superior\n");
                if (tabuleiro[1][0] == ' ')
                  printf("\t\t\t\t\t     EM - Esquerda do Meio\n");
                if (tabuleiro[1][1] == ' ')
                  printf("\t\t\t\t\t     CM - Centro do Meio\n");
                if (tabuleiro[1][2] == ' ')
                  printf("\t\t\t\t\t     DM - Direita do Meio\n");
                if (tabuleiro[2][0] == ' ')
                  printf("\t\t\t\t\t     EI - Esquerda Inferior\n");
                if (tabuleiro[2][1] == ' ')
                  printf("\t\t\t\t\t     CI - Centro Inferior\n");
                if (tabuleiro[2][2] == ' ')
                  printf("\t\t\t\t\t     DI - Direita Inferior\n");

                printf("\n\t\t\t     %s, Digite a sigla para preencher a posição: ", jogador[jogando].nome);
                // Recebe a sigla da posição que o jogador deseja preencher
                fgets(posicao, 5, stdin);
                fflush(stdin);
                limpar_tela();

                // Transformar o input em uppercase
                for (int i = 0; i < strlen(posicao); i++)
                  posicao[i] = toupper(posicao[i]);

                // Remove a quebra de linha
                posicao[strlen(posicao) - 1] = '\0';
                // Função para validar a posição inserida e verificar se já foi preenchida
              } while (validarPosicao(posicao) != TRUE);

              // Inserindo na posição digitada
              int y = 0, x = 0;
              for (int i = 0; i < 9; i++) {
                // Condição para iniciar a verificação em uma nova linha
                if (i == 3 || i == 6 ) {
                  y += 1;
                  x = 0;
                }
                // Verifica se a posição inserida é igual a sigla da posição e se a posição do tabuleiro esta limpa
                if (strcmp(posicao, posicaoSigla[i]) == 0 && tabuleiro[y][x] == ' ')
                  // Preenchimento da posição com o simbolo do jogador
                  tabuleiro[y][x] = simboloJogando;
                x += 1;
              }
            }

            quebrarLoop = 0;
            // Condição de vitória e adesão dos pontos
            for (int i = 0; i < 8; i++) {
              // Verifica se foi formado uma linha na horizontal, vertical ou diagonal pelos simbolos dos jogadores
              if ((tabuleiro[posTab[i][0]][posTab[i][1]] == tabuleiro[posTab[i][2]][posTab[i][3]] &&
              tabuleiro[posTab[i][2]][posTab[i][3]] == tabuleiro[posTab[i][4]][posTab[i][5]]) &&
              tabuleiro[posTab[i][0]][posTab[i][1]] != ' ') {
                for (int j = 0; j < 2; j++) {
                  // Verifica se a linha formada é do X ou O
                  if (tabuleiro[posTab[i][0]][posTab[i][1]] == simbolo[j]) {
                    // Verifica se o primeiro jogador escolheu o X ou O
                    if (optionChar == simbolo[j]) {
                      // Nome do jogador é armazenado em NOME para exibição da vitória
                      strcpy(nome, jogador[jogadorUm].nome);
                      // Atribuição da vitoria e derrota dos respectivos jogadores
                      jogador[jogadorUm].vitoria += 1;
                      jogador[jogadorDois].derrota += 1;
                      // Encerra a partida em caso de vitória antes das 9 jogadas
                      quebrarLoop = 1;
                      // Caso o primeiro jogador não vença, significa que a vitória foi do segundo jogador
                    } else {
                      strcpy(nome, jogador[jogadorDois].nome);
                      jogador[jogadorDois].vitoria += 1;
                      jogador[jogadorUm].derrota += 1;
                      quebrarLoop = 1;
                    }
                  }
                }
              }
            }

            // Se houver um jogador é exibido o tabuleiro e o jogador vitorioso
            if (quebrarLoop == 1) {
              exibirJogoDaVelha();
              printf("\n\t\t\t\t\t     Jogador %s Venceu!\n", nome);
              Sleep(2000);
              printf("\n\t\t\t\t");
              system("pause");
            }
            // Enquanto não houver um jogador e não ter ocorrido 9 jogadas, o jogo continua
          } while (aux < 9 && quebrarLoop != 1);

          // Se após 9 jogadas não houver vencedor é declarado empate
          if (aux == 9) {
            jogador[jogadorUm].empate += 1;
            jogador[jogadorDois].empate += 1;
            exibirJogoDaVelha();
            printf("\n\t\t\t\t\t           EMPATE!\n");
            aguardar(3);
            printf("\n");
            system("pause");
          }
          limpar_tela();
          do {
            // Exibe a opção perguntando se os jogadores desejam continuar em uma nova partida ou não
            printf("\nDeseja continuar? (Digite S para sim ou N para não)\n");
            printf("Resposta: ");
            scanf("%c", &resposta);
            fflush(stdin);
            resposta = toupper(resposta);
            limpar_tela();
            // Validação da resposta inserida
          } while (validarResposta(resposta) != TRUE);
          // Caso a resposta seja S, será retomado outra partida com os mesmos jogadores
        } while (resposta == 'S');
        limpar_tela();
        break;

      case 2:
        // Se não existir nenhum jogador registrado, não é exibido o placar
        if (id < 0) {
          printf("\n\t\tNENHUM PLACAR DISPONÍVEL!\n\n");
          aguardar(3);
        } else {
            // Exibe a tabela dos jogadores caso tenha jogadores registrados
            exibirTabela();
            printf("\n");
            aguardar(3);
            printf("\n");
            system("pause");
          }
        limpar_tela();
        break;

      case 3:
        printf("\n\n\t\tObrigado por jogar, volte sempre!\n\n");
        aguardar(3);
        limpar_tela();
        break;

      default:
        printf("Opção Inválida!\n");
        aguardar(3);
        limpar_tela();
        break;
    }
    // Caso a opção digitada seja 3, o jogo é fechado
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

// Função para Aguardar um tempo em segundos
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
    // retorna verdadeiro se for verdadeiro o resultado da comparação entre a sigla digitada
    // e as siglas que existe e se a posição do tabuleiro esta limpa
    if (((strcmp(posicao, posicaoSigla[i]) == 0) && (tabuleiro[y][x] == ' ')) == TRUE)
      return 1;
    x += 1;
  }
  // Caso contrario retorna falso
  return 0;
}

// Função para exibir o tabuleiro do jogo da velha e a logo
void exibirJogoDaVelha() {
  // Abrindo o arquivo e exibindo
  FILE *arq = fopen("logo/logo0.txt", "r");
  char txt[200];
  while(fgets(txt, sizeof(txt), arq) != NULL)
    printf("%s", txt);

  // Exibe o tabuleiro
  printf("\n\n\n");
  printf("\t\t\t\t\t          %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
  printf("\t\t\t\t\t         -----------\n");
  printf("\t\t\t\t\t          %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
  printf("\t\t\t\t\t         -----------\n");
  printf("\t\t\t\t\t          %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

// Função para exibir a tabela do placar de todos jogadores registrados
void exibirTabela() {
  // Declaração de variaveis locais da função
  float porcentagemWin[PLAYERS], auxFloat;
  int ordemJogador[PLAYERS], aux;

  for (int i = 0; i <= id; i++) {
    // Armazena o ID de cada jogador para comparação e organização dos jogadores
    ordemJogador[i] = (int) i;
    // Calcular a porcentagem de WIN em comparação a LOSE e DRAW
    porcentagemWin[i] = (float) jogador[i].vitoria * 100 / (jogador[i].vitoria + jogador[i].derrota + jogador[i].empate);
  }

  for (int i = 0; i <= id; i++) {
    for (int j = i; j <= id; j++) {
      // Verifica e organiza da maior Win em porcentagem para a menor
      if (porcentagemWin[i] < porcentagemWin[j]) {
        auxFloat = porcentagemWin[i];
        porcentagemWin[i] = porcentagemWin[j];
        porcentagemWin[j] = auxFloat;

        // Organiza do melhor para o pior jogador com base na porcentagem de WIN
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
  for (int i = 0; i < id; i++) {
    // Exibe a coluna POSIÇÃO
    sprintf(indiceString, "%d", i + 1);
    if (strlen(indiceString) == 1)
      printf("\n||      %d°     ||", i+1);
    else if (strlen(indiceString) == 2)
      printf("\n||     %d°     ||", i+1);

    // Armazena a diferença de caracteres entre a string e a coluna NOME
    difCaracteres = 28 - strlen(jogador[ordemJogador[i]].nome);

    // Exibe a coluna NOME
    // Verifica se a quantidade de letras do nome é impar
    // Se for impar, o nome é exibido com um espaço a mais depois
    if (difCaracteres % 2 != 0) {
      difCaracteres /= 2;
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < difCaracteres + j; k++)
          printf(" ");
        if (j == 0)
          printf("%s", jogador[ordemJogador[i]].nome);
      }
      printf("||");
      // Se for par, o nome é exibido centralizado
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

// Função para exibiçao da logo assim que o jogo é executado
void exibirLogo(){
	FILE *arq = fopen("logo/logo0.txt", "r");
	char txt[200];

  for (int i = 0; i < 3; i++) {
    while(fgets(txt, sizeof(txt), arq) != NULL)
      printf("%s", txt);
    Sleep(200);
    limpar_tela();

    arq = fopen("logo/logo1.txt", "r");
    while(fgets(txt, sizeof(txt), arq) != NULL)
      printf("%s", txt);
    Sleep(200);
    limpar_tela();

    arq = fopen("logo/logo2.txt", "r");
    while(fgets(txt, sizeof(txt), arq) != NULL)
      printf("%s", txt);
    Sleep(200);
    limpar_tela();

    arq = fopen("logo/logo3.txt", "r");
    while(fgets(txt, sizeof(txt), arq) != NULL)
      printf("%s", txt);
    Sleep(200);
    limpar_tela();

    arq = fopen("logo/logo0.txt", "r");
    while(fgets(txt, sizeof(txt), arq) != NULL)
      printf("%s", txt);
    Sleep(200);
  }
	fclose(arq);
}

