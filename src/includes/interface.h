#ifndef INTERFACE_H
#define INTERFACE_H

#define TRUE 1
#define FALSE 0
#define NUMBER_OF_PLAYERS 2

typedef struct {
  char name[25];
  int win, lose, draw;
} PlayerData;

typedef struct {
  const char *locale;
  const char *tabulation;
  const char *boardPosition[9];
  const char *positionName[9];
  const char *mainMenu[3];
  const char *firstOption[16];
  const char *general[9];
} LanguageStrings;

extern PlayerData players[NUMBER_OF_PLAYERS];
extern char board[3][3];
extern char *lang;
extern char *path;
extern char *imagesPath[4];

extern LanguageStrings english;
extern LanguageStrings portuguese;
extern LanguageStrings *cl;

char *getPath(char *path);
char *obtainLanguage(int argc, char *argv[]);

void showImage(char *imagePath);
void showLogo();
int showMainMenu();

void wait(float timeInSeconds);
void gameMenu(int option);

#endif