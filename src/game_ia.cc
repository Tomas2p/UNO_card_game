/**
 * @author Tomás Pino Pérez
 * @brief Implementation of tools
 * @date 09-02-2023
 * @file uno_tool.cc
 */

#include "card_pack_class.h"
#include "player_class.h"
#include "uno_tools.h"

// configuration for the game (number of players, name_human)
void GameConfigurations(int& num_players, std::string& name_human) {
  // get number of IA
  std::cout << "\n Vas a jugar contra la IA, ajustes de la partida:\n\n";
  std::cout << "  - Cantidad de oponentes IA: ";
  std::cin >> num_players;
  num_players += 1;  // add human

  // get human data
  std::cout << "  - Nombre del Jugador: ";
  std::cin >> name_human;
  Clear();
}

// get the position of the card in the card_pack
int CardIndex() {
  int card_index;
  std::cout << "  - Posición de la carta (desde 1): ";
  std::cin >> card_index;
  return card_index;
}

// event IA game secuence
void EventIAGame() {
  Clear();
  int option;

  // game configurations
  int num_players;
  std::string name_human;
  GameConfigurations(num_players, name_human);

  // card_pack to shuffle and give to players
  CardPack card_pack;
  card_pack.ShufflePack();  // shuffle it

  // game_card_pack
  CardPack game_card_pack;
  game_card_pack.clear();  // clear it

  // create players human[0] and IAs[1+]
  Player* players[num_players];
  players[0] = new Player(name_human);  // human
  for (int i{1}; i < num_players; ++i) {
    players[i] = new Player("IA_" + std::to_string(i));  // IAs
  }

  // give players cards from shuffled card_pack
  while (players[0]->card_pack().size() != 7) {
    for (int i{0}; i < num_players; ++i) {
      players[i]->CardGlobalToPlayerByIndex(card_pack, 0);
    }
  }

  // give the game_card_pack the first card to play with
  while (card_pack.pack()[0].type() > 10) {
    card_pack.ShufflePack();
  }
  game_card_pack.push_back(card_pack.pack()[0], card_pack.pack_color()[0]);
  card_pack.erase(0);

  // vector with the order turns by player name
  std::vector<std::string> players_name;
  players_name.reserve(num_players);
  for (int i{0}; i < num_players; ++i) {
    players_name.push_back(players[i]->name());
    players[i]->turn(i);
  }

  // IAGameMenu();
  do {
    Clear();

    // print title
    std::cout << "\n Jugando al UNO++ contra " << num_players - 1 << " IAs\n";

    // special card reverse rules
    if (game_card_pack.pack().back().type() == 11) {
      std::vector<std::string> aux_players_name;
      aux_players_name.reserve(players_name.size());
      std::reverse(players_name.begin(), players_name.end());
      aux_players_name.push_back(players_name.back());
      for (int i{0}; i < players_name.size() - 1; ++i) {
        aux_players_name.push_back(players_name.at(i));
      }
      for (int i{0}; i < aux_players_name.size(); ++i) {
        players_name.at(i) = aux_players_name.at(i);
      }
      aux_players_name.clear();
    }

    // special card +2 and +4 rules
    if (game_card_pack.pack().back().type() == 10) {
    }

    // print the players name and number of card
    std::cout << "\n Orden: ";
    for (int i{0}; i < players_name.size(); ++i) {
      std::cout << players_name.at(i);
      if (i != num_players - 1) {
        std::cout << " > ";
      }
    }

    std::cout << "\n\n\n";

    // print backcard and last card in game_card_pack
    std::cout << game_card_pack.PrintGameTable() << "\n\n";

    // print human player card_pack
    std::cout << players[0]->Print(7);

    // print option for human to do in the game
    std::cout << " [0] - Abandonar partida.\n";
    std::cout << " [1] - Poner carta.\n";
    std::cout << " [2] - Coger carta.\n";
    std::cout << " [3] - Gritar UNO++.\n";
    std::cout << " [4] - Debug options.\n";
    std::cout << "\n >>> ";
    std::cin >> option;

    // card_index initialization
    int card_index;
    // case 1 loop checker
    bool is_card_valid{false};

    switch (option) {
      case 0:  // finish game
        Clear();
        break;

      case 1:  // put index card - 1 from player to game_card_pack
        std::cout << "\n Vas a poner una carta en el mazo de juego\n";
        while (!is_card_valid) {
          card_index = CardIndex();
          if (game_card_pack.Check(players[0]->card_pack()[card_index - 1])) {
            players[0]->CardPlayerToGlobalByIndex(game_card_pack,
                                                  card_index - 1);
            is_card_valid = true;
          } else {
            std::cout << "\n No es una carta válida, prueba otra.\n\n";
            is_card_valid = false;
          }
        }
        break;

      case 2:  // take first card from card_pack to player
        std::cout << "\n Vas a coger una carta del mazo\n";
        players[0]->CardGlobalToPlayerByIndex(card_pack, 0);
        break;

      case 3:  // shout UNO++
        Clear();
        break;

      case 4:  // debug options
        // print all the card_pack to debug
        for (int i{0}; i < num_players; ++i) {
          std::cout << " Baraja " << players[i]->name() << "\n"
                    << players[i]->Print(7);
        }
        std::cout << " Baraja game_card_pack\n" << game_card_pack.Print(14);
        std::cout << " Baraja card_pack\n" << card_pack.Print(14);
        PressKey();
        break;

      default:
        break;
    }
  } while (option != 0);
}