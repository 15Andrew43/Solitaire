//
// Created by Андрей Боровец on 14.04.2021.
//

#include "Position.h"
#include <random>
#include <iostream>

Position::Position(uint16_t cnt_column, uint16_t cnt_decks) {
    std::vector<Card> generator;
    for (uint32_t i = 6; i < 15; ++i) {
        for (uint32_t j = 0; j < cnt_decks; ++j) {
            for (uint32_t k = 0; k < 4; ++k) {
                generator.emplace_back(k, i);
            }
        }
    }
    std::vector<Card> real_generator;
    for (uint32_t i = 0; i < cnt_decks * 36; ++i) {
        uint32_t number = std::rand() % generator.size();
        std::swap(generator[number], generator.back());
        real_generator.push_back(generator.back());
        generator.pop_back();
    }

    uint32_t cnt_card_in_col = cnt_decks * 36 / cnt_column;

    for (uint32_t i = 0; i < cnt_column; ++i) {
        std::vector<Card> col;
        col.clear();
        for (uint32_t j = i * cnt_card_in_col; j < cnt_card_in_col * (i+1); ++j) {
            col.push_back(real_generator[j]);
        }
        columns_.push_back(Column(col));
    }
}

std::vector<Move> Position::GetPossibleMoves(const std::vector<Column>& columns) {
    std::vector<Move> moves;
    std::vector<Card> move_cards;
    for (uint32_t i = 0; i < columns.size(); ++i) {
        for (uint32_t j = 0; j < columns.size(); ++j) {
            if (i == j) {
                continue;
            }
            auto sep1 = columns[i].GetOpenSepInd();
            auto sep2 = columns[j].GetOpenSepInd();
            if (columns[i][sep1].face_value_ == columns[j][sep2].face_value_ + 1) {
                move_cards.clear();
                for (uint32_t k = sep1; k < columns[i].Size(); ++k) {
                    move_cards.push_back(columns[i][k]);
                }
                moves.emplace_back(move_cards, i, j);
            }
        }
    }
    return moves;
}

void Position::MakeEvristic(const std::vector<Move> &moves) {
}

std::vector<Move> Position::GetPossibleMoves() {
    return GetPossibleMoves(columns_);
}



bool Position::Win() const {
    for (const auto& col: columns_) {
        if (col.Size() != 0) {
            return false;
        }
    }
    return true;
}

Position& Position::DoMove(const Move& move) {
    auto column_from = move.column_from_;
    auto column_to = move.column_to_;
    std::vector<Card> move_cards = move.cards_;
    for (uint32_t i = 0; i < move_cards.size(); ++i) {
        columns_[column_from].PopBack();
    }
    for (uint32_t i = 0; i < move_cards.size(); ++i) {
        columns_[column_to].PushBack(move_cards[i]);
    }
    moves_.push(move);
    Strike();
    return *this;
}

void Position::GoBackToPrevMove() {
    // go to the previous step( in order not to copy a lot)
}

bool Position::Strike() {
    // if right position - delete cards.
    return false;
}


Card::Card(Suit suit, FaceValue face_value) : suit_(suit), face_value_(face_value){
}

Column::Column(const std::vector<Card>& col) {
    cards_ = col;
    open_sep_ind_ = col.size() - 1;
}

Card Column::operator[](uint32_t i) const {
    return cards_[i];
}

Card& Column::operator[](uint32_t i) {
    return cards_[i];
}

uint32_t Column::GetOpenSepInd() const {
    return open_sep_ind_;
}

uint32_t Column::Size() const {
    return cards_.size();
}

void Column::PopBack() {
    cards_.pop_back();
}

void Column::PushBack(const Card& card) {
    cards_.push_back(card);
}



Move::Move(const std::vector<Card> &cards, uint32_t column_from, uint32_t column_to)
    : cards_(cards), column_from_(column_from), column_to_(column_to) {
}
