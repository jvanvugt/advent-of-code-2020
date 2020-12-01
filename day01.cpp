#include <range/v3/all.hpp>
#include <bits/stdc++.h>

using namespace std;

int a(const std::vector<int> &nums, int target = 2020)
{
    set<int> residuals;
    for (auto num : nums)
    {
        if (residuals.count(num))
            return (target - num) * num;
        residuals.insert(target - num);
    }
    return -1;
}

int b(const std::vector<int> &nums, int target = 2020)
{
    for (auto num1 : nums)
        for (auto num2 : nums)
            for (auto num3 : nums)
                if (num1 + num2 + num3 == target)
                    return num1 * num2 * num3;
    return -1;
}

int main()
{
    ifstream file("inputs/day01.txt");
    vector<int> nums(istream_iterator<int>{file}, istream_iterator<int>{});
    cout << a(nums) << "\n"
         << b(nums) << endl;
}
