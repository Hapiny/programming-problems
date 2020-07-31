#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int, vector<int> > LIS;

class Solution {
public:
    void lower_bound(vector<int>& sorted_vals, int start, int end, int value) {
        int cur_idx = start + (end - start) / 2;
        int cur_val = sorted_vals[cur_idx];
        while (start != end) {
            if (cur_val == value) {
                return;
            }
            if (cur_val < value) {
                start = cur_idx + 1;
            } else {
                end = cur_idx - 1;
            }
            if (end < start) {
                start = end;
            }

            cur_idx = start + (end - start) / 2;
            cur_val = sorted_vals[cur_idx];
        }
        if (cur_val > value) {
            sorted_vals[cur_idx] = value;
        } else if (cur_val < value) {
            sorted_vals[cur_idx + 1] = value;
        } else {
            return;
        }
    }

    LIS find_lis(vector<int>& nums) {
        int max_len = 0;
        vector<int> ids_min_val_of_lis(nums.size(), 0);
        vector<int> sorted_elems(nums.size(), 0);
        sorted_elems[0] = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (sorted_elems[max_len] < nums[i]) {
                sorted_elems[++max_len] = nums[i];
            } else if (sorted_elems[0] > nums[i]) {
                sorted_elems[0] = nums[i];
            } else {
                lower_bound(sorted_elems, 0, max_len, nums[i]);
            }
        }
        return make_tuple(max_len + 1, sorted_elems);
    }
};

int main() {
    Solution solver;
    int max_len;

    vector<int> found_lis, nums = { 3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10 };
    tie(max_len, found_lis) = solver.find_lis(nums);
    cout << "Input sequence: [ ";
    for (auto x : nums) {
        cout << x << ", ";
    }
    cout << "\b\b ]" << endl;
    cout << "Length of found LIS: " << max_len << endl;
    if (max_len > 1) {
        cout << "Found LIS: [ ";
        for (int i = 0; i < max_len; i++) {
            cout << found_lis[i] << ", ";
        }
        cout << "\b\b ]" << endl;
    }
    return 0;
}