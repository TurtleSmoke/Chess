#ifndef CHESS_BITBOARD_HH
#define CHESS_BITBOARD_HH

#include "board.hh"

namespace chess {

inline Square lsb(Bitboard& bitboard) {
    assert(bitboard && "Bitboard is empty");
    return Square(__builtin_ctzll(bitboard));
}

inline Square pop_lsb(Bitboard& bitboard) {
    assert(bitboard && "Bitboard is empty");
    const Square square = lsb(bitboard);
    bitboard &= bitboard - 1;
    return square;
}
}  // namespace chess

#endif  // CHESS_BITBOARD_HH
