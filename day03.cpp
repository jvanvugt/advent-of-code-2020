#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;

int a(const vector<string>& trees, int slope_x, int slope_y)
{
    int num_trees = 0;
    for (size_t xpos = 0, ypos = 0; ypos < trees.size(); ypos += slope_y, xpos += slope_x)
        num_trees += trees[ypos][xpos % trees[ypos].size()] == '#';
    return num_trees;
}

int b(const vector<string>& trees)
{
    array<pair<int, int>, 5> slopes{{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};
    auto num_trees = slopes | ranges::views::transform([&](const auto& s) { return a(trees, s.first, s.second); });
    return ranges::accumulate(num_trees, 1, multiplies<>());
}

int main()
{
    ifstream file("inputs/day03.txt");
    vector<string> trees(istream_iterator<string>{file}, istream_iterator<string>{});
    cout << a(trees, 3, 1) << "\n" << b(trees) << endl;
}
