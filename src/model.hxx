#pragma once

#include <ge211.hxx>
#include <iostream>

using Direction = ge211::geometry::Posn<int>;
using Location = ge211::geometry::Posn<int>;

class Model
{
public:

    // Constructor for basic 4x4 grid
    Model();

    const int grid_size = 4;

    // Checks what value a given tile is
    int tile_at_loc(int i, int j) const;

    // Sets value at tile location
    void tile_at_loc_val(int i, int j, int val);

    // Prints matrix with all values
    void tile_print_all();

    // List of all tile locations
    std::vector<Location> tile_all_locations();

    // Checks if tile can combine in direction
    bool tile_move_check(int i, int j, Direction dir);

    // Combine the tiles, check for winner
    void tile_combine_all(Direction dir);

    // Actually carry out the combining
    void tile_actually_combine_all();

    // Finds all empty locations
    std::vector<Location> tile_empty_loc();

    // Finds all 4 directions
    std::vector<Direction> directions();

    // Checks if user has won
    void check_winner();

    // Get if user has won
    bool winner();

    // Checks if user has lost
    void check_loser();

    // Get if user has lost
    bool loser();

    // Get win/loss without changing anything
    bool get_win_loss(std::string str) const;

    // Adds a random tile to an open location
    void add_random_tile();

    // Sets the direction currently inputted by user
    void set_dir(Direction dir);

    // Clears entire board (for testing and starting over)
    void clear_board();

    // Resets game
    void reset_board();

    // Checks if user wants to continue (default false)
    bool continue_game_get() const;

    // Writes if user wants to continue (default false)
    void continue_game_set();

    // Checks how if a move has been made. If greater than 0, tiles were
    // moved or combined.
    int moves_get() const;

    // Sets moves to zero.
    void moves_set();

    // Gets the score as a string
    std::string score_get() const;

    // Sets first
    void set_first(int val);

    // Gets first
    int get_first() const;


private:

    int squares_[4][4];
    bool win_;
    bool lose_;
    bool continue_;
    Direction dir_;
    int score_;
    int moves_;
    int first_;
    int winningtile_;

};
