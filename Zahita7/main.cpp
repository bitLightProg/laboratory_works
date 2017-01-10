#include <iostream>

using namespace std;

//------------------------------------------------------13
const int n = 10;
void sort(int in[], int n) // min элемент в правой части массива мен€етс€ с текущим
{
	for (int i = 0; i < n - 1; i++)
	{
		int j, k;
		for (j = i + 1, k = i; j < n; j++)
			if (in[j] < in[k])
				k = j;

		int c = in[k];
		in[k] = in[i];
		in[i] = c;
		for (j = 0; j < n; j++)
			cout << in[j] << " ";
		cout << endl;
	}
}

//------------------------------------------------------14

void sort(int in[], int a, int b)
{
	int i, j, mode;

	if (a >= b) return;

	for (i = a, j = b, mode = 1; i < j; mode > 0 ? j-- : i++)
		if (in[i] > in[j])
		{
			int c = in[i]; in[i] = in[j]; in[j] = c;
			mode = -mode;
			for (int k = 0; k < n; k++)
				cout << in[k] << " ";
			cout << endl;
		}
	
	sort(in, a, i - 1); sort(in, i + 1, b);
}

int main()
{
	int arr[10] = { 5, 2 , 1 , 7 , 8, 0, 3, 4, 6, 9 };
	sort(arr, 0, 9);
	system("pause");
	return 0;
}