#include <iostream>
#include <stdlib.h>

using namespace std;

class fmRadio{
private:
	bool state;
	double freq;
	double* stations;

public:
	fmRadio ();

	bool onoff();
	double inc ();
	double dec ();
};

int main (){
	fmRadio radio;

	cout << "Radio on" << endl;
	radio.onoff();

	cout << "Scrolling up:" << endl << endl;
	for ( int i = 0; i < 100; i++ ){
		double t = radio.inc();
		if ( t )
			cout << t << endl;
	}

	cout << "Scrolling down:" << endl << endl;
	for ( int i = 0; i < 100; i++ ){
		double t = radio.dec();

		if ( t )
			cout << t << endl;
	}

	cout << "Radio off" << endl;
	radio.onoff();
	cout << "Trying to scroll:" << endl << endl;
	for ( int i = 0; i < 100; i++ ){
		double t = radio.inc();

		if ( t )
			cout << t << endl;
	}

	cout << "Radio on:" << endl << endl;
	radio.onoff();

	cout << "Scrolling up:" << endl << endl;
	for ( int i = 0; i < 100; i++ ){
		double t = radio.inc();

		if ( t )
			cout << t << endl;
	}

	return 0;
}

fmRadio::fmRadio (){
	this->state = false;

	this->stations = new double[10];
	for ( int i = 0; i < 10; i++ )
		this->stations[i] = rand()%20 + 88.0;
}

bool fmRadio::onoff (){
	this->state = !this->state;
	if ( this->state )
		this->freq = 88.0;

	return state;
}

double fmRadio::inc (){
	if ( this->state ){
		this->freq += 0.25;

		if ( this->freq > 108.0 ) this->freq = 108.0;

		for ( int i = 0; i < 10; i++ )
			if ( this->stations[i] == this->freq )
				return this->freq;
	}

	return 0;
}

double fmRadio::dec (){
	if ( this->state ){
		this->freq -= 0.25;

		if ( this->freq < 88.0 ) this->freq = 88.0;

		for ( int i = 0; i < 10; i++ )
			if ( this->stations[i] == this->freq )
				return this->freq;
	}

	return 0;
}
