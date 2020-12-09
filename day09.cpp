#include <bits/stdc++.h>

using namespace std;


int a(const vector<int>& nums, int preamble = 25)
{
    for (int i = preamble; i < static_cast<int>(nums.size()); i++)
    {
        bool found = false;
        for (int j = i - preamble; j < i; j++)
            for (int k = j + 1; k < i; k++)
                if (nums[j] + nums[k] == nums[i])
                {
                    found = true;
                    break;
                }
        if (!found)
            return nums[i];
    }
    return -1;
}

int b(const vector<int>& nums, int target)
{
    for (size_t k = 2; k < nums.size(); k++)
    {
        int sum = reduce(nums.begin(), nums.begin() + k);
        if (sum == target)
            return *min_element(nums.begin(), nums.begin() + k) + *max_element(nums.begin(), nums.begin() + k);
        for (size_t i = k; i < nums.size(); i++)
        {
            sum += -nums[i - k] + nums[i];
            if (sum == target)
                return *min_element(nums.begin() + i - k + 1, nums.begin() + i + 1)
                       + *max_element(nums.begin() + i - k + 1, nums.begin() + i + 1);
        }
    }
    return -1;
}

int main()
{
    ifstream file("inputs/day09.txt");
    vector<int> nums(istream_iterator<int>(file), {});
    int answer_a = a(nums);
    cout << answer_a << endl;
    cout << b(nums, answer_a) << endl;
}
