#include <iostream>
using namespace std;

// -----------------------------
//				|		
//		1		|		2
//				|
// -----------------------------
//				|
//		3		|		4
//				|
// -----------------------------

int dc(int c, int r, int x, int y, int size)
{
	// if the size is 1, the coordinates are the target (c, r)
	if (size == 1) return 0;

	// Set the size of the square of N = K - 1
	int mid = size / 2;

	// Quadrant 1, 3
	if (c < x + mid)
	{
		// Quadrant 1
		if (r < y + mid) return dc(c, r, x, y, mid);
		// Quadrant 3
		else return mid * mid * 2 + dc(c, r, x, y + mid, mid);
	}
	// Quadrant 2, 4
	else
	{
		// Quadrant 2
		if (r < y + mid) return mid * mid * 1 + dc(c, r, x + mid, y, mid);
		// Quadrant 4
		else return mid * mid * 3 + dc(c, r, x + mid, y + mid, mid);
	}
}

int solution(int N, int r, int c)
{
	int size = 1;

	// Set the initial size
	for (int i = 0; i < N; i++)
	{
		size *= 2;
	}

	return dc(c, r, 0, 0, size);
}

int main()
{
	int N, r, c;
	
	cin >> N >> r >> c;
	
	cout << solution(N, r, c);

	return 0;
}