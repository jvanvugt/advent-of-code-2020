#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

u64 a(vector<int> cups, int moves = 100)
{
    vector<int> taken;
    for (int m = 0; m < moves; m++)
    {
        taken.clear();
        for (int i = 1; i < 4; i++)
            taken.push_back(cups.at(i));
        cups.erase(cups.begin() + 1, cups.begin()+4);
        int look_for = cups[0] - 1;
        while(true)
        {
            auto it = ranges::find(cups, look_for);
            if (it != cups.end())
            {
                cups.insert(it + 1, taken.begin(), taken.end());
                break;
            }
            look_for--;
            if (look_for < 0)
                look_for += cups.size() + 4;
        }
        rotate(cups.begin(), cups.begin() + 1, cups.end());
    }
    u64 answer = 0;
    auto one_pos = distance(cups.begin(), find(cups.begin(), cups.end(), 1));
    for (size_t i = 0; i < cups.size() - 1; i++)
        answer = answer * 10 + cups.at((i + one_pos + 1) % cups.size());
    return answer;
}

u64 b(vector<int> cups_v, u64 moves = 10'000'000ull)
{
    constexpr int max_num = 1'000'001;
    for (int i = 10; i < max_num; i++)
        cups_v.push_back(i);
    forward_list<int> cups(cups_v.begin(), cups_v.end());
    vector<decltype(cups)::iterator> index(max_num);
    for (auto i = cups.begin(); i != cups.end(); i++)
        index[*i] = i;

    vector<int> taken;
    auto current = cups.begin();
    for (u64 m = 0; m < moves; m++)
    {
        taken.clear();
        auto one_before_take = current;
        for (int i = 0; i < 3; i++)
        {
            auto to_take = next(one_before_take, 1);
            if (to_take == cups.end())
            {
                to_take = cups.begin();
                one_before_take = cups.before_begin();
            }
            taken.push_back(*to_take);
            cups.erase_after(one_before_take);
        }

        int look_for = *current;
        auto to_place = current;
        do {
            look_for = look_for - 1;
            if (look_for < 1)
                look_for += max_num - 1;
            if (find(taken.begin(), taken.end(), look_for) != taken.end())
                continue;
            to_place = index.at(look_for);
            break;
        } while(true);

        cups.insert_after(to_place, taken.begin(), taken.end());
        to_place++;
        for (int i = 0; i < 3; i++, to_place++)
            index[*to_place] = to_place;
        current++;
        if (current == cups.end())
            current = cups.begin();
    }

    auto one_after = next(index[1], 1);
    if (one_after == cups.end())
        one_after = cups.begin();
    auto two_after = next(one_after, 1);
    if (two_after == cups.end())
        two_after = cups.begin();
    return static_cast<u64>(*one_after) * static_cast<u64>(*two_after);
}

int main()
{
    string order = "583976241";
    vector<int> cups;
    for (char c : order)
        cups.push_back(c - '0');
    cout << a(cups) << endl;
    cout << b(cups) << endl;
    return 0;
}
