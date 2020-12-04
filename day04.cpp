#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;

using Passport = map<string, string>;

bool has_required_fields(const Passport& passport)
{
    static const std::array<string, 7> required_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    return ranges::all_of(required_fields, [&](const auto& f) { return passport.count(f); });
}

bool valid_color(const string& hcl)
{
    static const regex color_reg("#[0-9a-f]{6}");
    return regex_match(hcl, color_reg);
}

bool good_values(Passport& passport)
{
    static const set<string> eye_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    auto byr = atoi(passport["byr"].c_str());
    if (byr < 1920 || byr > 2002)
        return false;
    auto iyr = atoi(passport["iyr"].c_str());
    if (iyr < 2010 || iyr > 2020)
        return false;
    auto eyr = atoi(passport["eyr"].c_str());
    if (eyr < 2020 || eyr > 2030)
        return false;
    istringstream iss(passport["hgt"]);
    int hgt;
    string unit;
    iss >> hgt >> unit;
    if (unit != "cm" && unit != "in")
        return false;
    if (unit == "cm" && (hgt < 150 || hgt > 193))
        return false;
    else if (unit == "in" && (hgt < 59 || hgt > 76))
        return false;
    if (!valid_color(passport["hcl"]))
        return false;
    if (!eye_colors.count(passport["ecl"]))
        return false;
    if (passport["pid"].length() != 9)
        return false;
    if (!ranges::all_of(passport["pid"], [](unsigned char c) { return isdigit(c); }))
        return false;
    return true;
}

int a(const vector<Passport>& passports)
{
    return ranges::count_if(passports, has_required_fields);
}

int b(vector<Passport>& passport)
{

    auto with_fields = passport | ranges::view::filter(has_required_fields);
    return ranges::count_if(with_fields, good_values);
}

Passport parse_passport(const string& passport)
{
    Passport result;
    istringstream iss(passport);
    vector<string> words{istream_iterator<string>{iss}, {}};
    for (const auto& word : words)
    {
        auto split = word.find(':');
        auto key = word.substr(0, split);
        auto value = word.substr(split + 1);
        result[key] = value;
    }
    return result;
}


int main()
{
    ifstream file("inputs/day04.txt");
    vector<Passport> passports;
    string line;
    string passport;
    while (getline(file, line))
    {
        if (line == "")
        {
            passports.push_back(parse_passport(passport));
            passport.clear();
        }
        else
        {
            passport += line;
            passport += " ";
        }
    }
    passports.push_back(parse_passport(passport));
    cout << a(passports) << "\n" << b(passports) << endl;
}
