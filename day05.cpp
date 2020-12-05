#include <bits/stdc++.h>
#include <range/v3/all.hpp>

using namespace std;

struct BoardingPass
{
    uint8_t row = 0, col = 0;
};

istream& operator>>(istream& in, BoardingPass& bp)
{
    string line;
    in >> line;
    bp = {};
    for (int i = 0; i < 7; i++)
        bp.row |= (line[i] == 'B') << (6 - i);
    for (int i = 0; i < 3; i++)
        bp.col |= (line[i + 7] == 'R') << (2 - i);
    return in;
}


int a(const vector<BoardingPass>& passes)
{
    auto get_seat_id = [](const auto& pass) { return pass.row * 8 + pass.col; };
    return ranges::max(passes | ranges::view::transform(get_seat_id));
}

int b(const vector<BoardingPass>& passes)
{
    bool present[128][8] = {};
    for (const auto& pass : passes)
        present[pass.row][pass.col] = 1;
    int start = 0;
    for (int i = 0;; i++)
    {
        if (present[i][0])
        {
            start = i + 1;
            break;
        }
    }

    for (int i = start;; i++)
        for (int j = 0; j < 8; j++)
            if (!present[i][j])
                return i * 8 + j;
    return -1;
}


int main()
{
    ifstream file("inputs/day05.txt");
    vector<BoardingPass> passes(istream_iterator<BoardingPass>(file), {});
    cout << a(passes) << "\n" << b(passes) << endl;
}
