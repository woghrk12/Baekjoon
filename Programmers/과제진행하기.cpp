#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_TIME 100000

struct Plan
{
    string name;
    int start;
    int during;
};

int convertTimeToInt(string input)
{
    return stoi(input.substr(0, 2)) * 60 + stoi(input.substr(3, 2));
}

vector<string> solution(vector<vector<string>> plans)
{
    vector<string> answer;
    vector<Plan> sorted_plans;
    vector<Plan> remain_plans;

    sort(plans.begin(), plans.end(), [](vector<string> a, vector<string> b)
         { return a[1] < b[1]; });

    for (vector<string> plan : plans)
    {
        sorted_plans.push_back({plan[0], convertTimeToInt(plan[1]), stoi(plan[2])});
    }

    int curTime = 0;
    int length = sorted_plans.size();
    for (int i = 0; i < length; i++)
    {
        Plan curPlan = sorted_plans[i];
        int deadline = i + 1 < length ? sorted_plans[i + 1].start : MAX_TIME;

        curTime = curPlan.start;

        if (curTime + curPlan.during > deadline)
        {
            curPlan.during = curTime + curPlan.during - deadline;
            remain_plans.push_back(curPlan);
            continue;
        }

        curTime += curPlan.during;
        answer.push_back(curPlan.name);

        while (!remain_plans.empty())
        {
            Plan &remain = remain_plans.back();

            if (curTime + remain.during > deadline)
            {
                remain.during = curTime + remain.during - deadline;
                break;
            }

            curTime += remain.during;
            answer.push_back(remain.name);
            remain_plans.pop_back();
        }
    }

    return answer;
}

int main()
{
    // ["korean", "english", math"]
    vector<string> answer1 = solution({{"korean", "11:40", "30"}, {"english", "12:10", "20"}, {"math", "12:30", "40"}});
    // ["science", "history", "computer", "music"]
    vector<string> answer2 = solution({{"science", "12:40", "50"}, {"music", "12:20", "40"}, {"history", "14:00", "30"}, {"computer", "12:30", "100"}});
    // ["bbb", "ccc", "aaa"]
    vector<string> answer3 = solution({{"aaa", "12:00", "20"}, {"bbb", "12:10", "30"}, {"ccc", "12:40", "10"}});

    vector<string> answer4 = solution({{"A", "00:00", "60"}, {"B", "00:10", "60"}, {"C", "00:20", "60"}, {"D", "02:20", "60"}, {"E", "03:20", "10"}, {"F", "03:40", "20"}, {"G", "04:40", "60"}});

    cout << "answer1: ";
    for (auto s : answer1)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "answer2: ";
    for (auto s : answer2)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "answer3: ";
    for (auto s : answer3)
    {
        cout << s << " ";
    }
    cout << endl;

    cout << "answer4: ";
    for (auto s : answer4)
    {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}