#include "./includes/interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "./includes/game.h"

PlayerData players[NUMBER_OF_PLAYERS];
char board[3][3];
char *path = NULL;
char *lang = "en";
char *imagesPath[4];

int inputInt;
char inputChar;

LanguageStrings english = {
    "en_US.UTF-8",
    {"TL", "TM", "TR", "CL", "CM", "CR", "LL", "LM", "LR"},
    {"New game", "Scoreboard", "Exit", "Option"},
    {"Enter the player's name", "Enter an already registered player name",
     "Player",
     "Match cancelled: Number of registered players reached maximum!"},
    {"Wait"}};

LanguageStrings portuguese = {
    "Portuguese_Brazil",
    {"ES", "CS", "DS", "EC", "MC", "DC", "EI", "CI", "DI"},
    {"Novo jogo", "Placar", "Sair", "Opção"},
    {"Insira o nome do jogador", "Insira um nome de jogador já cadastrado",
     "Jogador",
     "Partida cancelada: Número de jogadores cadastros chegou ao máximo!"},
    {"Aguarde"}};

LanguageStrings *currentLanguage = &english;

char *obtainLanguage(int argc, char *argv[]) {
  char *defaultLang = "en", *ptLang = "pt";

  if (argc <= 1) return defaultLang;
  if (strcmp(argv[1], "--pt") == 0) return ptLang;

  return defaultLang;
}

char *getPath(char *argPath) {
  char *exePath = (char *)malloc(MAX_PATH);

  strcpy(exePath, argPath);
  char *lastBackslash = strrchr(exePath, '\\');
  if (lastBackslash != NULL) *lastBackslash = '\0';

  return exePath;
}

char *getImagePath(char *imageName) {
  char *imagePath = (char *)malloc(MAX_PATH);
  snprintf(imagePath, MAX_PATH, "%s\\imgs\\%s\\%s", path, lang, imageName);
  return imagePath;
}

void showImage(char *imagePath) {
  FILE *file;
  char txt[200];

  file = fopen(imagePath, "r");
  while (fgets(txt, sizeof(txt), file) != NULL) printf("%s", txt);
  fclose(file);
}

void showLogo() {
  char *imagesName[4] = {"logo0.txt", "logo1.txt", "logo2.txt", "logo3.txt"};

  for (int x = 0; x < 4; x++) imagesPath[x] = getImagePath(imagesName[x]);

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 4; y++) {
      showImage(imagesPath[y]);
      Sleep(200);
      system("cls");
    }
  }
}

void wait(float timeInSeconds) {
  timeInSeconds /= 5;
  printf("\n%s", currentLanguage->general[0]);
  for (int i = 0; i < 5; i++) {
    Sleep(timeInSeconds * 1000);
    printf(" .");
  }
}

int showMainMenu() {
  int validation;
  do {
    showImage(imagesPath[0]);

    printf("\n\n\n\t\t\t\t\t     1 - %s\n", currentLanguage->mainMenu[0]);
    printf("\t\t\t\t\t     2 - %s\n", currentLanguage->mainMenu[1]);
    printf("\t\t\t\t\t     3 - %s\n", currentLanguage->mainMenu[2]);
    printf("\n\t\t\t\t\t     %s: ", currentLanguage->mainMenu[3]);

    validation = scanf("%d", &inputInt);
    fflush(stdin);
    system("cls");
  } while (validation != TRUE);

  return inputInt;
}

void gameMenu(int option) {
  switch (option) {
    case 1:
      game();
      break;
  }
}