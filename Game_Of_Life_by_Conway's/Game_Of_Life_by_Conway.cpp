// Game_Of_Life_by_Conway's.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

const int N = 32;

void clearscreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
	cout << "\r";
}

class Life_Matrix {
public:
	unsigned int num_neigh;
	unsigned int Matrix[N][N];
	unsigned int Neigh[N][N];

	Life_Matrix()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Matrix[i][j] = 0;
	}

	Life_Matrix(int x, int y)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Matrix[i][j] = 0;
		Matrix[x][y] = 1;
	}

	void Find_Neighbours(int x, int y)
	{
		num_neigh = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				if (!(i == 0 && j == 0))
					if (Matrix[(x + i + N) % N][(y + j + N) % N] == 1)
						num_neigh++;
	}

	void Renew(Life_Matrix New)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				Matrix[i][j] = New.Matrix[i][j];
	}

	void Example()
	{
		Matrix[1][2] = 1;
		Matrix[1][3] = 1;
		Matrix[2][3] = 1;
		Matrix[3][3] = 1;
		Matrix[3][4] = 1;
		Matrix[3][5] = 1;
		Matrix[4][4] = 1;
		Matrix[4][5] = 1;
		Matrix[4][6] = 1;
	}

	void Matrix_Out()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				if (Matrix[i][j] == 1)
					cout << " * ";
				else
					cout << "   ";
			cout << endl;
		}
		Sleep(100);
	}

	bool Equal(Life_Matrix Oldest)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (Matrix[i][j] != Oldest.Matrix[i][j])
					return false;
		return true;
	}

	bool Check_Zero()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (Matrix[i][j] == 1)
					return false;
		return true;
	}

};

bool Next_Step(Life_Matrix* Old, Life_Matrix* New, Life_Matrix* Oldest)
{
	int num;
	bool f = false;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			(*Old).Find_Neighbours(i, j);
			num = (*Old).num_neigh;
			if ((*Old).Matrix[i][j] == 0)
			{
				if (num == 3)
					(*New).Matrix[i][j] = 1;
				goto cont;
			}
			(*New).Matrix[i][j] = (*Old).Matrix[i][j];
			if (num < 2 || num > 3)
				(*New).Matrix[i][j] = 0;
		cont:
			if ((*New).Matrix[i][j] != (*Old).Matrix[i][j])
				f = true;
		}

	if (f && !(*New).Check_Zero())
	{
		if ((*New).Equal(*Oldest))
		{
			cout << "System repeats it's configuration once in two turns" << endl;
			(*New).Matrix_Out();
			Sleep(1000);
			return true;
		}

		(*Oldest).Renew(*Old);
		(*Old).Renew(*New);
		(*Old).Matrix_Out();
		return false;
	}
	else
	{
		cout << "System reached stable situation" << endl;
		(*New).Matrix_Out();
		Sleep(1000);
		return true;
	}
}

int main()
{
	try_again:

	cout << "Start the game? (y/n)" << endl;
	char c;
	cin >> c; 
	cout << endl;
	
	if (c != 'y')
		return 0;
	else
	{
		Life_Matrix Life = Life_Matrix();
		Life_Matrix New = Life_Matrix();
		Life_Matrix Oldest = Life_Matrix();
		cout << "Enter the start positions (position (0, 0) must be the end): " << endl;
		unsigned int a, b;
		cin >> a;
		cin >> b;
		bool f = (a == 0), g = (b == 0);

		while (a != 0 && b != 0)
		{
			if (f || g)
			{
				cout << "Wrong position; try again" << endl;
				goto try_again;
			}
			Life.Matrix[a - 1][b - 1] = 1;
			cout << "Enter position:" << endl;
			cin >> a;
			cin >> b;
			f = (a == 0);
			g = (b == 0);
		}
		
		char t = 'y';

		bool h = false;

		Life.Matrix_Out();

		while (t != 's' && t != 'n')
		{
		contin:

			if (Next_Step(&Life, &New, &Oldest))
				goto endgame;
			
			clearscreen();

			if (!h && Life.Check_Zero())
			{
				cout << "No life left on field, better luck next time" << endl;
			endgame:
				cout << "Do you want to continue? (y/n)" << endl;
				cin >> t;
				if (t != 'n')
				{
					h = true;
					goto contin;
				}
				cout << "Game over" << endl;
				return 0;
			}
		}
	}

	return 0;
}