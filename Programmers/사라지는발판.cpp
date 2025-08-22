#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc)
{
	int width = board[0].size(), height = board.size();
	// loc[0] = y, loc[1] = x
	// board[y][x] = (x, y)
	
	// DFS를 통한 Minimax tree 탐색
	auto dfs = [&](vector<int> player_loc, vector<int> other_loc, auto&& dfs_ref)->int
	{
		if (board[player_loc[0]][player_loc[1]] == 0) return 0;

		int ret = 0;

		for (int i = 0; i < 4; i++)
		{
			int tx = player_loc[1] + dx[i];
			int ty = player_loc[0] + dy[i];

			if (tx < 0 || ty < 0 || tx >= width || ty >= height || board[ty][tx] == 0) continue;

			board[player_loc[0]][player_loc[1]] = 0;

			int val = dfs_ref(other_loc, { ty, tx }, dfs_ref) + 1;

			board[player_loc[0]][player_loc[1]] = 1;

			// 해당 턴의 플레이어가 이기는 케이스가 존재할 경우 최솟값을 반환
			// 해당 턴의 플레이어가 이기는 케이스가 존재하지 않을 경우 최댓값을 반환
			if (ret % 2 == 0 && val % 2 == 1) ret = val;
			else if (ret % 2 == 0 && val % 2 == 0) ret = max(ret, val);
			else if (ret % 2 == 1 && val % 2 == 1) ret = min(ret, val);
		}

		return ret;
	};

	return dfs(aloc, bloc, dfs);
}

int main()
{
	vector<vector<int>> board =
	{
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};

	vector<int> aloc = { 1, 0 }, bloc = { 1, 2 };

	cout << solution(board, aloc, bloc);

	return 0;
}