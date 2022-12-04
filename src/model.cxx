#include "model.hxx"
#include <cstdlib>
#include <ctime>
#include <cstdio>

Model::Model()
        : win_(false),
          lose_(false),
          continue_(false),
          dir_(Direction {0,0}),
          score_(0),
          moves_(0),
          winningtile_(2048)

{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = 0; /// i -> row
                                /// j -> column
        }
    }
    // add_random_tile();
    // add_random_tile();
    tile_at_loc_val(0,1,4);
    tile_at_loc_val(0,2,8);
    tile_at_loc_val(0,3,16);
    tile_at_loc_val(1,0,64);
    tile_at_loc_val(1,1,128);
    tile_at_loc_val(1,2,256);
    tile_at_loc_val(1,3,512);
    tile_at_loc_val(2,0,1024);
    tile_at_loc_val(2,1,2048);
    tile_at_loc_val(2,2,4096);
    tile_at_loc_val(2,3,8192);
    tile_at_loc_val(3,0,16384);
    tile_at_loc_val(3,1,32768);
    tile_at_loc_val(3,2,65536);
    tile_at_loc_val(3,3,131072);
}

void Model::tile_at_loc_val(int i, int j, int val)
{
    squares_[i][j] = val;
}

int Model::tile_at_loc(int i, int j) const
{
    return squares_[i][j];
}

std::vector<Location> Model::tile_all_locations()
{
    std::vector<Location> all_locations;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            all_locations.push_back(Location(i,j));
        }
    }
    return all_locations;
}

std::vector<Direction> Model::directions()
{
    std::vector<Direction> all_directions;
    all_directions.push_back(Direction (0,1));
    all_directions.push_back(Direction (0,-1));
    all_directions.push_back(Direction (1,0));
    all_directions.push_back(Direction (-1,0));
    return all_directions;
}

void Model::tile_print_all()
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            std::cout << "squares (" << i << ", " << j << ") = " <<
            tile_at_loc(i,j) << "\n";
        }
    }
    return;
}

bool Model::tile_move_check(int row, int column, Direction dir) {
    int current_tile_val = tile_at_loc(row, column);

    if (row > grid_size - 1 || row < 0 ||
        column > grid_size -1 || column < 0) {
        throw std::invalid_argument("Not a valid position");
    }

    if (current_tile_val == 0) {
        return false;
    }

    if (dir == Direction(1,0)) {
        if (column == 3) {
            return false;
        }
        else if (tile_at_loc(row, column + 1) == 0 ||
                 tile_at_loc(row, column + 1) == current_tile_val) {
            return true;
        }
        else {
            return false;
        }
    }

    else if (dir == Direction(-1,0)) {
        if (column == 0) {
            return false;
        }
        else if (tile_at_loc(row, column - 1) == 0 ||
                 tile_at_loc(row, column - 1) == current_tile_val) {
            return true;
        }
        else {
            return false;
        }
    }

    else if (dir == Direction(0,1)) {
        if (row == 0) {
            return false;
        }
        else if (tile_at_loc(row - 1, column) == 0 ||
                 tile_at_loc(row - 1, column) == current_tile_val) {
            return true;
        }
        else {
            return false;
        }
    }

    else if (dir == Direction(0,-1)) {
        if (row == 3) {
            return false;
        }
        else if (tile_at_loc(row + 1, column) == 0 ||
                 tile_at_loc(row + 1, column) == current_tile_val) {
            return true;
        }
        else {
            return false;
        }
    }

    else {
        throw std::invalid_argument("Not a 2D unit direction");
    }
}

