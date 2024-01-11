#include "./includes/game.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./includes/interface.h"

int id = -1, playerOne, playerTwo, isPlaying;
char playerOneSymbol, playerTwoSymbol, symbolPlaying, board[3][3];
const char X = 'X', O = 'O';
int winPosition[8][6] = {{0, 0, 0, 1, 0, 2}, {1, 0, 1, 1, 1, 2},
                         {2, 0, 2, 1, 2, 2}, {0, 0, 1, 0, 2, 0},
                         {0, 1, 1, 1, 2, 1}, {0, 2, 1, 2, 2, 2},
                         {0, 0, 1, 1, 2, 2}, {0, 2, 1, 1, 2, 0}};

int positionCoordinate[9][2] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1},
                                {1, 2}, {2, 0}, {2, 1}, {2, 2}};

char *inputNamePlayer() {
  const int NAME_LENGTH = 25;
  char *name = (char *)malloc(NAME_LENGTH);

  fgets(name, NAME_LENGTH, stdin);
  fflush(stdin);
  system("cls");

  name[strlen(name) - 1] = '\0';

  int temp = strlen(name);
  for (int x = 0; x < temp; x++) name[x] = toupper(name[x]);

  return name;
}

int checkIfPlayerExist(char *name, int index) {
  for (int x = 0; x < NUMBER_OF_PLAYERS; x++) {
    if (strcmp(name, players[x].name) == 0) {
      if (index == 0)
        playerOne = x;
      else
        playerTwo = x;

      free(name);
      return TRUE;
    }
  }

  return FALSE;
}

void createNewPlayer(char *name, int index) {
  if (index == 0)
    playerOne = ++id;
  else
    playerTwo = ++id;

  strcpy(players[id].name, name);
  free(name);

  players[id].win = 0;
  players[id].lose = 0;
  players[id].draw = 0;

  if (id == NUMBER_OF_PLAYERS - 1) id = NUMBER_OF_PLAYERS;
}

int insetPlayers() {
  int wasPlayerInserted = TRUE;

  for (int x = 0; x < 2; x++) {
    char *name;
    int isSameName = 0;
    do {
      if (isSameName) printf("\n%s!\n", cl->firstOption[5]);

      if (id < NUMBER_OF_PLAYERS - 1)
        printf("\n%s:\n", cl->firstOption[0]);
      else
        printf("\n%s:\n", cl->firstOption[1]);

      printf("%s: ", cl->firstOption[x + 2]);

      name = inputNamePlayer();
      isSameName = strcmp(players[playerOne].name, name) == 0;
    } while (isSameName);

    if (!checkIfPlayerExist(name, x) && id < NUMBER_OF_PLAYERS - 1)
      createNewPlayer(name, x);
    else {
      printf("\n%s\n", cl->firstOption[4]);
      wasPlayerInserted = FALSE;
      wait(5);
      system("cls");
      break;
    }
  }

  return wasPlayerInserted;
}

void chooseFirstToPlay() {
  int option, validation;
  do {
    printf("\n%s?\n", cl->firstOption[6]);
    printf("%s 1 %s %s ", cl->general[2], cl->general[3],
           players[playerOne].name);
    printf("%s 2 %s %s ", cl->general[4], cl->general[3],
           players[playerTwo].name);
    printf("\n%s: ", cl->general[1]);

    validation = scanf("%d", &option);
    fflush(stdin);

    validation = validation && (option >= 1 && option <= 2);

    if (validation && option == 2) {
      int temp = playerOne;
      playerOne = playerTwo;
      playerTwo = temp;
    }

    system("cls");

    if (!validation) {
      printf("\n%s!\n", cl->general[5]);
      wait(3);
      system("cls");
    }
  } while (!validation);
}

void showOrder() {
  printf("\n%s: %s\n", cl->firstOption[7], players[playerOne].name);
  printf("\n%s: %s\n", cl->firstOption[8], players[playerTwo].name);
  system("pause");
  system("cls");
}

void chooseSymbol() {
  char option;
  int isValidSymbol;

  do {
    printf("\n%s, %s? X %s O (%s)", players[playerOne].name, cl->firstOption[9],
           cl->general[4], cl->firstOption[10]);
    printf("\n%s: ", cl->firstOption[11]);
    scanf("%c", &option);
    fflush(stdin);
    system("cls");

    option = toupper(option);
    isValidSymbol = (option == X || option == O);
  } while (!isValidSymbol);

  if (option == X) {
    playerOneSymbol = X;
    playerTwoSymbol = O;
    return;
  }

  playerOneSymbol = O;
  playerTwoSymbol = X;
}

void showAvailablePositions() {
  int count = -1;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      count++;
      if (board[x][y] == ' ') {
        printf("%s     ", cl->tabulation);
        printf("%s - ", cl->boardPosition[count]);
        printf("%s\n", cl->positionName[count]);
      }
    }
  }
}

void showBoard() {
  showImage(imagesPath[0]);

  printf("\n\n\n");
  for (int x = 0; x < 3; x++) {
    printf("%s          ", cl->tabulation);
    printf("%c | %c | %c \n", board[x][0], board[x][1], board[x][2]);

    if (x < 2) printf("%s         -----------\n", cl->tabulation);
  }
}

int isValidPosition(char *position) {
  for (int x = 0; x < 9; x++) {
    int axisY = positionCoordinate[x][0], axisX = positionCoordinate[x][1];
    if (!strcmp(position, cl->boardPosition[x]) && board[axisY][axisX] == ' ') {
      board[axisY][axisX] = symbolPlaying;
      return TRUE;
    }
  }

  return FALSE;
}

void play() {
  char position[4];
  do {
    showBoard();
    printf("\n");

    showAvailablePositions();
    const char *tabulation = (strcmp(lang, "en") == 0) ? "\t\t" : "\t\t\t";
    printf("\n%s     %s, ", tabulation, players[isPlaying].name);
    printf("%s: ", cl->firstOption[12]);

    fgets(position, 4, stdin);
    fflush(stdin);
    system("cls");

    for (int x = 0; position[x] != '\0'; x++)
      position[x] = toupper(position[x]);

    position[strlen(position) - 1] = '\0';
  } while (!isValidPosition(position));
}

void clearBoard() {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) board[x][y] = ' ';
  }
}

void changeCurrentPlayer(int round) {
  const int IS_EVEN = !(round % 2);
  if (IS_EVEN) {
    isPlaying = playerOne;
    symbolPlaying = playerOneSymbol;
    return;
  }

  isPlaying = playerTwo;
  symbolPlaying = playerTwoSymbol;
}

int checkEndCondition(int round) {
  int availableWinCondition = 0;

  for (int x = 0; x < 8; x++) {
  }
}

void gameMatch() {
  int currentRound = -1;
  do {
    currentRound++;
    changeCurrentPlayer(currentRound);
    play();
    checkEndCondition(currentRound);

  } while (1);
}

void game() {
  if (!insetPlayers()) return;

  chooseFirstToPlay();
  showOrder();
  chooseSymbol();

  clearBoard();
  gameMatch();

  printf("Jogando\n");
  exit(1);
}