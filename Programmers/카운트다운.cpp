#include <iostream>
#include <vector>

using namespace std;

struct point
{
	int cnt_dart;
	int cnt_single_bull;

	bool operator< (const point& a)
	{
		if (this->cnt_dart < 0) return false;
		if (a.cnt_dart < 0) return true;

		return this->cnt_dart != a.cnt_dart ? this->cnt_dart < a.cnt_dart : this->cnt_single_bull > a.cnt_single_bull;
	};
};

vector<int> solution(int target)
{
	vector<int> answer;

	// dp[i] : i 점수 남았을 때 던진 다트의 갯수와 싱글/불 갯수
	vector<point> dp(100001, { -1, -1 });
	dp[target] = { 0, 0 };

	for (int i = target; i >= 0; i--)
	{
		// Bull
		if (i - 50 >= 0)
		{
			point cur;
			
			cur.cnt_dart = dp[i].cnt_dart + 1;
			cur.cnt_single_bull = dp[i].cnt_single_bull + 1;

			if (cur < dp[i - 50])
			{
				dp[i - 50] = cur;
			}
		}
		
		// Single
		for (int j = 1; j <= 20; j++)
		{
			if (i - j < 0) continue;

			point cur;

			cur.cnt_dart = dp[i].cnt_dart + 1;
			cur.cnt_single_bull = dp[i].cnt_single_bull + 1;

			if (cur < dp[i - j])
			{
				dp[i - j] = cur;
			}
		}
		
		// Dubble
		for (int j = 2; j <= 40; j += 2)
		{
			if (i - j < 0) continue;

			point cur;

			cur.cnt_dart = dp[i].cnt_dart + 1;
			cur.cnt_single_bull = dp[i].cnt_single_bull;

			if (cur < dp[i - j])
			{
				dp[i - j] = cur;
			}
		}

		// Tripple
		for (int j = 3; j <= 60; j += 3)
		{
			if (i - j < 0) continue;

			point cur;

			cur.cnt_dart = dp[i].cnt_dart + 1;
			cur.cnt_single_bull = dp[i].cnt_single_bull;

			if (cur < dp[i - j])
			{
				dp[i - j] = cur;
			}
		}
	}

	answer.push_back(dp[0].cnt_dart);
	answer.push_back(dp[0].cnt_single_bull);

	return answer;
}

int main()
{
	int target = 58;

	vector<int> results = solution(target);

	for (int result : results)
	{
		cout << result << " ";
	}

	cout << endl;

	return 0;
}