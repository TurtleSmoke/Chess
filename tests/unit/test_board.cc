#include "board.hh"
#include <gmock/gmock.h>

extern "C" {
void __ubsan_on_report() { FAIL() << "Encountered an undefined behavior sanitizer error"; }
void __asan_on_error() { FAIL() << "Encountered an address sanitizer error"; }
void __tsan_on_report() { FAIL() << "Encountered a thread sanitizer error"; }
}  // extern "C"

namespace chess {

TEST(BOARD, default_fen) {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    chess::Board actual(fen);

    // clang-format off
    Piece expected_board[SQUARE_NB] = {
        W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK,
        W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN, W_PAWN,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
        B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN, B_PAWN,
        B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK,
    };
    // clang-format on

    Bitboard expected_pieces[PIECE_TYPE_NB] = {
        0xFFFF00000000FFFF, 0x00FF00000000FF00, 0x4200000000000042, 0x2400000000000024,
        0x8100000000000081, 0x0800000000000008, 0x1000000000000010, 0x0000000000000000,
    };
    Bitboard expected_color[COLOR_NB] = {
        0x000000000000FFFF,
        0xFFFF000000000000,
    };

    ASSERT_THAT(actual.board, testing::ElementsAreArray(expected_board));
    ASSERT_EQ(actual.turn, WHITE);
    ASSERT_EQ(actual.castling_rights, ANY_CASTLING);
    ASSERT_THAT(actual.pieces, testing::ElementsAreArray(expected_pieces));
    ASSERT_THAT(actual.colors, testing::ElementsAreArray(expected_color));
}
TEST(BOARD, print_default_fen) {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    chess::Board board(fen);
    std::ostringstream oss;
    oss << board;

    std::string expected =
        "r n b q k b n r \n"
        "p p p p p p p p \n"
        ". . . . . . . . \n"
        ". . . . . . . . \n"
        ". . . . . . . . \n"
        ". . . . . . . . \n"
        "P P P P P P P P \n"
        "R N B Q K B N R \n";

    ASSERT_EQ(oss.str(), expected);
}
}  // namespace chess
