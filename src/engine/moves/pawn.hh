#ifndef CHESS_PAWN_HH
#define CHESS_PAWN_HH

#include "bitboard.hh"
#include "board.hh"
#include "move.hh"

namespace chess {

template <Color TURN>
Move *generate_pawn_pushes(const Board &board, Move *moves) {
    constexpr Bitboard double_push_rank = TURN == WHITE ? RANK_3_BB : RANK_6_BB;
    constexpr Bitboard promotion_rank = TURN == WHITE ? RANK_7_BB : RANK_2_BB;
    constexpr Direction push_direction = TURN == WHITE ? NORTH : SOUTH;

    Bitboard pawns = board.pieces[PAWN] & board.colors[TURN];
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

template <Color TURN>
Move *generate_pawn_attacks(const Board &board, Move *moves) {
    constexpr Direction left_attack = TURN == WHITE ? NORTH_WEST : SOUTH_EAST;
    constexpr Direction right_attack = TURN == WHITE ? NORTH_EAST : SOUTH_WEST;
    constexpr Bitboard promotion_rank = TURN == WHITE ? RANK_7_BB : RANK_2_BB;
    constexpr Color enemy = ~TURN;

    Bitboard pawns = board.pieces[PAWN] & board.colors[TURN];
    Bitboard non_promoting_pawns = pawns & ~promotion_rank;
    Bitboard their_pieces = board.colors[enemy];

    Bitboard left_attacks = shift<left_attack>(non_promoting_pawns) & their_pieces;
    Bitboard right_attacks = shift<right_attack>(non_promoting_pawns) & their_pieces;

    while (left_attacks) {
        Square to = pop_lsb(left_attacks);
        *moves++ = Move(to - left_attack, to);
    }

    while (right_attacks) {
        Square to = pop_lsb(right_attacks);
        *moves++ = Move(to - right_attack, to);
    }

    return moves;
}

template <Direction Direction>
Move *make_promotion(const Square to, Move *moves) {
    *moves++ = Move(to - Direction, to, KNIGHT);
    *moves++ = Move(to - Direction, to, BISHOP);
    *moves++ = Move(to - Direction, to, ROOK);
    *moves++ = Move(to - Direction, to, QUEEN);

    return moves;
}

template <Color TURN>
Move *generate_pawn_promotions(const Board &board, Move *moves) {
    constexpr Bitboard promotion_rank = TURN == WHITE ? RANK_7_BB : RANK_2_BB;
    constexpr Direction push_direction = TURN == WHITE ? NORTH : SOUTH;
    constexpr Direction left_attack = TURN == WHITE ? NORTH_WEST : SOUTH_EAST;
    constexpr Direction right_attack = TURN == WHITE ? NORTH_EAST : SOUTH_WEST;

    const Bitboard emptySquares = ~board.get_pieces();
    const Bitboard their_pieces = board.colors[~TURN];

    Bitboard pawns = board.pieces[PAWN] & board.colors[TURN];
    Bitboard promoting_pawns = pawns & promotion_rank;

    if (promoting_pawns) {
        Bitboard single_push = (shift<push_direction>(promoting_pawns) & emptySquares);
        Bitboard left_attacks = (shift<left_attack>(promoting_pawns) & their_pieces);
        Bitboard right_attacks = (shift<right_attack>(promoting_pawns) & their_pieces);

        while (single_push) {
            moves = make_promotion<push_direction>(pop_lsb(single_push), moves);
        }

        while (left_attacks) {
            moves = make_promotion<left_attack>(pop_lsb(left_attacks), moves);
        }

        while (right_attacks) {
            moves = make_promotion<right_attack>(pop_lsb(right_attacks), moves);
        }
    }

    return moves;
}

}  // namespace chess

#endif  // CHESS_PAWN_HH
