#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* args[])
{
	setlocale(LC_ALL, ".1251");

	ifstream fin(args[1], ios::binary);
	employee* empl = new employee[100];
	
	int size = 0;
	
	while (!fin.eof()) {
		employee e;
		fin.read((char*)&e, sizeof(e));
		empl[size] = e;
		size++;
	}
	size--;
	fin.close();

	ofstream fout(args[2]);
	int money_per_hour = atoi(args[3]);
	
	fout << "Otchet po faily \"" << args[1] << "\"" << endl;
	
	for (int i = 0; i < size; i++)
	{
		fout << empl[i].num << " " << empl[i].name << " " << empl[i].hours << " " << empl[i].hours * money_per_hour << endl;
	}
	fout.close();
}