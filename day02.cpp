#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;

struct PasswordLine
{
    int min_count;
    int max_count;
    char letter;
    std::string password;
};

istream& operator>>(istream& in, PasswordLine& pwdline)
{
    char dummy;
    in >> pwdline.min_count >> dummy >> pwdline.max_count >> pwdline.letter >> dummy >> pwdline.password;
    return in;
}

int a(const std::vector<PasswordLine>& passwords)
{
    return ranges::count_if(passwords, [](const PasswordLine& pwdline) {
        auto occ = ranges::count(pwdline.password, pwdline.letter);
        return occ >= pwdline.min_count && occ <= pwdline.max_count;
    });
}

int b(const std::vector<PasswordLine>& passwords)
{
    return ranges::count_if(passwords, [](const PasswordLine& pwdline) {
        return (pwdline.password.at(pwdline.min_count - 1) == pwdline.letter)
               ^ (pwdline.password.at(pwdline.max_count - 1) == pwdline.letter);
    });
}

int main()
{
    ifstream file("inputs/day02.txt");
    vector<PasswordLine> passwords(istream_iterator<PasswordLine>{file}, istream_iterator<PasswordLine>{});
    cout << a(passwords) << "\n" << b(passwords) << endl;
}
