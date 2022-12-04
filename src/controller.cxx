#include "controller.hxx"
#include "view.hxx"
#include "model.hxx"

Direction Left {0,1};
Direction Right {0,-1};
Direction Down {1,0};
Direction Up {-1,0};
Direction None {0,0};

Controller::Controller()
        : view_(model_),
          timer_(0)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key_down(ge211::Key key)
{
    if (model_.get_first() == 0) {
        if (key == ge211::Key::up() ||
        key == ge211::Key::down() ||
        key == ge211::Key::right() ||
        key == ge211::Key::left()) {
            model_.set_first(1);
        }
    }

    if (!model_.loser()) {
        if (!model_.winner() || model_.continue_game_get()) {
            if (key == ge211::Key::up()) {
                model_.set_dir(Up);
                model_.tile_actually_combine_all();
                if (model_.moves_get() > 0) {
                    model_.add_random_tile();
                }
                model_.moves_set();
            } else if (key == ge211::Key::down()) {
                model_.set_dir(Down);
                model_.tile_actually_combine_all();
                if (model_.moves_get() > 0) {
                    model_.add_random_tile();
                }
                model_.moves_set();
            } else if (key == ge211::Key::left()) {
                model_.set_dir(Left);
                model_.tile_actually_combine_all();
                if (model_.moves_get() > 0) {
                    model_.add_random_tile();
                }
                model_.moves_set();
            } else if (key == ge211::Key::right()) {
                model_.set_dir(Right);
                model_.tile_actually_combine_all();
                if (model_.moves_get() > 0) {
                    model_.add_random_tile();
                }
                model_.moves_set();
            } else {
                model_.set_dir(None);
            }
        }
    }

    if (model_.loser()) {
        model_.set_first(0);
        if (key == ge211::Key::code('r')) {
            model_.reset_board();
            view_.timerreset();
        }
    }

    if (model_.winner()) {
        model_.set_first(0);
        if (key == ge211::Key::code('c')) {
            model_.continue_game_set();
            model_.set_first(1);
        } else if (key == ge211::Key::code('r')) {
            model_.reset_board();
            view_.timerreset();
        }
    }
}

Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}