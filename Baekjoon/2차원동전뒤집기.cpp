#include <iostream>
#include <vector>
#include <string>

using namespace std;

void flip_column(int target_column, vector<vector<int>>& board)
{
	int row_size = board[target_column].size();

	for (int i = 0; i < row_size; i++)
	{
		board[target_column][i] = 1 - board[target_column][i];
	}
}

void flip_row(int target_row, vector<vector<int>>& board)
{
	int column_size = board.size();

	for (int i = 0; i < column_size; i++)
	{
		board[i][target_row] = 1 - board[i][target_row];
	}
}

bool is_equal(const vector<vector<int>>& board, const vector<vector<int>>& target)
{
	int row_size = board.size(), column_size = board[0].size();

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < column_size; j++)
		{
			if (board[i][j] != target[i][j]) return false;
		}
	}

	return true;
}

int solution(vector<vector<int>> beginning, vector<vector<int>> target)
{
	int answer = -1;
	int column_size = beginning.size(), row_size = beginning[0].size();

	if (column_size <= row_size)
	{
		for (int column_mask = 0; column_mask < (1 << column_size); column_mask++)
		{
			int cnt = 0;
			vector<vector<int>> board(beginning);

			for (int i = 0; i < column_size; i++)
			{
				if ((column_mask & (1 << i)) == 0) continue;

				flip_column(i, board);
				cnt++;
			}

			for (int i = 0; i < row_size; i++)
			{
				if (board[0][i] == target[0][i]) continue;

				flip_row(i, board);
				cnt++;
			}

			answer = is_equal(board, target) ? (answer >= 0 ? min(answer, cnt) : cnt) : answer;
		}
	}
	else
	{
		for (int row_mask = 0; row_mask < (1 << row_size); row_mask++)
		{
			int cnt = 0;
			vector<vector<int>> board(beginning);

			for (int i = 0; i < row_size; i++)
			{
				if ((row_mask & (1 << i)) == 0) continue;

				flip_row(i, board);
				cnt++;
			}

			for (int i = 0; i < column_size; i++)
			{
				if (board[i][0] == target[i][0]) continue;

				flip_column(i, board);
				cnt++;
			}

			answer = is_equal(board, target) ? (answer >= 0 ? min(answer, cnt) : cnt) : answer;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> beginning =
	{
		{0, 1, 0, 0, 0},
		{1, 0, 1, 0, 1},
		{0, 1, 1, 1, 0},
		{1, 0, 1, 1, 0},
		{0, 1, 0, 1, 0}
	};

	vector<vector<int>> target =
	{
		{0, 0, 0, 1, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 1, 0, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 1}
	};
	
	cout << solution(beginning, target);

	return 0;
}