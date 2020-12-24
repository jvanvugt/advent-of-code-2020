#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

enum class HexaDir
{
    E,
    SE,
    SW,
    W,
    NW,
    NE,
};

const array<HexaDir, 6> hexa_dirs = {HexaDir::E, HexaDir::SE, HexaDir::SW, HexaDir::W, HexaDir::NW, HexaDir::NE};

aoc::Vec2 dir_of(HexaDir dir)
{
    switch (dir)
    {
        case HexaDir::E: return {+1, 0};
        case HexaDir::SE: return {0, +1};
        case HexaDir::SW: return {-1, +1};
        case HexaDir::W: return {-1, 0};
        case HexaDir::NW: return {0, -1};
        case HexaDir::NE: return {+1, -1};
        default: return {0, 0};
    }
}

set<aoc::Vec2> initial_state(const vector<vector<HexaDir>>& instrs)
{
    set<aoc::Vec2> black_tiles;
    for (const auto& line : instrs)
    {
        aoc::Vec2 pos{0, 0};
        for (const auto dir : line)
            pos += dir_of(dir);
        if (black_tiles.count(pos))
            black_tiles.erase(pos);
        else
            black_tiles.insert(pos);
    }
    return black_tiles;
}

u64 a(const vector<vector<HexaDir>>& instrs)
{
    return initial_state(instrs).size();
}

u64 b(const vector<vector<HexaDir>>& instrs)
{
    auto black_tiles = initial_state(instrs);
    for (size_t i = 0; i < 100; i++)
    {
        auto new_black_tiles = black_tiles;
        set<aoc::Vec2> considered;
        for (const auto& active_pos : black_tiles)
        {
            vector<aoc::Vec2> neighs;
            for (HexaDir dir : hexa_dirs)
                neighs.push_back(active_pos + dir_of(dir));
            neighs.push_back(active_pos);
            for (const auto& loc : neighs)
            {
                if (considered.count(loc))
                    continue;
                considered.insert(loc);
                bool is_black = black_tiles.count(loc);
                int num_neighs = ranges::accumulate(
                    hexa_dirs, 0, [&](int acc, auto dir) { return acc + black_tiles.count(loc + dir_of(dir)); });
                if (is_black && (num_neighs == 0 || num_neighs > 2))
                    new_black_tiles.erase(loc);
                else if (!is_black && num_neighs == 2)
                    new_black_tiles.insert(loc);
            }
        }
        black_tiles = new_black_tiles;
    }

    return black_tiles.size();
}

int main()
{
    ifstream file("inputs/day24.txt");
    vector<string> lines(istream_iterator<string>(file), {});
    vector<vector<HexaDir>> instrs;
    for (const auto& line : lines)
    {
        vector<HexaDir> l;
        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == 'e')
                l.push_back(HexaDir::E);
            else if (line[i] == 'w')
                l.push_back(HexaDir::W);
            else
            {
                if (line[i] == 'n' && line[i + 1] == 'e')
                    l.push_back(HexaDir::NE);
                else if (line[i] == 'n' && line[i + 1] == 'w')
                    l.push_back(HexaDir::NW);
                else if (line[i] == 's' && line[i + 1] == 'e')
                    l.push_back(HexaDir::SE);
                else if (line[i] == 's' && line[i + 1] == 'w')
                    l.push_back(HexaDir::SW);
                i++;
            }
        }
        instrs.push_back(l);
    }
    cout << a(instrs) << endl;
    cout << b(instrs) << endl;
    return 0;
}
