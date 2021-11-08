#include "brett.h"

void Brett::read_board(){
    for (int k = 7; k > -1; k--)
    {
        for (int i = 0; i < 8; i++)
        {
            cout<<setw(2)<<real_brett[i][k]<<' ';
        }
        cout<<endl;
    }
}

//lager oppsettet for classic chess
vector<vector<string>> classic(){
    vector<vector<string>> re;
    for (int i = 0; i < 8; i++){
        vector<string> init (8, "");
        re.push_back(init);
    }
    string color="w";
    double speil=0;
    for (int c = 0; c < 2; c++)
    {
        for (int i= 0; i<8 ; i++){
            re[i][abs(1-speil)]=color+"p";
        }

        re[0][speil]=color+"r";
        re[7][speil]=color+"r";


        re[1][speil]=color+"n";
        re[6][speil]=color+"n";

        re[2][speil]=color+"b";
        re[5][speil]=color+"b";

        re[3][speil]=color+"q";
        re[4][speil]=color+"k";

        color="b";
        speil=7;
    }
    return re;
}

vector<vector<string>> test1(){
    vector<vector<string>> re;
    for (int i = 0; i < 8; i++){
        vector<string> init (8, "");
        re.push_back(init);
    }
    re[4][0]="wk";
    re[0][0]="wr";
    re[3][7]="bk";
    re[4][1]="wr";
    re[2][1]="wr";
    return re;
}

void Brett::draw(){
    brettbildet.draw(10*rute, 0);
    brettbildet.draw(0, 0);
    for (auto it=0; it!= brikkene.size(); it++){
        brikkene[it]->draw();
    }

    fl_draw_box(FL_FLAT_BOX, 8*rute, 0, 2*rute, 8*rute, FL_WHITE);
    if ( promotion ){
        if (! white_turn){
            wp.draw(promotion->x, promotion->y);
            wp.draw(17*rute-promotion->x, 7*rute-promotion->y);
            wq.draw(8*rute, 0);
            wr.draw(8*rute, 2*rute);
            wb.draw(8*rute, 4*rute);
            wn.draw(8*rute, 6*rute);
        }
        else
        {
            bp.draw(17*rute-promotion->x, 7*rute-promotion->y);
            bp.draw(promotion->x, promotion->y);
            bq.draw(8*rute, 0);
            br.draw(8*rute, 2*rute);
            bb.draw(8*rute, 4*rute);
            bn.draw(8*rute, 6*rute);
        }
    }
    if ( checkmate ){
        mate.draw(white_turn? 11*rute : rute, 2*rute);
    }
    else if ( stalemate )
    {
        stale.draw(white_turn? rute : 11*rute, rute);
    }
    
}

Brett::Brett(int x, int y)
    : Fl_Widget(0, 0, x, y),
    real_brett{classic()}, //kan eventuelt bytte dette senere, men ser ikke noe problem i å ha classic som default
    selected_piece{nullptr},
    white_turn{true},
    en_passant{-1, -1},
    en_passant_next{-1, -1},
    promotion{nullptr},
    checkmate{false},
    stalemate{false},
    brr{true},
    blr{true},
    wrr{true},
    wlr{true}
{
    brettbildet.scale(8*rute, 8*rute);
    bb.scale(2*rute, 2*rute);
    bq.scale(2*rute, 2*rute);
    br.scale(2*rute, 2*rute);
    bn.scale(2*rute, 2*rute);
    wq.scale(2*rute, 2*rute);
    wr.scale(2*rute, 2*rute);
    wn.scale(2*rute, 2*rute);
    wb.scale(2*rute, 2*rute);
    wp.scale(rute, rute);
    bp.scale(rute, rute);
    stale.scale(6*rute, 6*rute);
    mate.scale(6*rute, 6*rute);

    //read_board();
    for (int i = 0; i<8 ; i++){
        for (int k=0; k<8 ; k++){
            if ( !real_brett[i][k].empty() )
            {
                brikkene.push_back(new Brikke{(7-i)*rute, k*rute, real_brett[i][k]});
                brikkene.back()->pic.scale(rute, rute);
            }
        }
    }
}

Brikke* Brett::find_piece(int x, int y){
    int xx=(x/rute)*rute;
    int yy=(y/rute)*rute;
    for (auto i = 0; i < brikkene.size(); i++)
    {
        if ( xx == brikkene[i]->x() && yy == brikkene[i]->y() && brikkene[i]->is_white()== white_turn )
        {
            return brikkene[i];
        }
    }
    return nullptr;
}


