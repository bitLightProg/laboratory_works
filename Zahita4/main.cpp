#include <iostream>

using namespace std;

int F10(int a) {

	int n, k, s;

	for (n = a, s = 0; n != 0; n = n / 10)

	{
		k = n % 10; s = s * 10 + k;
	}

	return s;
}

void F11() {

	int a, n, k, s;

	for (a = 10; a<30000; a++) {

		for (n = a, s = 0; n != 0; n = n / 10)

		{
			k = n % 10; s = s + k;
		}

		if (a == s*s*s) printf("%d\n", a);

	}
}

int main()
{
	setlocale(LC_ALL, "");
	cout << "Введите число a" << endl;
	int a;
	cin >> a;
	cout << "Результат работы F10 = " << F10(a) << endl;
	cout << "Результат работы F11:" << endl;
	F11();
	system("pause");
	return 0;
}