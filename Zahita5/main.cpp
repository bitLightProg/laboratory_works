#include <iostream>
using namespace std;
//------------------------------------------------- 6

void F6(char c[], int nn)

{
	int k, mm;

	for (mm = nn, k = 0; mm != 0; mm /= 10, k++);

	for (c[k--] = '\0'; k >= 0; k--)

	{
		c[k] = nn % 10 + '0'; nn /= 10;
	}

}

//------------------------------------------------ 12

int F12(char c[]) {

	for (int i = 0; c[i] != 0; i++) {

		if (c[i] == ' ') continue;
		int j;

		for (j = i + 1; c[j] == c[i]; j++);

		for (; c[j] != 0; j++) {
			int k;

			for (k = 0; i + k < j && c[i + k] == c[j + k]; k++);

			if (k >= 4) return i;

		}
	} return -1;
}

int main()
{
	char ch[10];
	F6(ch,1000);
	cout << ch << endl;
	char ch1[21];
	int n;
	setlocale(LC_ALL, "");
	cout << "Введите количество символов <= 20" << endl;
	cin >> n;
	cout << "Введите символы"<< endl;
	int i;
	for (i = 0; i < n; i++)
	{
		cin >> ch1[i];
	}
	ch1[i] = '\0';
	cout << F12(ch1) << endl;
	//cout << ch << endl;
	system("pause");
	return 0;
}