#include <iostream>
#include <string>
#include <vector>

using namespace std;

string make_binary(long long number)
{
	string result;

	while (number > 0)
	{
		result = to_string(number % 2) + result;
		number >>= 1;
	}

	long long cnt = 1;
	while (cnt - 1 < result.size())
	{
		cnt <<= 1;
	}

	return string(cnt - 1 - result.size(), '0') + result;
}

bool check_binary_tree(const string& binary)
{
	if (binary.size() == 1) return true;

	int mid = binary.size() / 2;
	if (binary[mid] == '0') return binary.find('1') == string::npos;

	return check_binary_tree(binary.substr(0, mid)) && check_binary_tree(binary.substr(mid + 1));
}

vector<int> solution(vector<long long> numbers)
{
	vector<int> answer;

	for (auto number : numbers)
	{
		string binary = make_binary(number);
		answer.push_back(check_binary_tree(binary) ? 1 : 0);
	}

	return answer;
}

int main()
{
	int n;

	cin >> n;

	vector<long long> numbers;

	for (int i = 0; i < n; i++)
	{
		long long temp;
		cin >> temp;
		numbers.push_back(temp);
	}
	
	auto results = solution(numbers);

	for (auto result : results)
	{
		cout << result << " ";
	}

	cout << endl;

	return 0;
}