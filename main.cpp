#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left{};
    Node* right{};
    explicit Node(int k) : key(k) {}
};

Node* make(int v){ return new Node(v); }

void preorder(Node* r, vector<int>& out){      // сверху вниз
    if(!r) return;
    out.push_back(r->key);
    preorder(r->left, out);
    preorder(r->right, out);
}
void inorder(Node* r, vector<int>& out){       // слева направо
    if(!r) return;
    inorder(r->left, out);
    out.push_back(r->key);
    inorder(r->right, out);
}
void postorder(Node* r, vector<int>& out){     // снизу вверх
    if(!r) return;
    postorder(r->left, out);
    postorder(r->right, out);
    out.push_back(r->key);
}
vector<int> levelorder(Node* r){               // сверху вниз, по уровням
    vector<int> out;
    if(!r) return out;
    queue<Node*> q; q.push(r);
    while(!q.empty()){
        Node* cur = q.front(); q.pop();
        out.push_back(cur->key);
        if(cur->left)  q.push(cur->left);
        if(cur->right) q.push(cur->right);
    }
    return out;
}

int size(Node* r){
    return r ? 1 + size(r->left) + size(r->right) : 0;
}
long long checksum(Node* r){
    return r ? r->key + checksum(r->left) + checksum(r->right) : 0LL;
}
int height(Node* r){                            // в уровнях; лист = 1
    return r ? 1 + max(height(r->left), height(r->right)) : 0;
}
void sumDepth(Node* r, int d, long long& acc){  // для средней глубины
    if(!r) return;
    acc += d;
    sumDepth(r->left, d+1, acc);
    sumDepth(r->right, d+1, acc);
}

// вывод
template<class T>
void printSeq(const string& title, const T& a){
    cout << title << ": ";
    bool first=true;
    for (auto x: a){ if(!first) cout << ' '; first=false; cout << x; }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1,20);

    Node* n1 = make(dist(rng));
    Node* n2 = make(dist(rng));
    Node* n3 = make(dist(rng));
    Node* n4 = make(dist(rng));
    Node* n5 = make(dist(rng));
    Node* n6 = make(dist(rng));

    Node* root = n1;
    n1->left  = n2;
    n1->right = n5;
    n2->right = n3;
    n3->left  = n4;
    n5->right = n6;

    // --- ОБХОДЫ ---
    vector<int> pre, in, post;
    preorder(root, pre);     // сверху вниз
    inorder(root,  in);      // слева направо
    postorder(root, post);   // снизу вверх
    auto lvl = levelorder(root);

    // --- МЕТРИКИ ---
    int sz = size(root);
    long long cs = checksum(root);
    int h = height(root);
    long long sumD = 0; sumDepth(root, 0, sumD);         // глубина корня = 0
    double avgDepth = sz ? (double)sumD / sz : 0.0;

    // --- ВЫВОД ---
    printSeq("Сверху вниз", pre);
    printSeq("Слева направо", in);
    printSeq("Снизу вверх", post);
    printSeq("По уровням", lvl);

    cout << "Размер: " << sz << "\n";
    cout << "Контрольная сумма: " << cs << "\n";
    cout << "Высота: " << h << "\n";
    cout.setf(std::ios::fixed); cout << setprecision(2);
    cout << "Средняя глубина узла: " << avgDepth << "\n";

    // освобождение памяти
    vector<Node*> stack = {root};
    while(!stack.empty()){
        Node* cur = stack.back(); stack.pop_back();
        if(!cur) continue;
        stack.push_back(cur->left);
        stack.push_back(cur->right);
        delete cur;
    }
    return 0;
}
