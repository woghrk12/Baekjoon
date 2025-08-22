#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Compare
{
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

int calculate_waiting(const vector<int>& count_mento, const vector<vector<int>>& reqs)
{
	int result = 0;
	vector<priority_queue<int, vector<int>, Compare>> mentos(count_mento.size());

	for (auto req : reqs)
	{
		int start = req[0], time = req[1], type = req[2] - 1;
		
		if (mentos[type].size() < count_mento[type])
		{
			mentos[type].push(start + time);
			continue;
		}

		int end = mentos[type].top(), delay = end - start;
		mentos[type].pop();

		if (delay <= 0)
		{
			mentos[type].push(start + time);
			continue;
		}

		result += delay;
		mentos[type].push(end + time);
	}

	return result;
}

int solution(int k, int n, vector<vector<int>> reqs)
{
	int answer = 300000;
	vector<int> count_mento(k, 1);

	answer = calculate_waiting(count_mento, reqs);

	for (int i = 0; i < n - k; i++)
	{
		int min_value = answer, additional_mento_type = 0;

		for (int j = 0; j < k; j++)
		{
			count_mento[j]++;

			int value = calculate_waiting(count_mento, reqs);
			if (min_value > value)
			{
				additional_mento_type = j;
				min_value = value;
			}

			count_mento[j]--;
		}

		count_mento[additional_mento_type]++;
		answer = min_value;
	}

	return answer;
}

int main()
{
	int k, n, size;

	cin >> k >> n >> size;

	vector<vector<int>> reqs;

	for (int i = 0; i < size; i++)
	{
		vector<int> req;
		int start, time, type;
		
		cin >> start >> time >> type;
		
		req.push_back(start);
		req.push_back(time);
		req.push_back(type);

		reqs.push_back(req);
	}

	cout << solution(k, n, reqs);

	return 0;
}