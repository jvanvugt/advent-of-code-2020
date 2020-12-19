#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using SubRule = vector<string>;
using Rule = vector<SubRule>;


optional<string_view> matches_rule(const string_view& message, const vector<Rule>& rules, size_t rule_idx);

optional<string_view> match_subrule(string_view message, const vector<Rule>& rules, const SubRule& subrule)
{
    for (const auto& part : subrule)
    {
        if (isdigit(part.at(0)))
        {
            size_t next_rule_idx = stoull(part);
            auto maybe_match = matches_rule(message, rules, next_rule_idx);
            if (!maybe_match)
                return {};
            message = *maybe_match;
        }
        else
        {
            assert(part == "a" || part == "b");
            char c = part[0];
            if (message.length() > 0 && message.at(0) == c)
                message.remove_prefix(1);
            else
                return {};
        }
    }
    return message;
}


optional<string_view> matches_rule(const string_view& message, const vector<Rule>& rules, size_t rule_idx = 0)
{
    const Rule& rule = rules.at(rule_idx);
    vector<string_view> possibilities;
    for (const auto& subrule : rule)
    {
        auto maybe_match = match_subrule(message, rules, subrule);
        if (maybe_match)
            possibilities.push_back(*maybe_match);
    }
    if (possibilities.size() > 1)
    {
        return *ranges::min_element(possibilities, {}, [](const auto& sv) { return sv.length(); });
    }
    if (possibilities.size() == 1)
    {
        return possibilities[0];
    }
    return {};
}

int a(const vector<Rule>& rules, const vector<string>& messages)
{
    return ranges::accumulate(messages, 0, [&rules](int acc, const string& msg) {
        auto maybe_match = matches_rule(msg, rules);
        return acc + (maybe_match ? (*maybe_match).length() == 0 : false);
    });
}

int b(vector<Rule> rules, const vector<string>& messages)
{
    rules[8] = {{"42"}, {"42", "8"}};
    rules[11] = {{"42", "31"}, {"42", "11", "31"}};
    return ranges::accumulate(messages, 0, [&rules](int acc, const string& msg) {
        auto maybe_match = matches_rule(msg, rules);
        return acc + (maybe_match ? (*maybe_match).length() == 0 : false);
    });
}

int main()
{
    ifstream file("inputs/day19.txt");
    vector<string> rules_and_msgs = aoc::split(aoc::read_file(file), "\n\n");
    vector<string> messages = aoc::split(rules_and_msgs.at(1), "\n");
    vector<string> rule_lines = aoc::split(rules_and_msgs.at(0), "\n");
    vector<Rule> rules(rule_lines.size());
    for (const auto& rule_line : rule_lines)
    {
        auto num_and_rule = aoc::split(rule_line, ": ");
        size_t idx = stoull(num_and_rule.at(0));
        Rule rule;
        for (const auto& subrule_s : aoc::split(num_and_rule.at(1), " | "))
        {
            SubRule subrule;
            for (const auto& part : aoc::split(subrule_s, " "))
            {
                subrule.push_back(part.at(0) == '"' ? part.substr(1, part.length() - 2) : part);
            }
            rule.push_back(subrule);
        }
        rules[idx] = rule;
    }
    cout << a(rules, messages) << endl;
    cout << b(rules, messages) << endl;
}
