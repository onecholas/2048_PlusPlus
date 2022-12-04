#include "model.hxx"
#include <catch.hxx>

// Favorite Model Test #1:
// Checks that we can set tiles at desired locations (helper function used
// later on for combining tiles as well as adding random new tiles)
TEST_CASE("Test tile_at_loc_val")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0,0,2);
    m.tile_at_loc_val(0,1,2);
    m.tile_at_loc_val(0,2,2);
    m.tile_at_loc_val(0,3,2);
    m.tile_at_loc_val(1,0,2);
    m.tile_at_loc_val(1,1,2);
    m.tile_at_loc_val(1,2,2);
    m.tile_at_loc_val(1,3,2);
    m.tile_at_loc_val(2,0,2);
    m.tile_at_loc_val(2,1,2);
    m.tile_at_loc_val(2,2,2);
    m.tile_at_loc_val(2,3,2);
    m.tile_at_loc_val(3,0,2);
    m.tile_at_loc_val(3,1,2);

    CHECK(m.tile_at_loc(3,1) == 2);
    CHECK(m.tile_at_loc(3,2) == 0);
    CHECK(m.tile_at_loc(3,3) == 0);
}

// Favorite Model Test #2:
// Checks that we can clear the board when the clear_board() method is called
// during restart after the user has won or lost
TEST_CASE("Clear Board Check")
{
    Model m;
    m.clear_board();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            CHECK(m.tile_at_loc(i,j) == 0);
        }
    }
}

// Favorite Model Test #3: Checks whether tiles can move in allowed
// directions based on different locations
TEST_CASE("Test tile_move_check")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0,0,2);
    m.tile_at_loc_val(0,1,2);

    /// i -> row
    /// j -> column

    CHECK(m.tile_move_check(0,1,Direction {1,0}));
    CHECK(m.tile_move_check(0,1,Direction {-1,0}));
    CHECK(!m.tile_move_check(0,1,Direction {0,1}));
    CHECK(m.tile_move_check(0,1,Direction {0,-1}));
    // Skip (0,0) moving right because 0,1 would move
    CHECK(!m.tile_move_check(0,0,Direction {-1,0}));
    CHECK(!m.tile_move_check(0,0,Direction {0,1}));
    CHECK(m.tile_move_check(0,0,Direction {0,-1}));
    CHECK(!m.tile_move_check(1,1,Direction {0,1}));

    // Check right side of grid moving right
    m.clear_board();
    m.tile_at_loc_val(0,3,2);
    m.tile_at_loc_val(1,3,2);
    m.tile_at_loc_val(2,3,2);
    m.tile_at_loc_val(3,3,2);
    CHECK(!m.tile_move_check(0,3,Direction {1,0}));
    CHECK(!m.tile_move_check(1,3,Direction {1,0}));
    CHECK(!m.tile_move_check(2,3,Direction {1,0}));
    CHECK(!m.tile_move_check(3,3,Direction {1,0}));

    // Check bottom of grid moving down
    m.clear_board();
    m.tile_at_loc_val(3,0,2);
    m.tile_at_loc_val(3,1,2);
    m.tile_at_loc_val(3,2,2);
    m.tile_at_loc_val(3,3,2);
    CHECK(!m.tile_move_check(3,0,Direction {0,-1}));
    CHECK(!m.tile_move_check(3,1,Direction {0,-1}));
    CHECK(!m.tile_move_check(3,2,Direction {0,-1}));
    CHECK(!m.tile_move_check(3,3,Direction {0,-1}));

    // Check left of grid moving left
    m.clear_board();
    m.tile_at_loc_val(0,0,2);
    m.tile_at_loc_val(1,0,2);
    m.tile_at_loc_val(2,0,2);
    m.tile_at_loc_val(3,0,2);
    CHECK(!m.tile_move_check(0,0,Direction {-1,0}));
    CHECK(!m.tile_move_check(1,0,Direction {-1,0}));
    CHECK(!m.tile_move_check(2,0,Direction {-1,0}));
    CHECK(!m.tile_move_check(3,0,Direction {-1,0}));

    // Check top of grid moving up
    m.clear_board();
    m.tile_at_loc_val(0,0,2);
    m.tile_at_loc_val(0,1,2);
    m.tile_at_loc_val(0,2,2);
    m.tile_at_loc_val(0,3,2);
    CHECK(!m.tile_move_check(0,0,Direction {0,1}));
    CHECK(!m.tile_move_check(0,1,Direction {0,1}));
    CHECK(!m.tile_move_check(0,2,Direction {0,1}));
    CHECK(!m.tile_move_check(0,3,Direction {0,1}));

    // Check tile in the middle of board with no other tiles
    m.clear_board();
    m.tile_at_loc_val(2,2,2);
    CHECK(m.tile_move_check(2,2,Direction {0,1}));
    CHECK(m.tile_move_check(2,2,Direction {-1,0}));
    CHECK(m.tile_move_check(2,2,Direction {1,0}));
    CHECK(m.tile_move_check(2,2,Direction {0,-1}));
}

