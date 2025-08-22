#include <cmath>
#include <iostream>
#include <vector>
#include <string>

#define EXPRESSION_LENGTH 5

using namespace std;

// n진법의 수를 10진법으로 변환하는 함수
int convert_formation_to_decimal(int formation, int target)
{
	int result = 0;
	int cnt = 0;

	while (target > 0)
	{
		result += (target % 10) * pow(formation, cnt);
		target /= 10;
		cnt++;
	}

	return result;
}

// 10진법의 수를 n진법으로 변환하는 함수
int convert_decimal_to_formation(int formation, int target)
{
	int result = 0;
	int cnt = 0;
	
	while (target > 0)
	{
		result += (target % formation) * pow(10, cnt);
		target /= formation;
		cnt++;
	}

	return result;
}

vector<string> solution(vector<string> expressions)
{
	vector<string> answer;
	vector<vector<string>> incompletes;
	vector<bool> formation(10, true);

	for (string expression : expressions)
	{
		for (char c : expression)
		{
			int i = c - '0';

			if (i < 2 || i > 9) continue;

			for (int j = 2; j < 10; j++)
			{
				if (formation[j] == false) continue;

				formation[j] = i < j;
			}
		}

		int start = 0, end = 0;
		vector<string> splits;

		while ((end = expression.find(" ", start)) != string::npos)
		{
			splits.push_back(expression.substr(start, end - start));
			start = end + 1;
		}

		splits.push_back(expression.substr(start, end - start));

		if (splits[EXPRESSION_LENGTH - 1] == "X")
		{
			incompletes.push_back(splits);
		}
		else
		{
			for (int i = 2; i < 10; i++)
			{
				if (formation[i] == false) continue;

				int a = convert_formation_to_decimal(i, stoi(splits[0]));
				int b = convert_formation_to_decimal(i, stoi(splits[2]));
				int op = splits[1] == "+" ? 1 : -1;
				int c = convert_formation_to_decimal(i, stoi(splits[4]));

				if (a + op * b != c)
				{
					formation[i] = false;
				}
			}
		}
	}

	for (vector<string> incomplete : incompletes)
	{
		string result = incomplete[0]
			.append(" ")
			.append(incomplete[1])
			.append(" ")
			.append(incomplete[2])
			.append(" ")
			.append(incomplete[3])
			.append(" ");

		int value = -1;
		bool is_known = true;
		for (int i = 2; i < 10; i++)
		{
			if (formation[i] == false) continue;

			int a = convert_formation_to_decimal(i, stoi(incomplete[0]));
			int b = convert_formation_to_decimal(i, stoi(incomplete[2]));
			int op = incomplete[1] == "+" ? 1 : -1;
			
			if (value < 0)
			{
				value = convert_decimal_to_formation(i, a + op * b);
			}
			else
			{
				int temp = convert_decimal_to_formation(i, a + op * b);

				if (value != temp)
				{
					is_known = false;
					break;
				}
			}
		}

		result.append(is_known ? to_string(value) : "?");

		answer.push_back(result);
	}

	return answer;
}

int main()
{ 
	vector<string> expressions = 
	{
		"10 - 2 = X",
		"30 + 31 = 101",
		"3 + 3 = X",
		"33 + 33 = X"
	};

	vector<string> results = solution(expressions);

	for (string result : results)
	{
		cout << result << endl;
	}
	
	return 0;
}