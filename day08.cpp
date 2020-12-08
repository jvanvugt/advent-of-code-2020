#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

struct Computer
{
    int ip = 0;
    vector<pair<string, int>> instrs;
    int acc = 0;

    Computer(const string& program)
    {
        auto lines = aoc::split(program, "\n");
        for (const auto& line : lines)
        {
            auto parts = aoc::split(line, " ");
            instrs.emplace_back(parts[0], stoi(parts[1]));
        }
    }

    Computer(const Computer& other) : ip(other.ip), instrs(other.instrs), acc(other.acc)
    {
    }

    void exec_once()
    {
        const auto& [instr, arg] = instrs.at(ip++);
        if (instr == "nop")
        {
        }
        else if (instr == "acc")
            acc += arg;
        else if (instr == "jmp")
            ip += arg - 1;
        else
            cerr << "Invalid instruction: " << instr << " " << arg << endl;
    }

    void exec()
    {
        while (ip_is_valid())
            exec_once();
    }

    int num_instrs() const
    {
        return static_cast<int>(instrs.size());
    }

    bool ip_is_valid() const
    {
        return aoc::in_range(ip, 0, num_instrs());
    }
};


int a(Computer& computer)
{
    set<int> executed;
    while (!executed.count(computer.ip) && computer.ip_is_valid())
    {
        executed.insert(computer.ip);
        computer.exec_once();
    }
    return computer.acc;
}

int b(const Computer& computer)
{
    for (int i = 0; i < computer.num_instrs(); i++)
    {
        if (computer.instrs[i].first == "acc")
            continue;
        Computer comp(computer);
        string new_instr = computer.instrs[i].first == "jmp" ? "nop" : "jmp";
        comp.instrs[i] = {new_instr, computer.instrs[i].second};
        a(comp);
        if (comp.ip == comp.num_instrs())
            return comp.acc;
    }
    return -1;
}

int main()
{
    ifstream file("inputs/day08.txt");
    Computer computer(aoc::read_file(file));
    Computer comp_copy(computer);
    cout << a(computer) << endl;
    cout << b(comp_copy) << endl;
}
