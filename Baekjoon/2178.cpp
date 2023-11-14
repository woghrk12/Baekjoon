#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int solution(int N, int M, vector<string>& map)
{
	int answer = 0;

	int dx[4] = { 0, 0, 1, -1 };
	int dy[4] = { 1, -1, 0, 0 };
	vector<vector<bool>> visited;
	queue<vector<int>> bfs;

	// Initialize the map for checking whether the node has been visited
	for (int i = 0; i < N; i++)
	{
		vector<bool> temp;

		for (int j = 0; j < M; j++)
		{
			temp.push_back(false);
		}

		visited.push_back(temp);
	}

	// Input the start node
	bfs.push({ 1, 0, 0 });
	visited[0][0] = true;

	// Search the path by using bfs
	while (!bfs.empty())
	{
		vector<int> step = bfs.front();
		bfs.pop();

		int depth = step[0], x = step[1], y = step[2];

		// If the node is the target
		if (x == M - 1 && y == N - 1)
		{
			answer = depth;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int _x = x + dx[i], _y = y + dy[i];

			// Out of range, blocked node, or already visited node
			if (_x < 0 || _x >= M || _y < 0 || _y >= N || map[_y][_x] == '0' || visited[_y][_x]) continue;

			visited[_y][_x] = true;
			bfs.push({ depth + 1, _x, _y });
		}
	}

	return answer;
}

int main()
{
	int N, M;
	vector<string> map;

	cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		string temp;

		cin >> temp;

		map.push_back(temp);
	}

	cout << solution(N, M, map);

	return 0;
}