#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int max(int x, int y) {
    return x > y ? x : y;
}

class Solution {
public:
    tuple<int, string> longest_common_subsequence(string text1, string text2) {
        int len1 = text1.length(), len2 = text2.length();
        int dp_matrix[len1 + 1][len2 + 1];

        // Initialize matrix
        for (int i = 0; i <= len1; i++) {
            for (int j = 0; j <= len2; j++) {
                dp_matrix[i][j] = 0;
            }
        }

        string found_lcs = "";
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp_matrix[i][j] = dp_matrix[i - 1][j - 1] + 1;
                } else {
                    dp_matrix[i][j] = max(dp_matrix[i - 1][j], dp_matrix[i][j - 1]);
                }
            }
        }

        int i = len1, j = len2, cur_val;
        while (i > 0 && j > 0) {
            cur_val = dp_matrix[i][j];
//            cout << i << " " << j << " ";
            if (cur_val == dp_matrix[i - 1][j - 1] + 1 &&
                dp_matrix[i - 1][j] != cur_val &&
                dp_matrix[i][j - 1] != cur_val
            ) {
                found_lcs = text2[j - 1] + found_lcs;
                i--;
                j--;
//                cout << "diagonal" << endl;
            } else if (dp_matrix[i - 1][j] > dp_matrix[i][j - 1]) {
                i--;
//                cout << "up" << endl;
            } else {
                j--;
//                cout << "left" << endl;
            }
        }

        return make_tuple(dp_matrix[len1][len2], found_lcs);
    }
};

int main() {
    Solution solver;
    string text1 = "kokojambodon", text2 = "tojebaton";
    string lcs = "ojbon", found_lcs;
    int len_cls;

    cout << "Text1: " << text1 << endl;
    cout << "Text2: " << text2 << endl;
    tie(len_cls, found_lcs) = solver.longest_common_subsequence(text1, text2);

    cout << "Length of found LCS: " << len_cls << endl;
    cout << "Found LCS: " << found_lcs << endl;
    cout << "Correct LCS: " << lcs << endl;

    return 0;
}