// Favorite Model Tests #6+: These following model tests (4 and 5 are below,
// not included in this list) test movement with different combinations and
// directions.

TEST_CASE("Test tile_combine_all 1")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 3) == 2);
}

TEST_CASE("Test tile_combine_all 2")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 3")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 2) == 0);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 4")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 1, 2);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 4);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 5")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 2);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 6")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 2);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 7")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 0);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 0);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 8")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 2);
    m.tile_at_loc_val(0, 1, 4);
    m.tile_at_loc_val(0, 2, 0);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 2);
    CHECK(m.tile_at_loc(0, 2) == 4);
    CHECK(m.tile_at_loc(0, 3) == 2);
}

// Favorite Model Test #4: Checks if tiles are combining correctly (move to
// the right as well as not combining entirely).
//  [4 0 2 2
//   0 0 0 0
//   0 0 0 0
//   0 0 0 0]
// Tiles should combine to:
//  [0 0 4 4
//   0 0 0 0
//   0 0 0 0
//   0 0 0 0]
TEST_CASE("Test tile_combine_all 9")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 4);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 4);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 10")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 8);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (1,0));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(0, 1) == 0);
    CHECK(m.tile_at_loc(0, 2) == 8);
    CHECK(m.tile_at_loc(0, 3) == 4);
}

TEST_CASE("Test tile_combine_all 1 left")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 8);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (-1,0));
    CHECK(m.tile_at_loc(0, 0) == 8);
    CHECK(m.tile_at_loc(0, 1) == 4);
    CHECK(m.tile_at_loc(0, 2) == 0);
    CHECK(m.tile_at_loc(0, 3) == 0);
}

TEST_CASE("Test tile_combine_all 2 left")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 4);
    m.tile_at_loc_val(0, 1, 0);
    m.tile_at_loc_val(0, 2, 2);
    m.tile_at_loc_val(0, 3, 2);
    m.tile_combine_all(Direction (-1,0));
    CHECK(m.tile_at_loc(0, 0) == 4);
    CHECK(m.tile_at_loc(0, 1) == 4);
    CHECK(m.tile_at_loc(0, 2) == 0);
    CHECK(m.tile_at_loc(0, 3) == 0);
}

TEST_CASE("Test tile_combine_all 1 up")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 4);
    m.tile_at_loc_val(1, 0, 0);
    m.tile_at_loc_val(2, 0, 2);
    m.tile_at_loc_val(3, 0, 2);
    m.tile_combine_all(Direction (0,1));
    CHECK(m.tile_at_loc(0, 0) == 4);
    CHECK(m.tile_at_loc(1, 0) == 4);
    CHECK(m.tile_at_loc(2, 0) == 0);
    CHECK(m.tile_at_loc(3, 0) == 0);
}

TEST_CASE("Test tile_combine_all 1 down")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 4);
    m.tile_at_loc_val(1, 0, 0);
    m.tile_at_loc_val(2, 0, 2);
    m.tile_at_loc_val(3, 0, 2);
    m.tile_combine_all(Direction (0,-1));
    CHECK(m.tile_at_loc(0, 0) == 0);
    CHECK(m.tile_at_loc(1, 0) == 0);
    CHECK(m.tile_at_loc(2, 0) == 4);
    CHECK(m.tile_at_loc(3, 0) == 4);
}

// Favorite Model Test #5: Checks if user has won or lost the game
// continuously as new tiles are placed down
TEST_CASE("Test check_winner 1")
{
    Model m;
    m.clear_board();
    m.tile_at_loc_val(0, 0, 1);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(1, 0, 2);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(2, 0, 3);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(3, 0, 4);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(0, 1, 5);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(1, 1, 6);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(2, 1, 7);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(3, 1, 8);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(0, 2, 9);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(1, 2, 10);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(2, 2, 11);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(3, 2, 12);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(0, 3, 13);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(1, 3, 14);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(2, 3, 15);
    CHECK(!m.loser());
    CHECK(!m.winner());
    m.tile_at_loc_val(3, 3, 2048);
    CHECK(m.loser());
    CHECK(m.winner());
}