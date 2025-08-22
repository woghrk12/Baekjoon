#include <iostream>
#include <queue>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

int solution(vector<string> storage, vector<string> requests)
{
	int answer = 0;

	int height = storage.size(), width = storage[0].size();
	// pair<int, int> : x (first), y (second)
	unordered_map<char, set<pair<int, int>>> current_storage;

	// -1 : empty and visited, 0 : empty and not visited, 1 : exist and removable, 2 : exist and unremovable
	vector<vector<int>> states(height, vector<int>(width));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (current_storage.find(storage[y][x]) == current_storage.end())
			{
				current_storage.insert({ storage[y][x], set<pair<int, int>>() });
			}

			current_storage[storage[y][x]].insert({ { x, y } });
			states[y][x] = (x == 0 || y == 0 || x == width - 1 || y == height - 1) ? 1 : 2;
		}
	}

	for (auto request : requests)
	{
		char type = request[0];
		bool is_all = request.size() != 1;

		if (current_storage.find(type) == current_storage.end()) continue;
		
		vector<pair<int, int>> removed;
		queue<pair<int, int>> bfs;

		for (pair<int, int> pos : current_storage[type])
		{
			if (is_all == false && states[pos.second][pos.first] == 2) continue;

			removed.push_back(pos);

			if (states[pos.second][pos.first] == 1)
			{
				bfs.push(pos);
			}
		}

		for (pair<int, int> pos : removed)
		{
			current_storage[type].erase(pos);
			states[pos.second][pos.first] = 0;
		}

		while (bfs.empty() != true)
		{
			pair<int, int> pos = bfs.front();
			bfs.pop();

			int state = states[pos.second][pos.first];

			switch (state)
			{
			case -1:
			case 1:
				continue;
			case 2:
				states[pos.second][pos.first] = 1;
				continue;
			}

			states[pos.second][pos.first] = -1;

			for (int dir = 0; dir < 4; dir++)
			{
				int tx = pos.first + dx[dir], ty = pos.second + dy[dir];

				if (tx < 0 || ty < 0 || tx >= width || ty >= height) continue;

				bfs.push({ tx, ty });
			}
		}
	}

	for (auto s : current_storage)
	{
		answer += s.second.size();
	}

	return answer;
}

int main()
{
	// Test case 1
	// AZWQY
	// CAABX
	// BBDDA
	// ACACA
	// Result = 11
	vector<string> storage = { "AZWQY", "CAABX", "BBDDA", "ACACA" };
	vector<string> requests = { "A", "BB", "A" };
	
	/*
	// Test case 2
	// HAH
	// HBH
	// HHH
	// HAH
	// HBH
	// Result = 4
	vector<string> storage = { "HAH", "HBH", "HHH", "HAH", "HBH" };
	vector<string> requests = { "C", "B", "B", "B", "B", "H" };
	*/

	cout << solution(storage, requests);
}