#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<vector<int>, vector<int>>> pair_list;

void make_list(int depth, int count, vector<int> a_dice_list, vector<int> b_dice_list)
{
	if (depth == count)
	{
		pair_list.push_back({ a_dice_list, b_dice_list });
		return;
	}

	if (a_dice_list.size() < count / 2)
	{
		a_dice_list.push_back(depth);
		make_list(depth + 1, count, a_dice_list, b_dice_list);
		a_dice_list.pop_back();
	}
	if (b_dice_list.size() < count / 2)
	{
		b_dice_list.push_back(depth);
		make_list(depth + 1, count, a_dice_list, b_dice_list);
		b_dice_list.pop_back();
	}
}

vector<int> calculation_sum(vector<int> index_list, vector<vector<int>> dice)
{
	vector<int> result;
	int size = index_list.size();

	auto dfs = [&](int depth, int count, int sum, auto&& dfs_ref)
	{
		if (depth == count)
		{
			result.push_back(sum);
			return;
		}

		for (int face : dice[index_list[depth]])
		{
			dfs_ref(depth + 1, count, sum + face, dfs_ref);
		}
	};

	dfs(0, size, 0, dfs);

	sort(result.begin(), result.end());

	return result;
}

int calculation_portion(int index, vector<vector<int>> dice)
{
	int cnt_win = 0;
	vector<int> a_sum_list, b_sum_list;
	vector<int> a_index_list = pair_list[index].first;
	vector<int> b_index_list = pair_list[index].second;
	int size = dice.size() / 2;

	a_sum_list = calculation_sum(a_index_list, dice);
	b_sum_list = calculation_sum(b_index_list, dice);
	int cnt_case = a_sum_list.size();
	int a_index = 0, b_index = 0;

	while (a_index < cnt_case && b_index < cnt_case)
	{
		if (a_sum_list[a_index] <= b_sum_list[b_index])
		{
			cnt_win += b_index;
			a_index++;
			continue;
		}

		b_index++;
	}

	if (a_index < cnt_case)
	{
		cnt_win += cnt_case * (cnt_case - a_index);
	}

	return cnt_win;
}

vector<int> solution(vector<vector<int>> dice)
{
	vector<int> answer;
	vector<int> a_dice_list, b_dice_list;

	// 1. A와 B가 주사위를 나눠 가진다.
	make_list(0, dice.size(), a_dice_list, b_dice_list);

	// 2. 나눠 가진 주사위에 따라 A가 승리할 확률(승리한 횟수로 대체)을 구한다.
	int max_cnt = 0;
	for (int i = 0; i < pair_list.size(); i++)
	{
		int result = calculation_portion(i, dice);
		if (max_cnt >= result) continue;

		// 3. 승리할 확률이 가장 높은 케이스를 리턴한다.
		max_cnt = result;

		answer.clear();
		for (auto index : pair_list[i].first)
		{
			answer.push_back(index + 1);
		}
	}

	return answer;
}

int main()
{
	int n;
	vector<vector<int>> dice;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		vector<int> v;

		for (int j = 0; j < 6; j++)
		{
			int t;
			cin >> t;
			v.push_back(t);
		}

		dice.push_back(v);
	}

	vector<int> answer = solution(dice);
	for (auto a : answer)
	{
		cout << a << endl;
	}

	return 0;
}