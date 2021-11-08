#include "brett.h"
#include "std_lib_facilities.h"


bool in_range(int x, int y){
    return x>=0 && x<=7 && y>=0 && y<=7 ;
}

bool Brett::check(int piece_x, int piece_y, int move_x, int move_y, string piece, bool en_pass ){
    //konge posisjon
    int x{-1};
    //konge posisjon
    int y;

    char color{ white_turn? 'w':'b' };

    //omgjør brettet til det potensielle trekket, må tilbakestilles etterpå
    string en_pass_mid;
    int dir{white_turn?1:-1};
    if (en_pass){
        en_pass_mid=real_brett[move_x][move_y-dir];
        real_brett[move_x][move_y-dir]="";
    }
    string mid=real_brett[move_x][move_y];
    real_brett[piece_x][piece_y]="";
    real_brett[move_x][move_y]=piece;

    for ( int i=0; i<8; i++){
        for (int k=0; k<8; k++){
            string en_rute = real_brett[i][k];
            if (!en_rute.empty() && en_rute[1] == 'k' && en_rute[0] == piece[0] ){
                x=i;
                y=k;
                break;
            }
        }
        if ( x!=-1 ){ break; }
    }

    vector<char> possible_moves;

    possible_moves.push_back( basic_check(x, y, 1, 0, color) );
    possible_moves.push_back( basic_check(x, y, -1, 0, color) );
    possible_moves.push_back( basic_check(x, y, 0, 1, color) );
    possible_moves.push_back( basic_check(x, y, 0, -1, color) );

    for (char i : possible_moves){
        if (i=='q' || i=='r'){
            real_brett[piece_x][piece_y]=piece;
            real_brett[move_x][move_y]=mid;
            if (en_pass)
            {
                real_brett[move_x][move_y-dir]=en_pass_mid;
            }
            return true;
        }
    }
    possible_moves.clear();

    possible_moves.push_back( basic_check(x, y, -1, 1, color) );
    possible_moves.push_back( basic_check(x, y, -1, -1, color) );
    possible_moves.push_back( basic_check(x, y, 1, -1, color) );
    possible_moves.push_back( basic_check(x, y, 1, 1, color) );

    for (char i : possible_moves){
        if (i=='b' || i=='q'){
            real_brett[piece_x][piece_y]=piece;
            real_brett[move_x][move_y]=mid;
            if (en_pass)
            {
                real_brett[move_x][move_y-dir]=en_pass_mid;
            }
            return true;
        }
    }
    possible_moves.clear();

    int direction{1};
    if (color=='b') { direction = -1;}

    possible_moves.push_back( basic_check_one_move(x, y, -1, direction, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, direction, color) );

    for (char i : possible_moves){
        if (i=='p' ){
            real_brett[piece_x][piece_y]=piece;
            real_brett[move_x][move_y]=mid;
            if (en_pass)
            {
                real_brett[move_x][move_y-dir]=en_pass_mid;
            }
            return true;
        }
    }
    possible_moves.clear();

    possible_moves.push_back( basic_check_one_move(x, y, 2, -1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 2, 1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, -2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, 2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -1, -2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -1, 2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -2, -1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -2, 1, color) );

    for (char i : possible_moves){
        if (i=='n' ){
            real_brett[piece_x][piece_y]=piece;
            real_brett[move_x][move_y]=mid;
            if (en_pass)
            {
                real_brett[move_x][move_y-dir]=en_pass_mid;
            }
            return true;
        }
    }

    real_brett[piece_x][piece_y]=piece;
    real_brett[move_x][move_y]=mid;
    if (en_pass)
            {
                real_brett[move_x][move_y-dir]=en_pass_mid;
            }
    return false;
}

