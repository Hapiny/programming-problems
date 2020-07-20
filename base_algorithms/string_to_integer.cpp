#include <iostream>
#include <string>
#include <climits>

using namespace std;


class Solution {
public:
    // Convert string to integer if possible
    // The number in the line can overflow int32.
    // If number > 2^31 - 1 then return 2^31 - 1
    // If number < -2^31 then return -2^31
    int myAtoi(string str) {
        int str_len = str.length();
        if (!str_len) {
            return 0;
        }
        int num = 0;
        int max_val = 214748364;
        int min_add = 8, max_add = 7;
        bool is_negative = false, sign = false;
        int i = 0;
        // Skip whitespaces
        for (; i < str_len; i++) {
            if (str[i] == ' ') {
                continue;
            } else {
                break;
            }
        }
        int ord, add;
        for (; i < str_len; i++) {
            if (isdigit(str[i])) {
                ord = str[i] - '0';
                add = is_negative ? min_add : max_add;
                // Check integer overflow
                if (abs(num) > max_val || (abs(num) == max_val && ord > add)) {
                    if (is_negative) {
                        return INT_MIN;
                    } else {
                        return INT_MAX;
                    }
                } else {
                    if (is_negative) {
                        ord = -ord;
                    }
                    num = num * 10 + ord;
                }
            } else if (str[i] == '-' && !sign) {
                if (i > 0 && isdigit(str[i-1]))
                    break;
                is_negative = true;
                sign = true;
            } else if (str[i] == '+' && !sign) {
                if (i > 0 && isdigit(str[i-1]))
                    break;
                is_negative = false;
                sign = true;
            }
            else {
                break;
            }
        }
        return num;
    }
};

int main() {
    Solution solver;
    string s;
    cin >> s;
    cout << solver.myAtoi(s) << endl;
    return 0;
}
