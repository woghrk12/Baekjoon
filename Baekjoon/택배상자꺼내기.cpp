#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(int n, int w, int num)
{
	int h = (n - 1) / w + 1;
	int target_row = (num - 1) / w + 1;

	int target_direction = (target_row % 2) == 1 ? 1 : -1;
	int top_direction = (h % 2) == 1 ? 1 : -1;

	int target_left = target_direction == 1 ? (target_row - 1) * w + 1 : target_row* w;
	int top_left = top_direction == 1 ? (h - 1) * w + 1 : h * w;

	int offset = target_direction == 1 ? num - target_left : target_left - num;
	int top_element = top_direction == 1 ? top_left + offset : top_left - offset;

	return h - target_row + (top_element <= n ? 1 : 0);
}

int main()
{
	// Test case 1
	// .	.	22	21	20	19		.	.	21	20	19	18
	// 13	14	15	16	17	18	->	12	13	14	15	16	17
	// 12	11	10	9	8	7		11	10	9	8	7	6
	// 1	2	3	4	5	6		0	1	2	3	4	5
	// Result = 3
	// int n = 22, w = 6, num = 8;

	// Test case 2
	// Result = 4
	int n = 13, w = 3, num = 6;

	cout << solution(n, w, num) << endl;

	return 0;
}