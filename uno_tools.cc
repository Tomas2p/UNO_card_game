/**
 * @author Tomás Pino Pérez
 * @brief Implementation of tools
 * @date 09-02-2023
 * @file uno_tool.cc
 */

#include "uno_tools.h"

#include "card_pack_class.h"
#include "player_class.h"

// read art from file resources.art (inicio line to fin line)
void ReadArt(const std::string& file_name, const int inicio, const int fin) {
  std::ifstream File(file_name);
  std::string file_text;
  for (int i{0}; i < inicio; ++i) {
    getline(File, file_text);
  }
  std::cout << '\n';
  for (int i{inicio}; i < fin - 1; ++i) {
    getline(File, file_text);
    std::cout << file_text << '\n';
  }
  std::cout << '\n';
  File.close();
}

// wait until ENTER or SPACE keypressed
void PressKey() {
  std::cout << " Presione ENTER para continuar... ";
  while (getchar() != ' ' && getchar() != '\n') {
  }
}

// manage menu of the game
void Menu(int& option) {
  Clear();
  // UNO logo for the game
  UnoLogo();
  // display menu options
  DisplayOptions();
  std::cout << "\n >>> ";
  std::cin >> option;
}

// events
void EventFinish() { Clear(); }

void EventInfo() {
  Clear();
  DisplayInfo();
  PressKey();
}

void EventOptions() {
  Clear();
  DisplayOptions();
  PressKey();
}

void EventRules() {
  Clear();
  DisplayRules();
  PressKey();
}

void EventCredits() {
  Clear();
  DisplayCredits();
  PressKey();
}

void EventOnlineGame() {
  Clear();
  DisplayOnlineGame();
  PressKey();
}

// display SeeCardPack title
void DisplaySeeCardPack() {
  std::cout << BCYNB << BBLK << " || " << reset << "\t\t\t\t\t\t\t\t " << BCYNB
            << BBLK << " || " << reset << "\n";
  std::cout << BCYNB << BBLK << "-++-" << reset
            << "\t  Mira la baraja de cartas con las que vas a jugar\t "
            << BCYNB << BBLK << "-++-" << reset << "\n";
  std::cout << BCYNB << BBLK << " || " << reset << "\t\t\t\t\t\t\t\t " << BCYNB
            << BBLK << " || " << reset << "\n\n";
}
void EventSeeCardPack() {
  // initialize variables
  int option;
  CardPack card_pack;
  CardPack card_pack_shuffle;

  // menu logic
  do {
    Clear();

    // print the back of card and event title
    DisplaySeeCardPack();

    // menu options
    std::cout << " [0] - Volver atrás.\n";
    std::cout << " [1] - Baraja original.\n";
    std::cout << " [2] - Barajar (la baraja del juego es independiente).\n";
    std::cout << "\n >>> ";
    std::cin >> option;
    switch (option) {
      case 0:  // finish event
        Clear();
        break;

      case 1:  // see card pack
        Clear();
        // print the back of card and event title
        DisplaySeeCardPack();
        std::cout << card_pack.Print(14);
        PressKey();
        break;

      case 2:  // shuffle card pack
        Clear();
        card_pack_shuffle.ShufflePack();
        // print the back of card and event title
        DisplaySeeCardPack();
        std::cout << card_pack_shuffle.Print(14);
        PressKey();
        break;

      default:
        EventSeeCardPack();
        break;
    }
  } while (option != 0);
}