#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> solution(int N, vector<string>& map)
{
	vector<int> answer;
	vector<vector<bool>> visited;

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { 1, -1, 0, 0 };

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

	// Find connected apartments and add the number of apartments
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// There is no apartment
			if (map[i][j] == '0') continue;
			// Already visited
			if (visited[i][j]) continue;

			queue<pair<int, int>> bfs;
			
			// Calculate the number of connected apartments
			bfs.push({ i, j });
			visited[i][j] = true;
			int count = 0;

			while (!bfs.empty())
			{
				pair<int, int> pos = bfs.front();
				bfs.pop();
				count++;
				
				int x = pos.first, y = pos.second;
				for (int d = 0; d < 4; d++)
				{
					int tx = x + dx[d], ty = y + dy[d];

					// Out of range, there is no apartment, already visited
					if (tx < 0 || ty < 0 || tx >= N || ty >= N || map[tx][ty] == '0' || visited[tx][ty]) continue;

					visited[tx][ty] = true;
					bfs.push({ tx, ty });
				}
			}

			answer.push_back(count);
		}
	}

	sort(answer.begin(), answer.end());

	return answer;
}

int main()
{
	int N;
	vector<string> map;

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		string temp;

		cin >> temp;

		map.push_back(temp);
	}
	
	vector<int> result = solution(N, map);

	cout << result.size() << endl;
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}

	return 0;
}