void Model::tile_combine_all(Direction dir)
{
    // Right movement -> Start from right side and move left
    if (dir == Direction(1,0)) {
        for (int row = 0; row < grid_size; row++) {
            int final_loc = 3;
            for (int column = grid_size - 1; column > -1; column--) {
                int offset = 0;

                // Move the tile over as long as there are empty spaces, if
                // the next tile is the same value (if it has not been
                // combined before)
                while (tile_move_check(row, column + offset, Direction(1,0))
                       && column + offset < final_loc) {

                    // If two tiles are the same and combine, cannot
                    // recombine with another tile for the same move
                    if (tile_at_loc(row, column + offset) ==
                        tile_at_loc(row, column + offset + 1)) {
                        final_loc = column + offset;
                    }

                    // Move the tile over or combine the tiles
                    int value = tile_at_loc(row, column + offset) +
                                tile_at_loc(row, column + offset + 1);
                    tile_at_loc_val(row, column + offset + 1, value);
                    tile_at_loc_val(row, column + offset, 0);

                    // int tile00 = tile_at_loc(0, 0); // Debugging variables
                    // int tile01 = tile_at_loc(0, 1);
                    // int tile02 = tile_at_loc(0, 2);
                    // int tile03 = tile_at_loc(0, 3);
                    offset++;
                    moves_++;
                }
            }
        }
    }

    // Left -> Start from left side and move right
    if (dir == Direction(-1,0)) {
        for (int row = 0; row < grid_size; row++) {
            int final_loc = 0;
            for (int column = 0; column < grid_size; column++) {
                int offset = 0;
                while (tile_move_check(row, column - offset, Direction(-1,0))
                       && column - offset > final_loc) {
                    if (tile_at_loc(row, column - offset) ==
                        tile_at_loc(row, column - offset - 1)) {
                        final_loc = column - offset;
                    }
                    int value = tile_at_loc(row, column - offset) +
                                tile_at_loc(row, column - offset - 1);
                    tile_at_loc_val(row, column - offset - 1, value);
                    tile_at_loc_val(row, column - offset, 0);
                    offset++;
                    moves_++;
                }
            }
        }
    }

    // Up -> Start from top and move down
    if (dir == Direction(0,1)) {
        for (int column = 0; column < grid_size; column++) {
            int final_loc = 0;
            for (int row = 0; row < grid_size; row++) {
                int offset = 0;
                while (tile_move_check(row - offset, column, Direction(0,1))
                       && row - offset > final_loc) {
                    if (tile_at_loc(row - offset, column) ==
                        tile_at_loc(row - offset - 1, column)) {
                        final_loc = row - offset;
                    }
                    int value = tile_at_loc(row - offset, column) +
                                tile_at_loc(row - offset - 1, column);
                    tile_at_loc_val(row - offset - 1, column, value);
                    tile_at_loc_val(row - offset, column, 0);
                    offset++;
                    moves_++;
                }
            }
        }
    }

    // Down movement -> Start from bottom and move up
    if (dir == Direction(0,-1)) {
        for (int column = 0; column < grid_size; column++) {
            int final_loc = 3;
            for (int row = grid_size -1; row > -1; row--) {
                int offset = 0;
                while (tile_move_check(row + offset, column, Direction(0,-1))
                       && row + offset < final_loc) {
                    if (tile_at_loc(row + offset, column) ==
                        tile_at_loc(row + offset + 1, column)) {
                        final_loc = row + offset;
                    }
                    int value = tile_at_loc(row + offset, column) +
                                tile_at_loc(row + offset + 1, column);
                    tile_at_loc_val(row + offset + 1, column, value);
                    tile_at_loc_val(row + offset, column, 0);
                    offset++;
                    moves_++;
                }
            }
        }
    }
}

void Model::tile_actually_combine_all()
{
    tile_combine_all(dir_);
    check_winner();
    check_loser();
}

std::vector<Location> Model::tile_empty_loc()
{
    std::vector<Location> empty_locations;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (squares_[i][j] == 0) {
                empty_locations.push_back(Location(i, j));
            }
        }
    }
    return empty_locations;
}

void Model::check_winner()
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (tile_at_loc(i,j) == winningtile_) {
                win_ = true;
                return;
            }
        }
    }
    win_ = false;
}

bool Model::winner()
{
    check_winner();
    return win_;
}

void Model::check_loser()
{
    if (tile_empty_loc().size() != 0) {
        lose_ = false;
        return;
    }
    else if (tile_empty_loc().size() == 0) {
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                for (Direction dir : directions())
                    if (tile_move_check(i,j,dir)) {
                        lose_ = false;
                        return;
                }
            }
        }
    }
    lose_ = true;
}

bool Model::loser()
{
    check_loser();
    return lose_;
}

bool Model::get_win_loss(std::string str) const
{
    if (str == "W") {
        return win_;
    }
    else {
        return lose_;
    }
}

void Model::add_random_tile()
{
    srand(time(0));  // Comment out to always have same seed (Tests
                        // always clear board before starting and are not
                        // dependent upon seeding)
    if (tile_empty_loc().size() != 0) {
        int loc_index = rand() % tile_empty_loc().size();
        Location loc = tile_empty_loc()[loc_index];
        int val = (1 + (rand() % 2)) * 2;
        tile_at_loc_val(loc.x, loc.y, val);
        score_ += val;
    }
}

void Model::set_dir(Direction dir)
{
    dir_ = dir;
}

void Model::clear_board()
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = 0; /// i -> row
                                /// j -> column
        }
    }
}

bool Model::continue_game_get() const
{
    return continue_;
}

void Model::continue_game_set()
{
    continue_ = true;
}

int Model::moves_get() const
{
    return moves_;
}

void Model::moves_set()
{
    moves_ = 0;
}

std::string Model::score_get() const
{
    return std::to_string(score_);
}

void Model::set_first(int val)
{
    if (val == 0) {
        first_ = 0;
    }
    else if (val == 1) {
        first_ = 1;
    }
}

int Model::get_first() const
{
    return first_;
}

void Model::reset_board()
{
    clear_board();
    win_ = false;
    lose_ = false;
    continue_ = false;
    dir_ = Direction (0,0);
    score_ = 0;
    first_ = 0;
    add_random_tile();
    add_random_tile();
}

