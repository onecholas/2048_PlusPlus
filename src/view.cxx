#include "view.hxx"
#include "model.hxx"

static int const grid_size = 800;

View::View(Model const& model)
        : model_(model),
          timerval_(0),
          timervalmin_(0),
          gameover_(209, 196, 182, 180),
          gamewin_(240, 226, 72, 180),
          background_(187,173,160),
          edges_(205,193,180),
          two_(238, 228, 218),
          four_(238,225,201),
          eight_(243,178,122),
          onesix_(246,150,100),
          threetwo_(247,124,95),
          sixfour_(247,95,59),
          onetwoeight_(237,208,115),
          twofivesix_(237,204,98),
          fiveonetwo_(237,201,80),
          onezerotwofour_(237,197,63),
          twozerofoureight_(237,194,46),
          fourzeroninesix_(0, 0, 0),
          eightoneninetwo_(48, 148, 219),
          onesixthreeeightfour_(20, 90, 219),
          threetwosevensixeight_(80, 58, 224),
          sixfivefivethreesix_(117, 43, 237),
          onethreeonezeroseventwo_(208, 103, 230),

          game_win_tile_({grid_size, grid_size}, gamewin_),
          game_over_tile_({grid_size, grid_size}, gameover_),
          background_tile_({grid_size, grid_size}, background_),
          edges_tile_({int(grid_size * .18), int(grid_size * .18)}, edges_),
          two_tile_({int(grid_size * .18), int(grid_size * .18)}, two_),
          four_tile_({int(grid_size * .18), int(grid_size * .18)}, four_),
          eight_tile_({int(grid_size * .18), int(grid_size * .18)}, eight_),
          onesix_tile_({int(grid_size * .18), int(grid_size * .18)}, onesix_),
          threetwo_tile_({int(grid_size * .18), int(grid_size * .18)}, threetwo_),
          sixfour_tile_({int(grid_size * .18), int(grid_size * .18)}, sixfour_),
          onetwoeight_tile_({int(grid_size * .18), int(grid_size * .18)},
                            onetwoeight_),
          twofivesix_tile_({int(grid_size * .18), int(grid_size * .18)},
                           twofivesix_),
          fiveonetwo_tile_({int(grid_size * .18), int(grid_size * .18)},
                           fiveonetwo_),
          onezerotwofour_tile_({int(grid_size * .18), int(grid_size * .18)},
                               onezerotwofour_),
          twozerofoureight_tile_({int(grid_size * .18), int(grid_size * .18)},
                                 twozerofoureight_),
          fourzeroninesix_tile_({int(grid_size * .18), int(grid_size * .18)},
                                fourzeroninesix_),
          eightoneninetwo_tile_({int(grid_size * .18), int(grid_size * .18)},
                                eightoneninetwo_),
          onesixthreeeightfour_tile_({int(grid_size * .18),
                                      int(grid_size * .18)},
                                     onesixthreeeightfour_),
          threetwosevensixeight_tile_({int(grid_size * .18),
                                       int(grid_size * .18)},
                                      threetwosevensixeight_),
          sixfivefivethreesix_tile_({int(grid_size * .18),
                                     int(grid_size * .18)},
                                    sixfivefivethreesix_),
          onethreeonezeroseventwo_tile_({int(grid_size * .18),
                                         int(grid_size * .18)},
                                        onethreeonezeroseventwo_),

          gameoverfont_("sans.ttf", grid_size / 15),
          instructionsfont_("sans.ttf", grid_size / 35),
          scoretitlefont_("sans.ttf", grid_size / 20),
          scorefont_("sans.ttf", grid_size / 20),
          titlefont_("sans.ttf", grid_size / 20),
          timerfont_("sans.ttf", grid_size / 28),
          gameovermessage_({"Game Over!", gameoverfont_}),
          gameoverdesc_({"Press the \"r\" key to restart.",
                         instructionsfont_}),
          gamewinmessage_({"You Win!", gameoverfont_}),
          gamewindesc_({"Press \"c\" to continue and \"r\" to restart.",
                        instructionsfont_}),
          scoretitle_({"Score:", scoretitlefont_}),
          scorevalbuilder_(scorefont_),
          scoreval_(),
          title_("2048++", titlefont_),
          timerbuilder_(timerfont_),
          timer_(),
          timermin_(),

          tilefont_("sans.ttf", grid_size / 12),
          tilefonts_("sans.ttf", grid_size / 16),
          tilefontxs_("sans.ttf", grid_size / 22),
          tilevalbuilder_(tilefont_),
          tilevalbuilders_(tilefonts_),
          tilevalbuilderxs_(tilefontxs_),
          tileval2_(),
          tileval4_(),
          tileval8_(),
          tileval16_(),
          tileval32_(),
          tileval64_(),
          tileval128_(),
          tileval256_(),
          tileval512_(),
          tileval1024_(),
          tileval2048_(),
          tileval4096_(),
          tileval8192_(),
          tileval16384_(),
          tileval32768_(),
          tileval65536_(),
          tileval131072_()
{}

