#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

using namespace std;

enum typeWay { WALL, PATH };

struct cell
{
	cell()
	{
		visited = false;
	}

	bool visited;
	typeWay type;
};

struct step
{
	int x, y;
};

void filter(vector<step> *steps, cell **board, int sizeTable)
{
	for (unsigned int i = 0; i < (*steps).size(); i++)
	{
		if ((*steps)[i].x < 0 ||
			(*steps)[i].x >= sizeTable ||
			(*steps)[i].y < 0 ||
			(*steps)[i].y >= sizeTable ||
			board[(*steps)[i].x][(*steps)[i].y].visited == true
			)
		{
			(*steps).erase((*steps).begin() + i);
			i--;
		}
	}
}


step getStep(step s, cell **board, int sizeTable)
{
	vector<step> steps;
	step chooseStep;

	steps.push_back({ s.x, s.y + 2 });
	steps.push_back({ s.x, s.y - 2 });
	steps.push_back({ s.x + 2, s.y });
	steps.push_back({ s.x - 2, s.y });

	filter(&steps, board, sizeTable);
	if (steps.size() > 0)
	{
		chooseStep = steps[rand() % steps.size()];
		return chooseStep;
	}

	chooseStep = { 0,0 };
	return chooseStep;
}


cell ** createBoard(int n)
{
	cell **board = new cell *[n];
	for (int i = 0; i < n; i++)
		board[i] = new cell[n];
	return board;
}

void fillBoard(cell **board, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i % 2 == 0 || j % 2 == 0)
			{
				board[i][j].type = WALL;
			}
		}
	}
}

void printBoard(cell **board, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].type == WALL && board[i][j].visited == false)
			{
				printf("%c", 219);
			}
			else if (board[i][j].visited == true)
			{
				printf("%c", ' ');
			}
			else
			{
				printf("%c", 176);
			}
		}
		printf("\n");
	}
}

void crashWall(step a, step b, cell **board, int n)
{
	int z = 0;
	if (a.x == b.x)
	{
		z = a.y - b.y;
		if (z < 0)
		{
			board[a.x][a.y + 1].visited = true;
		}
		else
		{
			board[a.x][a.y - 1].visited = true;
		}
	}
	else if (a.y == b.y)
	{
		z = a.x - b.x;
		if (z < 0)
		{
			board[a.x + 1][a.y].visited = true;
		}
		else
		{
			board[a.x - 1][a.y].visited = true;
		}
	}
}

void generateLabirint(cell **board, int n)
{
	vector<step> steps;
	step doStep = { 1,1 };
	steps.push_back(doStep);

	while (steps.size() > 0)
	{
		doStep = getStep(steps.back(), board, n);
		if (doStep.x == 0) {
			steps.erase(steps.begin() + steps.size() - 1);
			continue;
		}
		crashWall(doStep, steps.back(), board, n);
		steps.push_back(doStep);
		board[steps.back().x][steps.back().y].visited = true;
	}
}

int main() {

	srand(time(NULL));
	int n = 50;

	int realN = n * 2 + 1;
	cell **board = createBoard(realN);

	fillBoard(board, realN);
	generateLabirint(board, realN);
	printBoard(board, realN);

	for (int i = 0; i < realN; i++)
		delete(board[i]);
	delete board;


	cin.get();
	return 0;
}