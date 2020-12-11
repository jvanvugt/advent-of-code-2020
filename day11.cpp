#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using NeighMap = map<aoc::Vec2, vector<aoc::Vec2>>;

NeighMap make_neighbour_map_a(const vector<string>& grid)
{
    NeighMap result;
    aoc::Vec2 grid_size(static_cast<int>(grid[0].size()), static_cast<int>(grid.size()));
    for (size_t r = 0; r < grid.size(); r++)
    {
        for (size_t c = 0; c < grid[r].size(); c++)
        {
            aoc::Vec2 pos(c, r);
            for (const auto& neigh : neighbours(pos, true))
                if (aoc::in_range(neigh, {0, 0}, grid_size))
                    result[pos].push_back(neigh);
        }
    }
    return result;
}

NeighMap make_neighbour_map_b(const vector<string>& grid)
{
    NeighMap result;
    aoc::Vec2 grid_size(static_cast<int>(grid[0].size()), static_cast<int>(grid.size()));
    for (size_t r = 0; r < grid.size(); r++)
    {
        for (size_t c = 0; c < grid[r].size(); c++)
        {
            aoc::Vec2 pos(c, r);
            for (const auto& dir : aoc::directions_diag_2)
            {
                for (int i = 1;; i++)
                {
                    auto n = pos + i * dir;
                    if (!aoc::in_range(n, {0, 0}, grid_size))
                        break;
                    if (grid[n.y][n.x] == 'L')
                    {
                        result[pos].push_back(n);
                        break;
                    }
                }
            }
        }
    }
    return result;
}

int simulate(vector<string> grid, int occ_leave, const NeighMap& neigh_map)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        auto gcopy = grid;
        for (size_t r = 0; r < grid.size(); r++)
        {
            for (size_t c = 0; c < grid[r].size(); c++)
            {
                if (grid[r][c] == '.')
                    continue;
                aoc::Vec2 pos(c, r);
                int num_occ = ranges::accumulate(
                    neigh_map.at(pos), 0, [&](int acc, const aoc::Vec2& n) { return acc + (grid[n.y][n.x] == '#'); });
                if (grid[r][c] == 'L' && num_occ == 0)
                {
                    gcopy[r][c] = '#';
                    changed = true;
                }
                else if (grid[r][c] == '#' && num_occ >= occ_leave)
                {
                    gcopy[r][c] = 'L';
                    changed = true;
                }
            }
        }
        grid = gcopy;
    }
    return ranges::accumulate(grid, 0, [](int acc, const string& row) { return acc + ranges::count(row, '#'); });
}


int a(const vector<string>& grid)
{
    const auto neigh_map = make_neighbour_map_a(grid);
    return simulate(grid, 4, neigh_map);
}


int b(const vector<string>& grid)
{
    const auto neigh_map = make_neighbour_map_b(grid);
    return simulate(grid, 5, neigh_map);
}


int main()
{
    ifstream file("inputs/day11.txt");
    vector<string> grid(istream_iterator<string>(file), {});
    cout << a(grid) << endl;
    cout << b(grid) << endl;
}
