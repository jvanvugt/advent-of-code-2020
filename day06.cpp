#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;


int main()
{
    ifstream file("inputs/day06.txt");
    string line;
    set<int> answered;
    map<char, int> answered_b;
    int answer_a = 0, answer_b = 0, group_size = 0;
    while (getline(file, line))
    {
        if (!line.length())
        {
            answer_a += answered.size();
            answer_b += ranges::accumulate(ranges::view::values(answered_b), 0,
                                           [&](int acc, int cnt) { return acc + (cnt == group_size); });
            answered.clear();
            answered_b.clear();
            group_size = 0;
            continue;
        }
        for (char c : line)
        {
            answered.insert(c);
            answered_b[c]++;
        }
        group_size++;
    }
    answer_a += answered.size();
    answer_b += ranges::accumulate(ranges::view::values(answered_b), 0,
                                   [&](int acc, int cnt) { return acc + (cnt == group_size); });

    cout << answer_a << endl;
    cout << answer_b << endl;
}
