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

    Node* getRoot()
    {
        return H;
    }

    Node* makeBinomialHeap()
    {
        Node* node = NIL;
        return node;
    }
    int binomialHeapMinimum() /// O(log n)
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
        return y->key;
    }

    Node* binomialHeapFind(Node* from, int value)
    {
        Node* x = from;
        bool found = false;

        if(x->key == value)
        {
            found = true;
            return x;
        }

        if(x->child != NIL and found == false)
        {
            binomialHeapFind(x->child, value);
        }

        if(x->sibling != NIL and found == false)
        {
            binomialHeapFind(x->sibling, value);
        }
    }


    binomialLink(Node* y, Node* z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree+1;
    }


    Node* binomialHeapUnion(Node* H1, Node* H2)
    {
        Node* Heap = makeBinomialHeap();
        Heap = binomialHeapMerge(H1, H2);

        if(Heap == NIL)
        {
            return Heap;
        }

        Node* prev_x = NIL;
        Node* x = Heap;

        Node* next_x = x->sibling;

        ///traverse from first to last sibling
        while(next_x != NIL)
        {
            ///if next degree is higher OR
            if(x->degree != next_x->degree ||(next_x->sibling != NIL and next_x->sibling->degree == x->degree))
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
                        Heap = next_x;
                    }
                    else
                    {
                        prev_x->sibling = next_x;
                    }
                    binomialLink(x, next_x);
                }
            }
            next_x = x->sibling;
        }
        return Heap;
    }

    Node* binomialHeapMerge(Node* H1, Node* H2)
    {
        ///build new heap
        Node* Heap = makeBinomialHeap();

        Node* y;
        Node* z;
        Node* a;
        Node* b;

        ///access H1, H2
        y = H1;
        z = H2;

        ///make H = min of H1 and H2
        if(y != NIL)
        {
            if(z != NIL)
            {
                if(y->degree <= z->degree)
                    Heap = y;
                else
                    Heap = z;
            }
            else
                Heap = y;
        }
        else
            Heap = z;


        ///attach one after another order ASC
        while(y != NIL and z!= NIL)
        {
            if(y->degree < z->degree)
                y = y->sibling;
            else if(y->degree == z->degree)
            {
                a = y->sibling;
                y->sibling = z;
                y = a;
            }
            else
            {
                b = z->sibling;
                z->sibling = y;
                z = b;
            }
        }
        return Heap;
    }


    void binomialHeapInsert(int value) ///done
    {
        Node* x = new Node;
        x->key = value;

        Node* H_prime = NIL;
        x->parent = NIL;
        x->child = NIL;
        x->sibling = NIL;
        x->degree = 0;
        H_prime = x;
        H = binomialHeapUnion(H, H_prime);
        //cout<<"inserted "<<H_prime->key<<endl;
        //Display(H);
    }

    binomialHeapDecreaseKey(Node* x, int k) ///done
    {
        if(k > x->key)
            cout<<"new key is greater than current key"<<endl;

        x->key = k;
        Node* y = x;
        Node* z = y->parent;

        while(z != NIL and y->key < z->key)
        {
            swap(y->key, z->key);
            y = z;
            z = y->parent; ///z = z->parent diye dekha hobe noile
        }
    }

    binomialHeapDelete(Node* x) ///done
    {
        binomialHeapDecreaseKey(x, -INF);
        binomialHeapExtractMin(H);
    }

    binomialHeapExtractMin(Node* H1)
    {
        Hreverse = NIL;
        Node* t = NIL;
        Node* x = H1;

        if(x == NIL)
        {
            cout<<"Nothing to Extract"<<endl;
            //return x;
        }

        int minimum = x->key;

        Node* p = x;

        while(p->sibling != NIL)
        {
            if(p->sibling->key < minimum)
            {
                minimum = p->sibling->key;
                t = p;
                x = p->sibling;
            }
            p = p->sibling;
        }

        if(t == NIL and x->sibling == NIL)
            H1 = NIL;
        else if(t == NIL)
            H1 = x->sibling;
        else if(t->sibling == NIL)
            t = NIL;
        else
            t->sibling = x->sibling;

        if(x->child != NIL)
        {
            binomialHeapRevertList(x->child);
            x->child->sibling = NIL;
        }
        H = binomialHeapUnion(H1, Hreverse);
        //return x;
    }

    binomialHeapRevertList(Node* y) ///done
    {
        if(y->sibling == NIL)
            Hreverse = y;

        else
        {
            binomialHeapRevertList(y->sibling);
            y->sibling->sibling = y;
        }
    }


    void Display(Node *h)
{
    while (h)
    {
        cout << h->key << " ";
        Display(h->child);
        h = h->sibling;
    }
}
};

int main()
{
    BinomialHeap bh;
    bh.binomialHeapInsert(10);
    bh.binomialHeapInsert(20);
    bh.binomialHeapInsert(30);
    bh.binomialHeapInsert(40);
    bh.binomialHeapInsert(50);
    bh.Display(bh.getRoot());
    bh.binomialHeapExtractMin(bh.getRoot());
    cout<<endl;
    bh.Display(bh.getRoot());
    bh.binomialHeapExtractMin(bh.getRoot());
    cout<<endl;
    bh.Display(bh.getRoot());
}
