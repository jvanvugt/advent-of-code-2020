#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

u64 a(const vector<u64>& starting_numbers, u64 rounds = 2020)
{
    u64 last_spoken = 0;
    unordered_map<u64, u64> prev_spoken;
    unordered_map<u64, u64> prev_prev_spoken;
    for (u64 i = 1; i < rounds + 1; i++)
    {
        u64 to_speak = 0;
        if (i - 1 < starting_numbers.size())
            to_speak = starting_numbers[i - 1];
        else
            to_speak = prev_prev_spoken.count(last_spoken) ? prev_spoken[last_spoken] - prev_prev_spoken[last_spoken]
                                                           : 0;
        if (prev_spoken.count(to_speak))
            prev_prev_spoken[to_speak] = prev_spoken[to_speak];
        prev_spoken[to_speak] = i;
        last_spoken = to_speak;
    }
    return last_spoken;
}

u64 b(const vector<u64>& starting_numbers)
{
    return a(starting_numbers, 30000000);
}

int main()
{
    ifstream file("inputs/day15.txt");
    auto parts = aoc::split(aoc::read_file(file), ",");
    vector<u64> starting_numbers;
    for (const auto& s : parts)
        starting_numbers.push_back(stoi(s));
    cout << a(starting_numbers) << endl;
    cout << b(starting_numbers) << endl;
}
