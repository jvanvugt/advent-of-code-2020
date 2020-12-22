#include <bits/stdc++.h>
#include <range/v3/all.hpp>
#include "aoc.hpp"

using namespace std;

template <typename T>
T take(deque<T>& q)
{
    assert(q.size() > 0);
    T el = q.front();
    q.pop_front();
    return el;
}

int compute_score(deque<int>& q)
{
    int score = 0;
    for (size_t i = 1; i < q.size()+1; i++)
        score += i * q[q.size() - i];
    return score;
}

int a(deque<int> deck1, deque<int> deck2)
{
    while (max(deck1.size(), deck2.size()) != deck1.size() + deck2.size())
    {
        int card1 = take(deck1);
        int card2 = take(deck2);
        if (card1 > card2)
        {
            deck1.push_back(card1);
            deck1.push_back(card2);
        }
        else
        {
            deck2.push_back(card2);
            deck2.push_back(card1);
        }
    }
    return compute_score(deck1.size() > 0 ? deck1 : deck2);
}

int b(deque<int> deck1, deque<int> deck2, u64 depth = 0)
{
    set<pair<deque<int>, deque<int>>> memory;
    while (max(deck1.size(), deck2.size()) != deck1.size() + deck2.size())
    {
        auto current = make_pair(deck1, deck2);
        if (memory.count(current))
            return depth > 0 ? 1 : compute_score(deck1);
        memory.insert(current);

        int card1 = take(deck1);
        int card2 = take(deck2);
        int round_winner = 0;
        if (static_cast<int>(deck1.size()) >= card1 && static_cast<int>(deck2.size()) >= card2)
            round_winner = b({deck1.begin(), deck1.begin() + card1}, {deck2.begin(), deck2.begin() + card2}, depth+1);
        else
            round_winner = card1 > card2;
        if (round_winner)
        {
            deck1.push_back(card1);
            deck1.push_back(card2);
        }
        else
        {
            deck2.push_back(card2);
            deck2.push_back(card1);
        }
    }
    return depth > 0 ? deck1.size() > deck2.size() : compute_score(deck1.size() > 0 ? deck1 : deck2);
}

int main()
{
    ifstream file("inputs/day22.txt");
    auto decks = aoc::split(aoc::read_file(file), "\n\n");
    assert(decks.size() == 2);
    deque<int> deck1, deck2;
    auto lines1 = aoc::split(decks[0], "\n");
    auto lines2 = aoc::split(decks[1], "\n");
    assert (lines1.size() == lines2.size());
    for (size_t i = 1; i < lines1.size(); i++)
    {
        deck1.push_back(stoi(lines1[i]));
        deck2.push_back(stoi(lines2[i]));
    }
    cout << a(deck1, deck2) << endl;
    cout << b(deck1, deck2) << endl;
    return 0;
}
