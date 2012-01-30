#include <iostream>
#include <fstream>

using namespace std;

class array1{
protected:
	int n;
	int* data;

public:
	array1 (int n);
	virtual void input ();
	void output ();
	int mult ();
};

class array2 : public array1 {
public:
	array2(int n);
	void input(char* filename);
};

int main () {
	array1 a1(10);
	array2 a2(10);

	a1.input();
	a1.output();
	cout << a1.mult() << endl << endl;

	a2.input("lab2.input");
	a2.output();
	cout << a2.mult() << endl;

	return 0;
}

array1::array1 (int n){
	this->n = n;
	this->data = new int[n];
}

void array1::input (){
	cout << "Be ready to enter array elements:" << endl;

	for ( int i = 0; i < this->n; i++ )
		cin >> this->data[i];

	cout << "Well done, dude" << endl;
}

void array1::output (){
	cout << "Outputing array:" << endl;

	for ( int i = 0; i < this->n; i++ )
		cout << this->data[i] << endl;
}

int array1::mult (){
	int t = 1;

	for ( int i = 0; i < this->n; i++ )
		t *= this->data[i];

	return t;
}

array2::array2(int n) : array1(n) {}

void array2::input (char* filename){
	ifstream fin(filename);

	cout << "Reading from file" << endl;

	for ( int i = 0; i < this->n; i++ )
		fin >> this->data[i];

	fin.close();
}
