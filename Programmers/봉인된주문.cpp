#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>

#define	ALPHABET_SIZE 26

using namespace std;

// convert_stoll : 문자열이 몇번째인지 반환
// 'a' ~ 'z'를 1부터 26까지 매칭
// 26진법처럼 계산
long long convert_stoll(string target)
{
	long long result = 0;

	int size = target.size();
	for (int i = 0; i < size; i++)
	{
		int index = target[size - 1 - i] - 'a' + 1;
		result += pow(ALPHABET_SIZE, i) * index;
	}
	
	return result;
}

// convert_lltos : n번째 문자열 반환
// 26으로 나눴을 때 나머지가 0이 아니라면 'a' ~ 'y'까지 매칭
// 나머지가 0인 경우 몫에 1을 빼고 'z'를 매칭
string convert_lltos(long long target)
{
	string result = "";
	while (target >= 1)
	{
		int index = target % ALPHABET_SIZE;
		target /= ALPHABET_SIZE;

		if (index == 0)
		{
			index += ALPHABET_SIZE;
			target--;
		}
		
		result = (char)(index - 1 + 'a') + result;
	}

	return result;
}

string solution(long long n, vector<string> bans)
{
	// a ~ z : 1 ~ 26
	// aa ~ az : 27 (1 * 26 + 1) ~ 52 (1 * 26 + 26)
	// ...
	// za ~ zz : 677 (26 * 26 + 1) ~ 702 (26 * 26 + 26)
	// aaa ~ aaz : 703 (1 * 26^2 + 1 * 26 + 1) ~ 728 (1 * 26^2 + 1 * 26 + 26)
	// ...
	// zza ~ zzz : 18253 (26 * 26^2 + 26 * 26 + 1) ~ 18278 (26 * 26^2 + 26 * 26 + 26)
	vector<long long> index_bans;
	for (string ban : bans)
	{
		index_bans.push_back(convert_stoll(ban));
	}

	sort(index_bans.begin(), index_bans.end());

	for (long long index : index_bans)
	{
		if (index > n) break;

		n++;
	}

	return convert_lltos(n);
}

int main()
{
	/*
	// Test case 1
	// Result = "ah"
	long long n = 30;
	vector<string> bans = { "d", "e", "bb", "aa", "ae" };
	*/

	// Test case 2
	// Result = "jxk"
	long long n = 7388;
	vector<string> bans = { "gqk", "kdn", "jxj", "jxi", "fug", "jxg", "exq", "len", "bhc" };

	cout << solution(n, bans) << endl;

	return 0;
}