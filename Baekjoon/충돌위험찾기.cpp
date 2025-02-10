#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int solution(vector<vector<int>> points, vector<vector<int>> routes)
{
	int answer = 0;
	map<int, map<pair<int, int>, int>> paths;
	for (vector<int> route : routes)
	{
		int length = route.size();
		int time = 0;
		int cur_r, cur_c;

		for (int i = 0; i < length - 1; i++)
		{
			int start = route[i], end = route[i + 1];
			int r_start = points[start - 1][0], c_start = points[start - 1][1];
			int r_end = points[end - 1][0], c_end = points[end - 1][1];

			cur_r = r_start;
			cur_c = c_start;
			
			int r_dir = r_start < r_end ? 1 : -1;
			int c_dir = c_start < c_end ? 1 : -1;

			// row 방향 이동
			for (int i = 0; i < abs(r_start - r_end); i++)
			{
				if (paths.find(time) == paths.end())
				{
					paths.insert({ time, map<pair<int, int>, int>() });
				}

				if (paths[time].find({ cur_r, cur_c }) == paths[time].end())
				{
					paths[time].insert({ { cur_r, cur_c }, 1 });
				}
				else
				{
					paths[time][{ cur_r, cur_c }]++;
				}
				
				cur_r += r_dir;
				time++;
			}

			// column 방향 이동
			for (int i = 0; i < abs(c_start - c_end); i++)
			{
				if (paths.find(time) == paths.end())
				{
					paths.insert({ time, map<pair<int, int>, int>() });
				}

				if (paths[time].find({ cur_r, cur_c }) == paths[time].end())
				{
					paths[time].insert({ { cur_r, cur_c }, 1 });
				}
				else
				{
					paths[time][{ cur_r, cur_c }]++;
				}

				cur_c += c_dir;
				time++;
			}
		}

		if (paths[time].find({ cur_r, cur_c }) == paths[time].end())
		{
			paths[time].insert({ { cur_r, cur_c }, 1 });
		}
		else
		{
			paths[time][{ cur_r, cur_c }]++;
		}
	}

	int cnt_robot = routes.size();
	for (auto path : paths)
	{
		for (auto pos : path.second)
		{
			if (pos.second == 1) continue;

			answer++;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> points =
	{
		{ 2, 2 },
		{ 2, 3 },
		{ 2, 7 },
		{ 6, 6 },
		{ 5, 2 }
	};
	vector<vector<int>> routes =
	{
		{ 2, 3, 4, 5 },
		{ 1, 3, 4, 5 },
	};
	
	cout << solution(points, routes) << endl;

	return 0;
}