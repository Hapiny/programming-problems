#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <tuple>

using namespace std;

typedef tuple<vector<int>, int, vector<int> > Test;

class StackWithMax {
    private:
        stack<int> data;
        stack<int> max_vals;

    public:
        bool empty() const {
            return data.empty();
        }

        int size() const {
            return data.size();
        }

        void Push(int value) {
            if (data.empty()) {
                max_vals.push(value);
            } else {
                int top_val = max_vals.top();
                if (value > top_val) {
                    max_vals.push(value);
                } else {
                    max_vals.push(top_val);
                }
            }
            data.push(value);
        }

        void Pop() {
            data.pop();
            max_vals.pop();
        }

        int Top() const {
            return data.top();
        }

        int Max() const {
            return max_vals.top();
        }

        void transfer(StackWithMax& stack, int num_ops, bool delete_last=true) {
            for (int i = 0; i < num_ops - 1; ++i) {
                stack.Push(this->Top());
                this->Pop();
            }
            if (delete_last)
                this->Pop();
        }
};


class QueueWithMax {
    public:
        StackWithMax left_stack, right_stack;

        void enQueue(int value) {
            right_stack.Push(value);
        }

        void deQueue() {
            if (!left_stack.empty()) {
                left_stack.Pop();
            } else {
                right_stack.transfer(left_stack,  right_stack.size());
            }
        }

        int Max() const {
            int max_value = INT_MIN;
            if (!right_stack.empty()) {
                int right_max = right_stack.Max();
                max_value = right_max > max_value ? right_max : max_value;
            }
            if (!left_stack.empty()) {
                int left_max = left_stack.Max();
                max_value = left_max > max_value ? left_max : max_value;
            }
            return max_value;
        }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> max_vals;
        if (nums.size() == 0) {
            return max_vals;
        } else if (nums.size() == 1) {
            max_vals.push_back(nums.at(0));
            return max_vals;
        }
        QueueWithMax queue;
        for (int i = k - 1; i >= 0; --i) {
            queue.left_stack.Push(nums[i]);
        }
        max_vals.push_back(queue.Max());
        for (size_t i = 1; i < nums.size() - k + 1; ++i) {
            queue.deQueue();
            queue.enQueue(nums.at(i + k - 1));
            max_vals.push_back(queue.Max());
        }
        return max_vals;
    }
};

void solve(vector<int>& nums, int k, vector<int>& correct, Solution& solver) {
    cout << "Input:" << endl;
    cout << "  Nums = ";
    for (auto val: nums) {
        cout << val << ", ";
    }
    cout << endl << "  K = " << k << endl;
    cout << "Output:" << endl;
    vector<int> solution = solver.maxSlidingWindow(nums, k);
    for (auto & val: solution) {
        cout << val << ", ";
    }
    cout << endl;
    cout << "Correct:" << endl;
    for (auto & val: correct) {
        cout << val << ", ";
    }
    cout << endl;
    if (solution == correct) {
        cout << "\tPASSED!" << endl;
    } else {
        cout << "\tFAILED!" << endl;
    }
    cout << endl;
    return;
}

int main() {
    Solution solver;
    vector<Test> tests;
    tests.push_back(make_tuple(
        vector<int>({1, 3, -1, -3, 5, 3, 6, 7}),
        3,
        vector<int>({3, 3, 5, 5, 6, 7})
    ));
    tests.push_back(make_tuple(
        vector<int>({10, 8, 6, 4, 2}),
        2,
        vector<int>({10, 8, 6, 4})
    ));
    tests.push_back(make_tuple(
        vector<int>({0, 1, 2, 0, -1, -2, 0, 10, -1, 2}),
        3,
        vector<int>({2, 2, 2, 0, 0, 10, 10, 10})
    ));

    for (int i = 0; i < tests.size(); ++i) {
        vector<int> nums = get<0>(tests[i]);
        int k = get<1>(tests[i]);
        vector<int> out = get<2>(tests[i]);
        cout << "\t===== Test " << i + 1 << " =====" << endl;
        solve(nums, k, out, solver);
    }

    return 0;
}
