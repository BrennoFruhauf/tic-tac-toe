#include "./includes/interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "./includes/game.h"

PlayerData players[NUMBER_OF_PLAYERS];
char *path = NULL;
char *lang = "en";
char *imagesPath[4];

int inputInt;
char inputChar;

LanguageStrings english = {
    "en_US.UTF-8",
    "\t\t\t\t",
    {"TL", "TC", "TR", "CL", "CC", "CR", "BL", "BC", "BR"},
    {"Top Left", "Top Center", "Top Right", "Center Left", "Central Center",
     "Center Right", "Bottom Left", "Bottom Center", "Bottom Right"},
    {"New game", "Scoreboard", "Exit"},
    {"Enter the player's name", "Enter an already registered player name",
     "First player", "Second player",
     "Match cancelled: Number of registered players reached maximum!",
     "First and second player can't be the same player",
     "Who will be the first to play", "First to play", "Second to play",
     "What do you want to be", "type the letter", "I want to be",
     "Enter the abbreviation to fill the position", "DRAW", "Won"},
    {"Wait", "Option", "Enter", "to", "or", "Invalid option", "Player"}};

LanguageStrings portuguese = {
    "Portuguese_Brazil",
    "\t\t\t\t\t",
    {"ES", "CS", "DS", "EC", "CC", "DC", "EI", "CI", "DI"},
    {"Esquerda Superior", "Centro Superior", "Direita Superior",
     "Esquerda Central", "Centro Central", "Direita Central",
     "Esquerda Inferior", "Centro Inferior", "Direita Inferior"},
    {"Novo jogo", "Placar", "Sair"},
    {"Insira o nome do jogador", "Insira um nome de jogador já cadastrado",
     "Primeiro jogador", "Segundo jogador",
     "Partida cancelada: Número de jogadores cadastros chegou ao máximo!",
     "Primeiro e segundo jogador não podem ser o mesmo jogador",
     "Quem será o primeiro a jogar?", "Primeira à jogar", "Segundo à jogar",
     "O que você quer ser", "digite a letra", "Eu quero ser",
     "Digite a sigla para preencher a posição", "EMPATE", "Venceu"},
    {"Aguarde", "Opção", "Digite", "para", "ou", "Opção inválida", "Jogador"}};

LanguageStrings *cl = &english;

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
  printf("\n%s", cl->general[0]);
  for (int i = 0; i < 5; i++) {
    Sleep(timeInSeconds * 1000);
    printf(" .");
  }
}

int showMainMenu() {
  int validation;
  do {
    showImage(imagesPath[0]);

    printf("\n\n\n%s     1 - %s\n", cl->tabulation, cl->mainMenu[0]);
    printf("%s     2 - %s\n", cl->tabulation, cl->mainMenu[1]);
    printf("%s     3 - %s\n", cl->tabulation, cl->mainMenu[2]);
    printf("\n%s     %s: ", cl->tabulation, cl->general[1]);

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