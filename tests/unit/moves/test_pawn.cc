#include "board.hh"
#include "move.hh"
#include "pawn.hh"
#include <gmock/gmock.h>

namespace chess {

#define ASSERT_MOVES(fen, expected, turn, function) \
    do {                                            \
        const Board actual(fen);                    \
        Move moves[MAX_NUM_MOVES];                  \
        Move* last = function<turn>(actual, moves); \
        ASSERT_EQ(last - moves, expected);          \
    } while (0)

// Define a macro instead of a function so the failing test will show the correct line number
#define ASSERT_PUSHES(fen, expected, turn)                       \
    do {                                                         \
        ASSERT_MOVES(fen, expected, turn, generate_pawn_pushes); \
    } while (0)

#define ASSERT_ATTACKS(fen, expected, turn)                       \
    do {                                                          \
        ASSERT_MOVES(fen, expected, turn, generate_pawn_attacks); \
    } while (0)

#define ASSERT_PROMOTIONS(fen, expected, turn)                       \
    do {                                                             \
        ASSERT_MOVES(fen, expected, turn, generate_pawn_promotions); \
    } while (0)

// Pawn pushes
TEST(PAWN_MOVES, white_pawn_starting) { ASSERT_PUSHES("8/8/8/8/8/8/PPPPPPPP/8 w HAha - 0 1", 16, WHITE); }

TEST(PAWN_MOVES, white_pawn_rank3) { ASSERT_PUSHES("8/8/8/8/8/PPPPPPPP/8/8 w HAha - 0 1", 8, WHITE); }

TEST(PAWN_MOVES, white_pawn_no_move) { ASSERT_PUSHES("8/8/8/8/8/4p3/4P3/8 w HAha - 0 1", 0, WHITE); }

TEST(PAWN_MOVES, black_pawn_starting) { ASSERT_PUSHES("8/pppppppp/8/8/8/8/8/8 b HAha - 0 1", 16, BLACK); }

TEST(PAWN_MOVES, black_pawn_rank6) { ASSERT_PUSHES("8/8/pppppppp/8/8/8/8/8 b HAha - 0 1", 8, BLACK); }

TEST(PAWN_MOVES, black_pawn_no_move) { ASSERT_PUSHES("8/4p3/4P3/8/8/8/8/8 b HAha - 0 1", 0, BLACK); }

// Pawn attacks
TEST(PAWN_MOVES, white_pawn_attack) { ASSERT_ATTACKS("8/8/8/8/8/3p4/4P3/8 w HAha - 0 1", 1, WHITE); }

TEST(PAWN_MOVES, white_pawn_double_attacks) { ASSERT_ATTACKS("8/8/8/8/8/3p1p2/4P3/8 w HAha - 0 1", 2, WHITE); }

TEST(PAWN_MOVES, white_pawn_many_attacks) { ASSERT_ATTACKS("8/8/8/8/8/1p1p1p1p/P1P1P1P1/8 w HAha - 0 1", 7, WHITE); }

TEST(PAWN_MOVES, white_pawn_no_attacks) { ASSERT_ATTACKS("8/8/8/8/8/4P3/3P4/8 w HAha - 0 1", 0, WHITE); }

TEST(PAWN_MOVES, black_pawn_attack) { ASSERT_ATTACKS("8/4p3/3P4/8/8/8/8/8 b HAha - 0 1", 1, BLACK); }

TEST(PAWN_MOVES, black_pawn_double_attacks) { ASSERT_ATTACKS("8/4p3/3P1P2/8/8/8/8/8 b HAha - 0 1", 2, BLACK); }

TEST(PAWN_MOVES, black_pawn_many_attacks) { ASSERT_ATTACKS("8/p1p1p1p1/1P1P1P1P/8/8/8/8/8 b HAha - 0 1", 7, BLACK); }

TEST(PAWN_MOVES, black_pawn_no_attacks) { ASSERT_ATTACKS("8/4P3/3p4/8/8/8/8/8 b HAha - 0 1", 0, BLACK); }

// Pawn promotions
TEST(PAWN_MOVES, white_pawn_promotion) { ASSERT_PROMOTIONS("8/3P4/8/8/8/8/8/8 w HAha - 0 1", 4, WHITE); }

TEST(PAWN_MOVES, white_pawn_attacks_only) { ASSERT_PROMOTIONS("2ppp3/3P4/8/8/8/8/8/8 w HAha - 0 1", 8, WHITE); }

TEST(PAWN_MOVES, white_pawn_all) { ASSERT_PROMOTIONS("2p1p3/3P4/8/8/8/8/8/8 w HAha - 0 1", 12, WHITE); }

TEST(PAWN_MOVES, white_pawn_hard) { ASSERT_PROMOTIONS("2ppp3/3PPPP1/8/8/8/8/8/8 w HAha - 0 1", 24, WHITE); }

TEST(PAWN_MOVES, black_pawn_promotion) { ASSERT_PROMOTIONS("8/8/8/8/8/8/3p4/8 b HAha - 0 1", 4, BLACK); }

TEST(PAWN_MOVES, black_pabn_attacks_only) { ASSERT_PROMOTIONS("8/8/8/8/8/8/3p4/2PPP3 b HAha - 0 1", 8, BLACK); }

TEST(PAWN_MOVES, black_pabn_all) { ASSERT_PROMOTIONS("8/8/8/8/8/8/3p4/2P1P3 b HAha - 0 1", 12, BLACK); }

TEST(PAWN_MOVES, black_pabn_hard) { ASSERT_PROMOTIONS("8/8/8/8/8/8/3pppp1/2PPP3 b HAha - 0 1", 24, BLACK); }
}  // namespace chess
