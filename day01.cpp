#include <bits/stdc++.h>

using namespace std;

int a(const std::vector<int>& nums, int target = 2020)
{
    unordered_set<int> residuals;
    for (auto num : nums)
    {
        if (residuals.count(num))
            return (target - num) * num;
        residuals.insert(target - num);
    }
    return -1;
}

int b(const std::vector<int>& nums, int target = 2020)
{
    for (size_t i = 0u; i < nums.size(); i++)
    {
        unordered_map<int, int> residuals;
        int new_target = target - nums[i];
        for (size_t j = i + 1; j < nums.size(); j++)
        {
            if (residuals.count(nums[j]))
                return residuals[nums[j]] * nums[j];
            residuals[new_target - nums[j]] = nums[i] * nums[j];
        }
    }
    return -1;
}

int main()
{
    ifstream file("inputs/day01.txt");
    vector<int> nums(istream_iterator<int>{file}, istream_iterator<int>{});
    cout << a(nums) << "\n"
         << b(nums) << endl;
}
