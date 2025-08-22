#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int dx[4] = { 0, 1, -1, 0 };
int dy[4] = { -1, 0, 0, 1 };

void rotate_clock(int x, int y, int cnt_rotation, vector<vector<int>>& clock_hands, bool is_counter)
{
	int size = clock_hands.size();

	if (x < 0 || y < 0 || x >= size || y >= size) return;

	clock_hands[y][x] = is_counter == false ? (clock_hands[y][x] + cnt_rotation) % 4 : (clock_hands[y][x] + 4 - cnt_rotation) % 4;

	for (int i = 0; i < 4; i++)
	{
		int tx = x + dx[i], ty = y + dy[i];

		if (tx < 0 || ty < 0 || tx >= size || ty >= size) continue;

		clock_hands[ty][tx] = is_counter == false ? (clock_hands[ty][tx] + cnt_rotation) % 4 : (clock_hands[ty][tx] + 4 - cnt_rotation) % 4;
	}
}

int solution(vector<vector<int>> clock_hands)
{
	int answer = -1, size = clock_hands.size();

	auto dfs = [&](int x, int y, int cnt_rotation, auto&& dfs_ref) -> void
	{
		if (y >= size)
		{
			for (int i = 0; i < size; i++)
			{
				if (clock_hands[size - 1][i] != 0) return;
			}

			answer = answer >= 0 ? min(answer, cnt_rotation) : cnt_rotation;

			return;
		}

		for (int i = 0; i < 4; i++)
		{
			rotate_clock(x, y, i, clock_hands, false);

			if (y - 1 >= 0 && clock_hands[y - 1][x] != 0)
			{
				rotate_clock(x, y, i, clock_hands, true);
				continue;
			}

			int tx = x + 1, ty = y;
			if (tx >= size)
			{
				tx = 0;
				ty += 1;
			}

			dfs_ref(tx, ty, cnt_rotation + i, dfs_ref);

			rotate_clock(x, y, i, clock_hands, true);
		}
	};

	dfs(0, 0, 0, dfs);

	return answer;
}

int main()
{
	vector<vector<int>> clock_hands
	{
		{ 0, 3, 3, 0 },
		{ 3, 2, 2, 3 },
		{ 0, 3, 2, 0 },
		{ 0, 3, 3, 3 }
	};

	cout << solution(clock_hands);
	
	return 0;
}