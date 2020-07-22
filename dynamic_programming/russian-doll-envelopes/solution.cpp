#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

struct Envelop {
    int w, h;
    Envelop(int w = 1, int h = 1): w(w), h(h) {}
};

bool comp_by_area(Envelop& a, Envelop& b) {
    int area_a = a.w * a.h, area_b = b.w * b.h;
    return area_a > area_b;
}

class Solution {
public:
    int get_max_envelopes(vector<Envelop>& envelopes) {
        if (!envelopes.size()) {
            return 0;
        }
        vector<int> dp_array(envelopes.size(), 1);
        sort(envelopes.begin(), envelopes.end(), comp_by_area);
        int max_num = 1, max_idx = 0;
        for (int i = 1; i < envelopes.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i].w < envelopes[j].w && envelopes[i].h < envelopes[j].h) {
                    dp_array[i] = max(dp_array[i], dp_array[j] + 1);
                    if (dp_array[i] > dp_array[max_idx]) {
                        max_idx = i;
                    }
                }
            }
        }
        max_num = dp_array[max_idx];

        vector<Envelop> found_seq;
        found_seq.push_back(envelopes[max_idx]);
        while (found_seq.size() != max_num && max_idx >= 0) {
            max_idx--;
            if (envelopes[max_idx].w > found_seq.back().w &&
                envelopes[max_idx].h > found_seq.back().h) {
                found_seq.push_back(envelopes[max_idx]);
            }
        }

        cout << "Found Russian Doll envelopes:" << endl;
        if (max_num > 1) {
            for (int i = 0; i < max_num; i++) {
                cout << "(" << found_seq[i].w << ", " << found_seq[i].h << ")";
                if (i != max_num - 1) {
                    cout << " => ";
                }
            }
            cout << endl;
        }

        return max_num;
    }
};


int main() {
    Solution solver;
    vector<Envelop> envelopes;
    envelopes.push_back(Envelop(5, 4));
    envelopes.push_back(Envelop(6, 4));
    envelopes.push_back(Envelop(6, 7));
    envelopes.push_back(Envelop(2, 3));

    cout << solver.get_max_envelopes(envelopes) << endl;

    return 0;
}
