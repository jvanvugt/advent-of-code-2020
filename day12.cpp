#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

struct Instruction
{
    char action;
    int amount;
};

istream& operator>>(istream& in, Instruction& instruction)
{
    return in >> instruction.action >> instruction.amount;
}

int a(const vector<Instruction>& instrs)
{
    aoc::Vec2 pos(0, 0);
    int dir = 0;
    const array<aoc::Vec2, 4> dirs{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
    for (const auto& instr : instrs)
        switch (instr.action)
        {
            case 'N': pos.y -= instr.amount; break;
            case 'E': pos.x += instr.amount; break;
            case 'S': pos.y += instr.amount; break;
            case 'W': pos.x -= instr.amount; break;
            case 'R': dir = (dir + (instr.amount / 90)) % 4; break;
            case 'L': dir = (dir - (instr.amount / 90) + 4) % 4; break;
            case 'F': pos = pos + dirs[dir] * instr.amount; break;
        }
    return abs(pos.x) + abs(pos.y);
}

int b(const vector<Instruction>& instrs)
{
    auto rot90 = [](const aoc::Vec2& v, bool cw) { return cw ? aoc::Vec2{-v.y, v.x} : aoc::Vec2{v.y, -v.x}; };
    aoc::Vec2 ship(0, 0);
    aoc::Vec2 waypoint(10, -1);
    for (const auto& instr : instrs)
        switch (instr.action)
        {
            case 'N': waypoint.y -= instr.amount; break;
            case 'E': waypoint.x += instr.amount; break;
            case 'S': waypoint.y += instr.amount; break;
            case 'W': waypoint.x -= instr.amount; break;
            case 'R':
            case 'L':
                for (int _ : ranges::view::iota(0, instr.amount / 90))
                    waypoint = rot90(waypoint, instr.action == 'R');
                break;
            case 'F': ship = ship + waypoint * instr.amount; break;
        }
    return abs(ship.x) + abs(ship.y);
}

int main()
{
    ifstream file("inputs/day12.txt");
    vector<Instruction> instrs(istream_iterator<Instruction>(file), {});
    cout << a(instrs) << endl;
    cout << b(instrs) << endl;
}
