// Bulls'n'Cows.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

const unsigned int N = 4;

void Show_Num(int n[N])
{
	for (int i = 0; i < N; i++)
		cout << n[i];
	cout << endl;
}

void Make_Intro(int arr[N])
{
	for (int i = 0; i < N; i++)
		arr[i] = -1;
}

void Transfer_Into_Arr(int a, int b[N])
{
	for (int i = 0; i < N; i++)
		b[i] = a / (int)pow(10, N - i - 1) % 10;
}

int turns;

void Check_Bulls_Cows(int n[N], int tmp[N], int ar_c[N], int ar_b[N], int n_c, int n_b)
{
	for (int j = 0; j < N; j++)
	{
		//ищем цифру в загаданном числе
		for (int k = 0; k < N; k++)

			if (n[j] == tmp[k])
			{
				if (j == k) //нашли быка
				{
				not_cow:

					ar_b[k] = tmp[k];
					n_b += 1;
				}
				else //нашли корову
					if (n[k] == tmp[k])
						goto not_cow;
					else
					{
						ar_c[k] = tmp[k];
						n_c += 1;
					}
				tmp[k] = -1; //учитываем что эта цифра уже бык или корова
			}
	}

	turns++;
}

void Find_Num(int n[N])
{
	int tmp_num[N], num_bul, num_cow, num[N], arr_bul[N], arr_cow[N];
	turns = 0;

	Make_Intro(arr_bul);
	Make_Intro(arr_cow);
	num_bul = 0;

	for (int i = 0; num_bul != N; i++)
	{
		num_bul = (num_cow = 0);
		Make_Intro(num);


		for (int j = 0; j < N; j++)
		{	
			if (arr_bul[j] > -1)
			{
				num[j] = arr_bul[j];	//заполнение быками
				arr_bul[j] = -1;
				continue;
			}

			if (arr_cow[j] > -1)
			{
				num[j] = arr_cow[j];	//заполнение коровами
				arr_cow[j] = -1;
				continue;
			}

			num[j] = i;
		}	
		
		continue_check:

		//инициализация рабочего числа
		for (int l = 0; l < N; l++)
			tmp_num[l] = n[l];

		// num, tmp_num, arr_cow, arr_bul, num_cow, num_bul

		//пробегаем по всем цифрам нашего хода
		for (int j = 0; j < N; j++)
		{
			//ищем цифру в загаданном числе
			for (int k = 0; k < N; k++)
				
				if (num[j] == tmp_num[k])
				{
					if (j == k) //нашли быка
					{
						not_cow:
						
						arr_bul[k] = tmp_num[k];
						num_bul += 1;
					}
					else //нашли корову
						if (num[k] == tmp_num[k])
							goto not_cow;
						else
						{
							arr_cow[k] = tmp_num[k];
							num_cow += 1;
						}
					tmp_num[k] = -1; //учитываем что эта цифра уже бык или корова
				}
		}

		
		turns++;

	/*	cout << "Number of bulls: " << num_bul << endl << "Number of cows: " << num_cow << endl;
		
		cout << "Bulls:";
		Show_Num(arr_bul);
		cout << "Cows:";
		Show_Num(arr_cow);

		cout << "Comp's turn: ";
		Show_Num(num);
	*/

		if (num_cow == 0)
			continue;
		else
			if (num_bul == 0)
			{
				if (num_cow == 4)
				{
					for (int k = 0; k < N; k++)
					{
						int tmp;
						if (k < N - 1)
						{
							tmp = arr_cow[k + 1];
							arr_cow[k + 1] = arr_cow[k];
							arr_cow[k] = tmp;
						}
						else
						{
							tmp = arr_cow[0];
							arr_cow[0] = arr_cow[k];
							arr_cow[k] = tmp;
						}
					}
					goto continue_check;
				}
				else
					for (int k = 0; k < N; k++)
						if (arr_cow[k] > -1)
						{
							int tmp;
							if (k < N - 1)
							{
								tmp = arr_cow[k + 1];
								arr_cow[k + 1] = arr_cow[k];
								arr_cow[k] = tmp;
							}
							else
							{
								tmp = arr_cow[0];
								arr_cow[0] = arr_cow[k];
								arr_cow[k] = tmp;
							}
						}
			}
			else
			{
				int pos_1, pos_2;
				pos_1 = (pos_2 = -1);

				for (int k = 0; k < N; k++)
					if (arr_bul[k] == -1)
						if (pos_1 == -1)
							pos_1 = k;
						else
						{
							pos_2 = k;
							break;
						}

				int tmp;
				tmp = arr_cow[pos_1];
				arr_cow[pos_1] = arr_cow[pos_2];
				arr_cow[pos_2] = tmp;
			}


	}

	//cout << endl << endl << endl << endl << endl << endl << "Number is: ";
	//Show_Num(num);	
	//cout << "Number of turns: " << turns << endl;	
}

int main()
{
	
	char c;
	cout << "Start the game?" << endl;
	cin >> c;
	if (c == 'n')
		return 0;
	if (c == 'm')
	{
		vector<int> turn;

		double begin = clock() / 1000.0;

		int num_it = 0;

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				for (int k = 0; k < 10; k++)
					for (int l = 0; l < 10; l++)
					{
						int num[N];
						num[0] = i;
						num[1] = j;
						num[2] = k;
						num[3] = l;
						
						Find_Num(num);
						num_it++;
						turn.push_back(turns);

					}

		double sum_turns = 0;
		int num_turns = turn.size();
		for (int i = num_turns - 1; i >= 0; i--)
		{
			int a;
			sum_turns = sum_turns + turn[i];
			turn.pop_back();
		}

		sum_turns = sum_turns / num_turns;

		cout << "General time: " << clock() / 1000.0 - begin << "sec." << endl;

		cout << endl << endl << endl << "Average number of turns: " << endl << sum_turns << endl;

		cout << "Number of games: " << num_it << endl;

		return 0;
	}
	else
	{
		vector<int> turn;

		for (; c != 'n'; )
		{
			cout << "Write your number: ";
			int num;
			cin >> num;

			int n[N];
			Transfer_Into_Arr(num, n);

			Find_Num(n);
			turn.push_back(turns);

			cout << "Continue? (y/n)" << endl;
			cin >> c;
		}

		double sum_turns = 0;
		int num_turns = turn.size();
		for (int i = num_turns - 1; i >= 0; i--)
		{
			int a;
			sum_turns = sum_turns + turn[i];
			turn.pop_back();
		}

		sum_turns = sum_turns / num_turns;

		cout << endl << endl << endl << "Average number of turns: " << endl << sum_turns << endl;

		return 0;
	}
}