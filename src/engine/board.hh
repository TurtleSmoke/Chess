#ifndef CHESS_BOARD_HH
#define CHESS_BOARD_HH

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string_view>

namespace chess {

using Bitboard = uint64_t;
constexpr std::string_view piece_to_char(".PNBRQK  pnbrqk");

enum Color : int {
    WHITE,
    BLACK,
    COLOR_NB = 2
};

// clang-format off
enum PieceType : int {
    NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    ALL_PIECES = 0,
    PIECE_TYPE_NB = 8
};

enum Piece : int {
    NO_PIECE,
    W_PAWN = PAWN,     W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = PAWN + 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 16
};

// SQ_A1 is the bottom left square (White Rook) and SQ_H8 is the top right square (Black Rook)
enum Square : int {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,

    SQUARE_ZERO = 0,
    SQUARE_NB   = 64
};

enum CastlingRights {
    NO_CASTLING,
    WHITE_KING_SIDE,
    WHITE_QUEEN_SIDE = WHITE_KING_SIDE << 1,
    BLACK_KING_SIDE  = WHITE_KING_SIDE << 2,
    BLACK_QUEEN_SIDE = WHITE_KING_SIDE << 3,

    KING_SIDE      = WHITE_KING_SIDE | BLACK_KING_SIDE,
    QUEEN_SIDE     = WHITE_QUEEN_SIDE | BLACK_QUEEN_SIDE,
    WHITE_CASTLING = WHITE_KING_SIDE | WHITE_QUEEN_SIDE,
    BLACK_CASTLING = BLACK_KING_SIDE | BLACK_QUEEN_SIDE,
    ANY_CASTLING   = WHITE_CASTLING | BLACK_CASTLING,

    CASTLING_RIGHT_NB = 16
};
// clang-format on

enum File : int {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB
};

enum Rank : int {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB
};

enum Direction : int {
    NORTH = 8,
    EAST = 1,
    SOUTH = -NORTH,
    WEST = -EAST,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
    NORTH_WEST = NORTH + WEST
};

class Board {
   public:
    explicit Board(const std::string& fen);

    void place_piece(Piece piece, Square square);
    [[nodiscard]] Piece piece_on(Square square) const;

    Piece board[SQUARE_NB] = {NO_PIECE};
    Bitboard pieces[PIECE_TYPE_NB] = {0};
    Bitboard colors[COLOR_NB] = {0};

    int turn = WHITE;
    int castling_rights = NO_CASTLING;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

// Sanity check
constexpr bool valid_square(Square square) { return square >= SQ_A1 && square <= SQ_H8; }

constexpr bool valid_piece(Piece piece) {
    return (piece >= W_PAWN && piece <= W_KING) || (piece >= B_PAWN && piece <= B_KING);
}

// Utils bitboard functions
constexpr Square at(File file, Rank rank) { return Square((rank << 3) + file); }

inline Piece Board::piece_on(Square square) const {
    assert(valid_square(square) && "Invalid square");

    return board[square];
}

constexpr Bitboard square_to_bb(Square square) {
    assert(valid_square(square));

    return Bitboard(1) << square;
}

constexpr PieceType type_of(Piece piece) {
    assert(piece != NO_PIECE && piece != PIECE_NB && "Invalid piece");

    // Piece is encoded on 4 bits with the type being the 3 lowest bits
    // So we apply a mask to get the 3 lowest bits
    constexpr int PIECE_TYPE_MASK = 0b111;
    return PieceType(piece & PIECE_TYPE_MASK);
}

constexpr Color color_of(Piece piece) {
    assert(piece != NO_PIECE && piece != PIECE_NB && "Invalid piece");

    // Piece is encoded on 4 bits with the color being the 4th bit
    // So we shift the piece to the right by 3 bits to get the color
    constexpr int COLOR_BIT = 3;
    return Color(piece >> COLOR_BIT);
}

// Overload ++ and -- operators:
inline Rank& operator--(Rank& rank) { return rank = Rank(int(rank) - 1); }
inline File& operator++(File& file) { return file = File(int(file) + 1); }
inline Square& operator++(Square& square) { return square = Square(int(square) + 1); }

// Handle square and direction operations
constexpr Direction operator*(int x, Direction dir) { return Direction(x * int(dir)); }
constexpr Square operator-(Square square, Direction dir) { return Square(int(square) - int(dir)); }
constexpr Square operator+(Square square, Direction dir) { return Square(int(square) + int(dir)); }
inline Square& operator+=(Square& square, Direction dir) { return square = square + dir; }
inline Square& operator-=(Square& square, Direction dir) { return square = square - dir; }

// Overload binary operators for bitboards
inline Bitboard operator&(Bitboard b, Square s) { return b & square_to_bb(s); }
inline Bitboard operator|(Bitboard b, Square s) { return b | square_to_bb(s); }
inline Bitboard operator^(Bitboard b, Square s) { return b ^ square_to_bb(s); }
inline Bitboard& operator|=(Bitboard& b, Square s) { return b |= square_to_bb(s); }
inline Bitboard& operator^=(Bitboard& b, Square s) { return b ^= square_to_bb(s); }

inline Bitboard operator&(Square s, Bitboard b) { return b & s; }
inline Bitboard operator|(Square s, Bitboard b) { return b | s; }
inline Bitboard operator^(Square s, Bitboard b) { return b ^ s; }

inline Bitboard operator|(Square s1, Square s2) { return square_to_bb(s1) | s2; }

// Useful board operations
inline void Board::place_piece(Piece piece, Square square) {
    assert(valid_square(square) && valid_piece(piece) && "Invalid piece or square");

    board[square] = piece;
    pieces[ALL_PIECES] |= pieces[type_of(piece)] |= square;
    colors[color_of(piece)] |= square;
}

}  // namespace chess

#endif  // CHESS_BOARD_HH