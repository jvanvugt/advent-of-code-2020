#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;
using namespace aoc;

using Nesting = map<string, vector<pair<string, int>>>;

Nesting parse_nesting(vector<string>& lines)
{
    Nesting can_carry;
    for (const auto& line : lines)
    {
        auto parts = aoc::split(line, ",");
        auto words = aoc::split(line, " ");
        auto bag = words[0] + " " + words[1];
        can_carry[bag].clear();
        for (const auto& part : parts)
        {
            words = aoc::split(part, " ");
            if (words[words.size() - 3] == "no")
                continue;
            can_carry[bag].push_back(
                {words[words.size() - 3] + " " + words[words.size() - 2], stoi(words[words.size() - 4])});
        }
    }
    return can_carry;
}

int count_a(const Nesting& nesting, const string& bag)
{
    if (bag == "shiny gold")
        return 1;
    return ranges::any_of(nesting.at(bag), [&](const auto& child) { return count_a(nesting, child.first); });
}

int a(Nesting& nesting)
{
    return ranges::accumulate(ranges::view::keys(nesting), -1,
                              [&](int acc, const auto& bag) { return acc + count_a(nesting, bag); });
}

int b(const Nesting& bags, const string& bag = "shiny gold")
{
    return ranges::accumulate(bags.at(bag), 0, [&](int acc, const auto& child) {
        return acc + child.second + child.second * b(bags, child.first);
    });
}

int main()
{
    ifstream file("inputs/day07.txt");
    auto lines = aoc::split(read_file(file), "\n");
    auto nesting = parse_nesting(lines);
    cout << a(nesting) << endl;
    cout << b(nesting) << endl;
}
