#include <bits/stdc++.h>
#include "aoc.hpp"

using namespace std;

constexpr u64 mod = 20201227ull;

u64 find_loop_size(u64 target, u64 start)
{
    u64 num = start;
    for (u64 i = 0;; i++)
    {
        if (num == target)
            return i + 1;
        num = (start * num) % mod;
    }
    return 0;
}


u64 a(u64 num1, u64 num2, u64 start = 7)
{
    u64 loop_size2 = find_loop_size(num2, start);
    auto encr = num1;
    for (u64 i = 0; i < loop_size2 -1; i++)
        encr = (encr * num1) % mod;
    return encr;
}

int main()
{
    u64 num1 = 9033205ull;
    u64 num2 = 9281649ull;
    cout << a(num1, num2) << endl;
    return 0;
}
