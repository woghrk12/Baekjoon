#include <iostream>
#include <vector>
using namespace std;

int solution(int N)
{
	vector<vector<int>> dp;

	// Initialize the dp array (0 : none, 1 : left, 2 : right)
	dp.push_back({ 1, 1, 1 });
	
	// Calculate the dp array
	for (int i = 1; i < N; i++)
	{
		vector<int> temp;

		// none
		temp.push_back((dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % 9901);
		// left
		temp.push_back((dp[i - 1][0] + dp[i - 1][2]) % 9901);
		// right
		temp.push_back((dp[i - 1][0] + dp[i - 1][1]) % 9901);
		
		dp.push_back(temp);
	}

	return (dp[N - 1][0] + dp[N - 1][1] + dp[N - 1][2]) % 9901;
}

int main()
{
	int N;

	cin >> N;

	cout << solution(N);

	return 0;
}