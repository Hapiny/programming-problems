#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

typedef tuple<int, vector<int> > LIS;

class Solution {
public:
     LIS find_lis(vector<int>& nums) {
        int max_len = 1, max_idx = 0;
        vector<int> dp_max_lens(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp_max_lens[i] = max(dp_max_lens[i], dp_max_lens[j] + 1);
                    if (dp_max_lens[i] > dp_max_lens[max_idx]) {
                        max_idx = i;
                    }
                } else {
                    continue;
                }
            }
        }
        max_len = dp_max_lens[max_idx];
        vector<int> lis(max_len, 0);
        int count = max_len - 1, last_seen_idx = max_idx;
        lis[count] = nums[max_idx];
        while (count != 0 && max_idx >= 0) {
            max_idx--;
            if (nums[max_idx] < lis[count] && abs(dp_max_lens[max_idx] - dp_max_lens[last_seen_idx]) == 1) {
                lis[--count] = nums[max_idx];
                last_seen_idx = max_idx;
            }
        }
        return make_tuple(max_len, lis);
    }
};

int main() {
    Solution solver;
    vector<int> nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
//    vector<int> nums = { 3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10 };
    int max_len;
    vector<int> lis;
    tie(max_len, lis) = solver.find_lis(nums);
    cout << "Length of found LIS: " << max_len << endl;
    if (max_len > 1) {
        cout << "Found LIS:" << endl;
        for (auto x : lis) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
