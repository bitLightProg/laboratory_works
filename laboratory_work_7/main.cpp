#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void create_file()
{
	try
	{
		ofstream fout("input.txt");
		system("cls");
		srand(time(NULL));
		while (true)
		{
			try
			{
				system("cls");
				int count;
				cout << "Введите количество чисел." << endl;
				cin >> count;
				if (count <= 0)
				{
					throw 1;
				}
				cout << "Введите диапазон возрастания чисел. (на сколько последующее число будет отличаться от предыдущего)\n"
					<< "(пример: 5-100, 666-6666). Числа должны быть больше 0. Если первое число будет больше второго, то они поменяются местами" << endl;

				long long a, b;
				char ch;
				cin >> a >> ch >> b;

				if (a <= 0 || b <= 0)
				{
					throw 1;
				}
				if (a > b)
				{
					long long c = a;
					a = b;
					b = c;
				}

				fout << count << endl;

				long long max = 0;
				int val = rand() % count;
				long long found = 0;
				b -= a;
				long long numb = a;
				for (int i = 0; i < count; i++)
				{
					if (b != 0)
						numb = a + rand() % b;
					max += numb;
					fout << max << " ";
					if (val == i)
						found = max;
				}
				fout << endl << found;
				fout.close();

				system("cls");
				cout << "Создание файла завершено." << endl;
				system("pause");
				return;

			}
			catch (...)
			{
				system("cls");
				cout << "Неправильный ввод. Повторите попытку." << endl;
				system("pause");
				continue;
			}
		}
	}
	catch (...)
	{
		cout << "Не удается создать файл. Завершение работы программы." << endl;
		system("pause");
	}

}

void create_bin_file()
{
	try
	{
		ofstream fout("input.bin", ios_base::binary);
		system("cls");
		srand(time(NULL));
		while (true)
		{
			try
			{
				system("cls");
				int count;
				cout << "Введите количество чисел." << endl;
				cin >> count;
				if (count <= 0)
				{
					throw 1;
				}
				cout << "Введите диапазон возрастания чисел. (на сколько последующее число будет отличаться от предыдущего)\n"
					<< "(пример: 5-100, 666-6666). Числа должны быть больше 0. Если первое число будет больше второго, то они поменяются местами" << endl;

				long long a, b;
				char ch;
				cin >> a >> ch >> b;

				if (a <= 0 || b <= 0)
				{
					throw 1;
				}
				if (a > b)
				{
					long long c = a;
					a = b;
					b = c;
				}

				fout.write((char *)&count, sizeof(count));

				long long max = 0;
				int val = rand() % count;
				long long found = 0;
				b -= a;
				long long numb = a;
				for (int i = 0; i < count; i++)
				{
					if (b != 0)
						numb = a + rand() % b;
					max += numb;
					fout.write((char *)&max, sizeof(max));					
					if (val == i)
						found = max;
				}
				fout.write((char *)&found, sizeof(found));
				fout.close();

				system("cls");
				cout << "Создание файла завершено." << endl;
				system("pause");
				return;

			}
			catch (...)
			{
				system("cls");
				cout << "Неправильный ввод. Повторите попытку." << endl;
				system("pause");
				continue;
			}
			
		}
	}
	catch (...)
	{
		cout << "Не удается создать файл. Завершение работы программы." << endl;
		system("pause");
	}

}


