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
	
	cout << "Введите исходную строку:" << endl;
	while (ch = getchar())
	{
		if (ch == '\n')
			break;

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
	
	char *outstring = (char*) calloc(size*2+1, size * 2 + 1);
	int out_index = 0;
	int k = 0;
	int begin_index;
	int length = index / 2;
	char *temp_str = (char*) calloc(length + 1, length + 1);
	unsigned deleted_chars = 0;

	while(length > 5)
	{
		for (int i = 0; length > 5 && index - (i + length) >= length; i++)
		{
			bool flag = false;
			begin_index = i + length;
			for (int j = 0; j < length; j++)
			{
				if (string[i + j] == ' ' || string[i + j] == '\n')
				{
					flag = true;
					break;
				}
				temp_str[j] = string[i + j];
			}
			if (flag)
				continue;
			temp_str[length] = '\0';
			char * seek = string + begin_index;
			seek = strstr(seek, temp_str);
			if (seek != 0)
			{
				k = seek - string;
				for (int q = i; q < length + i; q++)
				{
					outstring[out_index++] = string[q];
				}
				for (int q = i; q < length + i; q++)
				{
					outstring[out_index++] = string[q];
					string[q] = '\n';
					string[k + q - i] = '\n';
				}
				i = -1;
				deleted_chars += length;
				length = (index / 2) - deleted_chars;
			}
		}
		length--;
	}
	
	for (int i = 0; i < index; i++)
	{
		if (string[i] == '\n')
			continue;

		outstring[out_index++] = string[i];
	}
	outstring[out_index] = '\0';

	cout << "Результат работы программы:"<< endl << outstring << endl;
	
	free(string);
	free(outstring);
	free(temp_str);
	
	system("pause");
	return 0;
}