#include "std_lib_facilities.h"

#include "brett.h"



int main()
{
	//using namespace Graph_lib;
	srand(static_cast<unsigned int>(time(nullptr))); //srand(time(0)) funker også :)
	setlocale(LC_ALL, "nb_NO.UTF-8");
	
	auto win = std::make_unique<Fl_Double_Window>(18*rute, 8*rute, "Sjakk");
	win->color(FL_WHITE);

	Brett* spill= new Brett(win->w(), win->h());

	win->end();
	win->show();

	auto next_drawing = chrono::steady_clock::now();

	while( win -> shown() ){

		//dette er bedre enn sleep_for fordi her kan marskinen jobbe mens tiden går :)
		this_thread::sleep_until(next_drawing);
		next_drawing+=chrono::microseconds(1'000'000 / 40);

		Fl::check();
		//Fl::redraw();
	}
	

}
