#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
	int id;
	int intensity;
};

struct Compare
{
	bool operator()(Node a, Node b)
	{
		return a.intensity != b.intensity ? a.intensity > b.intensity : a.id > b.id;
	}
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits)
{
	vector<int> answer;
	vector<vector<pair<int, int>>> graph(n + 1);
	vector<int> intensity(n + 1, -1);
	vector<bool> is_summit(n + 1, false);

	for (vector<int> path : paths)
	{
		graph[path[0]].push_back({ path[1], path[2] });
		graph[path[1]].push_back({ path[0], path[2] });
	}

	for (int summit : summits)
	{
		is_summit[summit] = true;
	}

	priority_queue<Node, vector<Node>, Compare> pq;
	for (int gate : gates)
	{
		pq.push({ gate, 0 });
		intensity[gate] = 0;
	}

	int min_intensity = -1;
	int summit = -1;

	while (!pq.empty())
	{
		int cur_node = pq.top().id;
		int cur_intensity = pq.top().intensity;
		pq.pop();

 		if (min_intensity >= 0 && cur_intensity > min_intensity) continue;

		if (is_summit[cur_node] == true)
		{
			if (min_intensity < 0)
			{
				summit = cur_node;
				min_intensity = cur_intensity;
			}
			else if (cur_intensity < min_intensity)
			{
				summit = cur_node;
				min_intensity = cur_intensity;
			}
			else if (cur_intensity == min_intensity)
			{
				summit = min(summit, cur_node);
			}

			continue;
		}

		for (pair<int, int> v : graph[cur_node])
		{
			int cost = max(v.second, intensity[cur_node]);

			if (intensity[v.first] >= 0 && intensity[v.first] <= cost) continue;

			intensity[v.first] = cost;
			pq.push({ v.first, cost });
		}
	}

	answer.push_back(summit);
	answer.push_back(min_intensity);

	return answer;
}

int main()
{
	int n = 7;
	vector<vector<int>> paths =
	{
		{ 1, 4, 4 },
		{ 1, 6, 1 },
		{ 1, 7, 3 },
		{ 2, 5, 2 },
		{ 3, 7, 4 },
		{ 5, 6, 6 }
	};
	vector<int> gates = { 1 };
	vector<int> summits = { 2, 3, 4 };

	vector<int> results = solution(n, paths, gates, summits);

	for (int result : results)
	{
		cout << result << " ";
	}

	cout << endl;

	return 0;
}