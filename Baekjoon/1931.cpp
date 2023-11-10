#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
	return a.second != b.second ? a.second < b.second : a.first < b.first;
}


int solution(int N, vector<pair<int, int>>& meetings)
{
	int answer = 0;
	int lastEnd = 0;
	
	// If the end times are different, sort the vector based on the end time
	// if not, sort the vector based on the start time
	sort(meetings.begin(), meetings.end(), compare);

	// Count the number of meetings from the start time 0
	for (int i = 0; i < N; i++)
	{
		if (meetings[i].first < lastEnd) continue;

		answer++;
		lastEnd = meetings[i].second;
	}

	return answer;
}

int main()
{
	int N;
	vector<pair<int, int>> meetings;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int start, end;
		cin >> start >> end;
		meetings.push_back({ start, end });
	}

	cout << solution(N, meetings);

	return 0;
}