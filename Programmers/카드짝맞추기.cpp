#include <iostream>
#include <map>
#include <set>
#include <vector>

#define SIZE 4

using namespace std;

int calculate_cnt(const vector<vector<int>>& board, int start_r, int start_c, int target_r, int target_c)
{
	int result = -1;
	int dir_r = start_r < target_r ? 1 : -1, dir_c = start_c < target_c ? 1 : -1;

	auto dfs = [&](int depth, int cur_r, int cur_c, auto&& dfs_ref) -> void
	{
		if (result >= 0 && depth >= result) return;

		if (cur_r == target_r && cur_c == target_c)
		{
			result = result >= 0 ? min(depth, result) : depth;
			return;
		}

		if (cur_r != target_r)
		{
			// row
			int tr = cur_r + dir_r;
			if (tr >= 0 && tr < SIZE)
			{
				dfs_ref(depth + 1, tr, cur_c, dfs_ref);
			}

			// ctrl + row
			int nr = cur_r;
			while (nr >= 0 && nr < SIZE)
			{
				int dr = nr + dir_r;

				if (dr < 0 || dr >= SIZE) break;
				
				nr = dr;
				
				if (board[nr][cur_c] != 0) break;
			}

			if (abs(nr - cur_r) > 1)
			{
				dfs_ref(depth + 1, nr, cur_c, dfs_ref);
			}
		}

		if (cur_c != target_c)
		{
			// column
			int tc = cur_c + dir_c;
			if (tc >= 0 && tc < SIZE)
			{
				dfs_ref(depth + 1, cur_r, tc, dfs_ref);
			}

			// ctrl + column
			int nc = cur_c;
			while (nc >= 0 && nc < SIZE)
			{
				int dc = nc + dir_c;

				if (dc < 0 || dc >= SIZE) break;

				nc = dc;

				if (board[cur_r][nc] != 0) break;
			}

			if (abs(nc - cur_c) > 1)
			{
				dfs_ref(depth + 1, cur_r, nc, dfs_ref);
			}
		}
	};

	dfs(0, start_r, start_c, dfs);

	return result;
}

int solution(vector<vector<int>> board, int r, int c)
{
	int answer = -1;

	// [r][c], [y][x]
	map<int, vector<pair<int, int>>> pair_pos;
	set<int> pairs;

	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (board[j][i] == 0) continue;

			if (pair_pos.find(board[j][i]) == pair_pos.end())
			{
				pair_pos.insert({ board[j][i], vector<pair<int, int>>() });
				pairs.insert(board[j][i]);
			}

			pair_pos[board[j][i]].push_back({ i, j });
		}
	}

	auto dfs = [&](int r, int c, int cnt, auto&& dfs_ref) -> void
	{
		if (answer >= 0 && answer <= cnt) return;
		if (pairs.size() == 0)
		{
			answer = answer >= 0 ? min(answer, cnt) : cnt;
			return;
		}

		for (pair<int, vector<pair<int, int>>> pos : pair_pos)
		{
			if (pairs.find(pos.first) == pairs.end()) continue;

			pairs.erase(pos.first);

			pair<int, int> f = pos.second[0];
			pair<int, int> s = pos.second[1];

			// first to second
			int needs = calculate_cnt(board, r, c, f.second, f.first) 
				+ calculate_cnt(board, f.second, f.first, s.second, s.first)
				+ 2;

			board[f.second][f.first] = 0;
			board[s.second][s.first] = 0;

			dfs_ref(s.second, s.first, cnt + needs, dfs_ref);

			board[f.second][f.first] = pos.first;
			board[s.second][s.first] = pos.first;

			// second to first
			needs = calculate_cnt(board, r, c, s.second, s.first)
				+ calculate_cnt(board, s.second, s.first, f.second, f.first)
				+ 2;

			board[f.second][f.first] = 0;
			board[s.second][s.first] = 0;

			dfs_ref(f.second, f.first, cnt + needs, dfs_ref);

			board[f.second][f.first] = pos.first;
			board[s.second][s.first] = pos.first;

			pairs.insert(pos.first);
		}
	};

	dfs(r, c, 0, dfs);

	return answer;
}

int main()
{
	// Test case 1
	// Result = 14
	vector<vector<int>> board =
	{
		{ 1, 0, 0, 3 },
		{ 2, 0, 0, 0 },
		{ 0, 0, 0, 2 },
		{ 3, 0, 1, 0 }
	};
	int r = 1, c = 0;

	/*
	// Test case 2
	// Result = 16
	vector<vector<int>> board =
	{
		{ 3, 0, 0, 2 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 2, 0, 0, 3 }
	};
	int r = 0, c = 1;
	*/

	cout << solution(board, r, c) << endl;

	return 0;
}