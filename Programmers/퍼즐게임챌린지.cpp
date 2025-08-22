#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long calculate_time(int level, const vector<int>& diffs, const vector<int>& times)
{
	long long time = 0;
	int size = diffs.size();

	time += times[0];

	for (int i = 1; i < size; i++)
	{
		int diff = max(diffs[i] - level, 0);

		time += diff * times[i - 1];
		time += diff * times[i];
		time += times[i];
	}

	return time;
}

int solution(vector<int> diffs, vector<int> times, long long limit)
{
	int answer = 0;
	int left = 1, right = 100000, mid = (left + right) / 2;

	while (left <= right)
	{
		long long value = calculate_time(mid, diffs, times);

		if (value <= limit)
		{
			answer = mid;

			right = mid - 1;
			mid = (left + right) / 2;
		}
		else
		{
			left = mid + 1;
			mid = (left + right) / 2;
		}
	}

	return answer;
}

int main()
{
	vector<int> diffs = { 1, 328, 467, 209, 54 };
	vector<int> times = { 2, 7, 1, 4, 3 };
	long long limit = 1723;

	cout << solution(diffs, times, limit) << endl;

	return 0;
}