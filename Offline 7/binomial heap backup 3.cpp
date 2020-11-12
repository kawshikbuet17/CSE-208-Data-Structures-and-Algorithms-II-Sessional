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

    Node* setRoot(Node* x) ///get Heap pointer
    {
        H = x;
    }

    Node* getRoot() ///get Heap pointer
    {
        return H;
    }

    Node* makeBinomialHeap() ///make NULL pointer Node
    {
        Node* node = NIL;
        return node;
    }

    void binomialLink(Node* y, Node* z) ///adds y as a child of z
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree+1;
    }

    Node* binomialHeapMinimum(Node* h) ///Find-Min
    {
        Node* y = NIL;
        Node* x = h;
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
        Node* h = new Node;

        ///if h1 nil, head points to h2
        if(h1 == NULL)
        {
            h = h2;
            this->H = h;
            return;
        }
        ///if h2 nil, head points to h1
        if(h2 == NULL)
        {
            h = h1;
            this->H = h;
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

        Node* startMerge = h;
        while(h1 != NULL && h2 != NULL)
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
        if(h1 != NULL)
        {
            h->sibling = h1;
        }
        else
        {
            h->sibling = h2;
        }
        this->H = startMerge;
    }


    void binomialHeapUnion(Node* h1, Node* h2)
    {
        binomialHeapMerge(h1, h2);

        if(this->H == NIL)
        {
            return;
        }

        Node* prev_x = NIL;
        Node* x = this->H;

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
                        this->H = next_x;
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


    Node* binomialHeapExtractMin()//(Node* H1)
    {

        Hreverse = NIL;
        Node* x = binomialHeapMinimum(H);
        if(x == NULL)
            return NULL;
        if(x == this->H)
        {
            this->H = x->sibling;
        }
        else
        {
            Node* prev_x = this->H;
            while(prev_x->sibling != x)
            {
                prev_x = prev_x->sibling;
            }
            prev_x->sibling = x->sibling;
        }
        binomialHeapRevert(x->child);
        binomialHeapUnion(H, Hreverse);
        return x;
    }

    binomialHeapRevert(Node* h)
    {
        Node* next;
        Node* tail = NIL;

        if(h == NIL)
        {
            return NIL;
        }
        h->parent = NIL;
        while(h->sibling)
        {
            next = h->sibling;
            h->sibling = tail;
            tail = h;
            h = next;
            h->parent = NIL;
        }
        h->sibling = tail;
        Hreverse = h;
    }



    void binomialHeapPrint()
    {
        cout<<"Printing Binomial Heap..."<<endl;
        Node* h = this->H;
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
    freopen("in.txt","r",stdin);
    //freopen ("outfile.txt","w",stdout); ///comment this line to see output in console

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
            Node* temp = bh.binomialHeapMinimum(bh.getRoot());
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
