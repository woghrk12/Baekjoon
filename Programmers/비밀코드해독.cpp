#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define LENGTH 5

using namespace std;

void generate_combination(unordered_set<string>& candidates, int n, const unordered_set<int>& contained, const unordered_set<int>& excluded)
{
	vector<int> remained;
	for (int i = 1; i <= n; i++)
	{
		if (contained.find(i) != contained.end() || excluded.find(i) != excluded.end()) continue;

		remained.push_back(i);
	}

	int size = remained.size();
	int r = 5 - contained.size();
	int combination = (1 << r) - 1;

	while (combination < (1 << size))
	{
		vector<int> v;
		for (int e : contained)
		{
			v.push_back(e);
		}

		for (int i = 0; i < size; i++)
		{
			if ((combination & (1 << i)) == 0) continue;

			v.push_back(remained[i]);
		}

		sort(v.begin(), v.end());

		string candidate;
		for (int e : v)
		{
			candidate.append(to_string(e));
		}

		if (candidates.find(candidate) == candidates.end())
		{
			candidates.insert(candidate);
		}

		if (combination == 0) break;

		int x = combination & -combination;
		int y = combination + x;
		combination = ((combination & ~y) / x >> 1) | y;
	}
}

int solution(int n, vector<vector<int>> q, vector<int> ans)
{
	int size = ans.size();
	unordered_set<int> contained, excluded;
	unordered_set<string> candidates;

	auto dfs = [&](int depth, auto&& dfs_ref) -> void
	{
		if (contained.size() > 5) return;

		if (depth == size)
		{
			generate_combination(candidates, n, contained, excluded);
			return;
		}

		// 4 C 2
		// init = (1 << 2) - 1 = 0011
		
		// combination = 0011
		// x = 0011 & 1101 = 0001
		// y = 0011 + 0001 = 0100
		// combination & ~y = 0011 & 1011 = 0011
		// (combination & ~y) / x = 0011 / 0001 = 0011
		// (combination & ~y) / x >> 1 = 0001
		// ((combination & ~y) / x >> 1) | y = 0101
		
		// 비트 마스킹으로 조합의 경우의 수 순회 (ex. ans = 2 10010, 01001, ...)
		//		1인 경우 excluded에 포함되어 있으면 리턴, 0인 경우 contained에 포함되어 있으면 리턴
		//		1인 경우 contained에 포함, 0인 경우 excluded에 포함
		//		depth++, 재귀호출
		//		원복
		int combination = (1 << ans[depth]) - 1;

		while (combination < (1 << LENGTH))
		{
			bool is_valid = true;

			for (int i = 0; i < LENGTH; i++)
			{
				int bit = combination & (1 << i);

				if (bit > 0 && excluded.find(q[depth][i]) == excluded.end()) continue;
				if (bit == 0 && contained.find(q[depth][i]) == contained.end()) continue;

				is_valid = false;
			}

			if (is_valid)
			{
				vector<int> added, removed;

				for (int i = 0; i < LENGTH; i++)
				{
					int bit = combination & (1 << i);

					if (bit > 0 && contained.find(q[depth][i]) == contained.end())
					{
						added.push_back(q[depth][i]);
					}

					if (bit == 0 && excluded.find(q[depth][i]) == excluded.end())
					{
						removed.push_back(q[depth][i]);
					}
				}

				for (int element : added)
				{
					contained.insert(element);
				}

				for (int element : removed)
				{
					excluded.insert(element);
				}

				dfs_ref(depth + 1, dfs_ref);

				for (int element : added)
				{
					contained.erase(element);
				}

				for (int element : removed)
				{
					excluded.erase(element);
				}
			}

			if (combination == 0) break;

			int x = combination & -combination;
			int y = combination + x;
			combination = ((combination & ~y) / x >> 1) | y;
		}
	};

	dfs(0, dfs);

	return candidates.size();
}

int main()
{
	int n = 10;
	vector<vector<int>> q =
	{
		{ 1, 2, 3, 4, 5 },
		{ 6, 7, 8, 9, 10 },
		{ 3, 7, 8, 9, 10 },
		{ 2, 5, 7, 9, 10 },
		{ 3, 4, 5, 6, 7 }
	};
	vector<int> ans = { 2, 3, 4, 3, 3 };
	/*

	int n = 15;
	vector<vector<int>> q =
	{
		{ 2, 3, 9, 12, 13 },
		{ 1, 4, 6, 7, 9 },
		{ 1, 2, 8, 10, 12 },
		{ 6, 7, 11, 13, 15 },
		{ 1, 4, 10, 11, 14 }
	};
	vector<int> ans = { 2, 1, 3, 0, 1 };
	*/

	cout << solution(n, q, ans) << endl;

	return 0;
}