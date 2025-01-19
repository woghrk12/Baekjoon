#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
	int depth;
	pair<char, char> pos;
};

int calculate_distance(pair<int, int> a, pair<int, int> b)
{
	if (a.first == b.first && a.second == b.second) return 1;

	int dx = abs(a.first - b.first);
	int dy = abs(a.second - b.second);
	int e1 = abs(dx - dy);
	int e2 = min(dx, dy);

	return e1 * 2 + e2 * 3;
}

int solution(string numbers)
{
	int answer = 10000000;
	int size = numbers.size();
	map<char, pair<int, int>> boards;
	map<pair<char, char>, vector<int>> dp;

	boards.insert({ '1', { 0, 0 } });
	boards.insert({ '2', { 1, 0 } });
	boards.insert({ '3', { 2, 0 } });
	boards.insert({ '4', { 0, 1 } });
	boards.insert({ '5', { 1, 1 } });
	boards.insert({ '6', { 2, 1 } });
	boards.insert({ '7', { 0, 2 } });
	boards.insert({ '8', { 1, 2 } });
	boards.insert({ '9', { 2, 2 } });
	boards.insert({ '*', { 0, 3 } });
	boards.insert({ '0', { 1, 3 } });
	boards.insert({ '#', { 2, 3 } });

	for (auto left : boards)
	{
		for (auto right : boards)
		{
			vector<int> v(100001, 0);
			dp.insert({ { left.first, right.first }, v });
		}
	}

	// depth : 손가락을 이동한 횟수
	queue<Node> bfs;
	bfs.push({ 0, { '4', '6' } });
	while (bfs.empty() != true)
	{
		auto front = bfs.front();
		bfs.pop();

		int depth = front.depth;
		pair<char, char> pos = front.pos;

		if (front.depth == size)
		{
			answer = min(answer, dp[pos][depth]);
			continue;
		}

		char target = numbers[depth];

		if (target != pos.second)
		{
			int offset = calculate_distance(boards[pos.first], boards[target]);

			if (dp[{ target, pos.second }][depth + 1] == 0)
			{
				dp[{ target, pos.second }][depth + 1] = dp[pos][depth] + offset;
				bfs.push({ depth + 1, { target, pos.second } });
			}
			else
			{
				dp[{ target, pos.second }][depth + 1] = min(dp[{ target, pos.second }][depth + 1], dp[pos][depth] + offset);
			}
		}

		if (target != pos.first)
		{
			int offset = calculate_distance(boards[pos.second], boards[target]);

			if (dp[{ pos.first, target }][depth + 1] == 0)
			{
				dp[{ pos.first, target }][depth + 1] = dp[pos][depth] + offset;
				bfs.push({ depth + 1, { pos.first, target } });
			}
			else
			{
				dp[{ pos.first, target }][depth + 1] = min(dp[{ pos.first, target }][depth + 1], dp[pos][depth] + offset);
			}
		}
	}

	return answer;
}

int main()
{
	string numbers;

	cin >> numbers;

	cout << solution(numbers);

	return 0;
} 