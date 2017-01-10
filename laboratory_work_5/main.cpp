#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("1.txt");
	setlocale(LC_ALL, "");
	double eps;
	cout << "¬ведите точность eps=";
	cin >> eps;
	//fout << eps << endl;
	double Sum, sn; long long n;

	cout << "|" <<  setw(3) << "x" << setw(3) << "|" << setw(8) << "Sum" << setw(4) <<  "|" << setw(7) << "n" << setw(4) << "|" << setw(5) << "x/2" << setw(2)<< "|" << "\n";

	for (double x = 0.1; x <= 1.0; x += 0.1)
	{
		double sin_n, cos_n, sin_x = sin(x), cos_x = cos(x);

		int zn = -1;
		Sum = 0;
		n = 0;
		do
		{
			n++;
			if (n != 1)
			{
				double new_sin = sin_n * cos_x + cos_n * sin_x;
				cos_n = cos_n * cos_x - sin_n * sin_x;
				sin_n = new_sin;
			}
			else
			{
				sin_n = sin_x;
				cos_n = cos_x;
			}
			
			zn = -zn;
			sn = zn*sin_n / n;
			Sum += sn;

		} while (fabs(sn) > eps);

		cout << "|" << setw(4) << x << " |" << setw(10) << Sum << " |" << setw(9) << n << " |" << setw(5) << x/2 << " |" << "\n";

	}

	system("pause");
	return 0;
}