#ifndef CHESS_PAWN_HH
#define CHESS_PAWN_HH

#include "bitboard.hh"
#include "board.hh"
#include "move.hh"

namespace chess {

template <Color Turn>
Move *generate_pawn_pushes(const Board &board, Move *moves) {
    constexpr Bitboard double_push_rank = Turn == WHITE ? RANK_3_BB : RANK_6_BB;
    constexpr Bitboard promotion_rank = Turn == WHITE ? RANK_7_BB : RANK_2_BB;
    constexpr Direction push_direction = Turn == WHITE ? NORTH : SOUTH;

    Bitboard pawns = board.pieces[PAWN] & board.colors[board.turn];
    Bitboard non_promoting_pawns = pawns & ~promotion_rank;
    Bitboard empty_squares = ~board.get_pieces();

    Bitboard single_pushes = shift<push_direction>(non_promoting_pawns) & empty_squares;
    Bitboard double_pushes = shift<push_direction>(single_pushes & double_push_rank) & empty_squares;

    while (single_pushes) {
        Square to = pop_lsb(single_pushes);
        *moves++ = Move(to - NORTH, to);
    }

    while (double_pushes) {
        Square to = pop_lsb(double_pushes);
        *moves++ = Move(to - 2 * NORTH, to);
    }

    return moves;
}

}  // namespace chess

#endif  // CHESS_PAWN_HH
