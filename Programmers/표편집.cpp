#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	bool is_deleted;
	int prev;
	int next;
};

string solution(int n, int k, vector<string> cmds)
{
	vector<Node> cells;
	for (int i = 0; i < n; i++)
	{
		Node cell;
		
		cell.is_deleted = false;
		cell.prev = i - 1 >= 0 ? i - 1 : -1;
		cell.next = i + 1 < n ? i + 1 : -1;

		cells.push_back(cell);
	}

	stack<int> deleted;
	for (string cmd : cmds)
	{
		switch (cmd[0])
		{
			case 'U':
			{
				int dx = stoi(cmd.substr(2));

				for (int i = 0; i < dx; i++)
				{
					k = cells[k].prev;
				}
			
				break;
			}

			case 'D':
			{
				int dx = stoi(cmd.substr(2));

				for (int i = 0; i < dx; i++)
				{
					k = cells[k].next;
				}

				break;
			}

			case 'C':
			{
				deleted.push(k);

				int prev = cells[k].prev, next = cells[k].next;

				if (prev >= 0)
				{
					cells[prev].next = next;
				}
				if (next >= 0)
				{
					cells[next].prev = prev;
				}

				cells[k].is_deleted = true;

				k = cells[k].next >= 0 ? cells[k].next : cells[k].prev;

				break;
			}

			case 'Z':
			{
				int target = deleted.top();
				deleted.pop();

				int prev = cells[target].prev, next = cells[target].next;

				if (prev >= 0)
				{
					cells[prev].next = target;
				}
				if (next >= 0)
				{
					cells[next].prev = target;
				}

				cells[target].is_deleted = false;
			
				break;
			}
		}
	}
	
	string answer;
	for (Node node : cells)
	{
		answer += node.is_deleted ? "X" : "O";
	}

	return answer;
}

int main()
{
	/*
	// Test case 1
	// Result = "OOOOXOOO"
	int n = 8, k = 2;
	vector<string> cmd = { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z" };
	*/

	// Test case 2
	// Result = "OOXOXOOO
	int n = 8, k = 2;
	vector<string> cmd = { "D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z", "U 1", "C" };

	cout << solution(n, k, cmd) << endl;

	return 0;
}