int Brett::handle(int event){
    if (promotion)
    {
        if (event == FL_PUSH && Fl::event_x()<10*rute && Fl::event_x()>8*rute){
            if (Fl::event_y() < 2*rute){
                brikkene.push_back(new Brikke{promotion->x, promotion->y, white_turn? "bq": "wq"});
            }
            else if (Fl::event_y() < 4*rute){
                brikkene.push_back(new Brikke{promotion->x, promotion->y, white_turn? "br": "wr"});

            }
            else if (Fl::event_y() < 6*rute){
                brikkene.push_back(new Brikke{promotion->x, promotion->y, white_turn? "bb": "wb"});

            }
            else if (Fl::event_y() < 8*rute){
                brikkene.push_back(new Brikke{promotion->x, promotion->y, white_turn? "bn": "wn"});

            }
            brikkene.back()->pic.scale(rute, rute);
            delete promotion;
            promotion=nullptr;
        }
        white_turn = !white_turn;
        bool checkzy = check_pos();
        white_turn = !white_turn;
        if ( checkzy && no_possible_moves()){
            checkmate=true;
        }
        else if (no_possible_moves()){
            stalemate=true;
        }
        redraw();
    }
    else
    {
        if (event == FL_PUSH)
        {
            mouse_click(reverse_x(Fl::event_x()), reverse_y(Fl::event_x(), Fl::event_y()));
            redraw();
            return 1;
        }

        else if (event == FL_DRAG)
        {
            if (selected_piece)
            {
                mouse_drag(reverse_x(Fl::event_x()), reverse_y(Fl::event_x(), Fl::event_y())); //Fl::event_x(), Fl::event_y());
                //skal bare sjekke om den en in range
                if ( (selected_piece->x() > (7 * rute + rute / 4) || selected_piece->x() < -rute / 4) || (selected_piece->y() > (8 * rute + rute / 4) || selected_piece->y() < -rute / 4) )
                {
                    return_piece();
                    selected_piece = nullptr;
                }
                redraw();
            }
            return 1;
        }
        else if (event == FL_RELEASE)
        {
            release(reverse_x(Fl::event_x()), reverse_y(Fl::event_x(), Fl::event_y()));
            redraw();
            return 1;
        }
    }

    return Fl_Widget::handle(event);
}

void Brett::mouse_click(int x, int y){
    
    if ( ! selected_piece ){
        selected_piece=find_piece(x, y);
    }
    else if ( is_legal_move(x, y) ){
        final_move(x, y);
    }
    else{
        return_piece();
        selected_piece=nullptr;
    }

    
    mouse.x=x;
    mouse.y=y;
}

void Brett::mouse_drag(int x, int y){
        int dx = x - mouse.x;
        int dy = y - mouse.y;
        selected_piece->drag(dx, dy);
        mouse.x = x;
        mouse.y = y;

    //selected_piece=nullptr;
}

bool Brett::has_moved(int x, int y){
    int pos_x= (x/rute) * rute;
    int pos_y= (y/rute) * rute;
    return !( pos_x == selected_piece->x() && pos_y == selected_piece->y() ) ;
}

void Brett::release(int x, int y){
    if (selected_piece && has_moved(x, y))
    {
        if ( is_legal_move(x, y) )
        {
            final_move(x, y);
        }
        else 
        {
            return_piece();
            selected_piece = nullptr;
        }
    }
}

int Brett::reverse_x(int x){
    if (x >= 9*rute){
        return 18*rute-x;
    }
    return x;
}

int Brett::reverse_y(int x, int y){
    if (x >= 9*rute){
        return 8*rute-y;
    }
    return y;
}

void Brett::return_piece(){
    if (selected_piece){
        selected_piece->move(selected_piece->pos.x, selected_piece->pos.y);
    }
}

