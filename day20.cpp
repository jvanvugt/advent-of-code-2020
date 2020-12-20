#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using Tile = vector<string>;
using Tiles = map<int, Tile>;

constexpr size_t S = 10;

bool fits_top(const Tile& ref_tile, const Tile& to_fit_tile)
{
    for (size_t i = 0; i < S; i++)
        if (ref_tile[0][i] != to_fit_tile[S-1][i])
            return false;
    return true;
}

bool fits_left(const Tile& ref_tile, const Tile& to_fit_tile)
{
    for (size_t i = 0; i < S; i++)
        if (ref_tile[i][0] != to_fit_tile[i][S-1])
            return false;
    return true;
}

Tile flipud(const Tile& tile)
{
    return Tile(tile.rbegin(), tile.rend());
}

Tile fliplr(const Tile& tile)
{
    Tile result = tile;
    ranges::for_each(result, [](string& row) { ranges::reverse(row); });
    return result;
}

Tile rot90(const Tile& tile)
{
    Tile result = tile;
    for (size_t row = 0; row < S; row++)
        for (size_t col = 0; col < S; col++)
            result[col][S - row - 1] = tile[row][col];
    return result;
}

vector<function<Tile(const Tile&)>> get_transformations()
{
    return {
        [](const Tile t) { return t; },
        flipud,
        fliplr,
        rot90,
        [](const Tile& t) { return flipud(fliplr(t)); },
        [](const Tile& t) { return flipud(rot90(t)); },
        [](const Tile& t) { return fliplr(flipud(rot90(t))); },
    };
}

u64 a(const Tiles& tiles)
{
    map<int, map<char, vector< pair<int, int>> >> fits;
    const auto transformations = get_transformations();
    for (const auto& [id, tile] : tiles)
    {
        for (const auto& [other_id, other_tile] : tiles)
        {
            if (id == other_id) continue;

            for (size_t t_id = 0; t_id < transformations.size(); t_id++)
            {
                const auto transformed_other = transformations[t_id](other_tile);
                if (fits_left(tile, transformed_other)) fits[id]['L'].push_back({other_id, t_id});
                if (fits_top(tile, transformed_other)) fits[id]['T'].push_back({other_id, t_id});
                if (fits_left(transformed_other, tile))
                {
                    if (id == 1171) cout << other_id << ", T: " << t_id << endl;
                    fits[id]['R'].push_back({other_id, t_id});
                }
                if (fits_top(transformed_other, tile)) fits[id]['D'].push_back({other_id, t_id});
            }
        }
    }
    u64 result = 1;
    int num_twos = 0;
    for (const auto& [id, fitters] : fits)
    {
        int num_neighs = ranges::accumulate(ranges::view::values(fitters), 0, [](int acc, const auto& x) { return acc + x.size(); });
        cout << num_neighs << endl;
        if (num_neighs == 2)
        {
            num_twos++;
            result *= id;
        }

        cout << id << endl;
        for (const auto& [dir, x] : fitters)
        {
            cout << dir << ": " << x.size() << endl;
        }
        cout << "--------------------" << endl;
    }
    cout << num_twos << endl;
    return result;
}

int main()
{
    ifstream file("inputs/day20.txt");
    auto ids_and_tiles = aoc::split(aoc::read_file(file), "\n\n");
    Tiles tiles;
    for (const auto& id_and_tile: ids_and_tiles)
    {
        auto lines = aoc::split(id_and_tile, "\n");
        int id  = stoi(aoc::split(lines[0], " ")[1]);
        lines.erase(lines.begin());
        tiles[id] = lines;
    }
    cout << a(tiles) << endl;
    // cout << b(rules, messages) << endl;
}
