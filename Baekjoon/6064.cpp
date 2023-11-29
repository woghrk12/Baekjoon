#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	if (b == 0) return a;

	return gcd(b, a % b);
}

int solution(int M, int N, int x, int y)
{
	int answer = -1;
	// Repeat with a period equal to the LCM of M and N
	int max = M * N / gcd(M, N);

	// x and y are the remainders when divided by M and N
	for (int i = x; i <= max; i += M)
	{
		int ty = i % N;

		// if the remainder is 0, the value needs to be fixed because the calendar starts from 1
		if (ty == 0) ty += N;
		if (ty == y)
		{
			answer = i;
			break;
		}
	}

	return answer;
}

int main()
{
	int T, M, N, x, y;
	
	cin >> T;
	
	for (int i = 0; i < T; i++)
	{
		cin >> M >> N >> x >> y;
		cout << solution(M, N, x, y) << endl;
	}
	
	return 0;
}