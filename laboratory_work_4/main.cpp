#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

int del_on_7(char *number)
{
	int k = 10, i;
	char last_numb = number[k - 1] * 2;
	char dec_numb = number[k - 2] + 10 * number[k - 3];
	dec_numb -= last_numb;

	for (i = k - 3; i >= 1; i--)
	{
		last_numb = (dec_numb % 10) * 2;
		dec_numb = number[i - 1] * 10 + (int)(dec_numb / 10);
		dec_numb -= last_numb;
	}
	
	if (dec_numb % 7 == 0)
		return 0;
	else return 1;
}

int sdvig(int beg, int end, char *number)
{
	if (beg > end)
		return 1;

	int i, j, a;

	for (i = end; i >= beg; i--)// перебор до первой тройки слева
	{
		if (number[i - 1] == 3)
			break;
	}
	if (number[i] == 3) // если мы сейчас на тройке, то рекурсия не нужна(сокращение перебора)
		return 1;

	for (; i >= beg; i--)// сдвиг семерки влево и перебор всех вариантов положения других семерок относительно положения этой семерки
	{
		if (i - 1 >= 0)
		{
			a = number[i - 1];
			number[i - 1] = number[i];
			number[i] = a;
			if (!del_on_7(number))// если число делится
			{
				return 0;
			}
			if (sdvig(i + 1, end, number) == 0) // вызов перебора для правой части числа. Если функция вернула 0(число найдено), выходим из функции
				return 0;
		}
	}

	if (i == -1)//(обработка особых случаев)
		i++;
	for (j = end; j >= beg; j--)
	{
		if (number[i] == 3)// сокращение перебора
			return 1;
		if (number[j] == 3)// возвращение семерки в крайнюю правую не занятую семеркой ячейку
		{
			a = number[j];
			number[j] = number[i];
			number[i] = a;
			return 1;
		}
	}
}

int main()
{
	char number[10] = { 3,3,3,3,3,3,3,7,7,7 };
	setlocale(LC_ALL, "");
	
	sdvig(0, 9, number);
	cout << "Искомое число: ";
	for (int i = 0; i < 10; i++)
	{
		cout << (char)('0' + number[i]);
	}
	cout << endl;
	
	system("pause");
	return 0;
}