#include<bits/stdc++.h>
using namespace std;
#define red 0
#define black 1

class Node
{
public:
    int key;
    bool color;

    Node* parent;
    Node* left;
    Node* right;
};


class Red_Black_Tree
{
public:
    Node* root;
    Node* NIL;

    Red_Black_Tree()  ///constructor
    {
        root = new Node;
        NIL = new Node;

        NIL->color = black;
        NIL->left = NULL;
        NIL->right = NULL;

        root = NIL;
        root->parent = NIL;
    }

    ~Red_Black_Tree()   ///destructor
    {
        delete root;
        delete NIL;
    }


    void left_rotate(Node* x)
    {
        ///set y
        Node* y;
        y = x->right;
        x->right = y->left;
        if(y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;


        ///x is root
        if(x->parent == NIL)
            root = y;


        ///x is left child of p[x]
        else if(x == x->parent->left)
            x->parent->left = y;


        ///x is right child of p[x]
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }


    void right_rotate(Node* y)
    {
        ///set x
        Node* x;
        x = y->left;
        y->left = x->right;
        if(x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;


        ///y is root
        if(y->parent == NIL)
            root = x;


        ///y is the left child of p[y]
        else if(y == y->parent->left)
            y->parent->left = x;


        ///y is the right child of p[y]
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }


    Node* RB_successor(Node* x)
    {
        if(x->right != NIL)
        {
            Node* temp = x->right;
            while(temp->left != NIL)
                temp = temp->left;
            return temp;
        }

        Node* y = x->parent;
        while(y != NIL and x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }


    void insert(int value)
    {
        Node* z = new Node;
        z->key = value;
        z->color = red;
        z->left = NIL;
        z->right = NIL;

        Node* x = root;
        Node* y = NIL;

        while(x != NIL)
        {
            y = x;
            if(z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;

        if(y==NIL)
        {
            root = z;
        }

        else if(z->key < y->key)
            y->left = z;

        else
            y->right = z;

        insert_fixup(z);
    }

    void insert_fixup(Node* z)
    {
        while(z->parent->color == red)
        {
            ///p[z] is a left child of p[p[z]]
            if(z->parent == z->parent->parent->left)
            {
                ///set y as z's uncle
                Node* y = z->parent->parent->right;


                ///case 1 : z's uncle is red, z is a right child
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }

                else
                {
                    ///case 2 : z's uncle is black, z is a right child
                    if(z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
                    }


                    ///case 3: z's uncle is black, z is a left child
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotate(z->parent->parent);
                }
            }


            ///p[z] is a right child of p[p[z]]
            else
            {
                ///set y as z's uncle
                Node* y = z->parent->parent->left;


                ///case 1
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }

                else
                {
                    ///case 2
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }


                    ///case 3
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = black;
    }




    void RB_delete(Node* z)
    {
        ///initialize y and x
        ///z = which Node value will be deleted
        ///y = which Node(place) will be deleted
        ///x = which Node will replace y Node
        Node* y;
        Node* x;


        ///if z has <2 children
        if(z->left == NIL || z->right == NIL)
        {
            y = z;
        }


        ///if z has >=2 children
        else
        {
            y = RB_successor(z);
        }


        ///put x Node in y's place
        if(y->left != NIL)
        {
            x = y->left;
        }
        else
        {
            x = y->right;
        }


        ///set p[x]
        x->parent = y->parent;


        ///if y was the root
        if(y->parent == NIL)
        {
            root = x;
        }

        ///if y was a left child
        else if(y==y->parent->left)
        {
            y->parent->left = x;
        }


        ///if y was a right child
        else
        {
            y->parent->right = x;
        }


        ///if y are not z
        if(y != z)
        {
            z->key = y->key;
        }


        ///if y is black, then fixup
        if(y->color == black)
        {
            RB_delete_fixup(x);
        }
    }


    RB_delete_fixup(Node* x)
    {
        while(x->color == black and x != root)
        {
            ///x is a left child
            if(x == x->parent->left)
            {
                ///set w as x's sibling
                Node* w = x->parent->right;


                ///case 1 : w is red
                if(w->color == red)
                {
                    w->color = black;
                    x->parent->color = red;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }


                ///case 2 : w is black, both children of w are black
                if(w->left->color == black and w->right->color == black)
                {
                    w->color = red;
                    x = x->parent;
                }

                else
                {
                    ///case 3 : w is black, w.left is red, w.right is black
                    if(w->right->color == black)
                    {
                        w->left->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->parent->right;
                    }


                    ///case 4 : w is black, w.right is red, w.left is whatever
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    left_rotate(x->parent);
                    x = root;
                }
            }


            ///x is a right child
            else
            {
                ///set w as x's sibling
                Node* w = x->parent->left;


                ///case 1
                if(w->color == red)
                {
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }


                ///case 2
                if(w->left->color == black and w->right->color == black)
                {
                    w->color = red;
                    x = x->parent;
                }

                else
                {
                    ///case 3
                    if(w->left->color == black)
                    {
                        w->right->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->parent->left;
                    }


                    ///case 4
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = black;
    }


    Node* RB_Find(Node *p, int value)
    {
        if(p == NIL || p->key == value)
            return p;

        if(p->key < value)
            return RB_Find(p->right, value);

        return RB_Find(p->left, value);
    }


    bool isNode(Node *p, int value)
    {
        if(RB_Find(p, value) != NIL)
            return true;
        return false;
    }


    void RB_delete_by_value(Node *p, int value)
    {
        Node* del = RB_Find(p, value);
        if(del != NIL)
            RB_delete(del);
    }


    void RB_preorder_print(Node* p)
    {
        if(p == NIL)
        {
            return;
        }

        if(p->color == 1)
            cout<<p->key<<":b";
        else
            cout<<p->key<<":r";

        if(p->left==NIL && p->right==NIL)
            return;

        cout<<"(";
        RB_preorder_print(p->left);
        cout<<")(";
        RB_preorder_print(p->right);
        cout<<")";
    }
};


int main()
{
    Red_Black_Tree rbt;

    cout<<"------ Red Black Tree ------"<<endl;
    cout<<"----- Go to outfile.txt-----"<<endl;
    cout<<endl;

    ifstream infile;
    infile.open("input.txt");

    if(!infile.is_open())
    {
        cout<<"File input failed. Try again..."<<endl;
        exit(1);
    }

    freopen ("outfile.txt","w",stdout); ///comment this line to see output in console
    char c;
    int inp;

    while(!infile.eof())
    {

        infile>>c>>inp;
        if(!infile.good())
            break;
        if(c=='I' || c=='i')
        {
            rbt.insert(inp);
            rbt.RB_preorder_print(rbt.root);cout<<endl;
        }
        else if(c=='D' || c=='d')
        {
            rbt.RB_delete_by_value(rbt.root, inp);
            rbt.RB_preorder_print(rbt.root);cout<<endl;
        }
        else
        {
            if(rbt.isNode(rbt.root, inp))
                cout<<"True"<<endl;
            else
                cout<<"False"<<endl;
        }
    }

    fclose (stdout);
    return 0;
}
