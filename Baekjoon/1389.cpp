#include <iostream>
#include <vector>
using namespace std;

int solution(int N, vector<vector<int>>& relation)
{
	vector<vector<int>> adjMatrix;

	// Initialize the adjacency matrix
	for (int i = 0; i <= N; i++)
	{
		vector<int> temp;

		for (int j = 0; j <= N; j++)
		{
			temp.push_back(0);
		}

		adjMatrix.push_back(temp);
	}

	// Add the edges
	for (int i = 0; i < relation.size(); i++)
	{
		int first = relation[i][0];
		int second = relation[i][1];

		adjMatrix[first][second] = adjMatrix[second][first] = 1;
	}

	// Calculate the number of Kevin Bacon 
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (i == k) continue;

			for (int j = 1; j <= N; j++)
			{
				if (j == k || j == i) continue;

				if (adjMatrix[i][k] > 0 && adjMatrix[k][j] > 0)
				{
					if (adjMatrix[i][j] == 0) adjMatrix[i][j] = adjMatrix[j][i] = adjMatrix[i][k] + adjMatrix[k][j];
					else adjMatrix[i][j] = adjMatrix[j][i] = min(adjMatrix[i][k] + adjMatrix[k][j], adjMatrix[i][j]);
				}
			}
		}
	}

	// Find the min number 
	int minBacon = 100 * 100;
	int minNumber = 0;
	for (int i = 1; i <= N; i++)
	{
		int bacon = 0;

		for (int j = 1; j <= N; j++)
		{
			if (i == j) continue;

			bacon += adjMatrix[i][j];
		}

		if (minBacon > bacon)
		{
			minBacon = bacon;
			minNumber = i;
		}
	}

	return minNumber;
}

int main()
{
	int N, M;
	vector<vector<int>> relation;
	
	cin >> N >> M;
	
	for (int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		relation.push_back({ a, b });
	}

	cout << solution(N, relation);

	return 0;
}