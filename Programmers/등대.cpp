#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> lighthouse)
{
	int answer = 0;

	vector<bool> visited(n + 1, false);
	vector<bool> light(n + 1, false);
	vector<unordered_set<int>> child_set;
	for (int i = 0; i <= n; i++)
	{
		unordered_set<int> childs;
		child_set.push_back(childs);
	}

	for (auto edge : lighthouse)
	{
		child_set[edge[0]].insert(edge[1]);
		child_set[edge[1]].insert(edge[0]);
	}

	auto dfs = [&](int cur_node, auto&& dfs_ref) -> void
	{
		visited[cur_node] = true;
		bool is_on = false;

		for (int child : child_set[cur_node])
		{
			if (visited[child] == true) continue;

			dfs_ref(child, dfs_ref);

			if (is_on == true) continue;
			if (light[child] == true) continue;

			is_on = true;
			light[cur_node] = true;
			answer++;
		}
	};

	dfs(1, dfs);

	return answer;
}

int main()
{
	int n, e;

	cin >> n >> e;

	vector<vector<int>> lighthouse;

	for (int i = 0; i < e; i++)
	{
		vector<int> edge;
		int a, b;
		cin >> a >> b;

		edge.push_back(a);
		edge.push_back(b);

		lighthouse.push_back(edge);
	}

	cout << solution(n, lighthouse);

	return 0;
}