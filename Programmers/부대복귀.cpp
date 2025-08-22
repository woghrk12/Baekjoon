#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <string>

using namespace std;

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination)
{
	vector<int> answer;

	// -1 : not visited, positive : minimum distance
	vector<int> dp(n + 1, -1);

	vector<unordered_set<int>> child_set(n + 1);
	for (auto edge : roads)
	{
		child_set[edge[0]].insert(edge[1]);
		child_set[edge[1]].insert(edge[0]);
	}

	queue<int> bfs;
	bfs.push(destination);
	dp[destination] = 0;
	while (bfs.empty() != true)
	{
		int front = bfs.front();
		bfs.pop();

		if (child_set[front].size() == 0) continue;

		for (int child : child_set[front])
		{
			if (dp[child] >= 0)
			{
				dp[child] = min(dp[child], dp[front] + 1);
				continue;
			}

			dp[child] = dp[front] + 1;
			bfs.push(child);
		}
	}

	for (int source : sources)
	{
		answer.push_back(dp[source]);
	}

	return answer;
}

int main()
{
	int n;

	int e;
	vector<vector<int>> roads;
	vector<int> sources;

	cin >> n;
	
	cin >> e;
	for (int i = 0; i < e; i++)
	{
		vector<int> edge;
		int a, b;

		cin >> a >> b;

		edge.push_back(a);
		edge.push_back(b);

		roads.push_back(edge);
	}

	int s;
	
	cin >> s;

	for (int i = 0; i < s; i++)
	{
		int source;

		cin >> source;

		sources.push_back(source);
	}

	int destination;

	cin >> destination;

	vector<int> results = solution(n, roads, sources, destination);

	for (int result : results)
	{
		cout << result << endl;
	}

	return 0;
}