void Brett::final_move(int x, int y){

    //sjekke om rokade fortsatt er mulig, idk om det staves sånn
    if (selected_piece->get_piece_code() == "bk" ){
        brr=false;
        blr=false;
    }
    else if ( selected_piece->get_piece_code() == "wk" ){
        wrr=false;
        wlr=false;
    }
    else if (selected_piece->pos.x/rute == 7 && selected_piece->get_piece_code()[1]=='r' )
    {
        if ( selected_piece->is_white() ){
            wlr=false;
        }
        else
        {
            blr=false;
        }
    }
    else if (selected_piece->pos.x/rute == 0 && selected_piece->get_piece_code()[1]=='r' )
    {
        if ( selected_piece->is_white() ){
            wrr=false;
        }
        else
        {
            brr=false;
        }
    }
    // cout<<"x:" <<selected_piece->x()<<" x/rute: "<<selected_piece->x()/rute<<endl;
    // cout<<"x:" <<selected_piece->pos.x<<" x/rute: "<<selected_piece->pos.x/rute<<endl;
    // cout<<"y:" <<selected_piece->y()<<" y/rute: "<<selected_piece->y()/rute<<endl<<endl;
    

    int real_brett_x=7-x/rute;
    int real_brett_y=y/rute;

    //fjerner brikker som har blitt tatt
    if ( !real_brett[real_brett_x][real_brett_y].empty() ){
        for (auto i=0; i!=brikkene.size(); i++){
            if ( brikkene[i]->x()==(x/rute)*rute && brikkene[i]->y()==(y/rute)*rute && brikkene[i]->is_white()!=white_turn ){
                brikkene.erase(brikkene.begin()+i);
                break;
            }
        }
    }
    else if ( en_passant.x == real_brett_x && en_passant.y == real_brett_y ){

        int bonde_retning= white_turn? 1:-1;
        for (auto i=0; i!=brikkene.size(); i++){
            if ( brikkene[i]->x()==(x/rute)*rute && brikkene[i]->y()==(y/rute - bonde_retning)*rute && brikkene[i]->is_white()!=white_turn ){
                real_brett[7-x/rute][y/rute - bonde_retning]="";
                brikkene.erase(brikkene.begin()+i);
                
                break;
            }
        }
    }

    //fikse endringen i real_brett
    int vector_x=7-selected_piece->pos.x/rute;
    int vector_y=selected_piece->pos.y/rute;
    real_brett[vector_x][vector_y]="";
    int diff=vector_y;
    int diffx=vector_x;

    selected_piece->move(x, y);

    //oppdatere etter å ha flyttet, og fikse i real_brett
    vector_x=7-selected_piece->pos.x/rute;
    vector_y=selected_piece->pos.y/rute;
    real_brett[vector_x][vector_y]=selected_piece->get_piece_code();

    //her flytter jeg tårnet hvis det er rokade
    if ( diffx < vector_x && selected_piece->get_piece_code()[1]=='k' && abs( diffx-vector_x ) == 2){
        real_brett[5][selected_piece->pos.y/rute]=real_brett[7][selected_piece->pos.y/rute];
        real_brett[7][selected_piece->pos.y/rute]="";
        for (auto i=0; i!=brikkene.size(); i++){
            if ( brikkene[i]->x()==0 && brikkene[i]->y()==selected_piece->y() ){
                brikkene[i]->move(2*rute, selected_piece->y());
                break;
            }
        }

    }
    else if ( selected_piece->get_piece_code()[1]=='k' && abs( diffx-vector_x ) == 2){
        real_brett[3][selected_piece->pos.y/rute]=real_brett[0][selected_piece->pos.y/rute];
        real_brett[0][selected_piece->pos.y/rute]="";
        for (auto i=0; i!=brikkene.size(); i++){
            if ( brikkene[i]->x()==7*rute && brikkene[i]->y()==selected_piece->y() ){
                brikkene[i]->move(4*rute, selected_piece->y());
                break;
            }
        }
    }
    

    //her sletter jeg promotion brikken
    if ( selected_piece->get_piece_code()[1] == 'p' && ( selected_piece->y() == 0 || selected_piece->y() == 7*rute) ){
        for (auto i=0; i!=brikkene.size(); i++){
            if ( brikkene[i]->x()==selected_piece->x() && brikkene[i]->y()==selected_piece->y() ){
                brikkene.erase(brikkene.begin()+i);
                promotion=new Point{selected_piece->x(), selected_piece->y()};
                break;
            }
        }
    }

    //her fikses en passant
    if ( abs(diff-vector_y) == 2 && selected_piece->get_piece_code()[1] == 'p' ){
        en_passant={vector_x, vector_y - (vector_y-diff)/2};
    }
    else
    {
        en_passant={-1, -1};
    }

    selected_piece= nullptr;

    white_turn= !white_turn;

    //her sjekkes sjakkmatt og patmat, tror denne rekkefølgen er nice sånn at den ikke trenger å regne ut ting to ganger
    if ( check_pos() && no_possible_moves() ){
        checkmate=true;
    }
    else if (no_possible_moves()){
        stalemate=true;
    }
    //check(0, 0, 0, 0, real_brett[0][0])

    //read_board();

}

