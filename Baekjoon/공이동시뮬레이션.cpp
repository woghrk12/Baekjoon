#include <iostream>
#include <vector>

using namespace std;

bool check_collision(int dir, int n, int m, pair<int, int> bottom_left, pair<int, int> top_right)
{
	switch (dir)
	{
		case 0:
			return bottom_left.second == 0;
		case 1:
			return top_right.second == m - 1;
		case 2:
			return bottom_left.first == 0;
		case 3:
			return top_right.first == n - 1;
	}
}

long long solution(int n, int m, int x, int y, vector<vector<int>> queries)
{
	// n : 행, m : 열, [n][m]
	// query(dx, dy) : { 0, 0, -1, 1 }, { -1, 1, 0, 0 }
	// query[0] : 열 번호가 감소하는 방향
	// query[1] : 열 번호가 증가하는 방향
	// query[2] : 행 번호가 감소하는 방향
	// query[3] : 행 번호가 증가하는 방향
	// x행 y열 [x][y]
	// bottom_left : 행과 열 번호가 작은 쪽 모서리, top_right : 행과 열 번호가 큰 쪽 모서리
	int inv_dx[4] = { 0, 0, 1, -1 }, inv_dy[4] = { 1, -1, 0, 0 };
	pair<int, int> bottom_left = { x, y }, top_right = { x, y };

	for (int i = queries.size() - 1; i >= 0; i--)
	{
		switch (queries[i][0])
		{
			case 0:
				if (check_collision(0, n, m, bottom_left, top_right) == false)
				{
					bottom_left.second += inv_dy[0] * queries[i][1];
				}

				top_right.second += inv_dy[0] * queries[i][1];
				break;

			case 1:
				if (check_collision(1, n, m, bottom_left, top_right) == false)
				{
					top_right.second += inv_dy[1] * queries[i][1];
				}

				bottom_left.second += inv_dy[1] * queries[i][1];
				break;

			case 2:
				if (check_collision(2, n, m, bottom_left, top_right) == false)
				{
					bottom_left.first += inv_dx[2] * queries[i][1];
				}

				top_right.first += inv_dx[2] * queries[i][1];
				break;

			case 3:
				if (check_collision(3, n, m, bottom_left, top_right) == false)
				{
					top_right.first += inv_dx[3] * queries[i][1];
				}

				bottom_left.first += inv_dx[3] * queries[i][1];
				break;
		}

		if ((bottom_left.first < 0 && top_right.first < 0) || (bottom_left.first >= n && top_right.first >= n)) return 0;
		if ((bottom_left.second < 0 && top_right.second < 0) || (bottom_left.second >= m && top_right.second >= m)) return 0;

		bottom_left.first = max(0, min(n - 1, bottom_left.first));
		bottom_left.second = max(0, min(m - 1, bottom_left.second));
		top_right.first = max(0, min(n - 1, top_right.first));
		top_right.second = max(0, min(m - 1, top_right.second));
	}

	return (long long)(top_right.first - bottom_left.first + 1) * (top_right.second - bottom_left.second + 1);
}

int main()
{
	/*
	// Test case 1
	// Result = 4
	int n = 2, m = 2, x = 0, y = 0;
	vector<vector<int>> queries = { { 2, 1 }, { 0, 1 }, { 1, 1 }, { 0, 1 }, { 2, 1 } };
	*/

	// Test case 2
	// Result = 2
	int n = 2, m = 5, x = 0, y = 1;
	vector<vector<int>> queries = { { 3, 1 }, { 2, 2 }, { 1, 1 }, { 2, 3 }, { 0, 1 }, { 2, 1 } };

	cout << solution(n, m, x, y, queries) << endl;
	;
	return 0;
}
