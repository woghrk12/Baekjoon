#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Person
{
	int index;
	string parent;
	int earn;
};

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount)
{
	int size = enroll.size();
	map<string, Person> map;

	for (int i = 0; i < size; i++)
	{
		Person person;

		person.index = i;
		person.parent = referral[i];
		person.earn = 0;

		map.insert({ enroll[i], person });
	}

	for (int i = 0; i < seller.size(); i++)
	{
		string cur = seller[i];
		int remain = amount[i] * 100;

		while (cur != "-")
		{
			int charge = remain / 10;
			map[cur].earn += remain - charge;
			remain = charge;

			if (remain == 0) break;

			cur = map[cur].parent;
		}
	}

	vector<int> answer(size, 0);
	for (auto person : map)
	{
		answer[person.second.index] = person.second.earn;
	}

	return answer;
}

int main()
{
	/*
	// Test case 1
	// Result = [ 360, 958, 108, 0, 450, 18, 180, 1080 ]
	vector<string> enroll = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller = { "young", "john", "tod", "emily", "mary" };
	vector<int> amount = { 12, 4, 2, 5, 10 };
	*/

	// Test case 2
	// Result = [ 0, 110, 378, 180, 270, 450, 0, 0 ]
	vector<string> enroll = { "john", "mary", "edward", "sam", "emily", "jaimie", "tod", "young" };
	vector<string> referral = { "-", "-", "mary", "edward", "mary", "mary", "jaimie", "edward" };
	vector<string> seller = { "sam", "emily", "jaimie", "edward" };
	vector<int> amount = { 2, 3, 5, 4 };

	auto results = solution(enroll, referral, seller, amount);

	for (int result : results)
	{
		cout << result << endl;
	}

	return 0;
}