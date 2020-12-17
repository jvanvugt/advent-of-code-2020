#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

template <typename VEC>
int simulate(const vector<string>& initial_state)
{
    set<VEC> active;
    for (int i = 0; i < static_cast<int>(initial_state.size()); i++)
        for (int j = 0; j < static_cast<int>(initial_state[i].size()); j++)
            if (initial_state[i][j] == '#')
                active.insert({j, i, 0});

    for (int i = 0; i < 6; i++)
    {
        set<VEC> new_active;
        set<VEC> considered;
        for (const auto& active_loc : active)
        {
            auto neighs = aoc::neighbours(active_loc, true);
            neighs.push_back(active_loc);
            for (const auto& loc : neighs)
            {
                if (considered.count(loc))
                    continue;
                considered.insert(loc);
                bool state = active.count(loc);
                int neigh_count = ranges::accumulate(aoc::neighbours(loc, true), 0, [&](int acc, const auto& neigh) {
                    return acc + active.count(neigh);
                });
                if ((state && (neigh_count == 2 || neigh_count == 3)) || (!state && neigh_count == 3))
                    new_active.insert(loc);
            }
        }
        active = new_active;
    }
    return active.size();
}

int main()
{
    ifstream file("inputs/day17.txt");
    vector<string> initial_state(istream_iterator<string>(file), {});
    cout << simulate<aoc::Vec3>(initial_state) << endl;
    cout << simulate<aoc::Vec4>(initial_state) << endl;
}
