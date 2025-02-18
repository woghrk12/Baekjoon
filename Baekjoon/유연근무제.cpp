#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

bool check_in_range(int schedule, int timelog)
{
	int end_hour = schedule / 100;
	int end_min = (schedule % 100) + 10;
	int end = end_min >= 60 ? (end_hour + 1) * 100 + end_min - 60 : schedule + 10;

	return timelog <= end;
}

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday)
{
	unordered_set<int> targets;
	for (int i = 0; i < timelogs.size(); i++)
	{
		targets.insert(i);
	}

	for (int i = 0; i < 7; i++)
	{
		int today = (i + startday) % 7;

		if (today == 0 || today == 6) continue;

		vector<int> removeds;
		for (int target : targets)
		{
			if (check_in_range(schedules[target], timelogs[target][i]) == true) continue;

			removeds.push_back(target);
		}

		for (int removed : removeds)
		{	
			targets.erase(removed);
		}
	}

	return targets.size();
}

int main()
{
	vector<int> schedules = { 730, 855, 700, 720 };
	vector<vector<int>> timelogs =
	{
		{ 710, 700, 650, 735, 700, 931, 912 },
		{ 908, 901, 805, 815, 800, 831, 835 },
		{ 705, 701, 702, 705, 710, 710, 711 },
		{ 707, 731, 859, 913, 934, 931, 905 }
	};
	int startday = 1;

	cout << solution(schedules, timelogs, startday) << endl;

	return 0;
}