//
// Created by Андрей Боровец on 14.04.2021.
//

#ifndef SOLITAIRE_POSITION_H
#define SOLITAIRE_POSITION_H

#include <utility>
#include <vector>
#include <stack>

using FaceValue = uint32_t;
using Suit = uint32_t ;
//enum Suit {
//    Spades=0,
//    Hearts=1,
//    Clubs=2,
//    Diamonds=3
//};

class Card;

class Move {
public:
    Move(const std::vector<Card>& cards, uint32_t column_from, uint32_t column_to);
    std::vector<Card> cards_;
    uint32_t column_from_;
    uint32_t column_to_;
};

class Card {
public:
    Card(Suit suit, FaceValue face_value);
    Suit suit_;
    FaceValue face_value_; // [ 6 - 14 ]
};

class Column {
public:
    Column(const std::vector<Card>& col);
    Card operator[](uint32_t i) const;
    Card& operator[](uint32_t i);
    uint32_t GetOpenSepInd() const;
    uint32_t Size() const;
    void PopBack();
    void PushBack(const Card& card);

private:
    std::vector<Card> cards_;
    uint32_t open_sep_ind_;
};

class Position {
public:
    Position(uint16_t cnt_column, uint16_t cnt_decks);
    std::vector<Move> GetPossibleMoves();
    static void MakeEvristic(const std::vector<Move>& moves);
    Position& DoMove(const Move& move);
    void GoBackToPrevMove();
    bool Win() const;
    bool Strike();

private:
    static std::vector<Move> GetPossibleMoves(const std::vector<Column>& columns);
    std::vector<Column> columns_;
    std::stack<Move> moves_;
};








#endif //SOLITAIRE_POSITION_H
