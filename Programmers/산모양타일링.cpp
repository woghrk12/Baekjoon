#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MOD 10007

int solution(int n, vector<int> tops)
{
	vector<vector<int>> dp;
	// dp[n][0] : the case where it does not affect the (N + 1)th top
	// dp[n][1] : the case where it does affect the (N + 1)th top

	if (tops[0] == 0)
	{
		dp.push_back({2, 1});
	}
	else
	{
		dp.push_back({3, 1});
	}

	for (int i = 1; i < n; i++)
	{
		if (tops[i] == 0)
		{
			dp.push_back({(dp[i - 1][0] * 2 + dp[i - 1][1]) % MOD, (dp[i - 1][0] + dp[i - 1][1]) % MOD});
		}
		else
		{
			dp.push_back({(dp[i - 1][0] * 3 + dp[i - 1][1] * 2) % MOD, (dp[i - 1][0] + dp[i - 1][1]) % MOD});
		}
	}

	return (dp[n - 1][0] + dp[n - 1][1]) % MOD;
}

int main()
{
	// Test case 1
	// Result = 149
	int result1 = solution(4, {1, 1, 0, 1});
	cout << "Test case 1: " << result1 << endl;

	// Test case 2
	// Result = 11
	int result2 = solution(2, {0, 1});
	cout << "Test case 2: " << result2 << endl;

	// Test case 3
	// Result = 7704
	int result3 = solution(10, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	cout << "Test case 3: " << result3 << endl;

	return 0;
}