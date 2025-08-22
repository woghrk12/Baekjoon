#include <iostream>
#include <string>
#include <vector>

#define LENGTH 24

using namespace std;

int solution(vector<int> players, int m, int k)
{
	int answer = 0; 
	vector<int> added_servers(LENGTH, 0);

	for (int i = 0; i < LENGTH; i++)
	{
		int necessary = players[i] / m;

		if (added_servers[i] >= necessary) continue;

		int added = necessary - added_servers[i];

		for (int j = 0; j < k; j++)
		{
			if (i + j >= LENGTH) break;

			added_servers[i + j] += added;
		}

		answer += added;
	}

	return answer;
}

int main()
{
	// Test case 1
	// Result = 7
	vector<int> players = {
		0, 2, 3, 3, 1, 2, 
		0, 0, 0, 0, 4, 2, 
		0, 6, 0, 4, 2, 13, 
		3, 5, 10, 0, 1, 5 
	};
	int m = 3, k = 5;
	
	/*
	// Test case 2
	// Result = 11
	vector<int> players = {
		0, 0, 0, 10, 0,
		12, 0, 15, 0, 1, 0,
		1, 0, 0, 0, 5, 0, 0,
		11, 0, 8, 0, 0, 0
	};
	int m = 5, k = 1;
	*/

	/*
	// Test case 3
	// Result = 12
	vector<int> players = {
		0, 0, 0, 0, 0, 2,
		0, 0, 0, 1, 0, 5, 0,
		2, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 1
	};
	int m = 1, k = 1;
	*/

	cout << solution(players, m, k) << endl;

	return 0;
}