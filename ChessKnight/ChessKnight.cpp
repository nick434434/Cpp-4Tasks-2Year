// ChessKnight.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define N 8

void Make_Zero(int Pos_Matrix[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			Pos_Matrix[i][j] = 0;
		}
}

void Print_Matrix(int Pos_Matrix[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			cout << setw(7) << left << Pos_Matrix[i][j];
			if (j == N - 1)
				cout << endl;
		}
}

bool Shift_Counted(int i, int j, int sh1, int sh2)
{
	return (i + sh1 >= 0) && (i + sh1 < N) && (j + sh2 >= 0) && (j + sh2 < N);
}

int shift_x[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
int shift_y[] = { 2, -2, 2, -2, 1, -1, 1, -1 };

void Fill_Probabilities_Matrix(int Pos_Matrix[N][N])
{
	Make_Zero(Pos_Matrix);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < 8; k++)
			{
				if (Shift_Counted(i, j, shift_x[k], shift_y[k]))
					Pos_Matrix[i][j] += 1;
			}
}

int main()
{
	int Pos_Matrix[N][N], Prob_Matrix[N][N];
	
	//обработка исходной позиции коня
	int start_x, start_y;	
	
	cout << "Enter knight position" << endl;
	
	char ch, chess[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	cin >> ch;
	
	for (int i = 0; i < N; i++)
		if (chess[i] == ch)
			start_y = i;
	
	cin >> start_x; start_x = N - start_x;	
	//конец обработки
	
	//задание матриц
	Make_Zero(Pos_Matrix);
	Pos_Matrix[start_x][start_y] = 1;
	
	Make_Zero(Prob_Matrix);
	Fill_Probabilities_Matrix(Prob_Matrix);
	//конец задания матриц

	//алгоритм прозода шахм. доски, параллельно вывод последовательных ходов
	cout << chess[start_y] << N - start_x;
	
	int pos_x = start_x, pos_y = start_y;
	int Res_Matrix[N][N];
	
	Make_Zero(Res_Matrix);
	
	for (int i = 1; i < N*N; i++)
	{
		int pos_x_min = -1, pos_y_min = -1, min = N + 1;
		
		for (int j = 0; j < 8; j++)
		{
			int pos_x_t, pos_y_t;
			if (Shift_Counted(pos_x, pos_y, shift_x[j], shift_y[j]))
			{
				pos_x_t = pos_x + shift_x[j];
				pos_y_t = pos_y + shift_y[j];

				Prob_Matrix[pos_x_t][pos_y_t] = Prob_Matrix[pos_x_t][pos_y_t] - 1;

				if ((min > Prob_Matrix[pos_x_t][pos_y_t])
					&&(Pos_Matrix[pos_x_t][pos_y_t] == 0))
				{
					pos_x_min = pos_x_t;
					pos_y_min = pos_y_t;
					min = Prob_Matrix[pos_x_min][pos_y_min];
				}
			}
		}
		pos_x = pos_x_min;
		pos_y = pos_y_min;
		Pos_Matrix[pos_x][pos_y] = 1;
		Res_Matrix[pos_x][pos_y] = i;
		
		cout << " -> " << chess[pos_y] << N - pos_x;
	}
	cout << endl;
	//конец алгоритма

	Print_Matrix(Res_Matrix);

    return 0;
}