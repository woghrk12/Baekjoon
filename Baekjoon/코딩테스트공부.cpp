#include <iostream>
#include <vector>

using namespace std;

#define MAX 150

int solution(int alp, int cop, vector<vector<int>> problems)
{
	int target_alp = alp, target_cop = cop;
	for (vector<int> problem : problems)
	{
		target_alp = max(target_alp, problem[0]);
		target_cop = max(target_cop, problem[1]);
	}

	vector<vector<int>> dp(MAX + 1);
	vector<vector<bool>> visited(MAX + 1);
	for (int i = 0; i <= MAX; i++)
	{
		vector<int> temp_dp(MAX + 1, 0);
		vector<bool> temp_visited(MAX + 1, false);
		
		dp[i] = temp_dp;
		visited[i] = temp_visited;
	}

	for (int i = alp; i <= target_alp; i++)
	{
		for (int j = cop; j <= target_cop; j++)
		{
			if (i + 1 <= target_alp)
			{
				dp[i + 1][j] = visited[i + 1][j] ? min(dp[i][j] + 1, dp[i + 1][j]) : dp[i][j] + 1;
				visited[i + 1][j] = true;
			}

			if (j + 1 <= target_cop)
			{
				dp[i][j + 1] = visited[i][j + 1] ? min(dp[i][j] + 1, dp[i][j + 1]) : dp[i][j] + 1;
				visited[i][j + 1] = true;
			}

			for (vector<int> problem : problems)
			{
				int alp_req = problem[0];
				int cop_req = problem[1];
				int cost = problem[4];

				if (i < alp_req || j < cop_req) continue;

				int new_alp = min(target_alp, i + problem[2]);
				int new_cop = min(target_cop, j + problem[3]);
				
				dp[new_alp][new_cop] = visited[new_alp][new_cop]
					? min(dp[i][j] + cost, dp[new_alp][new_cop])
					: dp[i][j] + cost;

				visited[new_alp][new_cop] = true;
			}
		}
	}

	return dp[target_alp][target_cop];
}

int main()
{
	int alp = 10, cop = 10;
	vector<vector<int>> problems =
	{
		{ 10, 15, 2, 1, 2 },
		{ 20, 20, 3, 3, 4 }
	};

	cout << solution(alp, cop, problems);

	return 0;
}