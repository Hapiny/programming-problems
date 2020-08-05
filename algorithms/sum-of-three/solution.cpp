#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int max(int x, int y) {
        return x > y ? x : y;
    }

    int min(int x, int y) {
        return x < y ? x : y;
    }

    int max3(int x, int y, int z) {
        return max(x, max(y, z));
    }

    int min3(int x, int y, int z) {
        return min(x, min(y, z));
    }


    vector<vector<int>> three_sum(vector<int>& nums) {
        int size = nums.size();
        if (size < 3) {
            return {};
        }
        vector<vector<int>> result;
        sort(nums.begin(), nums.end()); // O(n logn)

        int a, b, c, sum, target;
        int s, e;
        for (int i = 0; i < size; i++) { // O(n^2)
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            s = i + 1;
            e = size - 1;
            target = -nums[i];
            while (s < e) {
                sum = nums[s] + nums[e];
                if (sum > target) {
                    e--;
                } else if (sum < target) {
                    s++;
                } else {
                    a = min3(nums[s], nums[e], nums[i]);
                    c = max3(nums[s], nums[e], nums[i]);
                    b = 0 - a - c;
//                    cout << "Found for i = " << i  << " Val: " << nums[i] << endl;
//                    cout << a << " " << b << " " << c << endl;
                    result.push_back({a, b, c});

                    while (s < e && nums[s] == nums[s + 1])
                        s++;
                    while (s < e && nums[e] == nums[e - 1])
                        e--;
                    s++;
                    e--;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution solver;

    vector<int> nums = { -1, 0, 1, 2, -1, -4 };
    cout << "Input:" << endl;
    for (auto x : nums)
        cout << x << " ";
    cout << endl;

    vector<vector<int>> result = solver.three_sum(nums);
    if (!result.size()) {
        cout << "Not found" << endl;
    } else {
        cout << "Found triplets:" << endl;
        for (auto v: result) {
            for (auto x : v)
                cout << x << " ";
            cout << endl;
        }
    }
    return 0;
}
