#include <iostream>
#include <vector>
#include <set>
#include <tuple>


using namespace std;

class Solution {
public:
    int max(int x, int y) {
        return x > y ? x : y;
    }

    // Example: Input = [ 100, 4, 200, 1, 3, 2 ]
    // Output: longest sequence =  [ 1, 2, 3, 4 ], => Answer = 4
    tuple<int, int> longest_consecutive_subsequence(vector<int>& nums) {
        set<int> uniq_nums(nums.begin(), nums.end());
        int max_len = 0, min_subseq_val, cur_len;
        for(int i = 0; i < nums.size();i++) {
            if (uniq_nums.find(nums[i] + 1) == uniq_nums.end()) {
                int j = nums[i];
                while(uniq_nums.find(j) != uniq_nums.end()) {
                    j--;
                }
                cur_len = nums[i] - j;
                if (cur_len > max_len) {
                    max_len = cur_len;
                    min_subseq_val = j + 1;
                }
            }
        }
        return make_tuple(max_len, min_subseq_val);
    }
};

int main() {
    Solution solver;
    vector<int> nums = { 100, 4, 200, 1, 3, 2 };

    cout << "Input sequence: [ " ;
    for (auto x : nums) {
        cout << x << ", ";
    }
    cout << "\b\b ]" << endl;

    int max_len, min_subseq_val;
    tie(max_len, min_subseq_val) = solver.longest_consecutive_subsequence(nums);
    vector<int> LCS(max_len, min_subseq_val);
    for (int i = 1; i < max_len; i++) {
        LCS[i] = min_subseq_val + i;
    }

    cout << "Longest subsequence has length: " << max_len << endl;
    cout << "Input sequence: [ " ;
    for (auto x : LCS) {
        cout << x << ", ";
    }
    cout << "\b\b ]" << endl;

    return 0;
}
