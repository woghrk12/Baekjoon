#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int solution(int N, vector<vector<int>>& map)
{
	int answer = 0;

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { 1, -1, 0, 0 };
	vector<vector<bool>> visited;

	// Initialize the matrix for checking whether the node is visited
	for (int i = 0; i < N; i++)
	{
		vector<bool> temp;
		for (int j = 0; j < N; j++)
		{
			temp.push_back(false);
		}
		visited.push_back(temp);
	}

	// Find the max number of safety zone
	for (int h = 0; h <= 100; h++)
	{
		// Initialize the matrix value
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				visited[i][j] = false;
			}
		}

		// Search the map
		int num = 0;
		queue<pair<int, int>> bfs;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] <= h) continue;
				if (visited[i][j]) continue;

				// Calculate the area of the safety zone
				bfs.push({ i, j });
				while (!bfs.empty())
				{
					pair<int, int> pos = bfs.front();
					bfs.pop();

					int x = pos.first, y = pos.second;
					for (int i = 0; i < 4; i++)
					{
						int tx = x + dx[i], ty = y + dy[i];
						// Out of range, already flooded, already visited
						if (tx < 0 || ty < 0 || tx >= N || ty >= N || map[tx][ty] <= h || visited[tx][ty]) continue;

						bfs.push({ tx, ty });
						visited[tx][ty] = true;
					}
				}

				num++;
			}
		}

		// Check the max number of safety zone
		if (answer < num)
		{
			answer = num;
		}
	}

	return answer;
}

int main()
{
	int N;
	vector<vector<int>> map;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		vector<int> temp;

		for (int j = 0; j < N; j++)
		{
			int h;
			cin >> h;
			temp.push_back(h);
		}

		map.push_back(temp);
	}

	cout << solution(N, map);

	return 0;
}