#pragma once
#include "std_lib_facilities.h"
#include <map>
#include "Graph.h"
#include "GUI.h" 
#include "Simple_window.h"

#include <utility>

#include "FL/Fl_Widget.H"
#include "FL/Fl_PNG_Image.H"

const int rute=50;


class Brikke : public Fl_Widget
{

    const char* sted;

public:

    Point pos;

    Fl_PNG_Image pic;//{"bilder/bb.png"};
    //static array<Fl_PNG_Image, 12> finnArray;


    //virtual vector<string> get_legal_moves() = 0;
    //virtual bool is_legal_move() = 0;

    Brikke(int x, int y, string hvilken_brikke);

    void update_pos();

    void draw() override;
    //tror det at jeg bruker x() og y() er det som kommer til å la meg flytte på bildet senere

    void move(int xx, int yy)
    { x( (xx/rute)*rute ); y( (yy/rute)*rute ); update_pos();}

    void drag(int dx, int dy)
    { x( x() + dx ); y( y() + dy ); }

    string get_piece_code() const;  
    bool is_white() const;
};
