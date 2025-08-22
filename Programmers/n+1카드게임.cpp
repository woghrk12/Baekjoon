#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int solution(int coin, vector<int> cards)
{
	int answer = 1;
	int size = cards.size();
	int target = size + 1;

	queue<int> deck;
	for (int card : cards)
	{
		deck.push(card);
	}

	set<int> hands;
	int hand_pairs = 0;
	set<int> spares;
	int spare_pairs = 0;

	for (int i = 0; i < size / 3; i++)
	{
		int card = deck.front();
		deck.pop();

		if (hands.find(target - card) != hands.end())
		{
			hands.erase(target - card);
			hand_pairs++;
		}
		else
		{
			hands.insert(card);
		}
	}

	while (!deck.empty())
	{
		for (int i = 0; i < 2; i++)
		{
			int card = deck.front();
			deck.pop();

			if (hands.find(target - card) != hands.end() && coin > 0)
			{
				coin -= 1;
				hand_pairs++;

				continue;
			}

			if (spares.find(target - card) != spares.end())
			{
				spare_pairs++;
				continue;
			}

			spares.insert(card);
		}

		if (hand_pairs == 0)
		{
			if (spare_pairs == 0) break;
			if (coin <= 1) break;

			spare_pairs--;
			coin -= 2;
		}
		else
		{
			hand_pairs--;
		}

		answer++;
	}

	return answer;
}

int main()
{
	int n, coin;
	vector<int> cards;

	cin >> n >> coin;

	for (int i = 0; i < n; i++)
	{
		int card;
		cin >> card;
		cards.push_back(card);
	}

	cout << solution(coin, cards) << endl;

	return 0;
}