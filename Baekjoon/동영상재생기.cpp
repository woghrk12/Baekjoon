#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// "00:00"������ ��Ʈ���� n�ʷ� ��ȯ
int convert_string_to_int(string value)
{
	int min = stoi(value.substr(0, 2));
	int sec = stoi(value.substr(3, 2));

	return min * 60 + sec;
}

// n�ʸ� "00:00" ������ ��Ʈ������ ��ȯ
string convert_int_to_string(int value)
{
	int min = value / 60;
	int sec = value % 60;
	
	ostringstream oss;
	oss << setw(2) << setfill('0') << min << ":" << setw(2) << setfill('0') << sec;

	return oss.str();
}

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands)
{
	int cur_pos = convert_string_to_int(pos);
	int max = convert_string_to_int(video_len);
	int start = convert_string_to_int(op_start);
	int end = convert_string_to_int(op_end);

	for (string command : commands)
	{
		if (cur_pos >= start && cur_pos <= end)
		{
			cur_pos = end;
		}

		if (command == "prev")
		{
			cur_pos = std::max(cur_pos - 10, 0);
		}
		else
		{
			cur_pos = std::min(cur_pos + 10, max);
		}

		if (cur_pos >= start && cur_pos <= end)
		{
			cur_pos = end;
		}
	}

	return convert_int_to_string(cur_pos);
}

int main()
{
	string video_len = "07:22";
	string pos = "04:05";
	string op_start = "00:15", op_end = "04:07";
	vector<string> commands = { "next" };

	cout << solution(video_len, pos, op_start, op_end, commands) << endl;

	return 0;
}