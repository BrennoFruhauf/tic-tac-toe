#include "./includes/game.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./includes/interface.h"

int id = -1, playerOne, playerTwo;

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
    if (id < NUMBER_OF_PLAYERS - 1)
      printf("\n%s:\n", currentLanguage->firstOption[0]);
    else
      printf("\n%s:\n", currentLanguage->firstOption[1]);

    printf("%d° %s: ", x + 1, currentLanguage->firstOption[2]);
    char *name = inputNamePlayer();

    if (!checkIfPlayerExist(name, x) && id < NUMBER_OF_PLAYERS - 1)
      createNewPlayer(name, x);
    else {
      printf("\n%s\n", currentLanguage->firstOption[3]);
      wasPlayerInserted = FALSE;
      wait(5);
      system("cls");
      break;
    }
  }

  return wasPlayerInserted;
}

void game() {
  if (!insetPlayers()) return;

  printf("Jogando\n");
  exit(1);
}