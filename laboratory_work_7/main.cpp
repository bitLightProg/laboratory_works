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
				cout << "������� ���������� �����." << endl;
				cin >> count;
				if (count <= 0)
				{
					throw 1;
				}
				cout << "������� �������� ����������� �����. (�� ������� ����������� ����� ����� ���������� �� �����������)\n"
					<< "(������: 5-100, 666-6666). ����� ������ ���� ������ 0. ���� ������ ����� ����� ������ �������, �� ��� ���������� �������" << endl;

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
				cout << "�������� ����� ���������." << endl;
				system("pause");
				return;

			}
			catch (...)
			{
				system("cls");
				cout << "������������ ����. ��������� �������." << endl;
				system("pause");
				continue;
			}
		}
	}
	catch (...)
	{
		cout << "�� ������� ������� ����. ���������� ������ ���������." << endl;
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
				cout << "������� ���������� �����." << endl;
				cin >> count;
				if (count <= 0)
				{
					throw 1;
				}
				cout << "������� �������� ����������� �����. (�� ������� ����������� ����� ����� ���������� �� �����������)\n"
					<< "(������: 5-100, 666-6666). ����� ������ ���� ������ 0. ���� ������ ����� ����� ������ �������, �� ��� ���������� �������" << endl;

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
				cout << "�������� ����� ���������." << endl;
				system("pause");
				return;

			}
			catch (...)
			{
				system("cls");
				cout << "������������ ����. ��������� �������." << endl;
				system("pause");
				continue;
			}
			
		}
	}
	catch (...)
	{
		cout << "�� ������� ������� ����. ���������� ������ ���������." << endl;
		system("pause");
	}

}


void binary_search()
{
	while (true)
	{
		system("cls");
		srand(time(NULL));
		cout << "1. ������������ ��������� ����.(input.txt)"
			<< endl << "2. ������������ �������� ����. (input.bin)"
			<< endl << "3. ������ ������ � ����������." << endl;
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
					cout << "������ �������� �������� ������� ����� "<< 0 << endl;
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
				cout << "���������� ���������� ������� �������� ����� "<< count << endl;
				//cout << (double) clock() - T0 << endl;
				cout << "������ �������� �������� ������� ����� " << m << endl;
				delete[] arr;
				system("pause");
				return;
			}
			catch (...)
			{
				cout << "�� ������� ����� ����, ���� �� ���������. ���������� ������ ���������." << endl;
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
					cout << "������ �������� �������� ������� ����� " << 0 << endl;
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
				cout << "���������� ���������� ������� �������� ����� " << count << endl;
				//cout << (double) clock() - T0 << endl;
				cout << "������ �������� �������� ������� ����� " << m << endl;
				delete[] arr;
				system("pause");
				return;
			}
			catch (...)
			{
				cout << "�� ������� ����� ����, ���� �� ���������. ���������� ������ ���������." << endl;
				system("pause");
				continue;
			}
		}
		case '3':
		{
			cout << "������� ���������� ��������� �������" << endl;
			int b;
			cin >> b;
			long long *arr = new long long[b];

			ofstream fout("output.bin", ios_base::binary);
			fout.write((char *)&b, sizeof(b));

			cout << "������� �������� �������" << endl;
			for (int i = 0; i < b; i++)
			{
				cin >> arr[i];
				fout.write((char *)&arr[i], sizeof(arr[i]));
			}

			long long a = 0;
			long long val;
			cout << "������� ������� ��������" << endl;
			cin >> val;
			fout.write((char *)&val, sizeof(val));
			fout.close();
			
			if (a == b - 1)
			{
				cout << "������ �������� �������� ������� ����� " << 0 << endl;
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
			cout << "���������� ���������� ������� �������� ����� " << count << endl;
			//cout << (double) clock() - T0 << endl;
			cout << "������ �������� �������� ������� ����� " << m << endl;
			delete[] arr;
			system("pause");
			return;
		}
		default:
		{
			system("cls");
			cout << "������������ ����. ��������� �������." << endl;
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
		cout << "0. ���������� ������ ���������."
			<< endl << "1. ������� ��������� ���� ��� ������ ���������. (� ������� ������������� ����������)"
			<< endl << "2. ������� �������� ���� ��� ������ ���������. (� ������� ������������� ����������)"
			<< endl << "3. ���������������� �������� �����. (��������� ����� ������� ������ � ����������, ��������� � ���������� ������ �����\n�������� � output.bin)" << endl;
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
			cout << "������������ ����. ��������� �������." << endl;
			system("pause");
			continue;
		}
		}
	}
	
	return 0;
}