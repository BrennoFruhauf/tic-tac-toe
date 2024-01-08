#include <locale.h>
#include <string.h>

#include "./includes/interface.h"

int main(int argc, char *argv[]) {
  lang = obtainLanguage(argc, argv);
  path = getPath(argv[0]);

  if (strcmp(lang, "pt") == 0) currentLanguage = &portuguese;

  setlocale(LC_ALL, currentLanguage->locale);
  showLogo();

  int option;
  do {
    option = showMainMenu();
    gameMenu(option);
  } while (option != 3);

  return 0;
}