#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skills)
{
	int answer = 0;
	int width = board[0].size(), height = board.size();

	// skill�� ���� : K, width : N, height : M
	// ���Ʈ ������ ������ ��� O(K * N * M)��ŭ�� �ð��� �ɸ� 
	// N�� M�� ������ K�� ���� �ſ� ũ�� ������ ȿ���� �׽�Ʈ���� �ð������� �߻� (�־��� ��� 250,000 * 1,000 * 1,000)
	// �������� Ȱ���Ͽ� O(K + N * M)���� ������ �� ����

	vector<vector<int>> degrees(height + 1, vector<int>(width + 1, 0));

	// 2���� �迭�� ��ȭ�� ��ŷ �۾� : O(K)
	for (auto skill : skills)
	{
		int r1 = skill[1];
		int c1 = skill[2];
		int r2 = skill[3];
		int c2 = skill[4];
		int degree = (skill[0] == 1 ? -1 : 1) * skill[5];

		degrees[r1][c1] += degree;
		degrees[r1][c2 + 1] -= degree;
		degrees[r2 + 1][c2 + 1] += degree;
		degrees[r2 + 1][c1] -= degree;
	}

	// �ش� �迭�� ��ŷ�� ��ȭ���� ���������� ��� : O(2 * N * M)
	// 2���� �迭�� �������� ����� �� ������ �Ʒ��� �켱 ����� �ؾ� ������ ������ �߻����� ����
	// ������ �Ʒ��� ���
	for (int i = 1; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			degrees[i][j] += degrees[i - 1][j];
		}
	}
	// ���ʿ��� ���������� ���
	for (int j = 1; j <= width; j++)
	{
		for (int i = 0; i <= height; i++)
		{
			degrees[i][j] += degrees[i][j - 1];
		}
	}

	// ���������� �������� ���� �迭�� ���� ���� ����� ����
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] += degrees[i][j];

			if (board[i][j] > 0) answer++;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> board =
	{
		{ 5, 5, 5, 5, 5 },
		{ 5, 5, 5, 5, 5 },
		{ 5, 5, 5, 5, 5 },
		{ 5, 5, 5, 5, 5 }
	};

	vector<vector<int>> skills =
	{
		{ 1, 0, 0, 3, 4, 4 },
		{ 1, 2, 0, 2, 3, 2 },
		{ 2, 1, 0, 3, 1, 2 },
		{ 1, 0, 1, 3, 3, 1 }
	};

	cout << solution(board, skills) << endl;

	return 0;
}