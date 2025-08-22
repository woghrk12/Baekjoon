#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k)
{
	int dx[4] = { 1, 0, 0, -1 };
	int dy[4] = { 0, -1, 1, 0 };
	string dir[4] = { "d", "l", "r", "u" };

	string answer = "";
	vector<string> path;

	int dist = abs(x - r) + abs(y - c);
	if (dist > k || (k - dist) % 2 == 1) return "impossible";

	bool is_find_path = false;
	auto dfs = [&](vector<string> path, int cur_x, int cur_y, auto&& dfs_ref)
	{
		if (is_find_path == true) return;

		if (cur_x == r && cur_y == c && path.size() == k)
		{
			is_find_path = true;
			for (string d : path)
			{
				answer += d;
			}

			return;
		}

		int dist = abs(cur_x - r) + abs(cur_y - c);
		if (dist > k - path.size()) return;

		for (int i = 0; i < 4; i++)
		{
			int tx = cur_x + dx[i], ty = cur_y + dy[i];
			if (tx < 1 || ty < 1 || tx > n || ty > m) continue;

			path.push_back(dir[i]);
			dfs_ref(path, tx, ty, dfs_ref);
			path.pop_back();
		}
	};

	dfs(path, x, y, dfs);

	return answer;
}

int main()
{
	int n, m, x, y, r, c, k;

	cin >> n >> m >> x >> y >> r >> c >> k;

	cout << solution(n, m, x, y, r, c, k);

	return 0;
}