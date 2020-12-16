#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using Range = pair<int, int>;
using Ticket = vector<int>;
using Rule = pair<Range, Range>;

bool is_valid_num(int num, const Rule& rule)
{
    return aoc::in_range(num, rule.first.first, rule.first.second + 1)
           || aoc::in_range(num, rule.second.first, rule.second.second + 1);
}

u64 a(const vector<Rule>& rules, const vector<Ticket>& tickets)
{
    u64 invalid = 0;
    for (const auto& ticket : tickets)
        for (auto num : ticket)
            if (!ranges::any_of(rules, [num](const auto& rule) { return is_valid_num(num, rule); }))
                invalid += num;
    return invalid;
}

vector<vector<size_t>> find_valid(const vector<Rule>& rules, const vector<Ticket>& tickets)
{
    vector<vector<size_t>> valid_rules_per_num;
    for (size_t i = 0; i < tickets[0].size(); i++)
    {
        valid_rules_per_num.push_back({});
        for (size_t r = 0; r < rules.size(); r++)
        {
            if (ranges::all_of(tickets, [&](const Ticket& ticket) { return is_valid_num(ticket[i], rules[r]); }))
                valid_rules_per_num.back().push_back(r);
        }
    }
    return valid_rules_per_num;
}

u64 b(const vector<Rule>& rules, const vector<Ticket>& tickets, Ticket my_ticket)
{
    vector<Ticket> valid_tickets;
    for (const auto& ticket : tickets)
    {
        bool correct = true;
        for (auto num : ticket)
        {
            if (!ranges::any_of(rules, [num](const auto& rule) { return is_valid_num(num, rule); }))
            {
                correct = false;
                break;
            }
        }
        if (correct)
            valid_tickets.push_back(ticket);
    }
    auto valid_rules_per_num = find_valid(rules, valid_tickets);
    vector<size_t> argsort(valid_rules_per_num.size());
    ranges::iota(argsort, 0);
    ranges::sort(argsort,
                 [&](size_t a, size_t b) { return valid_rules_per_num[a].size() < valid_rules_per_num[b].size(); });

    vector<size_t> assignment(valid_rules_per_num.size(), 999999);
    for (size_t num_idx : argsort)
    {
        for (size_t valid_rule : valid_rules_per_num[num_idx])
        {
            if (!ranges::count(assignment, valid_rule))
            {
                assignment[num_idx] = valid_rule;
                break;
            }
        }
    }
    u64 answer = 1;
    for (size_t i = 0; i < my_ticket.size(); i++)
        if (assignment[i] < 6)
            answer *= static_cast<u64>(my_ticket[i]);
    return answer;
}

int main()
{
    ifstream file("inputs/day16.txt");
    auto lines = aoc::split(aoc::read_file(file), "\n");
    vector<Rule> rules;
    size_t rules_end = 0;
    for (size_t i = 0; i < lines.size(); i++)
    {
        const auto& line = lines[i];
        if (line == "")
        {
            rules_end = i;
            break;
        }
        auto middle = line.find(':') + 2;
        auto second = line.substr(middle, line.length() - middle);
        auto ranges = aoc::split(second, " or ");
        auto nums1 = aoc::split(ranges.at(0), "-");
        auto nums2 = aoc::split(ranges.at(1), "-");
        rules.push_back({{stoi(nums1[0]), stoi(nums1[1])}, {stoi(nums2[0]), stoi(nums2[1])}});
    }
    auto mine_s = aoc::split(lines[rules_end + 2], ",");
    Ticket my_ticket;
    for (const auto& s : mine_s)
        my_ticket.push_back(stoi(s));

    vector<Ticket> tickets;
    for (size_t i = rules_end + 5; i < lines.size(); i++)
    {
        Ticket ticket;
        for (const auto& s : aoc::split(lines[i], ","))
            ticket.push_back(stoi(s));
        tickets.push_back(ticket);
    }
    cout << a(rules, tickets) << endl;
    cout << b(rules, tickets, my_ticket) << endl;
}