//sjekker om posisjonen man står i er en sjakk posisjon
bool Brett::check_pos(){
    //konge posisjon
    int x{-1};
    //konge posisjon
    int y;

    char color{ white_turn? 'w':'b' };

    for ( int i=0; i<8; i++){
        for (int k=0; k<8; k++){
            string en_rute = real_brett[i][k];
            if (!en_rute.empty() && en_rute[1] == 'k' && en_rute[0] == color ){
                x=i;
                y=k;
                break;
            }
        }
        if ( x!=-1 ){ break; }
    }

    vector<char> possible_moves;

    possible_moves.push_back( basic_check(x, y, 1, 0, color) );
    possible_moves.push_back( basic_check(x, y, -1, 0, color) );
    possible_moves.push_back( basic_check(x, y, 0, 1, color) );
    possible_moves.push_back( basic_check(x, y, 0, -1, color) );

    for (char i : possible_moves){
        if (i=='q' || i=='r'){
            return true;
        }
    }
    possible_moves.clear();

    possible_moves.push_back( basic_check(x, y, -1, 1, color) );
    possible_moves.push_back( basic_check(x, y, -1, -1, color) );
    possible_moves.push_back( basic_check(x, y, 1, -1, color) );
    possible_moves.push_back( basic_check(x, y, 1, 1, color) );

    for (char i : possible_moves){
        if (i=='b' || i=='q'){
            return true;
        }
    }
    possible_moves.clear();

    int direction{1};
    if (color=='b') { direction = -1;}

    possible_moves.push_back( basic_check_one_move(x, y, -1, direction, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, direction, color) );

    for (char i : possible_moves){
        if (i=='p' ){
            return true;
        }
    }
    possible_moves.clear();

    possible_moves.push_back( basic_check_one_move(x, y, 2, -1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 2, 1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, -2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, 1, 2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -1, -2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -1, 2, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -2, -1, color) );
    possible_moves.push_back( basic_check_one_move(x, y, -2, 1, color) );

    for (char i : possible_moves){
        if (i=='n' ){
            return true;
        }
    }
    return false;
    
}

//finner trekk i en retning til det ikke er flere
void Brett::basic(int xx, int yy, int dx, int dy, char color, vector<Point>& vec){
    int x=dx+xx;
    int y=dy+yy;

    while ( in_range(x, y) ){

        bool checked = check(xx, yy, x, y, real_brett[xx][yy]);

        if ( !checked && real_brett[x][y].empty() ){
            vec.push_back({x, y});
        }
        else if ( !checked && color != real_brett[x][y][0] )
        {
            vec.push_back({x, y});
            break;
        }
        else if ( real_brett[x][y][0]==color )
        {
            break;
        }
        
        x+=dx;
        y+=dy;
    }
}

//finner bare et trekk i en rettning, hest og konge
void Brett::basic_one_move(int xx, int yy, int dx, int dy, char color, vector<Point>& vec){
    int x=dx+xx;
    int y=dy+yy;

    if ( in_range(x, y) && !check(xx, yy, x, y, real_brett[xx][yy]) && ( real_brett[x][y].empty() || (real_brett[x][y][0] != color) ) ){
        vec.push_back({x, y});
    }
}

//brukt for å finne sjakk
char Brett::basic_check(int king_x, int king_y, int retning_dx, int retning_dy, char color){
    king_x+=retning_dx;
    king_y+=retning_dy;

    while ( in_range(king_x, king_y) ){
        //rekkefølgen er nice her, får nok ikke range error
        if ( !real_brett[king_x][king_y].empty() )
        {
            if (color != real_brett[king_x][king_y][0])
            {
                return real_brett[king_x][king_y][1];
            }
            return '0';
            
        }
        king_x+=retning_dx;
        king_y+=retning_dy;
    }
    return '0';
}

//for bonde og hest
char Brett::basic_check_one_move(int king_x, int king_y, int retning_dx, int retning_dy, char color){
    king_x+=retning_dx;
    king_y+=retning_dy;

    if ( in_range(king_x, king_y) ){
        //rekkefølgen er nice her, får nok ikke range error
        if ( !real_brett[king_x][king_y].empty() && color != real_brett[king_x][king_y][0])
        {
            return real_brett[king_x][king_y][1];
        }
    }
    return '0';
}

void Brett::bishop(int x, int y, char color, vector<Point>& re){
    basic(x, y, 1, 1, color, re);
    basic(x, y, -1, -1, color, re);
    basic(x, y, 1, -1, color, re);
    basic(x, y, -1, 1, color, re);
}

void Brett::rook(int x, int y, char color, vector<Point>& re){
    basic(x, y, 0, 1, color, re);
    basic(x, y, 0, -1, color, re);
    basic(x, y, 1, 0, color, re);
    basic(x, y, -1, 0, color, re);
}

void Brett::queen(int x, int y, char color, vector<Point>& re){

    rook(x, y, color, re);
    bishop(x, y, color, re);

}

