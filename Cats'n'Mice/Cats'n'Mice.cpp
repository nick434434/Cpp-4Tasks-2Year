// Cats'n'Mice.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
#include <vector>

class vertex
{
public:
	int x;
	int y;

	vertex() {
		x = 0;
		y = 0;
	}

	vertex(int a, int b) {
		x = a;
		y = b;
	}

	friend vertex operator+(vertex &a, vertex &b) {
		return vertex(a.x + b.x, a.y + b.y);
	}
};

vertex Next_Step(vertex s) {
	int dist[8][8];
	for (auto i : dist)
		i = 0;

	bool used[8][8];
	for (auto i : used)
		i = false;

	vertex pred[8][8], shift[4];
	std::queue<vertex> q;

	q.push(s);
	used[s.x][s.y] = true;
	dist[s.x][s.y] = 0;

	while ( !q.empty() ) {
		
		vertex v = q.front();
		q.pop();
		
		for (auto i : shift) {
			vertex u = v + i;
			
			if (used[u.x][u.y])
				continue;
			
			dist[u.x][u.y] = dist[v.x][v.y] + 1;
			used[u.x][u.y] = true;
			pred[u.x][u.y] = v;
			
			q.push(u);
		}
		v = q.front();
		if (v == f1 || v == f2 || v == f3 || v == f4)
			break;
	}

	return q.front();

}

int main()
{
    return 0;
}