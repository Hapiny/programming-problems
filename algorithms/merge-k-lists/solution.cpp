#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

struct Pair {
    int first, second;
    Pair() : first(INT_MAX), second(-1) {}
    Pair(int val, int idx) : first(val), second(idx) {}
};

struct Node {
     int val;
     Node* next;
     Node() : val(0), next(nullptr) {}
     Node(int x) : val(x), next(nullptr) {}
     Node(int x, Node* next) : val(x), next(next) {}
 };

void print(Node* lst) {
    if (!lst)
        return;
    Node* p = lst;
    while (p) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

class MinHeap {
    int max_size;
    int cur_size;
    Pair* data;
public:
    MinHeap(int size): max_size(size), cur_size(0), data(new Pair[size]) {}

    void insert(int val, int idx) {
        data[cur_size].first = val;
        data[cur_size].second = idx;
        sift_up(cur_size);
        cur_size++;
    }

    Pair* top() {
        return &data[0];
    }

    void swap(int idx1, int idx2) {
        int tmp_val = data[idx1].first, tmp_idx = data[idx1].second;
        data[idx1].first = data[idx2].first;
        data[idx1].second = data[idx2].second;

        data[idx2].first = tmp_val;
        data[idx2].second = tmp_idx;
    }

    int get_parent(int idx) {
        return (int)floor((idx - 1) / 2);
    }

    int get_child(int idx, bool left) {
        return left ? 2 * idx + 1 : 2 * idx + 2;
    }

    void sift_up(int idx) {
        int parent_idx = get_parent(idx);
        while ((idx > 0) && (data[idx].first < data[parent_idx].first)) {
            this->swap(idx, parent_idx);
            idx = parent_idx;
            parent_idx = get_parent(idx);
        }
    }

    void sift_down(int idx) {
        int min_idx = idx, left_idx = get_child(idx, true), right_idx = get_child(idx, false);
        while (idx < max_size) {
            // Check if left child less than current value
            if ((left_idx < max_size) && (data[left_idx].first < data[min_idx].first))
                min_idx = left_idx;
            // Check if right child less than current value and left child
            if ((right_idx < max_size) && (data[right_idx].first < data[min_idx].first))
                min_idx = right_idx;
            // No need to sift element down
            if (min_idx == idx) {
                return;
            } else {
                this->swap(idx, min_idx);
                idx = min_idx;
                left_idx = get_child(idx, true);
                right_idx = get_child(idx, false);
            }
        }
    }

    void print() {
        for (int i = 0; i < max_size; i++) {
            cout << "(" << data[i].first << ", " << data[i].second << ") " ;
        }
        cout << endl;
    }
};

class Solution {
public:
    Node* merge_k_lists(vector<Node*>& lists) {
        vector<Node*> not_empty_lists;
        for (Node* lst : lists) {
            if (lst)
                not_empty_lists.push_back(lst);
        }
        int num_lists = not_empty_lists.size();
        if (num_lists < 2) {
            return num_lists == 1 ? not_empty_lists[0] : nullptr;
        }
        Node* lst = new Node();
        Node* head = lst;
        MinHeap heap(num_lists);
        for (int i = 0; i < num_lists; i++)
            heap.insert(not_empty_lists[i]->val, i);

        int idx = 0, val = 0;
        Pair* p;
        Node* cur_lst;
        while (true) {
            p = heap.top();
            val = p->first;
            idx = p->second;
            if (idx == -1)
                break;
            lst->val = val;
            cur_lst = not_empty_lists[idx];
            p->first = cur_lst->next ? cur_lst->next->val : INT_MAX;
            p->second = cur_lst->next ? idx : -1;
            heap.sift_down(0);
            not_empty_lists[idx] = cur_lst->next ? cur_lst->next : nullptr;
            if (!cur_lst->next)
                num_lists--;
            lst->next = num_lists > 0 ? new Node() : nullptr;
            lst = lst->next;
        }
        return head;
    }
};

int main() {
    Solution solver;
    vector<Node*> lists(3, nullptr);

    lists[0] = new Node(1);
    lists[0]->next = new Node(4);
    lists[0]->next->next = new Node(5);

    lists[1] = new Node(1);
    lists[1]->next = new Node(3);
    lists[1]->next->next = new Node(4);

    lists[2] = new Node(2);
    lists[2]->next = new Node(6);

    cout << "Input lists:" << endl;
    for (Node* p : lists) {
        print(p);
    }
    Node* merged = solver.merge_k_lists(lists);
    cout << "Merged list:" << endl;
    print(merged);
    return 0;
}
