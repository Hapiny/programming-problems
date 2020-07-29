#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    int max(int x, int y) {
        return x > y ? x : y;
    }

    int min(int x, int y) {
        return x > y ? y : x;
    }

    int min3(int x, int y, int z) {
        return min(x, min(y , z));
    }

    tuple<int, vector<string> > min_edit_distance(string text1, string text2) {
        int len1 = text1.length(), len2 = text2.length();
        int dp[len2 + 1][len1 + 1];

        for (int i = 0; i <= len2; i++) {
            for (int j = 0; j <= len1; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = max(i, j);
                } else {
                    if (text1[j - 1] == text2[i - 1]) {
                        dp[i][j] = dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = 1 + min3(dp[i - 1][j],
                                            dp[i - 1][j - 1],
                                            dp[i][j - 1]);
                    }
                }
            }
        }

        int i = len2, j = len1, min_val;
        int left, up, diag, index = dp[len2][len1] - 1;
        vector<string> edits(dp[len2][len1]);
        string edit, chr1, chr2;
        while (i > 0 && j > 0) {
            if (text1[j - 1] == text2[i - 1]) {
                i--;
                j--;
            } else {
                chr1 = text1[j - 1];
                chr2 = text2[i - 1];
                left = dp[i][j - 1];
                up = dp[i - 1][j];
                diag = dp[i - 1][j - 1];
                min_val = min3(left, up, diag);
                if (min_val == diag) {
                   edit = "replace '" + chr1 + "' with '" + chr2 + "'";
                   i--;
                   j--;
                } else if (min_val == left) {
                    edit = "delete '" + chr1 + "'";
                    j--;
                } else {
                    edit = "insert '" + chr2 + "'";
                    i--;
                }
                edits[index] = edit;
                index--;
            }
        }
        return make_tuple(dp[len2][len1], edits);
    }
};

int main() {
    Solution solver;
    string text1 = "horse", text2 = "ros";
    int num_edits;
    vector<string> edits;

    cout << "Text1: " << text1 << endl;
    cout << "Text2: " << text2 << endl;
    tie(num_edits, edits) = solver.min_edit_distance(text1, text2);

    cout << "Minimum num edits: " << num_edits << endl;
    for (auto & edit : edits) {
        cout << edit << endl;
    }

    return 0;
}