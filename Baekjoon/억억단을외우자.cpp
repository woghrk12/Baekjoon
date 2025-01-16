#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int e, vector<int> starts)
{
	vector<int> count_divisor(e + 1, 0);
	for (int i = 1; i <= e; i++)
	{
		for (int j = i; j <= e / i; j++)
		{
			count_divisor[i * j] += i == j ? 1 : 2;
		}
	}

	vector<int> dp(e + 1, 0);
	dp[e] = e;
	for (int i = e - 1; i > 0; i--)
	{
		dp[i] = count_divisor[i] >= count_divisor[dp[i + 1]] ? i : dp[i + 1];
	}

	vector<int> answer;
	for (int start : starts)
	{
		answer.push_back(dp[start]);
	}
	return answer;
}

int main()
{
	int e, n;
	vector<int> starts;

	cin >> e >> n;
	for (int i = 0; i < n; i++)
	{
		int start;
		cin >> start;
		starts.push_back(start);
	}

	vector<int> results = solution(e, starts);

	for (int result : results)
	{
		cout << result << endl;
	}
	
	return 0;
}