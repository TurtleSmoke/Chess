#include "board.hh"

#include <cassert>
#include <cctype>
#include <cstring>
#include <sstream>

namespace chess {

/*
 * Initializes the board from the given FEN string.
 * No error checking is done on the FEN string as it is assumed to be valid
 * and verified in the frontend.
 */
Board::Board(const std::string& fen) {
    std::istringstream ss(fen);

    ss >> std::noskipws;

    // Handle Piece placement
    unsigned char token = 0;
    Square current_square = SQ_A8;
    while ((ss >> token) && !isspace(token)) {
        if (isdigit(token)) {
            current_square += (token - '0') * EAST;
        } else if (token == '/') {
            current_square += 2 * SOUTH;
        } else {
            place_piece(Piece(piece_to_char.find(token)), current_square);
            ++current_square;
        }
    }

    // TODO: Handle the rest of the FEN string
    ss >> token;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (Rank rank = RANK_8; rank >= RANK_1; --rank) {
        for (File file = FILE_A; file <= FILE_H; ++file) {
            os << piece_to_char[board.piece_on(at(file, rank))] << " ";
        }
        os << "\n";
    }
    return os;
}

}  // namespace chess