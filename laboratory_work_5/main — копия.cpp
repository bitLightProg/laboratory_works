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
	double s, sn; long long n = 1;
	int otstup[4] = { 0,0,0,0 };
	for (double x = 0.1; x <= 1.0; x += 0.1)
	{
		int zn = -1;
		n = 1;
		for (s = 0, sn = x; fabs(sn) > eps; n++)
		{			
			if ((n + 1) % 2 == 1)
				zn = -1;
			else zn = 1;
			sn = zn*sin(x*n)/n;
			s += sn;
		}
		if (fabs(sn) == eps)
		{
			sn = -zn*sin(x*n) / n;
			s += sn;
		}
		if (n == 1 && s == 0) s += sin(x*n) / n;
		//printf("n=%d\t x=%0.1lf\t sum=%0.4lf\t x/2=%0.4lf\n", n, x, s, x/2);
		for (int i = 0; i < 4; i++)
		{
			char str[20];
			char numb[15];
			str[0] = '\0';
			switch (i) {
			case 0:				
				_itoa_s(n, numb, 10);
				strcat_s(str,"n=");
				strcat_s(str, numb);
				break;
			case 1:
				sprintf_s(numb, "%.1g", x);
				strcat_s(str, "x=");
				strcat_s(str, numb);
				break;
			case 2:
				sprintf_s(numb, "%.4g", s);
				strcat_s(str, "sum=");
				strcat_s(str, numb);
				break;
			case 3:
				sprintf_s(numb, "%.4g", x / 2);
				strcat_s(str, "x/2=");
				strcat_s(str, numb);
				break;
			}
			int length = strlen(str);
			if (length > otstup[i])
				otstup[i] = 0;
			for (int j = length; length < otstup[i] || otstup[i] == 0; length++)
			{
				if (i == 2)
				{
					if (length < 12)
						str[length] = ' ';
					else break;
				}
				else if (otstup[i] != 0)
				{
					str[length] = ' ';
				}
				else if (length < 12 && j*1.4 > length)
				{
					str[length] = ' ';
				}
				else break;
				
			}
			otstup[i] = length;
			str[length] = '\0';
			cout << str;
		}
		cout << endl;
		//cout << "n=" << setw(7) << n << "x=" << setw(7) << x << "sum=" << setw(7) << s << "x/2=" << setw(7) << x / 2 << "\n";
	}

	system("pause");
	return 0;
}