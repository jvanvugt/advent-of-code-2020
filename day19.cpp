#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

using SubRule = vector<string>;
using Rule = vector<SubRule>;

vector<string_view> matches_rule(const string_view& message, const vector<Rule>& rules, const Rule& rule);

vector<string_view> match_subrule(string_view message, const vector<Rule>& rules, const SubRule& subrule, size_t si = 0)
{
    if (si == subrule.size())  // Finished matching this subrule
        return {message};
    const auto& part = subrule[si];
    if (!isdigit(part.at(0)))  // Matching a char literal
    {
        if (message.length() > 0 && message.at(0) == part[0])
            return match_subrule(message.substr(1), rules, subrule, si + 1);
        else
            return {};
    }

    vector<string_view> possibilities;
    for (const auto& match : matches_rule(message, rules, rules[stoull(part)]))
    {
        auto rest_matches = match_subrule(match, rules, subrule, si + 1);
        possibilities.insert(possibilities.end(), rest_matches.begin(), rest_matches.end());
    }
    return possibilities;
}

vector<string_view> matches_rule(const string_view& message, const vector<Rule>& rules, const Rule& rule)
{
    vector<string_view> possibilities;
    for (const auto& subrule : rule)
    {
        auto submatches = match_subrule(message, rules, subrule);
        possibilities.insert(possibilities.end(), submatches.begin(), submatches.end());
    }
    return possibilities;
}

int a(const vector<Rule>& rules, const vector<string>& messages)
{
    return ranges::accumulate(messages, 0, [&rules](int acc, const string& msg) {
        auto matches = matches_rule(msg, rules, rules[0]);
        return acc + ranges::any_of(matches, [](const auto& m) { return m.length() == 0; });
    });
}

int b(vector<Rule> rules, const vector<string>& messages)
{
    rules[8] = {{"42"}, {"42", "8"}};
    rules[11] = {{"42", "31"}, {"42", "11", "31"}};
    return ranges::accumulate(messages, 0, [&rules](int acc, const string& msg) {
        auto matches = matches_rule(msg, rules, rules[0]);
        return acc + ranges::any_of(matches, [](const auto& m) { return m.length() == 0; });
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
        for (const auto& subrule_s : aoc::split(num_and_rule.at(1), " | "))
        {
            SubRule subrule;
            for (const auto& part : aoc::split(subrule_s, " "))
                subrule.push_back(part.at(0) == '"' ? part.substr(1, part.length() - 2) : part);
            rules[idx].push_back(subrule);
        }
    }
    cout << a(rules, messages) << endl;
    cout << b(rules, messages) << endl;
}
