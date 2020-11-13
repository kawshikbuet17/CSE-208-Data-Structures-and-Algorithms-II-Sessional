#include<bits/stdc++.h>
using namespace std;

#define INF INT_MAX
#define NIL NULL

class Node
{
public:
    int key;
    Node* parent;
    Node* child;
    Node* sibling;
    int degree;

};


class BinomialHeap
{
    Node* H;
    Node* Hreverse;
public:
    BinomialHeap() ///constructor
    {
        H = NIL;
        Hreverse = NIL;
    }

    ~BinomialHeap() ///destructor
    {
        delete H;
        delete Hreverse;
    }

    Node* setRoot(Node* x)
    {
        H = x;
    }

    Node* getRoot()
    {
        return H;
    }

    Node* makeBinomialHeap()
    {
        Node* node = NIL;
        return node;
    }

    void binomialLink(Node* y, Node* z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree+1;
    }

    Node* binomialHeapMinimum()
    {
        Node* y = NIL;
        Node* x = H;
        int minimum = INF;

        while(x != NIL)
        {
            if(x->key < minimum)
            {
                minimum = x->key;
                y = x;
            }
            x = x->sibling;
        }
        return y;
    }

    void binomialHeapMerge(Node* h1, Node* h2)
    {
        Node* h;

        ///if h1 nil, head points to h2
        if(h1 == NIL)
        {
            h = h2;
            H = h;
            return;
        }
        ///if h2 nil, head points to h1
        if(h2 == NIL)
        {
            h = h1;
            H = h;
            return;
        }

        ///if degree[h1] < degree[h2], h points to h1, h1 right shift
        if(h1->degree <= h2->degree)
        {
            h = h1;
            h1 = h1->sibling;
        }
        else
        {
            h = h2;
            h2 = h2->sibling;
        }

        Node* startMerge = h;  ///startMerge = starting pivot, h = pivot for ASC order of degree
        while(h1 != NIL && h2 != NIL)
        {
            if(h1->degree <= h2->degree)
            {
                h->sibling = h1;
                h1 = h1->sibling;
            }
            else
            {
                h->sibling = h2;
                h2 = h2->sibling;
            }
            h = h->sibling;
        }
        if(h1 == NIL)
        {
            h->sibling = h2;
        }
        else
        {
            h->sibling = h1;
        }
        H = startMerge;
    }


    void binomialHeapUnion(Node* h1, Node* h2)
    {
        binomialHeapMerge(h1, h2);

        if(H == NIL)
        {
            return;
        }

        Node* prev_x = NIL;
        Node* x = H;

        Node* next_x = x->sibling;

        while(next_x != NIL)
        {
            if((x->degree != next_x->degree) ||(next_x->sibling != NIL and next_x->sibling->degree == x->degree))
            {
                prev_x = x;
                x = next_x;
            }

            else
            {
                if(x->key <= next_x->key)
                {
                    x->sibling = next_x->sibling;
                    binomialLink(next_x, x);
                }

                else
                {
                    if(prev_x == NIL)
                    {
                        H = next_x;
                    }
                    else
                    {
                        prev_x->sibling = next_x;
                    }
                    binomialLink(x, next_x);
                    x = next_x;
                }
            }
            next_x = x->sibling;
        }
    }

    void binomialHeapInsert(int value)
    {
        Node* x = new Node;
        x->key = value;
        x->parent = NIL;
        x->child = NIL;
        x->sibling = NIL;
        x->degree = 0;

        binomialHeapUnion(H, x);
    }


    Node* binomialHeapExtractMin()
    {
        Hreverse = NIL;

        Node* y = NIL;
        Node* x = H;
        int minimum = INF;

        while(x != NIL)
        {
            if(x->key < minimum)
            {
                minimum = x->key;
                y = x;
            }
            x = x->sibling;
        }
        /// y is the minimum


        if(y == NIL)
            return NIL;
        if(y == H)
        {
            H = y->sibling;
        }
        else
        {
            Node* prev_y = H;
            while(prev_y->sibling != y)
            {
                prev_y = prev_y->sibling;
            }
            prev_y->sibling = y->sibling;
        }
        binomialHeapRevert(y->child);
        binomialHeapUnion(H, Hreverse);
        return y;
    }

    Node* binomialHeapRevert(Node* h)
    {
        if(h == NIL)
        {
            return NIL;
        }
        h->parent = NIL;
        stack<Node*> s;
        while(h != NIL)
        {
            s.push(h);
            h = h->sibling;
        }

        Node* curr = s.top();
        Node* temp = curr;
        s.pop();
        while(!s.empty())
        {
            curr->sibling = s.top();
            s.pop();
            curr = curr->sibling;
        }
        curr->sibling = NIL;
        Hreverse = temp;
    }



    void binomialHeapPrint()
    {
        cout<<"Printing Binomial Heap..."<<endl;
        Node* h = H;
        while(h != NIL)
        {
            cout<<"Binomial Tree, B"<<h->degree<<endl;
            vector<int>v;
            queue <Node*> q;
            q.push(h);
            while(!q.empty())
            {
                Node* t = q.front();
                q.pop();
                v.push_back(t->key);

                if(t->child != NIL)
                {
                    q.push(t->child);
                    Node* sib = t->child->sibling;
                    while(sib != NIL)
                    {
                        q.push(sib);
                        sib = sib->sibling;
                    }
                }
            }
            int level = 0;
            int upperLevel = h->degree;
            int how_many = nCr(upperLevel, level);
            int count = how_many;
            cout<<"Level "<<level<<" : ";
            for(auto i : v)
            {
                if(count==0 && level<=upperLevel)
                {
                    level++;
                    how_many = nCr(upperLevel, level);
                    count = how_many;
                    cout<<endl;
                    cout<<"Level "<<level<<" : ";
                }
                cout<<i<<" ";
                count--;

            }
            h = h->sibling;
            if(q.empty())
                cout<<endl;
        }
    }

    int nCr(int n, int r)
    {
        return factorial(n)/(factorial(r)*factorial(n-r));
    }

    int factorial(int n)
    {
        if(n<=1)
            return 1;
        return n*factorial(n-1);
    }
};

int main()
{
    BinomialHeap bh;
    freopen("infile.txt","r",stdin);      ///comment this line to give input in console
    freopen ("outfile.txt","w",stdout);  ///comment this line to see output in console

    char c;
    while(cin>>c)
    {
        if(c == 'I' || c == 'i')
        {
            int x;
            cin>>x;
            bh.binomialHeapInsert(x);
        }
        else if(c == 'F' || c == 'f')
        {
            cout<<"Find-Min returned ";
            Node* temp = bh.binomialHeapMinimum();
            cout<<temp->key<<endl;
        }
        else if(c == 'E' || c == 'e')
        {
            cout<<"Extract-Min returned ";
            Node* temp = bh.binomialHeapExtractMin();
            cout<<temp->key<<endl;
        }
        else if(c == 'P' || c == 'p')
        {
            bh.binomialHeapPrint();
        }
        else if(c == 'U' || c == 'u')
        {
            BinomialHeap* bh2 = new BinomialHeap;
            int value;
            string s;
            getline(cin, s);
            istringstream is(s);
            while(is>>value)
            {
                bh2->binomialHeapInsert(value);
            }
            bh.binomialHeapUnion(bh.getRoot(), bh2->getRoot());
        }
    }
}
