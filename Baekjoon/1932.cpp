#include <iostream>
#include <vector>
using namespace std;

int solution(int N, vector<vector<int>>& tree)
{
	vector<vector<int>> dp;

	// Initialize the dp tree
	dp.push_back({ tree[0][0] });

	// Calculate the dp tree
	for (int i = 1; i < N; i++)
	{
		vector<int> temp;

		// The leftmost element
		temp.push_back(dp[i - 1][0] + tree[i][0]);
		for (int j = 1; j < i; j++)
		{
			temp.push_back(max(dp[i - 1][j - 1], dp[i - 1][j]) + tree[i][j]);
		}
		// The rightmost element
		temp.push_back(dp[i - 1][i - 1] + tree[i][i]);

		dp.push_back(temp);
	}

	// Find the max value of the path
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		if (dp[N - 1][i] > max)
		{
			max = dp[N - 1][i];
		}
	}

	return max;
}

int main()
{
	int N;
	vector<vector<int>> tree;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		vector<int> temp;

		for (int j = 0; j <= i; j++)
		{
			int value;
			cin >> value;
			temp.push_back(value);
		}

		tree.push_back(temp);
	}

	cout << solution(N, tree);

	return 0;
}