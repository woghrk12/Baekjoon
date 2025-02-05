#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skills)
{
	int answer = 0;
	int width = board[0].size(), height = board.size();

	// skill의 갯수 : K, width : N, height : M
	// 브루트 포스로 실행할 경우 O(K * N * M)만큼의 시간이 걸림 
	// N과 M은 작지만 K의 값이 매우 크기 때문에 효율성 테스트에서 시간제한이 발생 (최악의 경우 250,000 * 1,000 * 1,000)
	// 누적합을 활용하여 O(K + N * M)으로 단축할 수 있음

	vector<vector<int>> degrees(height + 1, vector<int>(width + 1, 0));

	// 2차원 배열에 변화량 마킹 작업 : O(K)
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

	// 해당 배열에 마킹된 변화량을 누적합으로 계산 : O(2 * N * M)
	// 2차원 배열의 누적합을 계산할 땐 위에서 아래로 우선 계산을 해야 누락된 정보가 발생하지 않음
	// 위에서 아래로 계산
	for (int i = 1; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			degrees[i][j] += degrees[i - 1][j];
		}
	}
	// 왼쪽에서 오른쪽으로 계산
	for (int j = 1; j <= width; j++)
	{
		for (int i = 0; i <= height; i++)
		{
			degrees[i][j] += degrees[i][j - 1];
		}
	}

	// 마지막으로 누적합을 원본 배열에 더해 최종 결과를 산출
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