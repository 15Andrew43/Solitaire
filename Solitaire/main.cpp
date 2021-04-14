#include <iostream>

#include "Position.h"

bool Convergence(Position& position);

int main() {

    Position position(8, 2);

    Convergence(position);

    std::cout << (Convergence(position) ? "YES" : "NO");

    return 0;
}

bool Convergence(Position& position) {
    if (position.Win()) {
        return true;
    }
    std::vector<Move> possible_moves = position.GetPossibleMoves();

    position.MakeEvristic(possible_moves);

//    for (auto move: possible_moves) {
//        std::cout << move.column_to_ << ' ' << move.column_from_ << ' '
//                  << move.cards_[0].suit_ << '\n';
//    }

    for (const auto& move: possible_moves) {
//        if (Convergence(position.DoMove(move))) {
//            return true;
//        }
    }
    return false;
}
