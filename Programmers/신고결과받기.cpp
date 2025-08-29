#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
    int length = id_list.size();

    vector<int> answer(length, 0);

    map<string, int> index_map;
    map<string, set<string>> report_map;
    map<string, int> cnt_reported;

    for (int i = 0; i < length; i++)
    {
        string id = id_list[i];

        index_map.insert({id, i});
        report_map.insert({id, set<string>()});
    }

    for (string r : report)
    {
        string sep = " ";
        int pos = r.find(sep, 0);
        string reporter = r.substr(0, pos);
        string reported = r.substr(pos + 1);

        if (report_map[reporter].find(reported) != report_map[reporter].end())
            continue;

        report_map[reporter].insert(reported);
        if (cnt_reported.find(reported) == cnt_reported.end())
        {
            cnt_reported.insert({reported, 1});
        }
        else
        {
            cnt_reported[reported]++;
        }
    }

    for (auto pair : report_map)
    {
        int cnt = 0;

        for (string reported : pair.second)
        {
            if (cnt_reported.find(reported) == cnt_reported.end() || cnt_reported[reported] < k)
                continue;

            cnt++;
        }

        answer[index_map[pair.first]] = cnt;
    }

    return answer;
}

int main()
{
    // Test case 1
    // Result = [2, 1, 1, 0]
    vector<int> result1 = solution({"muzi", "frodo", "apeach", "neo"}, {"muzi frodo", "apeach frodo", "frodo neo", "muzi neo", "apeach muzi"}, 2);

    // Test case 2
    // Result = [0, 0]
    vector<int> result2 = solution({"con", "ryan"}, {"ryan con", "ryan con", "ryan con", "ryan con"}, 3);

    cout << "result 1: [ ";
    for (int i : result1)
    {
        cout << i << " ";
    }
    cout << "]" << endl;

    cout << "result 2: [ ";
    for (int i : result2)
    {
        cout << i << " ";
    }
    cout << "]" << endl;
}