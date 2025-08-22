#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define MAX_SIZE 51

using namespace std;

int solution(vector<vector<int>> rectangles, int characterX, int characterY, int itemX, int itemY)
{
	int answer = 0;
	// 0 : up, 1 : right, 2 : down, 3 : left
	int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };
	// coordinates[y][x] = (x, y)
	// -1 : empty, 0 : inner, positive : edge or vertex
	vector<vector<int>> coordinates(MAX_SIZE, vector<int>(MAX_SIZE, -1));

	for (vector<int> rectangle : rectangles)
	{
		pair<int, int> bottom_left = { rectangle[0], rectangle[1] };
		pair<int, int> top_right = { rectangle[2], rectangle[3] };

		// Vertex
		if (coordinates[bottom_left.second][bottom_left.first] < 0)
		{
			coordinates[bottom_left.second][bottom_left.first] = 1 << UP | 1 << RIGHT;
		}
		if (coordinates[bottom_left.second][top_right.first] < 0)
		{
			coordinates[bottom_left.second][top_right.first] = 1 << UP | 1 << LEFT;
		}
		if (coordinates[top_right.second][bottom_left.first] < 0)
		{
			coordinates[top_right.second][bottom_left.first] = 1 << DOWN | 1 << RIGHT;
		}
		if (coordinates[top_right.second][top_right.first] < 0)
		{
			coordinates[top_right.second][top_right.first] = 1 << DOWN | 1 << LEFT;
		}

		// Horizontal-Edge
		bool is_inner_top = coordinates[top_right.second][bottom_left.first] == 0, is_inner_bottom = coordinates[bottom_left.second][bottom_left.first] == 0;
		for (int i = bottom_left.first + 1; i < top_right.first; i++)
		{
			// Top
			if (coordinates[top_right.second][i] < 0)
			{
				coordinates[top_right.second][i] = 1 << RIGHT | 1 << LEFT;
			}
			else if (coordinates[top_right.second][i] > 0)
			{
				is_inner_top = !is_inner_top;
				coordinates[top_right.second][i] = 1 << UP | 1 << (is_inner_top ? LEFT : RIGHT);
			}

			// Bottom
			if (coordinates[bottom_left.second][i] < 0)
			{
				coordinates[bottom_left.second][i] = 1 << RIGHT | 1 << LEFT;
			}
			else if (coordinates[bottom_left.second][i] > 0)
			{
				is_inner_bottom = !is_inner_bottom;
				coordinates[bottom_left.second][i] = 1 << DOWN | 1 << (is_inner_bottom ? LEFT : RIGHT);
			}
		}

		// Vertical-Edge
		bool is_inner_left = coordinates[bottom_left.second][bottom_left.first] == 0, is_inner_right = coordinates[bottom_left.second][top_right.first] == 0;
		for (int i = bottom_left.second + 1; i < top_right.second; i++)
		{
			// Left
			if (coordinates[i][bottom_left.first] < 0)
			{
				coordinates[i][bottom_left.first] = 1 << UP | 1 << DOWN;
			}
			else if (coordinates[i][bottom_left.first] > 0)
			{
				is_inner_left = !is_inner_left;
				coordinates[i][bottom_left.first] = 1 << LEFT | 1 << (is_inner_left ? DOWN : UP);
			}

			// Right
			if (coordinates[i][top_right.first] < 0)
			{
				coordinates[i][top_right.first] = 1 << UP | 1 << DOWN;
			}
			else if (coordinates[i][top_right.first] > 0)
			{
				is_inner_right = !is_inner_right;
				coordinates[i][top_right.first] = 1 << RIGHT | 1 << (is_inner_right ? DOWN : UP);
			}
		}

		// Inner
		for (int i = bottom_left.first + 1; i < top_right.first; i++)
		{
			for (int j = bottom_left.second + 1; j < top_right.second; j++)
			{
				coordinates[j][i] = 0;
			}
		}
	}

	queue<pair<int, pair<int, int>>> bfs;
	
	bfs.push({ 0, { characterX, characterY } });

	while (bfs.empty() != true)
	{
		auto front = bfs.front();
		bfs.pop();

		int depth = front.first;
		pair<int, int> node = front.second;

		if (node.first == itemX && node.second == itemY)
		{
			answer = depth;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int dir = 1 << i;

			if ((dir & coordinates[node.second][node.first]) == 0) continue;

			int tx = node.first + dx[i], ty = node.second + dy[i];

			if (coordinates[ty][tx] < 0) continue;

			bfs.push({ depth + 1, { tx, ty } });
		}

		coordinates[node.second][node.first] = -1;
	}

	return answer;
}

int main()
{
	/*
	// rectangels : [ bottom-left.x, bottom-left.y, top-right.x, top-right.y ]
	// range of coordinate : 1 ~ 50
	// Test case 1
	// Result = 17
	vector<vector<int>> rectangles =
	{
		{ 1, 1, 7, 4 },
		{ 3, 2, 5, 5 },
		{ 4, 3, 6, 9 },
		{ 2, 6, 8, 8 }
	};
	int characterX = 1, characterY = 3, itemX = 7, itemY = 8;
	*/

	/*
	// Test case 2
	// Result = 11
	vector<vector<int>> rectangles =
	{
		{ 1, 1, 8, 4 },
		{ 2, 2, 4, 9 },
		{ 3, 6, 9, 8 },
		{ 6, 3, 7, 7 }
	};
	int characterX = 9, characterY = 7, itemX = 6, itemY = 1;
	*/

	/*
	// Test case 3
	// Result = 9
	vector<vector<int>> rectangles =
	{
		{ 1, 1, 5, 7 }
	};
	int characterX = 1, characterY = 1, itemX = 4, itemY = 7;
	*/

	/*
	// Test case 4
	// Result = 15
	vector<vector<int>> rectangles =
	{
		{ 2, 1, 7, 5 },
		{ 6, 4, 10, 10 }
	};
	int characterX = 3, characterY = 1, itemX = 7, itemY = 10;
	*/

	// Test case 5
	// Result = 10
	vector<vector<int>> rectangles =
	{
		{ 2, 2, 5, 5 },
		{ 1, 3, 6, 4 },
		{ 3, 1, 4, 6 }
	};
	int characterX = 1, characterY = 4, itemX = 6, itemY = 3;

	cout << solution(rectangles, characterX, characterY, itemX, itemY) << endl;

	return 0;
}