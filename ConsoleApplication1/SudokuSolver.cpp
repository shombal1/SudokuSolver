
#include <iostream>
#include <list>
#include <vector>
#include <stack>


using namespace std;

struct  MyPoint
{
	int y = 0; int x = 0;
};

stack<pair<MyPoint, int>> lastPoint;
vector<bool > FindVector;

MyPoint FindAdd(vector<vector<char>>& graf,MyPoint &point)
{
	for (int q = 0; q < graf.size(); q++)
	{
		for (int w = 0; w < graf[q].size(); w++)
		{
			if (graf[q][w] == '.')
			{
				point.y = q;
				point.x = w;
				return point;
			}
		}
	}
	point.y = -1;
	point.x = -1;
	return point;

}
void CreateFindVector(MyPoint &point, vector<bool>& ar, vector<vector<char>>& graf)
{
	for (int q = 0; q < graf.size(); q++)
	{
		ar[(abs)(graf[q][point.x])] = true;
	}
	for (int q = 0; q < graf[0].size(); q++)
	{
		ar[(abs)(graf[point.y][q])] = true;
	}
	MyPoint a;
	int Xsize = (sqrt)(graf[0].size());
	int Ysize = (sqrt)(graf.size());
	a.y = (point.y / Ysize) * Ysize;
	a.x = (point.x / Xsize) * Xsize;
	for (int q = a.y; q < a.y + Ysize; q++)
	{
		for (int w = a.x; w < a.x + Xsize; w++)
		{
			ar[(abs)(graf[q][w])] = true;
		}
	}
}

void SetSoduca(vector<vector<char>>& graf, int value = 0)
{
	MyPoint point;
	FindAdd(graf, point);
	if (point.x == -1)
	{
		return;
	}
	fill(FindVector.begin()+='0',FindVector.end(), false);
	CreateFindVector(point, FindVector, graf);
	for (int q = 1 + value; q < graf.size() + 1; q++)
	{
		if (!FindVector[q+'0'])
		{
			lastPoint.push({ point,q });
			graf[point.y][point.x] = (char)(q + '0');
			SetSoduca(graf);
			return;
		}
	}
	graf[lastPoint.top().first.y][lastPoint.top().first.x] = '.';
	int a = lastPoint.top().second;
	lastPoint.pop();
	SetSoduca(graf, a);
}

int main()
{
	vector<vector<char>> graf(
		{
			{'5','3','.','.','7','.','.','.','.'},
			{'6','.','.','1','9','5','.','.','.'},
			{'.','9','8','.','.','.','.','6','.'},
			{'8','.','.','.','6','.','.','.','3'},
			{'4','.','.','8','.','3','.','.','1'},
			{'7','.','.','.','2','.','.','.','6'},
			{'.','6','.','.','.','.','2','8','.'},
			{'.','.','.','4','1','9','.','.','5'},
			{'.','.','.','.','8','.','.','7','9'}
		});
	int y = clock();
	FindVector.resize(graf.size()+'1');

	SetSoduca(graf);
	cout << "time work = " << clock() - y << "\n";
	for (int q = 0; q < graf.size(); q++)
	{
		for (int w = 0; w < graf[q].size(); w++)
		{
			cout << graf[q][w] << " ";
		}
		cout << "\n";
	}
}