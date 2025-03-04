#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int solution(vector<int> info, vector<vector<int>> edges)
{
	int answer = 0;
	vector<vector<int>> tree(info.size(), vector<int>());

	for (vector<int> edge : edges)
	{
		tree[edge[0]].push_back(edge[1]);
	}

	auto dfs = [&](int cur_node, int sheep, int wolf, set<int> candidates, auto&& dfs_ref) -> void
	{
		sheep += info[cur_node] ^ 1;
		wolf += info[cur_node];

		if (wolf >= sheep) return;

		answer = max(answer, sheep);

		for (int child : tree[cur_node])
		{
			candidates.insert(child);
		}

		for (int candidate : candidates)
		{
			set<int> next_candidates(candidates);
			next_candidates.erase(candidate);
			dfs_ref(candidate, sheep, wolf, next_candidates, dfs_ref);
		}
	};

	dfs(0, 0, 0, set<int>(), dfs);

	return answer;
}

int main()
{
	// info : 0(¾ç), 1(´Á´ë)
	// edges : [parent] - [child]
	// Test case 1
	// Result = 5
	vector<int> info = { 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1 };
	vector<vector<int>> edges =
	{
		{ 0, 1 }, { 1, 2 }, { 1, 4 }, { 0, 8 }, { 8, 7 }, { 9, 10 },
		{ 9, 11 }, { 4, 3 }, { 6, 5 }, { 4, 6 }, { 8, 9 }
	};

	/*
	// Test case 2
	// Result = 5
	vector<int> info = { 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0 };
	vector<vector<int>> edges =
	{
		{ 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 4 }, { 2, 5 }, 
		{ 2, 6 }, { 3, 7 }, { 4, 8 }, { 6, 9 }, { 9, 10 }
	};
	*/

	cout << solution(info, edges) << endl;

	return 0;
}