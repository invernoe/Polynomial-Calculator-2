#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string>
using namespace std;

struct poly {
	int order;
	double x;
	double coeffVal[21] = {};
};

poly readPoly() {
	poly m;
	cout << "Enter polynomial order: ";
	cin >> m.order;
	cout << "Enter polynomial coefficients: ";
	for (int i = 0; i <= m.order; i++)
	{
		cin >> m.coeffVal[i];
	}
	cout << "Enter the value of x: ";
	cin >> m.x;

	return m;
}

double evalPoly(poly p) {
	int order = p.order;
	double m = 0;
	for (int i = 0; i <= p.order; i++)
	{
		m += p.coeffVal[i] * pow(p.x, order);
		order--;
	}
	return m;
}

poly addPoly(poly p1, poly p2) {
	poly p3;
	p3.order = p1.order;
	int power = 0;

	for (int j = 0; j < p1.order - p2.order; j++)
	{
		p3.coeffVal[j] = p1.coeffVal[j];
		power++;
	}

	for (int i = 0; i <= p2.order; i++)
	{
		p3.coeffVal[power] = p1.coeffVal[power] + p2.coeffVal[i];
		power++;
	}
	return p3;
}

poly subPoly(poly p1, poly p2) {
	poly p3;
	p3.order = p1.order;
	int power = 0;

	for (int j = 0; j < p1.order - p2.order; j++)
	{
		p3.coeffVal[j] = p1.coeffVal[j];
		power++;
	}

	for (int i = 0; i <= p2.order; i++)
	{
		p3.coeffVal[power] = p1.coeffVal[power] - p2.coeffVal[i];
		power++;
	}
	return p3;
}

poly mulPoly(poly p1, poly p2) {
	poly p3;

	p3.order = p1.order + p2.order;
	if (p3.order > 20) {
		p3.order = -1;
		return p3;
	}
	else {
		int index = 0;
		for (int i = p3.order; i >= 0; i--) {

			int order2 = p2.order;
			for (int j = 0; j <= p2.order; j++)
			{
				int order1 = p1.order;
				for (int k = 0; k <= p1.order; k++) {
					if (i == order1 + order2) { p3.coeffVal[index] += (p2.coeffVal[j] * p1.coeffVal[k]); }
					order1--;
				}
				order2--;
			}
			index++;
		}
		return p3;
	}

}

void polyCompare(poly &p1, poly &p2) {
	if (p1.order < p2.order) {
		poly tmp = p1;
		p1 = p2;
		p1 = tmp;
	}
}

void printPoly(poly p) {
	if (p.order != -1) {
		int power = p.order;
		cout << "f(x) = ";
		for (int i = 0; i <= p.order; i++)
		{
			if (p.coeffVal[i] != 0) {
				if (power == 1) {
					cout << p.coeffVal[i] << "x ";
					if (p.coeffVal[i + 1] > 0)
						cout << "+";
				}
				else if (power == 0)
					cout << p.coeffVal[i];
				else {
					cout << p.coeffVal[i] << "x^" << power << " ";
					if (p.coeffVal[i + 1] > 0)
						cout << "+";
				}
			}
			else
				if (p.coeffVal[i + 1] > 0)
					cout << "+";
			power--;
		}
		cout << endl << "f(x = " << p.x << ") = " << evalPoly(p) << endl << endl;
	}
	else
		cout << "error, please restart program." << endl;
}

void main() {
	poly x[3];
	for (int j = 0; j < 2; j++)
	{
		x[j] = readPoly();

		printPoly(x[j]);
	}
	polyCompare(x[0], x[1]);

	cout << "Choose operation to be performed(+, -, *) : ";
	char op;
	cin >> op;

	if (op == '+' || op == '-' || op == '*') {

		cout << "Enter value of x for the result polynomial: ";
		cin >> x[2].x;
		double xVal = x[2].x;
		switch (op) {
		case '*':

			x[2] = mulPoly(x[0], x[1]);
			x[2].x = xVal;
			printPoly(x[2]);
			break;

		case '+':

			x[2] = addPoly(x[0], x[1]);
			x[2].x = xVal;
			printPoly(x[2]);
			break;

		case '-':

			x[2] = subPoly(x[0], x[1]);
			x[2].x = xVal;
			printPoly(x[2]);
			break;
		}

	}
	else
		cout << "error, please restart program." << endl;

	system("pause");
}