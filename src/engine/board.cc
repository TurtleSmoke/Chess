#include "board.hh"

#include <cctype>
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
    char token = 0;
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

    // Handle active color
    ss >> token;
    turn = (token == 'w') ? WHITE : BLACK;
    ss >> token;

    // Handle Castling rights
    while ((ss >> token) && isspace(token)) {
        if (token == 'K') {
            castling_rights |= WHITE_KING_SIDE;
        } else if (token == 'Q') {
            castling_rights |= WHITE_QUEEN_SIDE;
        } else if (token == 'k') {
            castling_rights |= BLACK_KING_SIDE;
        } else if (token == 'q') {
            castling_rights |= BLACK_QUEEN_SIDE;
        }
    }

    // TODO: Handle the rest of the FEN string when backend is more complete
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