#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

struct Food
{
    set<string> ingredients;
    set<string> allergens;
};

map<string, string> find_all_per_ingr(const vector<Food>& foods)
{
    set<string> all_allergens;
    set<string> all_ingrs;
    for (const Food& food : foods)
    {
        all_ingrs.insert(food.ingredients.begin(), food.ingredients.end());
        all_allergens.insert(food.allergens.begin(), food.allergens.end());
    }
    map<string, set<string>> poss_ing_per_all;
    for (const auto& allergen : all_allergens)
    {
        auto ingrs_for_allergen = all_ingrs;
        for (const auto& food : foods)
        {
            if (food.allergens.count(allergen))
            {
                set<string> inter;
                set_intersection(ingrs_for_allergen.begin(), ingrs_for_allergen.end(), food.ingredients.begin(), food.ingredients.end(), inserter(inter, inter.begin()));
                ingrs_for_allergen = inter;
            }
        }
        poss_ing_per_all[allergen] = ingrs_for_allergen;
    }
    map<string, string> allergen_per_ingr;
    for (const auto& ingr : all_ingrs)
        allergen_per_ingr[ingr] = "";
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (const auto& [allergen, poss_ingrs] : poss_ing_per_all)
        {
            if (poss_ingrs.size() == 1)
            {
                changed = true;
                string ingr = *poss_ingrs.begin();
                allergen_per_ingr[ingr] = allergen;
                for (auto& other_ingrs : ranges::view::values(poss_ing_per_all))
                    other_ingrs.erase(ingr);
            }
        }
    }
    return allergen_per_ingr;
}

int a(const vector<Food>& foods)
{
    auto allergen_per_ingr = find_all_per_ingr(foods);
    int answer = 0;
    for (const auto& [ingr, allergen] : allergen_per_ingr)
        if (allergen.length() == 0)
            answer += ranges::accumulate(foods, 0, [&](int acc, const Food& food) { return acc + food.ingredients.count(ingr);});
    return answer;
}

string b(const vector<Food>& foods)
{
    auto allergen_per_ingr = find_all_per_ingr(foods);
    map<string, string> ingr_per_all;
    vector<string> allergens;
    for (const auto& [ingr, all] : allergen_per_ingr)
    {
        if (all.length() != 0)
        {
            allergens.push_back(all);
            ingr_per_all[all] = ingr;
        }
    }
    ranges::sort(allergens);
    stringstream ss;
    for (const auto& allergen : allergens)
        ss << ingr_per_all[allergen] << ",";
    string res = ss.str();
    return res.substr(0, res.length() - 1);
}

int main()
{
    ifstream file("inputs/day21.txt");
    auto lines = aoc::split(aoc::read_file(file), "\n");
    vector<Food> foods;
    for (auto line : lines)
    {
        line = line.substr(0, line.length() - 1);
        auto ingrs_and_all = aoc::split(line, " (contains ");
        assert (ingrs_and_all.size() == 2);
        auto parts = aoc::split(ingrs_and_all[0], " ");
        set<string> ingr(parts.begin(), parts.end());
        auto allergens = aoc::split(ingrs_and_all[1], ", ");
        foods.push_back({ingr, set<string>(allergens.begin(), allergens.end())});
    }
    cout << a(foods) << endl;
    cout << b(foods) << endl;
    return 0;
}
