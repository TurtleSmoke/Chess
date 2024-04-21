#include "board.hh"
#include <gmock/gmock.h>

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

    ASSERT_THAT(actual.board, testing::ElementsAreArray(expected_board));
    ASSERT_EQ(actual.turn, WHITE);
    ASSERT_EQ(actual.castling_rights, ANY_CASTLING);
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