void
View::draw(ge211::Sprite_set& set)
{
    if (model_.get_first() == 1) {
        timerval_++;
        if (timerval_/120 == 60) {
            timerval_ = 0;
            timervalmin_++;
        }
    }
    set.add_sprite(title_, ge211::Posn<int> {grid_size * 12/100,
                                             grid_size * 3/100}, 3);
    set.add_sprite(scoretitle_, ge211::Posn<int> {grid_size * 70/100,
                                                  grid_size * 3/100}, 3);
    scorevalbuilder_.message(model_.score_get());
    scoreval_.reconfigure(scorevalbuilder_);
    set.add_sprite(scoreval_, ge211::Posn<int> {grid_size * 86/100,
                                                grid_size * 3/100}, 3);
    timerbuilder_.message(std::to_string(timerval_/120) + "s");
    timer_.reconfigure(timerbuilder_);
    set.add_sprite(timer_, ge211::Posn<int> {grid_size * 50/100,
                                             grid_size * 4/100}, 3),
    timerbuilder_.message(std::to_string(timervalmin_) + "m");
    timermin_.reconfigure(timerbuilder_);
    set.add_sprite(timermin_, ge211::Posn<int> {grid_size * 44/100,
                                             grid_size * 4/100}, 3),

    set.add_sprite(background_tile_, ge211::Posn<int> {0,0}, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            set.add_sprite(edges_tile_, ge211::Posn<int>
                    {int(grid_size * .11 + .2 * i * grid_size),
                     int(grid_size * .15 + .2 * j * grid_size)}, 1);
        }
    }

    if (model_.get_win_loss("L")) {
        set.add_sprite(game_over_tile_, ge211::Posn<int> {0,0}, 5);
        set.add_sprite(gameovermessage_, ge211::Posn<int> {grid_size * 32/100,
                                                           grid_size * 37/100},
                       6);
        set.add_sprite(gameoverdesc_, ge211::Posn<int> {grid_size * 33/100,
                                                        grid_size * 52/100}, 6);
    }

    if (model_.get_win_loss("W") && !model_.continue_game_get()) {
        set.add_sprite(game_win_tile_, ge211::Posn<int> {0,0}, 5);
        set.add_sprite(gamewinmessage_, ge211::Posn<int> {grid_size * 37/100,
                                                          grid_size * 37/100},
                       6);
        set.add_sprite(gamewindesc_, ge211::Posn<int> {grid_size * 29/100,
                                                       grid_size * 52/100}, 6);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int tile_val = model_.tile_at_loc(i, j);
            if (tile_val == 0) {}
            else if (tile_val == 2) {
                set.add_sprite(two_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(2));
                tileval2_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval2_, ge211::Posn<int>
                        {int(grid_size * .18 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 4) {
                set.add_sprite(four_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(4));
                tileval4_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval4_, ge211::Posn<int>
                        {int(grid_size * .18 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 8) {
                set.add_sprite(eight_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(8));
                tileval8_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval8_, ge211::Posn<int>
                        {int(grid_size * .18 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 16) {
                set.add_sprite(onesix_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(16));
                tileval16_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval16_, ge211::Posn<int>
                        {int(grid_size * .15 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 32) {
                set.add_sprite(threetwo_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(32));
                tileval32_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval32_, ge211::Posn<int>
                        {int(grid_size * .15 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 64) {
                set.add_sprite(sixfour_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(64));
                tileval64_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval64_, ge211::Posn<int>
                        {int(grid_size * .15 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 128) {
                set.add_sprite(onetwoeight_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(128));
                tileval128_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval128_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 256) {
                set.add_sprite(twofivesix_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(256));
                tileval256_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval256_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 512) {
                set.add_sprite(fiveonetwo_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilder_.message(std::to_string(512));
                tileval512_.reconfigure(tilevalbuilder_);
                set.add_sprite(tileval512_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .17 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 1024) {
                set.add_sprite(onezerotwofour_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilders_.message(std::to_string(1024));
                tileval1024_.reconfigure(tilevalbuilders_);
                set.add_sprite(tileval1024_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .19 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 2048) {
                set.add_sprite(twozerofoureight_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilders_.message(std::to_string(2048));
                tileval2048_.reconfigure(tilevalbuilders_);
                set.add_sprite(tileval2048_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .19 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 4096) {
                set.add_sprite(fourzeroninesix_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilders_.message(std::to_string(4096));
                tileval4096_.reconfigure(tilevalbuilders_);
                set.add_sprite(tileval4096_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .19 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 8192) {
                set.add_sprite(eightoneninetwo_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilders_.message(std::to_string(8192));
                tileval8192_.reconfigure(tilevalbuilders_);
                set.add_sprite(tileval8192_, ge211::Posn<int>
                        {int(grid_size * .13 + .2 * i * grid_size),
                         int(grid_size * .19 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 16384) {
                set.add_sprite(onesixthreeeightfour_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilderxs_.message(std::to_string(16384));
                tileval16384_.reconfigure(tilevalbuilderxs_);
                set.add_sprite(tileval16384_, ge211::Posn<int>
                        {int(grid_size * .14 + .2 * i * grid_size),
                         int(grid_size * .20 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 32768) {
                set.add_sprite(threetwosevensixeight_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilderxs_.message(std::to_string(32768));
                tileval32768_.reconfigure(tilevalbuilderxs_);
                set.add_sprite(tileval32768_, ge211::Posn<int>
                        {int(grid_size * .14 + .2 * i * grid_size),
                         int(grid_size * .20 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 65536) {
                set.add_sprite(sixfivefivethreesix_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilderxs_.message(std::to_string(65536));
                tileval65536_.reconfigure(tilevalbuilderxs_);
                set.add_sprite(tileval65536_, ge211::Posn<int>
                        {int(grid_size * .14 + .2 * i * grid_size),
                         int(grid_size * .20 + .2 * j * grid_size)}, 3);
            }
            else if (tile_val == 131072) {
                set.add_sprite(onethreeonezeroseventwo_tile_, ge211::Posn<int>
                        {int(grid_size * .11 + .2 * i * grid_size),
                         int(grid_size * .15 + .2 * j * grid_size)}, 2);
                tilevalbuilderxs_.message(std::to_string(131072));
                tileval131072_.reconfigure(tilevalbuilderxs_);
                set.add_sprite(tileval131072_, ge211::Posn<int>
                        {int(grid_size * .125 + .2 * i * grid_size),
                         int(grid_size * .20 + .2 * j * grid_size)}, 3);
            }
            else {} // No tiles higher valued than 131072
        }
    }

}

Dimensions
View::initial_window_dimensions() const
{
    return {800, 800};
}

std::string
View::initial_window_title() const
{
    return "2048++";
}

void
View::timerreset()
{
    timerval_ = 0;
    timervalmin_ = 0;
}