#pragma once

#include "brikke.h"

#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <chrono>
#include <cstdlib>
#include <thread>
#include <memory>

#include <iostream>     // std::cout
#include <iterator> 

//må fikse sjakk som kan stoppes ved an passant og noe rar bonde posision


vector<vector<string>> classic();

class Brett : public Fl_Widget
{
    Point en_passant_next;
    Point en_passant;
    vector<vector<string>> real_brett;
    vector<Brikke*> brikkene;
    Point mouse;
    Brikke* selected_piece;
    bool white_turn;
    Point* promotion;
    bool checkmate;
    bool stalemate;
    bool wlr;
    bool wrr;
    bool brr;
    bool blr;

    Fl_PNG_Image brettbildet{"bilder/boardL.png"};

    //for å velge ny brikke etter bonde har nådd toppen :)
    Fl_PNG_Image bb{"bilder/bb.png"};
    Fl_PNG_Image bq{"bilder/bq.png"};
    Fl_PNG_Image br{"bilder/br.png"};
    Fl_PNG_Image bn{"bilder/bn.png"};
    Fl_PNG_Image wq{"bilder/wq.png"};
    Fl_PNG_Image wr{"bilder/wr.png"};
    Fl_PNG_Image wn{"bilder/wn.png"};
    Fl_PNG_Image wb{"bilder/wb.png"};
    Fl_PNG_Image wp{"bilder/wp.png"};
    Fl_PNG_Image bp{"bilder/bp.png"};
    Fl_PNG_Image mate{"bilder/checkmate.png"};
    Fl_PNG_Image stale{"bilder/stalemate.png"};

    //her er funksjoner knyttet til reglene
    bool check(int piece_x, int piece_y, int move_x, int move_y, string piece, bool en_pass = false);
    bool check_pos();
    void basic(int xx, int yy, int dx, int dy, char color, vector<Point>& vec);
    void basic_one_move(int xx, int yy, int dx, int dy, char color, vector<Point>& vec);
    char basic_check(int king_x, int king_y, int retning_dx, int retning_dy, char color);
    char basic_check_one_move(int king_x, int king_y, int retning_dx, int retning_dy, char color);
    void bishop(int x, int y, char color, vector<Point>& re);
    void rook(int x, int y, char color, vector<Point>& re);
    void queen(int x, int y, char color, vector<Point>& re);
    void knight(int x, int y, char color, vector<Point>& re);
    void king(int x, int y, char color, vector<Point>& re);
    void basic_pawn_takes(int x, int y, int dx, int dy, char color, vector<Point>& vec);
    void pawn(int x, int y, char color, vector<Point>& re);
    void get_moves(int piece_pos_x, int piece_pos_y, string code,vector<Point>& re);
    bool is_legal_move(int x, int y);
    bool no_possible_moves();


    //her er funksjoner med ganske direkte bruk for det visuelle
    Brikke* find_piece(int x, int y);
    void draw() override;
    void read_board();
    int handle(int event) override;
    void mouse_drag(int x, int y);
    void mouse_click(int x, int y);
    void release(int x, int y); 
    bool has_moved(int x, int y);
    int reverse_x(int x);
    int reverse_y(int x, int y);
    void return_piece();

    //siste funksjonen som kalles hver tur, etter trekket er valgt og godkjent
    void final_move(int x, int y);

public:
    Brett(int x, int y);
};
