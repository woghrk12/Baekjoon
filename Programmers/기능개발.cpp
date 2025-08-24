#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds)
{
    vector<int> answer;
    int length = progresses.size();
    int cur_day = 0;
    int cnt_release = 0;

    for (int i = 0; i < length; i++)
    {
        int progress = progresses[i];
        int speed = speeds[i];

        int require_day = (int)ceil((float)(100 - progress) / speed);

        if (require_day <= cur_day)
        {
            cnt_release++;
            continue;
        }

        if (cnt_release > 0)
        {
            answer.push_back(cnt_release);
            cnt_release = 0;
        }

        cur_day = require_day;
        cnt_release++;
    }

    if (cnt_release > 0)
    {
        answer.push_back(cnt_release);
    }

    return answer;
}

int main()
{
    // Test case 1
    // Result = [2, 1]
    vector<int> answer1 = solution({93, 30, 55}, {1, 30, 5});

    // Test case 2
    // Result = [1, 3, 2]
    vector<int> answer2 = solution({95, 90, 99, 99, 80, 99}, {1, 1, 1, 1, 1, 1});

    cout << "answer 1: [ ";
    for (int i : answer1)
    {
        cout << i << " ";
    }
    cout << "]" << endl;

    cout << "answer 2: [ ";
    for (int i : answer2)
    {
        cout << i << " ";
    }
    cout << "]" << endl;
}