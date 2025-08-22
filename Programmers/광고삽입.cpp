#include <iostream>
#include <string>
#include <vector>

using namespace std;

int convert_string_to_int(string target)
{
	return stoi(target.substr(0, 2)) * 3600 + stoi(target.substr(3, 2)) * 60 + stoi(target.substr(6, 2));
}

string convert_int_to_string(int target)
{
	int hour = target / 3600;
	target %= 3600;
	int min = target / 60;
	target %= 60;
	int sec = target;

	return (hour < 10 ? "0" + to_string(hour) : to_string(hour)) + ":" 
		+ (min < 10 ? "0" + to_string(min) : to_string(min)) + ":" 
		+ (sec < 10 ? "0" + to_string(sec) : to_string(sec));
}

string solution(string play_time, string adv_time, vector<string> logs)
{
	int answer = 0;
	int pt = convert_string_to_int(play_time);
	int at = convert_string_to_int(adv_time);
	
	vector<int> time_line(pt + 1, 0);

	for (string log : logs)
	{
		string start_time = log.substr(0, 8);
		string end_time = log.substr(9);
		int st = convert_string_to_int(start_time);
		int et = convert_string_to_int(end_time);

		time_line[st]++;
		time_line[et]--;
	}

	for (int i = 1; i < pt + 1; i++)
	{
		time_line[i] += time_line[i - 1];
	}

	long long sum = 0;

	for (int i = 0; i < at; i++)
	{
		sum += time_line[i];
	}

	long long max = sum;

	for (int i = 1; i < pt + 1 - at; i++)
	{
		sum -= time_line[i - 1];
		sum += time_line[i + at - 1];

		if (max < sum)
		{
			max = sum;
			answer = i;
		}
	}

	return convert_int_to_string(answer);
}

int main()
{
	// Test case 1
	// Result = "01:30:59"
	string play_time = "02:03:55", adv_time = "00:14:15";
	vector<string> logs = { "01:20:15-01:45:14", "00:40:31-01:00:00", "00:25:50-00:48:29", "01:30:59-01:53:29", "01:37:44-02:02:30" };
	
	/*
	// Test case 2
	// Result = "01:00:00"
	string play_time = "99:59:59", adv_time = "25:00:00";
	vector<string> logs = { "69:59:59-89:59:59", "01:00:00-21:00:00", "79:59:59-99:59:59", "11:00:00-31:00:00" };
	*/

	/*
	// Test case 3
	// Result = "00:00:00"
	string play_time = "50:00:00", adv_time = "50:00:00";
	vector<string> logs = { "15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45" };
	*/

	cout << solution(play_time, adv_time, logs) << endl;

	return 0;
}	
