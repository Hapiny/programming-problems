#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int max(int x, int y) {
        return x > y ? x : y;
    }

    int min(int x, int y) {
        return x < y ? x : y;
    }

    double find_median_of_two_sorted(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        vector<int>& arr1 = len1 < len2 ? nums1 : nums2;
        vector<int>& arr2 = len1 < len2 ? nums2 : nums1;
        len1 = arr1.size();
        len2 = arr2.size();
        int total_len = len1 + len2;

        cout << "First array: ";
        for (auto x : arr1)
            cout << x << " ";
        cout << endl;

        cout << "Second array: ";
        for (auto x : arr2)
            cout << x << " ";
        cout << endl;

        int idx1, idx2, s = 0, e = len1;
        int max_left1, min_right1;
        int max_left2, min_right2;
        double median = 0.0;
        while (s <= e) {
            idx1 = (s + e) / 2;
            idx2 = (total_len + 1) / 2 - idx1;

            max_left1 = idx1 > 0 ? arr1[idx1 - 1] : INT_MIN;
            max_left2 = idx2 > 0 ? arr2[idx2 - 1] : INT_MIN;

            min_right1 = idx1 >= len1 ? INT_MAX : arr1[idx1];
            min_right2 = idx2 >= len2 ? INT_MAX : arr2[idx2];

            if (max_left1 > min_right2) {
                e = idx1 - 1;
            } else if (max_left2 > min_right1) {
                s = idx1 + 1;
            } else {
                if (total_len % 2) {
                    median = (double)max(max_left1, max_left2);
                } else {
                    median = (double)(max(max_left1, max_left2) + min(min_right1, min_right2)) / 2.0;
                }
                break;
            }
        }
        return median;
    }
};

int main() {
    Solution solver;
    vector<int> nums1 = { 1, 3, 3, 8, 8, 9, 15 };
    vector<int> nums2 = { 7, 11, 18, 19, 19, 21, 25 };

    double median = solver.find_median_of_two_sorted(nums1, nums2);
    cout << "Median of two sorted arrays is " << median << endl;
    return 0;
}
