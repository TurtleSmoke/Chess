#ifndef CHESS_MOVE_HH
#define CHESS_MOVE_HH

#include "board.hh"

namespace chess {

/*
 * Move representation:
 *
 * bit 0-5: destination square
 * bit 6-11: origin square
 * bit 12-13: promotion piece (0: KNIGHT, 1: BISHOP, 2: ROOK, 3: QUEEN)
 * bit 14-15: special flag (1: promotion, 2: en passant, 3: castling)
 */
constexpr int FROM_SHIFT = 6;
constexpr int MAX_NUM_MOVES = 256;

struct Move {
   public:
    Move() = default;

    constexpr Move(Square from, Square to) : data((from << FROM_SHIFT) + to) {}

   protected:
    std::uint16_t data;
};

}  // namespace chess

#endif  // CHESS_MOVE_HH
