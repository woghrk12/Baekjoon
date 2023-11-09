#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long solution(int N, vector<vector<int>>& map)
{
	vector<vector<long>> dp;

	// Initialize the dp matrix
	for (int i = 0; i < N; i++)
	{
		vector<long> temp;

		for (int j = 0; j < N; j++)
		{
			temp.push_back(0);
		}

		dp.push_back(temp);
	}

	// Initialize the value
	dp[0][0] = 1;

	// Calculate the number of the path
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (dp[i][j] == 0) continue;
			if (map[i][j] == 0) continue;

			int dist = map[i][j];

			if (i + dist < N) // if the next point is in range
			{
				dp[i + dist][j] += dp[i][j];
			}
			if (j + dist < N) // if the next point is in range
			{
				dp[i][j + dist] += dp[i][j];
			}
		}
	}

	return dp[N - 1][N - 1];
}

int main()
{
	int N;
	vector<vector<int>> map;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		vector<int> temp;

		for (int j = 0; j < N; j++)
		{
			int value;
			cin >> value;
			temp.push_back(value);
		}

		map.push_back(temp);
	}

	cout << solution(N, map);

	return 0;
}