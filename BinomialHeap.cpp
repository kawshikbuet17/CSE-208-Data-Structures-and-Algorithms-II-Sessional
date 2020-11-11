#include <bits/stdc++.h>
using namespace std;

int C(int n, int r)
{
    if(n < r)   return -1;
    if(r == n || r == 0)  return 1;
    if(r == 1)  return n;
    if(r > (n-r))   r = n-r;
    return C(n-1, r) + C(n-1, r-1);
}

class node
{
public:
    int key;
    node* p;
    node* child;
    node* next;
    int degree;
};

class BinomialHeap
{
public:
    node* head;
    BinomialHeap(){ head = NULL; }
    ~BinomialHeap(){ delete head; }
    node* FindMin();
    void BinomialLink(node* y, node* z);
    void BinomialHeapMerge(BinomialHeap* H2);
    void BinomialHeapUnion(BinomialHeap* H2);
    void Insert(int n);
    node* ReverseRoots(node* h);
    node* ExtractMin();
    void print();
};

node* BinomialHeap::FindMin()
{
    node* y = NULL;
    node* x = this->head;
    int mn = 1 << 20;
    while(x != NULL){
        if(x->key < mn){
            mn = x->key;
            y = x;
        }
        x = x->next;
    }
    return y;
}

void BinomialHeap::BinomialLink(node* y, node* z) ///makes z the parent of y
{
    y->p = z;
    y->next = z->child;
    z->child = y;
    z->degree++;
}


void BinomialHeap::BinomialHeapMerge(BinomialHeap* H2)
{
    node* h = new node;
    node* h1 = this->head;
    node* h2 = H2->head;
    if(h1 == NULL && h2 == NULL)    return;
    if(h1 == NULL)  { this->head = h2; return; }
    if(h2 == NULL)  { this->head = h1; return; }
    if(h1->degree < h2->degree){
        h = h1;
        h1 = h1->next;
    }
    else{
        h = h2;
        h2 = h2->next;
    }
    node* t = h;
    while(h1 != NULL && h2 != NULL){
        if(h1->degree < h2->degree){
            t->next = h1;
            h1 = h1->next;
        }
        else{
            t->next = h2;
            h2 = h2->next;
        }
        t = t->next;
    }
    if(h1 != NULL){
        t->next = h1;
    }
    else{
        t->next = h2;
    }
    this->head = h;
}

void BinomialHeap::BinomialHeapUnion(BinomialHeap* H2)
{
    BinomialHeapMerge(H2);

    if(this->head == NULL){
        return;
    }
    node *x = this->head;
    node* prev_x = NULL;
    node* next_x = x->next;
    while(next_x != NULL){
        if((x->degree != next_x->degree) || (next_x->next != NULL && x->degree == next_x->next->degree)){
            prev_x = x;
            x = next_x;
        }
        else{
            if(x->key <= next_x->key){
                x->next = next_x->next;
                BinomialLink(next_x, x);
            }
            else{
                if(prev_x == NULL){
                    this->head = next_x;
                }
                else{
                    prev_x->next = next_x;
                }
                BinomialLink(x, next_x);
                x = next_x;
            }
        }
        next_x = x->next;
    }
}

void BinomialHeap::Insert(int n)
{
    BinomialHeap* H2 = new BinomialHeap;
    node* x = new node;
    x->p = NULL;
    x->next = NULL;
    x->child = NULL;
    x->degree = 0;
    x->key = n;
    H2->head = x;

    BinomialHeapUnion(H2);
}

node* BinomialHeap::ReverseRoots(node* h)
{
    if(h == NULL)   return NULL;
    node* prev_h = NULL;
    node* next_h;
    h->p = NULL;
    while(h->next != NULL){
        next_h = h->next;
        h->next = prev_h;
        prev_h = h;
        h = next_h;
        h->p = NULL;
    }
    h->next = prev_h;
    return h;
}

node* BinomialHeap::ExtractMin()
{
    node* x = FindMin();
    if(x == NULL)   return NULL;
    if(x == this->head){
        this->head = x->next;
    }
    else{
        node* prev_x = this->head;
        while(prev_x->next != x){
            prev_x = prev_x->next;
        }
        prev_x->next = x->next;
    }
    BinomialHeap* H2 = new BinomialHeap;
    H2->head = ReverseRoots(x->child);
    BinomialHeapUnion(H2);
    return x;

}

void BinomialHeap::print()
{
    queue<node*> q;
    cout << "Printing Binomial Heap...\n";
    node* h = this->head;
    node* t;
    while(h != NULL){
        int n = h->degree;
        cout << "Binomial Tree, B" << n << endl;
        q.push(h);
        int i = 1, lvl = 1;
        cout << "Level 0 : ";
        while(!q.empty()){
            t = q.front();
            q.pop();
            cout << t->key << " ";
            i--;
            if(!i && lvl <= n){
                cout << "\nLevel " << lvl << " : ";
                i = C(n, lvl++);
            }
            t = t->child;

            while(t != NULL){
                q.push(t);
                t = t->next;
            }

        }

        h = h->next;
        if(q.empty())   cout << endl;
    }
}

int main()
{
    BinomialHeap H;

    freopen("out.txt", "w", stdout);
    if(!freopen("in.txt", "r", stdin)){
        cout << "Error opening file\n";
        exit(1);
    }

    char c;
    int x, y;

    while(cin >> c){
        if(c == 'F'){
            node* minKeyNode = H.FindMin();
            if(minKeyNode != NULL)
                cout << "Find-Min returned " << minKeyNode->key << endl;
        }
        else if(c == 'E'){
            node* minKeyNode = H.ExtractMin();
            if(minKeyNode != NULL)
                cout << "Extract-Min returned " << minKeyNode->key << endl;
        }
        else if(c == 'I'){
            cin >> x;
            H.Insert(x);
        }
        else if(c == 'U'){
            BinomialHeap* H1 = new BinomialHeap;
            string str;
            getline(cin, str);
            istringstream is(str);
            while(is >> x)  H1->Insert(x);
            H.BinomialHeapUnion(H1);
        }
        else if(c == 'P'){
            H.print();
        }
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
