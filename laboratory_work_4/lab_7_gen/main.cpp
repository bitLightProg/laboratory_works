#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	ofstream fout("input.txt");

	int b = 200000 + rand() % 100000;
	fout << b << endl;
	
	unsigned long long max = 0;	
	int val = rand() % b;
	unsigned long long a = 0;

	for (int i = 0; i < b; i++)
	{
		srand(time(NULL));
		int numb = rand() % 100000;
		max += numb;
		fout << max << " ";
		if (val == i)
			a = max;
	}
	
	fout << endl << a;	
	
	fout.close();
	//system("pause");
	return 0;
}