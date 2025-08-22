#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long solution(vector<int> sequence)
{
	long long answer = 0;
	int size = sequence.size();

	vector<long long> positive_start_sequence(size, 0), negative_start_sequence(size, 0);
	for (int i = 0; i < size; i++)
	{
		positive_start_sequence[i] = sequence[i] * (i % 2 == 0 ? 1 : -1);
		negative_start_sequence[i] = sequence[i] * (i % 2 != 0 ? 1 : -1);
	}

	// dp[n][0] : n��° ���ұ����� �κ� �迭 �߿��� 1���� �����ϴ� �޽� �迭�� ����Ͽ� ���� ���� ū ��
	// dp[n][1] : n��° ���ұ����� �κ� �迭 �߿��� -1���� �����ϴ� �޽� �迭�� ����Ͽ� ���� ���� ū ��
	vector<vector<long long>> dp(size, { 0, 0 });
	dp[0] = { positive_start_sequence[0], negative_start_sequence[0] };
	answer = max(dp[0][0], dp[0][1]);

	for (int i = 1; i < size; i++)
	{
		dp[i] = { max(dp[i - 1][0] + positive_start_sequence[i], positive_start_sequence[i]), max(dp[i - 1][1] + negative_start_sequence[i], negative_start_sequence[i]) };

		if (answer < dp[i][0])
		{
			answer = dp[i][0];
		}

		if (answer < dp[i][1])
		{
			answer = dp[i][1];
		}
	}

	return answer;
}

int main()
{
	int n;
	
	cin >> n;

	vector<int> sequence;

	for (int i = 0; i < n; i++)
	{
		int element;
		cin >> element;
		sequence.push_back(element);
	}

	cout << solution(sequence);

	return 0;
}