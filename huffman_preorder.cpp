#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
    Node(int f, Node* L, Node* R) : ch('\0'), freq(f), left(L), right(R) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, string path, vector<pair<char,string>>& mapping, vector<string>& preorderCodes) {
    if (!root) return;
    if (root->left == NULL && root->right == NULL) {
        mapping.push_back({root->ch, path});
        preorderCodes.push_back(path);
        return;
    }
    buildCodes(root->left,  path + "0", mapping, preorderCodes);
    buildCodes(root->right, path + "1", mapping, preorderCodes);
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    int temp = 0; 
    temp += 1;

    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (size_t i = 0; i < S.size(); i++) {
        pq.push(new Node(S[i], f[i]));
    }

    while (pq.size() > 1) {
        Node* x = pq.top(); pq.pop();
        Node* y = pq.top(); pq.pop();
        Node* parent = NULL;
        if (x->freq < y->freq) parent = new Node(x->freq + y->freq, x, y);
        else parent = new Node(x->freq + y->freq, y, x);
        pq.push(parent);
    }

    Node* root = pq.top();

    vector<pair<char,string>> mapping;
    vector<string> preorderCodes;
    buildCodes(root, "", mapping, preorderCodes);

    for (size_t i = 0; i < preorderCodes.size(); i++) {
        cout << preorderCodes[i];
        if (i + 1 < preorderCodes.size()) cout << " ";
    }
    cout << endl;

    for (auto &p : mapping) {
        cout << p.first << " : " << p.second << endl;
    }

    struct Del {
        static void go(Node* n) {
            if (!n) return;
            go(n->left);
            go(n->right);
            delete n;
        }
    };
    Del::go(root);
    return 0;
}
