#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

constexpr int BITS = 36;

u64 a(const vector<string>& lines)
{
    map<int, bitset<BITS>> memory;
    string mask;
    for (const auto& line : lines)
    {
        auto parts = aoc::split(line, " = ");
        if (parts[0] == "mask")
            mask = parts[1];
        else
        {
            auto start = parts[0].find('[') + 1;
            auto end = parts[0].find(']');
            auto mem_addr = stoi(parts[0].substr(start, end));
            auto value = bitset<BITS>(stoi(parts[1]));
            for (size_t i = 0; i < BITS; i++)
                if (mask[BITS - i - 1] != 'X')
                    value[i] = mask[BITS - i - 1] == '1';
            memory[mem_addr] = value;
        }
    }
    auto nums = ranges::view::values(memory) | ranges::view::transform([](const auto bs) { return bs.to_ullong(); });
    return ranges::accumulate(nums, 0ull);
}

void write_all(map<u64, bitset<BITS>>& memory, size_t cur, string& addr, const bitset<BITS>& value_to_write)
{
    if (cur == BITS)
    {
        string x = string(addr.rbegin(), addr.rend());
        u64 mem_addr = bitset<BITS>(x).to_ullong();
        memory[mem_addr] = value_to_write;
    }
    else if (addr[cur] != 'X')
        write_all(memory, cur + 1, addr, value_to_write);
    else
    {
        addr[cur] = '1';
        write_all(memory, cur + 1, addr, value_to_write);
        addr[cur] = '0';
        write_all(memory, cur + 1, addr, value_to_write);
        addr[cur] = 'X';
    }
}


u64 b(const vector<string>& lines)
{
    map<u64, bitset<BITS>> memory;
    string mask;
    for (const auto& line : lines)
    {
        auto parts = aoc::split(line, " = ");
        if (parts[0] == "mask")
            mask = parts[1];
        else
        {
            auto start = parts[0].find('[') + 1;
            auto end = parts[0].find(']');
            string mem_addr = bitset<BITS>(stoi(parts[0].substr(start, end))).to_string();
            mem_addr = string(mem_addr.rbegin(), mem_addr.rend());
            auto value = bitset<BITS>(stoi(parts[1]));
            for (size_t i = 0; i < BITS; i++)
                if (mask[BITS - i - 1] != '0')
                    mem_addr[i] = mask[BITS - i - 1];
            write_all(memory, 0, mem_addr, value);
        }
    }
    auto nums = ranges::view::values(memory) | ranges::view::transform([](const auto bs) { return bs.to_ullong(); });
    return ranges::accumulate(nums, 0ull);
}

int main()
{
    ifstream file("inputs/day14.txt");
    auto lines = aoc::split(aoc::read_file(file), "\n");
    cout << a(lines) << endl;
    cout << b(lines) << endl;
}
