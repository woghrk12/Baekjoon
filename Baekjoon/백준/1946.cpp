#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int>& a, vector<int>& b)
{
	return a[0] < b[0];
}

int solution(int N, vector<vector<int>>& score)
{
	int answer = 0;
	
	// Sort the array by document review score
	sort(score.begin(), score.end(), compare);

	int min = 100001;
	for (int i = 0; i < N; i++)
	{
		// Not selected if the interview score is low
		if (min <= score[i][1]) continue;

		min = score[i][1];
		answer++;
	}

	return answer;
}

int main()
{
	int T, N;
	
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> N;

		vector<vector<int>> score;

		for (int j = 0; j < N; j++)
		{
			int a, b;
			cin >> a >> b;
			score.push_back({ a, b });
		}

		cout << solution(N, score) << endl;
	}

	return 0;
}