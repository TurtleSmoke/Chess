#include "board.hh"
#include <iostream>

int main() {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    chess::Board board(fen);
    std::cout << board << std::endl;
    return 0;
}
