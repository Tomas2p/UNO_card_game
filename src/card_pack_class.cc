/**
 * @author Tomás Pino Pérez
 * @brief Implementation of class for card_pack
 * @date 09-02-2023
 * @file card_pack_class.cc
 */

#include "card_pack_class.h"

// generate pack_
void CardPack::GeneratePack() {
  // generate the 0-9, +2, > <, XX cards
  for (int j{0}; j < 4; ++j) {
    pack_.push_back(Card(j, 0));
    for (int k{1}; k <= 12; ++k) {
      for (int i{0}; i < 2; ++i) {
        pack_.push_back(Card(j, k));
      }
    }
  }
  // generate the <> card
  for (int i{0}; i < 8; ++i) {
    pack_.push_back(Card(4, 13));
  }
  // generate the +4 card
  for (int i{0}; i < 4; ++i) {
    pack_.push_back(Card(4, 14));
  }
}

// generate pack_color_
void CardPack::GeneratePackColor() {
  for (int i{0}; i < kSize_; ++i) {
    std::string pack_color{pack_[i].color_display() + "    " + reset};
    pack_color_.push_back(pack_color);
  }
}

// constructor default 112 cards
CardPack::CardPack() {
  // reserve size of card pack
  pack_.reserve(kSize_);
  // generate pack_
  GeneratePack();
  // reserve size of color pack
  pack_color_.reserve(kSize_);
  // generate pack_color_
  GeneratePackColor();
}

// constructor of player card_pack
CardPack::CardPack(const int& size) {
  // reserve size of card pack
  pack_.reserve(size);
  // reserve size of color pack
  pack_color_.reserve(size);
}

// clear the card_pack
void CardPack::clear() {
  pack_.clear();
  pack_color_.clear();
}

// erase given index
void CardPack::erase(const int& index) {
  pack_.erase(pack_.begin() + index);
  pack_color_.erase(pack_color_.begin() + index);
}

// push_back
void CardPack::push_back(const Card& card_type, const std::string& card_color) {
  pack_.push_back(card_type);
  pack_color_.push_back(card_color);
}

// print cards until width
std::string CardPack::Print(const int& width) {
  std::string out;
  for (int i{0}; i < pack_.size() && i < pack_color_.size(); i += width) {
    for (int j{i}; (j < i + width) && (j < pack_color_.size()); ++j) {
      out.append(pack_color_[j] + " ");
    }
    out.append("\n");
    for (int j{i}; (j < i + width) && (j < pack_.size()); ++j) {
      out.append(pack_[j].Print());
      out.append(" ");
    }
    out.append("\n");
    for (int j{i}; (j < i + width) && (j < pack_color_.size()); ++j) {
      out.append(pack_color_[j] + " ");
    }
    out.append("\n\n");
  }
  return out;
}

// print the game table (backcard and las card in pack)
std::string CardPack::PrintGameTable() {
  std::string out;
  auto index{pack_.size() - 1};
  out.append("\t  ");
  out.append(BCYNB);
  out.append(BBLK);
  out.append(" || ");
  out.append(reset);
  out.append("\t    " + pack_color_[index] + "\n");
  out.append("\t  ");
  out.append(BCYNB);
  out.append(BBLK);
  out.append("-++-");
  out.append(reset);
  out.append("\t    " + pack_[index].Print() + "\n");
  out.append("\t  ");
  out.append(BCYNB);
  out.append(BBLK);
  out.append(" || ");
  out.append(reset);
  out.append("\t    " + pack_color_[index] + "\n");
  return out;
}

// mix the CardPack
void CardPack::ShufflePack() {
  std::mt19937 rgn(std::random_device{}());
  std::shuffle(pack_.begin(), pack_.end(), rgn);
  for (int i{0}; i < pack_.size(); ++i) {
    pack_color_[i] = (pack_[i].color_display() + "    " + reset);
  }
}

// check if the card to put is valid
bool CardPack::Check(Card& card) {
  bool value;
  if (pack_.back().type() == card.type()) {
    value = true;
  } else if (pack_.back().color() == card.color()) {
    value = true;
  } else if (card.color() == 4) {
    value = true;
  } else {
    value = false;
  }
  return value;
}