void binary_search()
{
	while (true)
	{
		system("cls");
		srand(time(NULL));
		cout << "1. Использовать текстовый файл.(input.txt)"
			<< endl << "2. Использовать бинарный файл. (input.bin)"
			<< endl << "3. Ввести данные с клавиатуры." << endl;
		char choice;
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			try
			{
				//double T1 = clock();
				ifstream fin("input.txt");
				
				int b;
				
				fin >> b;
				long long *arr = new long long[b];

				for (int i = 0; i < b; i++)
				{
					fin >> arr[i];
				}

				long long a = 0;
				long long val;
				fin >> val;
				if (a == b - 1)
				{
					cout << "Индекс искомого элемента массива равен "<< 0 << endl;
					delete[] arr;
					system("pause");
					return;
				}
				int count = 0;
				double T0 = clock();
				long long m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
				//cout << m << endl;
				count++;
				//cout << m << endl;
				while (b <= m)
					m--;
				while (a > m)
					m++;
				while (arr[m] != val)
				{
					//cout << m << endl;
					if (arr[m] < val)
					{
						if (a >= m)
						{
							m = ((a + b) / 2) + ((a + b) % 2);
							count++;
							while (arr[m] != val)
							{
								//cout << m << endl;
								if (arr[m] < val)
								{
									a = m;
									m = ((a + b) / 2) + ((a + b) % 2);
									count++;
								}
								else
								{
									b = m;
									m = ((a + b) / 2);
									count++;
								}
							}
							break;
						}
						else
						{
							a = m;
							m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
							count++;
						}
					}
					else
					{
						if (b <= m)
						{
							m = ((a + b) / 2) + ((a + b) % 2);
							count++;
							while (arr[m] != val)
							{
								//cout << m << endl;
								if (arr[m] < val)
								{
									a = m;
									m = ((a + b) / 2) + ((a + b) % 2);
									count++;
								}
								else
								{
									b = m;
									m = ((a + b) / 2);
									count++;
								}
							}
							break;
						}
						else
						{
							b = m;
							m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
							count++;
						}
					}
				}
				double T1 = clock();
				//cout << T1 - T0 << endl;
				cout << "Количество вычислений индекса искомого числа "<< count << endl;
				//cout << (double) clock() - T0 << endl;
				cout << "Индекс искомого элемента массива равен " << m << endl;
				delete[] arr;
				system("pause");
				return;
			}
			catch (...)
			{
				cout << "Не удается найти файл, либо он поврежден. Завершение работы программы." << endl;
				system("pause");
				continue;
			}
		}
		case '2':
		{
			try
			{
				ifstream fin("input.bin", ios_base::binary);

				int b;
				
				fin.read((char *)&b, sizeof(b));
				long long *arr = new long long[b];

				for (int i = 0; i < b; i++)
				{
					fin.read((char *)&arr[i], sizeof(arr[i]));
					//fin >> arr[i];
				}

				long long a = 0;
				long long val;
				fin.read((char *)&val, sizeof(val));
				//fin >> val;
				if (a == b - 1)
				{
					cout << "Индекс искомого элемента массива равен " << 0 << endl;
					delete[] arr;
					system("pause");
					return;
				}
				long long T0 = clock();
				int count = 0;
				//double T0 = clock();
				long long m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
				//cout << m << endl;
				count++;
				//cout << m << endl;
				while (b <= m)
					m--;
				while (a > m)
					m++;
				while (arr[m] != val)
				{
					//cout << m << endl;
					if (arr[m] < val)
					{
						if (a >= m)
						{
							m = ((a + b) / 2) + ((a + b) % 2);
							count++;
							while (arr[m] != val)
							{
								//cout << m << endl;
								if (arr[m] < val)
								{
									a = m;
									m = ((a + b) / 2) + ((a + b) % 2);
									count++;
								}
								else
								{
									b = m;
									m = ((a + b) / 2);
									count++;
								}
							}
							break;
						}
						else
						{
							a = m;
							m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
							count++;
						}
					}
					else
					{
						if (b <= m)
						{
							m = ((a + b) / 2) + ((a + b) % 2);
							count++;
							while (arr[m] != val)
							{
								//cout << m << endl;
								if (arr[m] < val)
								{
									a = m;
									m = ((a + b) / 2) + ((a + b) % 2);
									count++;
								}
								else
								{
									b = m;
									m = ((a + b) / 2);
									count++;
								}
							}
							break;
						}
						else
						{
							b = m;
							m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
							count++;
						}
					}
				}
				double T1 = clock();
				//cout << T1 - T0 << endl;
				cout << "Количество вычислений индекса искомого числа " << count << endl;
				//cout << (double) clock() - T0 << endl;
				cout << "Индекс искомого элемента массива равен " << m << endl;
				delete[] arr;
				system("pause");
				return;
			}
			catch (...)
			{
				cout << "Не удается найти файл, либо он поврежден. Завершение работы программы." << endl;
				system("pause");
				continue;
			}
		}
		case '3':
		{
			cout << "Введите количество элементов массива" << endl;
			int b;
			cin >> b;
			long long *arr = new long long[b];

			ofstream fout("output.bin", ios_base::binary);
			fout.write((char *)&b, sizeof(b));

			cout << "Введите элементы массива" << endl;
			for (int i = 0; i < b; i++)
			{
				cin >> arr[i];
				fout.write((char *)&arr[i], sizeof(arr[i]));
			}

			long long a = 0;
			long long val;
			cout << "Введите искомое значение" << endl;
			cin >> val;
			fout.write((char *)&val, sizeof(val));
			fout.close();
			
			if (a == b - 1)
			{
				cout << "Индекс искомого элемента массива равен " << 0 << endl;
				delete[] arr;
				system("pause");
				return;
			}
			int count = 0;
			double T0 = clock();
			long long m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
			//cout << m << endl;
			count++;
			//cout << m << endl;
			while (b <= m)
				m--;
			while (a > m)
				m++;
			while (arr[m] != val)
			{
				//cout << m << endl;
				if (arr[m] < val)
				{
					if (a >= m)
					{
						m = ((a + b) / 2) + ((a + b) % 2);
						count++;
						while (arr[m] != val)
						{
							//cout << m << endl;
							if (arr[m] < val)
							{
								a = m;
								m = ((a + b) / 2) + ((a + b) % 2);
								count++;
							}
							else
							{
								b = m;
								m = ((a + b) / 2);
								count++;
							}
						}
						break;
					}
					else
					{
						a = m;
						m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
						count++;
					}
				}
				else
				{
					if (b <= m)
					{
						m = ((a + b) / 2) + ((a + b) % 2);
						count++;
						while (arr[m] != val)
						{
							//cout << m << endl;
							if (arr[m] < val)
							{
								a = m;
								m = ((a + b) / 2) + ((a + b) % 2);
								count++;
							}
							else
							{
								b = m;
								m = ((a + b) / 2);
								count++;
							}
						}
						break;
					}
					else
					{
						b = m;
						m = (b - a)*(val - arr[a]) / (arr[b - 1] - arr[a]) + a;
						count++;
					}
				}
			}
			double T1 = clock();
			//cout << T1 - T0 << endl;
			cout << "Количество вычислений индекса искомого числа " << count << endl;
			//cout << (double) clock() - T0 << endl;
			cout << "Индекс искомого элемента массива равен " << m << endl;
			delete[] arr;
			system("pause");
			return;
		}
		default:
		{
			system("cls");
			cout << "Неправильный ввод. Повторите попытку." << endl;
			system("pause");
			continue;
		}
		}
	}
}

int main()
{
	while (true)
	{
		system("cls");
		setlocale(LC_ALL, "");
		cout << "0. Завершение работы программы."
			<< endl << "1. Создать текстовый файл для работы программы. (с линейно возрастающими элементами)"
			<< endl << "2. Создать бинарный файл для работы программы. (с линейно возрастающими элементами)"
			<< endl << "3. Оптимизированный двоичный поиск. (программа может принять данные с клавиатуры, введенные с клавиатуры данные будут\nзаписаны в output.bin)" << endl;
		char choice;
		cin >> choice;

		switch (choice)
		{
		case '0':
		{
			return 0;
			break;
		}
		case '1':
		{
			create_file();
			break;
		}
		case '2':
		{
			create_bin_file();
			break;
		}
		case '3':
		{
			binary_search();
			break;
		}
		default:
		{
			system("cls");
			cout << "Неправильный ввод. Повторите попытку." << endl;
			system("pause");
			continue;
		}
		}
	}
	
	return 0;
}