#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int value;
	vector<int> childs;
};

long long solution(vector<int> values, vector<vector<int>> edges)
{
	long long answer = 0;

	int size = values.size();
	vector<Node> tree(size, Node());
	vector<bool> visited(size, false);

	for (int i = 0; i < size; i++)
	{
		tree[i].value = values[i];
		tree[i].childs = vector<int>();
	}

	for (vector<int> edge : edges)
	{
		tree[edge[0]].childs.push_back(edge[1]);
		tree[edge[1]].childs.push_back(edge[0]);
	}

	auto dfs = [&](int cur_node, auto&& dfs_ref) -> long long
	{
		long long result = tree[cur_node].value;
		visited[cur_node] = true;

		for (int child : tree[cur_node].childs)
		{
			if (visited[child] == true) continue;

			long long r = dfs_ref(child, dfs_ref);

			answer += abs(r);
			result += r;
		}

		return result;
	};

	long long result = dfs(0, dfs);

	return result == 0 ? answer : -1;
}

int main()
{
	// Test case 1
	// Result = 9
	vector<int> a = { -5, 0, 2, 1, 2 };
	vector<vector<int>> edges = { { 0, 1 }, { 3, 4 }, { 2, 3 }, { 0, 3 } };
	
	/*
	// Test case 2
	// Result = -1
	vector<int> a = { 0, 1, 0 };
	vector<vector<int>> edges = { { 0, 1 }, { 1, 2 } };
	*/

	cout << solution(a, edges) << endl;

	return 0;
}