void Brett::knight(int x, int y, char color, vector<Point>& re){
    basic_one_move(x, y, 2, -1, color, re);
    basic_one_move(x, y, 2, 1, color, re);
    basic_one_move(x, y, 1, -2, color, re);
    basic_one_move(x, y, 1, 2, color, re);
    basic_one_move(x, y, -1, -2, color, re);
    basic_one_move(x, y, -1, 2, color, re);
    basic_one_move(x, y, -2, -1, color, re);
    basic_one_move(x, y, -2, 1, color, re);
}

void Brett::king(int x, int y, char color, vector<Point>& re){

    for(int i = -1; i<=1; i++){
        for (int k=-1; k<=1; k++){
            if ( i==0 && k==0 ){
                continue;
            }
            basic_one_move(x, y, i, k, color, re);
        }
    }

    vector<Point> rokade;
    
    if (!check(0, 0, 0, 0, real_brett[0][0]))
    {
        if ((white_turn && wrr) || (!white_turn && brr))
        {
            basic(x, y, 1, 0, color, rokade);
            if (rokade.size() == 2)
            {
                re.push_back(rokade[1]);
            }
        }
        rokade.clear();
        if ((white_turn && wlr) || (!white_turn && blr))
        {
            basic_one_move(x, y, -1, 0, color, rokade);
            basic_one_move(x, y, -2, 0, color, rokade);
            if (rokade.size() == 2 && real_brett[x - 3][y].empty())
            {
                re.push_back(rokade[1]);
            }
        }
    }
}

void Brett::basic_pawn_takes(int x, int y, int dx, int dy, char color, vector<Point>& vec){
    x+=dx;
    y+=dy;
    if (in_range(x, y))
    {
        if (!real_brett[x][y].empty() && (real_brett[x][y][0] != color) && !check(x-dx, y-dy, x, y, real_brett[x-dx][y-dy]))
        {
            vec.push_back({x, y});
        }
        else if (en_passant.x > 0 && en_passant.y > 0 && en_passant.x == x && en_passant.y == y && !check(x-dx, y-dy, x, y, real_brett[x-dx][y-dy], true) )
        {
            vec.push_back({x, y});
        }
    }
}

void Brett::pawn(int x, int y, char color, vector<Point>& re){
    int direction{1};
    int start_pos{1};
    if (color=='b') { direction = -1; start_pos=6;}

    if ( real_brett[x][y+direction].empty() && !check(x, y, x, y+direction, real_brett[x][y])) {
        re.push_back({x, direction+y});
    }

    basic_pawn_takes(x, y, -1, direction, color, re);
    basic_pawn_takes(x, y, 1, direction, color, re);

    if ( y==start_pos && real_brett[x][y+direction].empty() && real_brett[x][y+2*direction].empty() && !check(x, y, x, y+2*direction, real_brett[x][y]) ){
        re.push_back({x, y+direction*2});
    }
}

void Brett::get_moves(int piece_pos_x, int piece_pos_y, string code, vector<Point>& re){
    if (code[1] == 'r'){
        rook(piece_pos_x, piece_pos_y, code[0], re);
    }
    else if (code[1] == 'b') {
        bishop(piece_pos_x, piece_pos_y, code[0], re);
    }
    else if (code[1] == 'p'){
        pawn(piece_pos_x, piece_pos_y, code[0], re);
    }
    else if (code[1] == 'k'){
        king(piece_pos_x, piece_pos_y, code[0], re);
    }
    else if (code[1] == 'q'){
        queen(piece_pos_x, piece_pos_y, code[0], re);
    }
    else if (code[1] == 'n'){
        knight(piece_pos_x, piece_pos_y, code[0], re);
    }
}

bool Brett::is_legal_move(int x, int y){
    x/=rute;
    y/=rute;
    x=7-x;

    int piece_pos_x=7-selected_piece->pos.x/rute;
    int piece_pos_y=selected_piece->pos.y/rute;

    string code = selected_piece->get_piece_code();

    vector<Point> re;

    get_moves(piece_pos_x, piece_pos_y, code, re);

    for (auto i = re.begin(); i!=re.end(); i++){
        if ( i->x == x && i->y== y){
            return true;
        }
    }
    return false;
}

bool Brett::no_possible_moves(){
    
    vector <Point> possible_moves;

    for (auto i= 0; i<brikkene.size(); i++){
        if ( brikkene[i]->is_white() == white_turn ){

            get_moves(7-brikkene[i]->pos.x/rute, brikkene[i]->pos.y/rute, brikkene[i]->get_piece_code(), possible_moves);
            
            if ( !possible_moves.empty() ){
                return false;
            }
        }
    }
    return true;
}

