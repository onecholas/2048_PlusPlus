#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key_down(ge211::Key key) override;
    // void on_frame(double dt) override;
    Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    int timer_;
};
