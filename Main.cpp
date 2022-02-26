#include <windows.h>
#include <iostream>
#include <fstream>
#include <math.h>

#pragma warning(disable : 4996)

using namespace std;

volatile double res_num;
volatile double res_den;

struct polynom {
	int degree;
	double* coefficients;
	double x;
	

	polynom(int degree, double* coef, double x) {
		this->degree = degree;
		this->coefficients = coef;
		this->x = x;
	}

	polynom(polynom* temp) {
		this->degree = temp->degree;
		this->coefficients = temp->coefficients;
		this->x = temp->x;
	}
};


DWORD WINAPI Numerator(LPVOID temp)
{
	

	polynom num = new polynom((polynom*)temp);
	double result = 0.0;
	for (int i = 0; i < num.degree + 1; i++) {
		result += (num.coefficients[i] * pow(num.x, num.degree - i));
		Sleep(15);
	}
	cout << "Numerator is P(x) = " << result << endl;
	res_num = result;
	return 0;
}


DWORD WINAPI Denominator(LPVOID temp)
{
	polynom den = new polynom((polynom*)temp);
	double result = 0.0;
	for (int i = 0; i < den.degree + 1; i++) {
		result += (den.coefficients[i] * pow(den.x, den.degree - i));
		Sleep(15);
	}
	cout << "Denominator is P(x) = " << result << endl;
	res_den = result;
	return 0;
}



int main()
{
	int num_degree;
	cout << "Enter the Numerator polynom degree\n";
	cin >> num_degree;

	double* num_coef = new double[num_degree+1];
	cout<< "Enter the Numerator polynom coefficients\n";
	for (int i = 0; i < num_degree + 1; i++) {
		cin >> num_coef[i];
	}
	
	int den_degree;
	cout << "Enter the Denominator polynom degree\n";
	cin >> den_degree;

	double* den_coef = new double[den_degree + 1];
	cout << "Enter the Denominator polynom coefficients\n";
	for (int i = 0; i < den_degree + 1; i++) {
		cin >> den_coef[i];
	}

	double x;
	cout << "Enter the x value\n";
	cin >> x;

	HANDLE hThread[2];
	DWORD IDThread[2];

	polynom* num = new polynom(num_degree, num_coef, x);
	polynom* den = new polynom(den_degree, den_coef, x);

	
	hThread[0] = CreateThread(NULL, 0, Numerator, (void*)num, 0, &IDThread[0]);
	if (hThread[0] == NULL) {
		cout << "error";
		return GetLastError();
	}

	hThread[1] = CreateThread(NULL, 0, Denominator, (void*)den, 0, &IDThread[1]);
	if (hThread[1] == NULL) {
		cout << "error";
		return GetLastError();
	}


	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);


	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);


	if (res_den != 0) {
		cout << "f(x) = " << res_num / res_den << endl;
	}
	else {
		cout << "Denominator is 0! we can't divide by 0 " << endl;
	}
	
	return 0;
}