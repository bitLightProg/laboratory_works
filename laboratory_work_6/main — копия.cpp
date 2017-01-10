#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char *string;
	unsigned size = 64;
	string = (char*) calloc(size+1,size+1);

	char ch;
	unsigned index = 0;
	unsigned spaces = 0;
	while (ch = getchar())
	{
		if (ch == '\n')
			break;

		if (ch == ' ')
			spaces++;

		if (index > size)
		{
			char* ptr;
			if ((ptr = (char*)realloc(string, (size * 2) + 1)) != NULL)
			{
				
				size *= 2;
				string = ptr;				
			}
			else
			{
				cout << "Невозможно выделить память. Завершение работы программы.";
				system("pause");
				return 1;
			}
		}

		string[index++] = ch;
		string[index] = '\0';
	}
	//cout << string << endl;
	char *outstring = (char*) calloc(size*2+1, size * 2 + 1);
	int out_index = 0;
	int k = 0;
	//strstr(string, );
	for (int i = 0; i < index; i++)
	{
		if (string[i] == '\n')
			continue;
		

		for (int j = i + 6; j < index; j++)
		{
			if (string[i+k] == string[j])
			{
				if (string[j] == ' ')
				{
					if (k > 5)
					{
						for (int q = i; q < i + k; q++)
						{
							outstring[out_index++] = string[q];
						}
						j -= k;
						for (int q = i; q < i + k; q++)
						{
							outstring[out_index++] = string[q];
							string[q] = '\n';
							string[j + q - i] = '\n';
						}

						i = 0;
						j = i + 6;
						k = 0;
						break;
					}
					else
					{
						j -= k;
						k = 0;
					}
				}
				else
					k++;
			}
			else
			{
				if (k > 5)
				{
					for (int q = i; q < (i + k); q++)
					{
						outstring[out_index++] = string[q];
					}
					j -= k;
					for (int q = i; q < (i + k); q++)
					{
						outstring[out_index++] = string[q];
						string[q] = '\n';
						string[j + q - i] = '\n';
					}

					i = 0;
					j = i + 6;
					k = 0;
					break;
				}
				else
				{
					j -= k;
					k = 0;
				}
			}
		}
	}

	for (int i = 0; i < index; i++)
	{
		if (string[i] == '\n')
			continue;

		outstring[out_index++] = string[i];
	}
	outstring[out_index] = '\0';
	cout << outstring << endl;
	free(string);
	free(outstring);
	//cout << endl;
	system("pause");
	return 0;
}