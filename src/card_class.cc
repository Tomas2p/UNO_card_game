/**
 * @author Tomás Pino Pérez
 * @brief Implementation of class for card
 * @date 09-02-2023
 * @file card_class.cc
 */

#include "card_class.h"

// constructor
Card::Card(int color, int type) {
  color_ = color;
  type_ = type;
}

// print card
std::string Card::Print() {
  return (kColors_[color_] + ' ' + kTypes_[type_] + ' ' + reset);
}

// operator<< overload
std::ostream& operator<<(std::ostream& out, const Card& card) {
  out << card.kColors_[card.color_] + ' ' + card.kTypes_[card.type_] + ' ';
  out << reset;
  return out;
}

// operator= overload
Card& Card::operator=(const Card& card) {
  color_ = card.color_;
  type_ = card.type_;
  return *this;
}

// operator== overload
bool Card::operator==(const Card& card) const {
  return (type_ == card.type_ && color_ == card.color_);
}

// swap function
void swap(Card& card1, Card& card2) {
  int temp_color{card1.color_}, temp_type{card1.type_};
  card1.color_ = card2.color_;
  card1.type_ = card2.type_;
  card2.color_ = temp_color;
  card2.type_ = temp_type;
}

// erase function
void erase(const int& index) {}