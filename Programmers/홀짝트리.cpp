#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> solution(vector<int> nodes, vector<vector<int>> edges)
{
	// odd-even tree, inv-odd-even tree
	vector<int> answer(2, 0);
	unordered_map<int, vector<int>> forest;
	unordered_map<int, bool> is_visited;

	for (int node : nodes)
	{
		forest.insert({ node, vector<int>() });
		is_visited.insert({ node, false });
	}

	for (vector<int> edge : edges)
	{
		forest[edge[0]].push_back(edge[1]);
		forest[edge[1]].push_back(edge[0]);
	}

	for (int node : nodes)
	{
		if (is_visited[node] == true) continue;

		int cnt = 0;
		int cnt_inv = 0;

		queue<int> bfs;
		bfs.push(node);

		while (bfs.empty() != true)
		{
			int front = bfs.front();
			bfs.pop();

			is_visited[front] = true;

			if (front % 2 == 0)
			{
				// odd-even node
				if ((forest[front].size() - 1) % 2 == 0) cnt++;
				// inv-odd-even node
				else cnt_inv++;
			}
			else
			{
				// inv-odd-even node
				if ((forest[front].size() - 1) % 2 == 0) cnt_inv++;
				// odd-even node
				else cnt++;
			}

			for (int child : forest[front])
			{
				if (is_visited[child] == true) continue;

				bfs.push(child);
			}
		}

		if (cnt == 1) answer[1]++;
		if (cnt_inv == 1) answer[0]++;
	}

	return answer;
}

int main()
{
	// Test case 1
	// Result = { 1, 0 }
	vector<int> nodes = { 11, 9, 3, 2, 4, 6 };
	vector<vector<int>> edges = { { 9, 11 }, { 2, 3 }, { 6, 3 }, { 3, 4 } };
	
	/*
	// Test case 2
	// Result = { 2, 1 }
	vector<int> nodes = { 9, 15, 14, 7, 6, 1, 2, 4, 5, 11, 8, 10 };
	vector<vector<int>> edges = { { 5, 14 }, { 1, 4 }, { 9, 11 }, { 2, 15 }, { 2, 5 }, { 9, 7 }, { 8, 1 }, { 6, 4 } };
	*/

	vector<int> results = solution(nodes, edges);
	for (int result : results)
	{
		cout << result << " ";
	}
	
	cout << endl;

	return 0;
}