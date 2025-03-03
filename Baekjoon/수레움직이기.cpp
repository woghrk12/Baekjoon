#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> maze)
{
	int answer = 0;

	int dx[4] = { 0, 0, -1, 1 }, dy[4] = { -1, 1, 0, 0 };
	int width = maze[0].size(), height = maze.size();
	vector<vector<bool>> red_visited(height, vector<bool>(width, false));
	vector<vector<bool>> blue_visited(height, vector<bool>(width, false));
	pair<int, int> cur_red, cur_blue, target_red, target_blue;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			switch (maze[j][i])
			{
			case 1:
				cur_red = { i, j };
				continue;
			case 2:
				cur_blue = { i, j };
				continue;
			case 3 :
				target_red = { i, j };
				continue;
			case 4:
				target_blue = { i, j };
				continue;
			}
		}
	}

	red_visited[cur_red.second][cur_red.first] = true;
	blue_visited[cur_blue.second][cur_blue.first] = true;

	auto dfs = [&](int depth, pair<int, int> cur_red, pair<int, int> cur_blue, auto&& dfs_ref) -> void
	{
		// 이미 정답이 나왔을 경우 그 이상의 탐색은 무의미함
		if (answer > 0 && depth >= answer) return;

		// 모든 수레가 목표 지점에 도착한 경우
		if (cur_red == target_red && cur_blue == target_blue)
		{
			answer = depth;
			return;
		}

		set<pair<pair<int, int>, pair<int, int>>> candidates;

		// 빨간 수레가 목표 지점에 도착하여 고정된 경우
		if (cur_red == target_red)
		{
			for (int i = 0; i < 4; i++)
			{
				int tx = cur_blue.first + dx[i];
				int ty = cur_blue.second + dy[i];

				if (tx < 0 || ty < 0 || tx >= width || ty >= height) continue;
				if (maze[ty][tx] == 5 || blue_visited[ty][tx] == true) continue;
				if (tx == cur_red.first && ty == cur_red.second) continue;

				if (candidates.find({ { cur_red.first, cur_red.second }, { tx, ty } }) != candidates.end()) continue;

				candidates.insert({ { cur_red.first, cur_red.second }, { tx, ty } });
			}
		}
		// 파란 수레가 목표 지점에 도착하여 고정된 경우
		else if (cur_blue == target_blue)
		{
			for (int i = 0; i < 4; i++)
			{
				int tx = cur_red.first + dx[i];
				int ty = cur_red.second + dy[i];

				if (tx < 0 || ty < 0 || tx >= width || ty >= height) continue;
				if (maze[ty][tx] == 5 || red_visited[ty][tx] == true) continue;
				if (tx == cur_blue.first && ty == cur_blue.second) continue;

				if (candidates.find({ { tx, ty }, { cur_blue.first, cur_blue.second } }) != candidates.end()) continue;

				candidates.insert({ { tx, ty }, { cur_blue.first, cur_blue.second } });
			}
		}
		// 두 수레가 모두 목표 지점에 도착하지 않은 경우
		else
		{
			// 빨간 수레가 먼저 움직인 경우
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int red_tx = cur_red.first + dx[i], red_ty = cur_red.second + dy[i];

					if (red_tx < 0 || red_ty < 0 || red_tx >= width || red_ty >= height) continue;
					if (maze[red_ty][red_tx] == 5 || red_visited[red_ty][red_tx] == true) continue;
					if (red_tx == cur_blue.first && red_ty == cur_blue.second) continue;

					int blue_tx = cur_blue.first + dx[j], blue_ty = cur_blue.second + dy[j];
					
					if (blue_tx < 0 || blue_ty < 0 || blue_tx >= width || blue_ty >= height) continue;
					if (maze[blue_ty][blue_tx] == 5 || blue_visited[blue_ty][blue_tx] == true) continue;
					if (blue_tx == red_tx && blue_ty == red_ty) continue;

					if (candidates.find({ { red_tx, red_ty }, { blue_tx, blue_ty } }) != candidates.end()) continue;

					candidates.insert({ { red_tx, red_ty }, { blue_tx, blue_ty } });
				}
			}
			// 파란 수레가 먼저 움직인 경우
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int blue_tx = cur_blue.first + dx[i], blue_ty = cur_blue.second + dy[i];

					if (blue_tx < 0 || blue_ty < 0 || blue_tx >= width || blue_ty >= height) continue;
					if (maze[blue_ty][blue_tx] == 5 || blue_visited[blue_ty][blue_tx] == true) continue;
					if (blue_tx == cur_red.first && blue_ty == cur_red.second) continue;

					int red_tx = cur_red.first + dx[j], red_ty = cur_red.second + dy[j];

					if (red_tx < 0 || red_ty < 0 || red_tx >= width || red_ty >= height) continue;
					if (maze[red_ty][red_tx] == 5 || red_visited[red_ty][red_tx] == true) continue;
					if (red_tx == blue_tx && red_ty == blue_ty) continue;

					if (candidates.find({ { red_tx, red_ty }, { blue_tx, blue_ty } }) != candidates.end()) continue;

					candidates.insert({ { red_tx, red_ty }, { blue_tx, blue_ty } });
				}
			}
		}

		for (auto candidate : candidates)
		{
			pair<int, int> next_red = candidate.first;
			pair<int, int> next_blue = candidate.second;

			if (next_red != cur_red)
			{
				red_visited[next_red.second][next_red.first] = true;
			}
			if (next_blue != cur_blue)
			{
				blue_visited[next_blue.second][next_blue.first] = true;
			}

			dfs_ref(depth + 1, next_red, next_blue, dfs_ref);

			if (next_red != cur_red)
			{
				red_visited[next_red.second][next_red.first] = false;
			}
			if (next_blue != cur_blue)
			{
				blue_visited[next_blue.second][next_blue.first] = false;
			}
		}
	};

	dfs(0, cur_red, cur_blue, dfs);

	return answer;
}

int main()
{
	// Test case 1
	// Result = 3
	vector<vector<int>> maze = { { 1, 4 }, { 0, 0 }, { 2, 3 } };
	
	/*
	// Test case 2
	// Result = 7
	vector<vector<int>> maze = { { 1, 0, 2 }, { 0, 0, 0 }, { 5, 0, 5 }, { 4, 0, 3 } };
	*/

	/*
	// Test case 3
	// Result = 0
	vector<vector<int>> maze = { { 1, 5 }, { 2, 5 }, { 4, 5 }, { 3, 5 } };
	*/

	/*
	// Test case 4
	// Result = 0
	vector<vector<int>> maze = { { 4, 1, 2, 3 } };
	*/

	cout << solution(maze) << endl;

	return 0;
}