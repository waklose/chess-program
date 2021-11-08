#include "brikke.h"

//måtte gjøre masse tull her fordi disse arrayene var for inkompetente til å lage sin egen end
    char bp[]={'b','i','l','d','e','r','/','b','p','.','p','n','g'};
    int a=1;
    char bk[]={'b','i','l','d','e','r','/','b','k','.','p','n','g'};
    int b=1;
    char bb[]={'b','i','l','d','e','r','/','b','b','.','p','n','g'};
    int c=1;
    char bn[]={'b','i','l','d','e','r','/','b','n','.','p','n','g'};
    int d=1;
    char bq[]={'b','i','l','d','e','r','/','b','q','.','p','n','g'};
    int e=1;
    char br[]={'b','i','l','d','e','r','/','b','r','.','p','n','g'};
    int f=1;
    char wk[]={'b','i','l','d','e','r','/','w','k','.','p','n','g'};
    int g=1;
    char wn[]={'b','i','l','d','e','r','/','w','n','.','p','n','g'};
    int h=1;
    char wp[]={'b','i','l','d','e','r','/','w','p','.','p','n','g'};
    int i=1;
    char wq[]={'b','i','l','d','e','r','/','w','q','.','p','n','g'};
    int j=1;
    char wb[]={'b','i','l','d','e','r','/','w','b','.','p','n','g'};
    int k=1;
    char wr[]={'b','i','l','d','e','r','/','w','r','.','p','n','g'};

const map<string, char*> finnMap{
    {"bp", bp}, 
    {"bk", bk},
    {"bb", bb},
    {"bn", bn},
    {"bq", bq},
    {"br", br},

    {"wp", wp}, 
    {"wk", wk},
    {"wb", wb},
    {"wn", wn},
    {"wq", wq},
    {"wr", wr}
};

void Brikke::draw(){
    pic.draw(x(), y());
    pic.draw(17*rute-x(), 7*rute-y());
}

Brikke::Brikke(int x, int y, string hvilken_brikke)
    : Fl_Widget(x, y, rute, rute),
      sted{finnMap.at(hvilken_brikke)},
      pic{sted},
      pos({x, y})
{
}

void Brikke::update_pos(){
    pos.x=x();
    pos.y=y();
}
string Brikke::get_piece_code() const {
    string re;
    re+=sted[7];
    re+=sted[8];
    return re;
}

bool Brikke::is_white() const{
    return sted[7]=='w';
}

