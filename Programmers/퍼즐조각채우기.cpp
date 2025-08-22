#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int dx[4] = { 0, 1, 0, -1 }, dy[4] = { -1, 0, 1, 0 };
int rx[4] = { 1, 1, -1, -1 }, ry[4] = { 1, -1, -1, 1 };

set<pair<int, int>> find_shape(pair<int, int> start, vector<vector<int>>& board, int target_num)
{
	int width = board[0].size(), height = board.size();

	pair<int, int> pivot = start;
	set<pair<int, int>> points;
	queue<pair<int, int>> bfs;

	points.insert(start);
	bfs.push(start);

	board[start.second][start.first] = target_num ^ 1;

	while (bfs.empty() != true)
	{
		pair<int, int> front = bfs.front();
		bfs.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int tx = front.first + dx[dir], ty = front.second + dy[dir];

			if (tx < 0 || ty < 0 || tx >= width || ty >= height || board[ty][tx] == (target_num ^ 1)) continue;

			points.insert({ tx, ty });
			bfs.push({ tx, ty });

			pivot = { min(tx, pivot.first), min(ty, pivot.second) };

			board[ty][tx] = target_num ^ 1;
		}
	}

	set<pair<int, int>> result;
	for (pair<int, int> point : points)
	{
		result.insert({ point.first - pivot.first, point.second - pivot.second });
	}

	return result;
}

bool is_same_shape(const set<pair<int, int>>& a, const set<pair<int, int>>& b)
{
	for (int i = 0; i < 4; i++)
	{
		set<pair<int, int>> rotated;
		pair<int, int> pivot = { 50, 50 };
		
		// Rotate the shape
		for (pair<int, int> point : a)
		{
			if (i % 2 == 0)
			{
				point = { point.first * rx[i], point.second * ry[i] };
			}
			else
			{
				point = { point.second * rx[i], point.first * ry[i] };
			}

			pivot = { min(pivot.first, point.first), min(pivot.second, point.second) };
			rotated.insert(point);
		}

		set<pair<int, int>> result;
		for (pair<int, int> point : rotated)
		{
			result.insert({ point.first - pivot.first, point.second - pivot.second });
		}

		// Compare the shape
		bool is_same = true;
		for (pair<int, int> point : result)
		{
			if (b.find(point) != b.end()) continue;

			is_same = false;
			break;
		}

		if (is_same == true) return true;
	}

	return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table)
{
	int answer = 0;
	int width = table[0].size(), height = table.size();

	// Key : 조각의 크기, Value : 해당 크기의 조각들
	map<int, queue<set<pair<int, int>>>> pieces;

	// table에 존재하는 조각들 찾기
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (table[j][i] == 0) continue;

			set<pair<int, int>> piece = find_shape({ i, j }, table, 1);
			int size = piece.size();

			if (pieces.find(size) == pieces.end())
			{
				pieces.insert({ size, queue<set<pair<int, int>>>() });
			}

			pieces[size].push(piece);
		}
	}

	// game_board에서 맞는 조각 찾기
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (game_board[j][i] == 1) continue;

			set<pair<int, int>> target = find_shape({ i, j }, game_board, 0);
			int size = target.size();

			if (pieces.find(size) == pieces.end()) continue;

			int length = pieces[size].size();
			for (int index = 0; index < length; index++)
			{
				auto front = pieces[size].front();
				pieces[size].pop();

				if (is_same_shape(target, front) == false)
				{
					pieces[size].push(front);
					continue;
				}

				answer += size;
				break;
			}
		}
	}

	return answer;
}

int main()
{
	/*
	// Test case 1
	// Result = 14
	vector<vector<int>> game_board =
	{
		{ 1, 1, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 0, 0 }
	};
	vector<vector<int>> table =
	{
		{ 1, 0, 0, 1, 1, 0 },
		{ 1, 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 0, 1, 1 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0 }
	};
	*/

	// Test case 2
	// Result = 0
	vector<vector<int>> game_board =
	{
		{ 0, 0, 0 },
		{ 1, 1, 0 },
		{ 1, 1, 1 }
	};
	vector<vector<int>> table =
	{
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 0, 0, 0 }
	};

	cout << solution(game_board, table) << endl;

	return 0;
}