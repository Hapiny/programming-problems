#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void print_list(ListNode* head) {
    ListNode* tmp = head;
    while (tmp) {
        cout << tmp->val << " ";
        tmp = tmp->next;
    }
    cout << endl;
}


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int num1, num2, sum = 0, add = 0;
        ListNode* lst = new ListNode();
        ListNode* head = lst;
        while (l1 || l2) {
            num1 = l1 ? l1->val : 0;
            num2 = l2 ? l2->val : 0;
            sum = num1 + num2 + add;

            if (sum > 9) {
                lst->val = sum % 10;
                if (!add)
                    add += 1;
            } else {
                lst->val = sum;
                add = 0;
            }

            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;

            if (l1 || l2) {
                lst->next = new ListNode();
                lst = lst->next;
            }

        }
        if (add) {
            while (add > 9) {
                lst->next = new ListNode();
                lst = lst->next;
                lst->val = add % 10;
                add /= 10;
            }
            if (add) {
                lst->next = new ListNode();
                lst = lst->next;
                lst->val = add;
            }
        }
        return head;
    }
};

int main() {
    ListNode* l1 = new ListNode();
    ListNode* l2 = new ListNode();
    ListNode* tmp1 = l1;
    ListNode* tmp2 = l2;

    tmp1->val = 1;
//    tmp1->next = new ListNode();
//    tmp1 = tmp1->next;
//
//    tmp1->val = 9;

    tmp2->val = 9;
    tmp2->next = new ListNode();
    tmp2 = tmp2->next;

    tmp2->val = 9;


    cout << "First list:" << endl;
    print_list(l1);
    cout << "Second list:" << endl;
    print_list(l2);
    cout << endl;

    Solution solver;
    ListNode* list_sum = solver.addTwoNumbers(l1, l2);
    cout << "Result list:" << endl;
    print_list(list_sum);
    return 0;
}