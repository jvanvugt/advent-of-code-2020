#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

int a(const vector<string>& bus_ids, int arrival)
{
    int min_time = numeric_limits<int>::max();
    int min_id = -1;
    for (const auto& bus_id : bus_ids)
    {
        if (bus_id == "x")
            continue;
        int time = stoi(bus_id);
        int wait_time = time - (arrival % time);
        if (wait_time < min_time)
        {
            min_time = wait_time;
            min_id = time;
        }
    }
    return min_time * min_id;
}

int main()
{
    ifstream file("inputs/day13.txt");
    int arrival;
    string busses;
    file >> arrival >> busses;
    vector<string> bus_ids = aoc::split(busses, ",");
    cout << a(bus_ids, arrival) << endl;
}
