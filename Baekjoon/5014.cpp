#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int solution(int f, int s, int g, int u, int d)
{
	// Initialize the list for checking whether the node is visited
	vector<bool> visited;
	for (int i = 0; i <= f; i++)
	{
		visited.push_back(false);
	}

	// Find shortest path -> BFS
	// queue item : <depth, position>
	queue<pair<int, int>> bfs;
	bfs.push({ 0, s });
	visited[s] = true;

	while (!bfs.empty())
	{
		pair<int, int> item = bfs.front();
		bfs.pop();

		int depth = item.first;
		int position = item.second;

		// if the node is the target position
		if (position == g)
		{
			return depth;
		}
		
		// Up direction
		int upPos = position + u;
		// if the node is in range and not visited
		if (upPos <= f && !visited[upPos])
		{
			visited[upPos] = true;
			bfs.push({ depth + 1, upPos });
		}

		// Down Direction
		int downPos = position - d;
		// if the node is in range and not visited
		if (downPos > 0 && !visited[downPos])
		{
			visited[downPos] = true;
			bfs.push({ depth + 1, downPos });
		}
	}

	// Not found
	return -1;
}

int main()
{
	int F, S, G, U, D;

	cin >> F >> S >> G >> U >> D;

	int result = solution(F, S, G, U, D);

	if (result >= 0)
	{
		cout << result << endl;
	}
	else
	{
		cout << "use the stairs" << endl;
	}

	return 0;
}