#include <iostream>
#include <fstream>
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
	ofstream fout(args[1], ios::binary);
	int n = atoi(args[2]);

	for (int i = 0; i < n; i++)
	{
		system("cls");
		employee empl;
		cout << "Enter employee number:\n";
		cin >> empl.num;

		cout << "Enter employee name:\n";
		cin >> empl.name;

		cout << "Enter hours of work:\n";
		cin >> empl.hours;
		fout.write((char*)&empl, sizeof(empl));
	}
	fout.close();
}