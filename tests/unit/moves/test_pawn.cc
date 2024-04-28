#include "board.hh"
#include "move.hh"
#include "pawn.hh"
#include <gmock/gmock.h>

namespace chess {

// Instantiate the template function for the test
template Move* generate_pawn_pushes<WHITE>(const Board&, Move*);

// Define a macro instead of a function so the failing test will show the correct line number
#define ASSERT_MOVE(fen, expected, Turn)                     \
    do {                                                     \
        const Board actual(fen);                             \
        Move moves[MAX_NUM_MOVES];                           \
        Move* last = moves;                                  \
        if (Turn == BOTH) {                                  \
            last = generate_pawn_pushes<WHITE>(actual, last); \
            last = generate_pawn_pushes<BLACK>(actual, last); \
        } else {                                             \
            last = generate_pawn_pushes<Turn>(actual, last);  \
        }                                                    \
        ASSERT_EQ(last - moves, expected);                   \
    } while (0)

TEST(PAWN_MOVES, pawn_starting) { ASSERT_MOVE("8/8/8/8/8/8/PPPPPPPP/8 w HAha - 0 1", 16, WHITE); }

TEST(PAWN_MOVES, pawn_rank3) { ASSERT_MOVE("8/8/8/8/8/PPPPPPPP/8/8 w HAha - 0 1", 8, WHITE); }

TEST(PAWN_MOVES, pawn_no_move) { ASSERT_MOVE("8/8/8/8/8/4p3/4P3/8 w HAha - 0 1", 0, WHITE); }

}  // namespace chess