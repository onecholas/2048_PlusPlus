#pragma once

#include "model.hxx"

using Key = ge211::Key;
using Rectangle = ge211::Rect<int>;
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
using Dimensions = ge211::Dims<int>;

class View
{
public:
    explicit View(Model const& model);
    void draw(ge211::Sprite_set& set);
    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

    // Reset timer
    void timerreset();
private:
    Model const& model_;
    int timerval_;
    int timervalmin_;
    Color gameover_;
    Color gamewin_;
    Color background_;
    Color edges_;
    Color two_;
    Color four_;
    Color eight_;
    Color onesix_;
    Color threetwo_;
    Color sixfour_;
    Color onetwoeight_;
    Color twofivesix_;
    Color fiveonetwo_;
    Color onezerotwofour_;
    Color twozerofoureight_;
    Color fourzeroninesix_;
    Color eightoneninetwo_;
    Color onesixthreeeightfour_;
    Color threetwosevensixeight_;
    Color sixfivefivethreesix_;
    Color onethreeonezeroseventwo_;

    ge211::Rectangle_sprite const game_win_tile_;
    ge211::Rectangle_sprite const game_over_tile_;
    ge211::Rectangle_sprite const background_tile_;
    ge211::Rectangle_sprite const edges_tile_;
    ge211::Rectangle_sprite const two_tile_;
    ge211::Rectangle_sprite const four_tile_;
    ge211::Rectangle_sprite const eight_tile_;
    ge211::Rectangle_sprite const onesix_tile_;
    ge211::Rectangle_sprite const threetwo_tile_;
    ge211::Rectangle_sprite const sixfour_tile_;
    ge211::Rectangle_sprite const onetwoeight_tile_;
    ge211::Rectangle_sprite const twofivesix_tile_;
    ge211::Rectangle_sprite const fiveonetwo_tile_;
    ge211::Rectangle_sprite const onezerotwofour_tile_;
    ge211::Rectangle_sprite const twozerofoureight_tile_;
    ge211::Rectangle_sprite const fourzeroninesix_tile_;
    ge211::Rectangle_sprite const eightoneninetwo_tile_;
    ge211::Rectangle_sprite const onesixthreeeightfour_tile_;
    ge211::Rectangle_sprite const threetwosevensixeight_tile_;
    ge211::Rectangle_sprite const sixfivefivethreesix_tile_;
    ge211::Rectangle_sprite const onethreeonezeroseventwo_tile_;

    ge211::Font gameoverfont_;
    ge211::Font instructionsfont_;
    ge211::Font scoretitlefont_;
    ge211::Font scorefont_;
    ge211::Font titlefont_;
    ge211::Font timerfont_;
    ge211::Text_sprite gameovermessage_;
    ge211::Text_sprite gameoverdesc_;
    ge211::Text_sprite gamewinmessage_;
    ge211::Text_sprite gamewindesc_;
    ge211::Text_sprite scoretitle_;
    ge211::Text_sprite::Builder scorevalbuilder_;
    ge211::Text_sprite scoreval_;
    ge211::Text_sprite title_;
    ge211::Text_sprite::Builder timerbuilder_;
    ge211::Text_sprite timer_;
    ge211::Text_sprite timermin_;

    ge211::Font tilefont_;
    ge211::Font tilefonts_;
    ge211::Font tilefontxs_;
    ge211::Text_sprite::Builder tilevalbuilder_;
    ge211::Text_sprite::Builder tilevalbuilders_;
    ge211::Text_sprite::Builder tilevalbuilderxs_;
    ge211::Text_sprite tileval2_;
    ge211::Text_sprite tileval4_;
    ge211::Text_sprite tileval8_;
    ge211::Text_sprite tileval16_;
    ge211::Text_sprite tileval32_;
    ge211::Text_sprite tileval64_;
    ge211::Text_sprite tileval128_;
    ge211::Text_sprite tileval256_;
    ge211::Text_sprite tileval512_;
    ge211::Text_sprite tileval1024_;
    ge211::Text_sprite tileval2048_;
    ge211::Text_sprite tileval4096_;
    ge211::Text_sprite tileval8192_;
    ge211::Text_sprite tileval16384_;
    ge211::Text_sprite tileval32768_;
    ge211::Text_sprite tileval65536_;
    ge211::Text_sprite tileval131072_; // Highest possible tile with perfect
                                       // setup

};
