#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> info, int n, int m)
{
	// 1 <= info.size() <= 40
	// 1 <= n, m <= 120
	// dp[x][y] : x + 1∞≥¿« π∞∞«¿ª »…√∆¿ª ∂ß, B¿« »Á¿˚ ∞πºˆ∞° y¿œ ∞ÊøÏ A¿« √÷º“ »Á¿˚ ∞πºˆ
	int length = info.size();
	vector<map<int, int>> dp(length, map<int, int>());
	
	if (info[0][0] < n)
	{
		dp[0].insert({ 0, info[0][0] });
	}
	if (info[0][1] < m)
	{
		dp[0].insert({ info[0][1], 0 });
	}

	for (int i = 1; i < length; i++)
	{
		for (pair<int, int> p : dp[i - 1])
		{
			// A∞° »…√∆¿ª ãö
			int cnt_a = p.second + info[i][0];
			if (cnt_a < n)
			{
				if (dp[i].find(p.first) == dp[i].end())
				{
					dp[i].insert({ p.first, cnt_a });
				}
				else
				{
					dp[i][p.first] = min(dp[i][p.first], cnt_a);
				}
			}
			// B∞° »…√∆¿ª ∂ß
			int cnt_b = p.first + info[i][1];
			if (cnt_b < m)
			{
				if (dp[i].find(cnt_b) == dp[i].end())
				{
					dp[i].insert({ cnt_b , p.second });
				}
				else
				{
					dp[i][cnt_b] = min(dp[i][cnt_b], p.second);
				}
			}
		}
	}

	int answer = -1;
	for (pair<int, int> p : dp[length - 1])
	{
		answer = answer < 0 ? p.second : min(answer, p.second);
	}

	return answer;
}

int main()
{
	/*
	// Test case 1
	// Result = 2
	vector<vector<int>> info = { { 1, 2 }, { 2, 3 }, { 2, 1 } };
	int n = 4, m = 4;
	*/

	/*
	// Test case 2
	// Result = 0
	vector<vector<int>> info = { { 1, 2 }, { 2, 3 }, { 2, 1 } };
	int n = 1, m = 7;
	*/
	
	/*
	// Test case 3
	// Result = 6
	vector<vector<int>> info = { { 3, 3 }, { 3, 3 } };
	int n = 7, m = 1;
	*/

	// Test case 4
	// Result = -1
	vector<vector<int>> info = { { 3, 3 }, { 3, 3 } };
	int n = 6, m = 1;

	cout << solution(info, n, m) << endl;

	return 0;
}

