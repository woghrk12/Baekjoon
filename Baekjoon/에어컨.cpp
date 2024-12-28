#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard)
{
	// unordered_map<int, int> : key는 해당 Index에 도달 가능한 온도, value는 해당 온도가 되기 위해 사용한 전력량
	vector<unordered_map<int, int>> dp;

	dp.push_back({ { temperature, 0 } });

	int size = onboard.size();
	int offset = temperature > t2 ? -1 : 1;

	for (int i = 0; i < size; i++)
	{
		dp.push_back({ });

		if (onboard[i] == 0)
		{
			for (auto element : dp[i])
			{
				int modified = element.first + offset;
				if (dp[i + 1].find(modified) != dp[i + 1].end())
				{
					dp[i + 1][modified] = min(dp[i + 1][modified], element.second + a);
				}
				else
				{
					dp[i + 1].insert({ modified, element.second + a });
				}

				int maintained = element.first;
				if (dp[i + 1].find(maintained) != dp[i + 1].end())
				{
					dp[i + 1][maintained] = min(dp[i + 1][maintained], element.second + b);
				}
				else
				{
					dp[i + 1].insert({ maintained, element.second + b });
				}

				int off = element.first != temperature ? element.first - offset : temperature;
				if (dp[i + 1].find(off) != dp[i + 1].end())
				{
					dp[i + 1][off] = min(dp[i + 1][off], element.second);
				}
				else
				{
					dp[i + 1].insert({ off, element.second });
				}
			}
		}
		else
		{
			for (auto element : dp[i])
			{
				int modified = element.first + offset;
				if (modified >= t1 && modified <= t2)
				{
					if (dp[i + 1].find(modified) != dp[i + 1].end())
					{
						dp[i + 1][modified] = min(dp[i + 1][modified], element.second + a);
					}
					else
					{
						dp[i + 1].insert({ modified, element.second + a });
					}
				}
				int maintained = element.first;
				if (maintained >= t1 && maintained <= t2)
				{
					if (dp[i + 1].find(maintained) != dp[i + 1].end())
					{
						dp[i + 1][maintained] = min(dp[i + 1][maintained], element.second + b);
					}
					else
					{
						dp[i + 1].insert({ maintained, element.second + b });
					}
				}

				int off = element.first != temperature ? element.first - offset : temperature;
				if (off >= t1 && off <= t2)
				{
					if (dp[i + 1].find(off) != dp[i + 1].end())
					{
						dp[i + 1][off] = min(dp[i + 1][off], element.second);
					}
					else
					{
						dp[i + 1].insert({ off, element.second });
					}
				}
			}
		}
	}

	int answer = size * a;
	for (auto element : dp[size])
	{
		answer = min(answer, element.second);
	}

	return answer;
}

int main()
{
	int temperature, t1, t2, a, b;
	cin >> temperature >> t1 >> t2 >> a >> b;
	
	vector<int> onboard;
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		onboard.push_back(temp);
	}

	cout << solution(temperature, t1, t2, a, b, onboard);

	return 0;
}