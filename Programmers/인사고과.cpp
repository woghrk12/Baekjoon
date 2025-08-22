#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> scores)
{
	int answer = 1;
	int a = scores[0][0], b = scores[0][1];

	sort(scores.begin(), scores.end(), [](vector<int> a, vector<int> b) { return a[0] != b[0] ? a[0] > b[0] : a[1] > b[1]; });

	int previous_value = 100001;
	int previous_max = 0, cur_max = 0;

	for (auto score : scores)
	{
		if (previous_value != score[0])
		{
			previous_value = score[0];
			previous_max = cur_max;
		}

		cur_max = max(score[1], cur_max);

		if (score[1] < previous_max)
		{
			if (score[0] == a && score[1] == b) return -1;

			continue;
		}

		if (a + b >= score[0] + score[1]) continue;

		answer++;
	}

	return answer;
}

int main()
{
	int n;

	cin >> n;

	vector<vector<int>> scores;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		scores.push_back({ a, b });
	}

	cout << solution(scores);

	return 0;
}