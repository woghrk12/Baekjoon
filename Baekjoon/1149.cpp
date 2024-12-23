#include <iostream>
#include <vector>
using namespace std;

int solution(vector<vector<int>>& costVector)
{
	vector<vector<int>> dp;
	int size = costVector.size();

	// Initialize the cost value of N = 1
	dp.push_back(costVector[0]);

	for (int i = 1; i < size; i++)
	{
		vector<int> temp;

		// if the house's color is Red
		temp.push_back(costVector[i][0] + min(dp[i - 1][1], dp[i - 1][2]));
		// if the house's color is Blue
		temp.push_back(costVector[i][1] + min(dp[i - 1][0], dp[i - 1][2]));
		// if the house's color is Green
		temp.push_back(costVector[i][2] + min(dp[i - 1][0], dp[i - 1][1]));

		dp.push_back(temp);
	}

	return min(dp[size - 1][0], min(dp[size - 1][1], dp[size - 1][2]));
}

int main()
{
	int N;
	vector<vector<int>> costVector;

	cin >> N;

	// Set the initial value
	for (int i = 0; i < N; i++)
	{
		vector<int> temp;
		for (int j = 0; j < 3; j++)
		{
			int cost;
			cin >> cost;
			temp.push_back(cost);
		}
		costVector.push_back(temp);
	}

	cout << solution(costVector);

	return 0;
}