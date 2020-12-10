#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;


uint64_t a(const vector<int>& adapters)
{
    vector<uint64_t> diffs(adapters.size());
    adjacent_difference(adapters.begin(), adapters.end(), diffs.begin());
    uint64_t num_ones = 0, num_threes = 0;
    for (size_t i = 1; i < diffs.size(); i++)
        if (diffs[i] == 1)
            num_ones++;
        else if (diffs[i] == 3)
            num_threes++;
    return num_ones * num_threes;
}

uint64_t b(const vector<int>& adapters)
{
    vector<uint64_t> dp(adapters.back() + 1);
    dp[0] = 1;
    for (const int joltage : adapters)
        for (int i = joltage - 1; i > joltage - 4 && i >= 0; i--)
            dp[joltage] += dp[i];
    return dp.back();
}

int main()
{
    ifstream file("inputs/day10.txt");
    vector<int> adapters(istream_iterator<uint64_t>(file), {});
    adapters.push_back(0);
    ranges::sort(adapters);
    adapters.push_back(adapters.back() + 3);
    cout << a(adapters) << endl;
    cout << b(adapters) << endl;
}
