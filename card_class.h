/**
 * @author Tomás Pino Pérez
 * @brief Declarations of class for card
 * @date 09-02-2023
 * @file card_class.h
 */

#include <iostream>
#include <string>

#include "ANSI-color-codes.h"

// Class for manage the card
#ifndef CARD_CLASS_H
#define CARD_CLASS_H

class Card {
 public:
  // constructor
  Card(int color, int type);

  // operator<< overload
  friend std::ostream& operator<<(std::ostream&, const Card&);
  // operator= overload
  Card& operator=(const Card& card);
  // operator== overload
  bool operator==(const Card& card) const;

  // swap function
  friend void swap(Card& card1, Card& card2);
  // erase function
  friend void erase(const int& index);

  // print card
  std::string Print();

  // getters
  int color() { return color_; }
  int type() { return type_; }
  std::string color_display() { return kColors_[color_]; }
  std::string type_display() { return kTypes_[type_]; }

  // setters
  void color(int color) { color_ = color; }

 private:
  // background colors: red, blue, green, yellow, white
  const std::string kColors_[5] = {BREDB, BBLUB, BGRNB, BYELB, BWHTB};
  // numbers 0-9; plus +2, +4; change direccion ><; change color <>; block XX
  const std::string kTypes_[15] = {BBLK "00", BBLK "01", BBLK "02", BBLK "03",
                                   BBLK "04", BBLK "05", BBLK "06", BBLK "07",
                                   BBLK "08", BBLK "09", BBLK "+2", BBLK "><",
                                   BBLK "XX", BBLK "<>", BBLK "+4"};
  // eassy to implement by index of the const string with the similar name
  int color_;
  int type_;
};

#endif
