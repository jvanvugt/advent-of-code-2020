#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using Tile = vector<string>;
using Tiles = map<int, Tile>;

bool fits_top(const Tile& ref_tile, const Tile& to_fit_tile)
{
    const size_t S = ref_tile.size();
    for (size_t i = 0; i < S; i++)
        if (ref_tile[0][i] != to_fit_tile[S - 1][i])
            return false;
    return true;
}

bool fits_bot(const Tile& ref_tile, const Tile& to_fit_tile)
{
    return fits_top(to_fit_tile, ref_tile);
}

bool fits_left(const Tile& ref_tile, const Tile& to_fit_tile)
{
    const size_t S = ref_tile.size();
    for (size_t i = 0; i < S; i++)
        if (ref_tile[i][0] != to_fit_tile[i][S - 1])
            return false;
    return true;
}

bool fits_right(const Tile& ref_tile, const Tile& to_fit_tile)
{
    return fits_left(to_fit_tile, ref_tile);
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
    const size_t S = tile.size();
    Tile result = tile;
    for (size_t row = 0; row < S; row++)
        for (size_t col = 0; col < S; col++)
            result[col][S - row - 1] = tile[row][col];
    return result;
}

const array<function<Tile(const Tile&)>, 8> transformations = {
    [](const Tile t) { return t; },
    flipud,
    fliplr,
    rot90,
    [](const Tile& t) { return fliplr(flipud(t)); },
    [](const Tile& t) { return rot90(flipud(t)); },
    [](const Tile& t) { return rot90(fliplr(t)); },
    [](const Tile& t) { return rot90(fliplr(flipud(t))); },
};

void solve(const Tiles& tiles,
           map<aoc::Vec2, pair<int, size_t>>& full_image,
           const aoc::Vec2& curpos,
           set<int>& used_ids)
{
    if (used_ids.size() == tiles.size())
        return;
    const auto [tile_id, transform_idx] = full_image.at(curpos);
    const Tile& cur_tile = transformations[transform_idx](tiles.at(tile_id));
    const array<aoc::Vec2, 4> directions{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
    const array<function<bool(const Tile&, const Tile&)>, 4> checks{{fits_right, fits_bot, fits_left, fits_top}};
    for (size_t d = 0; d < 4; d++)
    {
        auto neigh = curpos + directions[d];
        const auto& check_fn = checks[d];
        if (full_image.count(neigh))
            continue;
        bool found = false;
        for (const auto& [other_id, other_tile] : tiles)
        {
            if (used_ids.count(other_id))
                continue;
            for (size_t t_idx = 0; t_idx < transformations.size(); t_idx++)
            {
                if (check_fn(cur_tile, transformations[t_idx](other_tile)))
                {
                    full_image[neigh] = {other_id, t_idx};
                    used_ids.insert(other_id);
                    found = true;
                    solve(tiles, full_image, neigh, used_ids);
                    break;
                }
            }
            if (found)
                break;
        }
    }
}

vector<vector<pair<u64, size_t>>> create_grid(const Tiles& tiles)
{
    map<aoc::Vec2, pair<int, size_t>> full_image;
    int first_id = tiles.begin()->first;
    full_image[{0, 0}] = {first_id, 0};
    set<int> used{{first_id}};
    solve(tiles, full_image, {0, 0}, used);
    aoc::Vec2 min_coords{0, 0};
    aoc::Vec2 max_coords{0, 0};
    for (const auto& pos : ranges::view::keys(full_image))
    {
        min_coords.x = min(min_coords.x, pos.x);
        min_coords.y = min(min_coords.y, pos.y);
        max_coords.x = max(max_coords.x, pos.x);
        max_coords.y = max(max_coords.y, pos.y);
    }
    int grid_size = sqrt(tiles.size());
    vector<vector<pair<u64, size_t>>> grid(grid_size, vector<pair<u64, size_t>>(grid_size));
    for (const auto& pos : ranges::view::keys(full_image))
    {
        auto c = pos - min_coords;
        grid[c.y][c.x] = {full_image[pos].first, full_image[pos].second};
    }
    return grid;
}

u64 a(const Tiles& tiles)
{
    auto grid = create_grid(tiles);
    auto n = grid.size() - 1;
    return grid[0][0].first * grid[n][0].first * grid[0][n].first * grid[n][n].first;
}

u64 b(Tiles tiles)
{
    auto grid = create_grid(tiles);
    for (size_t x = 0; x < grid.size(); x++)
    {
        for (size_t y = 0; y < grid.size(); y++)
        {
            const auto [tile_id, trans_id] = grid[y][x];
            tiles[tile_id] = transformations[trans_id](tiles.at(tile_id));
        }
    }

    const size_t S = tiles.begin()->second.size();
    const size_t N = S - 2;
    auto grid_size = grid.size() * N;
    Tile image(grid_size, string(grid_size, '%'));
    for (size_t row = 0; row < grid_size; row++)
    {
        for (size_t col = 0; col < grid_size; col++)
        {
            size_t grid_y = row / N;
            size_t grid_x = col / N;
            size_t tile_y = row % N;
            size_t tile_x = col % N;
            image[row][col] = tiles.at(grid[grid_y][grid_x].first)[tile_y + 1][tile_x + 1];
        }
    }
    vector<string> sea_monster{
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   ",
    };
    vector<aoc::Vec2> sea_monster_coords;
    for (size_t y = 0; y < sea_monster.size(); y++)
        for (size_t x = 0; x < sea_monster[0].size(); x++)
            if (sea_monster[y][x] == '#')
                sea_monster_coords.push_back({static_cast<int>(x), static_cast<int>(y)});

    for (const auto& transform : transformations)
    {
        bool found = false;
        auto t_image = transform(image);
        for (size_t row = 0; row < image.size() - sea_monster.size(); row++)
        {
            for (size_t col = 0; col < image.size() - sea_monster[0].size(); col++)
            {
                if (ranges::all_of(sea_monster_coords,
                                   [&](const auto& o) { return t_image[row + o.y][col + o.x] == '#'; }))
                {
                    found = true;
                    for (const auto& offset : sea_monster_coords)
                    {
                        auto v = aoc::Vec2{static_cast<int>(col), static_cast<int>(row)} + offset;
                        t_image[v.y][v.x] = 'O';
                    }
                }
            }
        }
        if (found)
        {
            image = t_image;
            break;
        }
    }
    return ranges::accumulate(image, 0ull, [](u64 acc, const string& s) { return acc + ranges::count(s, '#'); });
}

int main()
{
    ifstream file("inputs/day20.txt");
    auto ids_and_tiles = aoc::split(aoc::read_file(file), "\n\n");
    Tiles tiles;
    for (const auto& id_and_tile : ids_and_tiles)
    {
        auto lines = aoc::split(id_and_tile, "\n");
        int id = stoi(aoc::split(lines[0], " ")[1]);
        lines.erase(lines.begin());
        tiles[id] = lines;
    }
    cout << a(tiles) << endl;
    cout << b(tiles) << endl;
}
