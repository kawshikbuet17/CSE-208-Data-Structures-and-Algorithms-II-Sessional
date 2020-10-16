#include<bits/stdc++.h>
using namespace std;
#define red 0
#define black 1

class node
{
public:
    int key;
    bool color;

    node* parent;
    node* left;
    node* right;
};


class Red_Black_Tree
{
public:
    node* root;
    node* NIL;

    Red_Black_Tree()
    {
        NIL = new node;
        NIL->key = -1;
        NIL->color = black;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;

        root = NIL;
    }

    void insert(int value)
    {
        ///cout<<"called insert "<<value<<endl;
        ///get root
        node *p = root;


        ///make new node
        node* t = new node;
        t->key = value;
        t->color = red;
        t->left = NIL;
        t->right = NIL;

        node* y = NIL;


        ///root NIL
        if(root==NIL)
        {
            root = t;
            root->parent = NIL;
        }


        ///root not NIL
        else
        {
            while(p != NIL)
            {
                y = p;
                if(t->key < p->key)
                    p = p->left;
                else
                    p = p->right;
            }

            ///set p as t's parent
            t->parent = y;
            t->key = value;

            ///set t as p's child
            if(y->key > t->key)
                y->left = t;
            else
                y->right = t;
        }

        ///insert fixup
        insert_fixup(t);
    }

    void insert_fixup(node* z)
    {
        //cout<<"called insert_fixup for value"<<z->key<<endl;
        /*if(root == z)
        {
            z->color = black;
            return;
        }*/

        while(z->parent->color == red)
        {
            ///p[z] is a left child of p[p[z]]
            if(z->parent == z->parent->parent->left)
            {
                ///set y as z's uncle
                node* y = z->parent->parent->right;


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
                node* y = z->parent->parent->left;


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
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }


                    ///case 3: z's uncle is black, z is a left child
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = black;
    }


    void RB_delete(node* z)
    {
        ///initialize y and x
        ///z = which node value will be deleted
        ///y = which node(place) will be deleted
        ///x = which node will replace y node
        node* y;
        node* x;


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


        ///put x node in y's place
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
        //return y
    }


    RB_delete_fixup(node* x)
    {
        while(x->color == black and x != root)
        {
            ///x is a left child
            if(x == x->parent->left)
            {
                ///set w as x's sibling
                node* w = x->parent->right;


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


                    ///case 4 : w is black, w.right is read, w.left is whatever
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
                node* w = x->parent->left;


                ///case 1 : w is red
                if(w->color == red)
                {
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
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
                        left_rotate(w);
                        w = x->parent->left;
                    }


                    ///case 4 : w is black, w.right is read, w.left is whatever
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = black;
    }


    node* RB_Find(node *p, int value)
    {
        if(p == NIL || p->key == value)
            return p;

        if(p->key < value)
            return RB_Find(p->right, value);

        return RB_Find(p->left, value);
    }

    bool isNode(node *p, int value)
    {
        if(RB_Find(p, value) != NIL)
            return true;
        return false;
    }

    void RB_delete_by_value(node *p, int value)
    {
        node* del = RB_Find(p, value);
        if(del != NIL)
            RB_delete(del);
    }


    void left_rotate(node* x) ///DONE
    {
        //cout<<"called left_rotate"<<endl;
        ///set y
        node* y;
        y = x->right;
        x->right = y->left;
        if(y->left != NIL)
            y->left->parent = x; ///maybe NIL check y.left
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


    void right_rotate(node* y) ///DONE
    {
        //cout<<"called right_rotate"<<endl;
        ///set x
        node* x;
        x = y->left;
        y->left = x->right;
        if(x->right != NIL)
            x->right->parent = y; ///x.right != nil check
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


    node* RB_successor(node* x)
    {
        if(x->right != NIL)
        {
            node* temp = x->right;
            while(temp->left != NIL)
                temp = temp->left;
            return temp;
        }

        node* y = x->parent;
        while(y != NIL and x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void RB_preorder_print(node* p)
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
    cout<<"To insert    : type I <space> value"<<endl;
    cout<<"To delete    : type D <space> value"<<endl;
    cout<<"To find      : type F <space> value"<<endl;
    cout<<endl;

    while(1)
    {
        char c;
        int inp;
        cin>>c>>inp;
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
                cout<<"true"<<endl;
            else
                cout<<"false"<<endl;
        }
    }
}
