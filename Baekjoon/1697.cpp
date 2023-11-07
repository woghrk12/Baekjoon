#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solution(int N, int K)
{
	const int MAX = 100000;

	int answer = 0;
	queue<pair<int, int>> bfs;
	vector<bool> visited;

	// Initialize the value { level, position }
	bfs.push({ 0, N });
	for (int i = 0; i <= MAX; i++)
	{
		visited.push_back(false);
	}

	// Search the position by bfs
	while (!bfs.empty())
	{
		pair<int, int> move = bfs.front();
		bfs.pop();

		// Find the position
		if (move.second == K)
		{
			answer = move.first;
			break;
		}
		else
		{
			if (move.second + 1 <= MAX && !visited[move.second + 1])
			{
				bfs.push({ move.first + 1, move.second + 1 });
				visited[move.second + 1] = 1;
			}
			if (move.second * 2 <= MAX && !visited[move.second * 2])
			{
				bfs.push({ move.first + 1, move.second * 2 });
				visited[move.second * 2] = 1;
			}
			if (move.second - 1 >= 0 && !visited[move.second - 1])
			{
				bfs.push({ move.first + 1, move.second - 1 });
				visited[move.second - 1] = 1;
			}
		}
	}
	
	return answer;
}

int main()
{
	int N, K;

	cin >> N >> K;

	cout << solution(N, K);

	return 0;
}