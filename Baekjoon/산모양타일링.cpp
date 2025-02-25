#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MOD 10007

vector<vector<int>> dp;

int solution(int n, vector<int> tops)
{
	// dp[n][0] : n + 1번째 top에 영향을 주지 않는 경우
	// dp[n][1] : n + 1번째 top에 영향을 주는 경우

	if (tops[0] == 0)
	{
		dp.push_back({ 2, 1 });
	}
	else
	{
		dp.push_back({ 3, 1 });
	}

	for (int i = 1; i < n; i++)
	{
		if (tops[i] == 0)
		{
			dp.push_back({ (dp[i - 1][0] * 2 + dp[i - 1][1]) % MOD, (dp[i - 1][0] + dp[i - 1][1]) % MOD });
		}
		else
		{
			dp.push_back({ (dp[i - 1][0] * 3 + dp[i - 1][1] * 2) % MOD, (dp[i - 1][0] + dp[i - 1][1]) % MOD });
		}
	}

	return (dp[n - 1][0] + dp[n - 1][1]) % MOD;
}

int main()
{
	int n;
	vector<int> tops;

	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		int top;
		cin >> top;
		tops.push_back(top);
	}

	cout << solution(n, tops);

	return 0;
}