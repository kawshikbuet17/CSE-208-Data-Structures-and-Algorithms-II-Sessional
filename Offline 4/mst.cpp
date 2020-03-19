#define NIL -1
#define INFINITY INT_MAX
#define WHITE 1
#define GRAY 2

#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
using namespace std;


class Edge
{
    int v;
    int w;
public:
    Edge(int v, int w)
    {
        this->v = v;
        this->w = w;
    }
    void setv(int v)
    {
        this->v=v;
    }
    void setweight(int w)
    {
        this->w=w;
    }
    int getv()
    {
        return v;
    }
    int getweight()
    {
        return w;
    }
};

class Edge2
{
    int u, v;
    int w;
public:
    Edge2(int u, int v, int w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    int getu()
    {
        return u;
    }
    int getv()
    {
        return v;
    }
    int getw()const
    {
        return w;
    }
};

bool comp(const Edge2& lhs, const Edge2& rhs)
{
    return lhs.getw() < rhs.getw();
}

class Graph
{
    int V, neg =0;
    int mst_w=0;
    vector<Edge>*adjList;
    vector<Edge2>edge;
    vector<Edge2>T;
    vector<int>key;
    vector<int>parent;
    vector<int>visited;
    vector<int>path;

    fstream outfile;



public:
    void setnVertices(int V)
    {
        this->V = V;
        adjList=new vector<Edge>[V];
        parent.resize(V);
        key.resize(V);
        visited.resize(V);
        outfile.open("output.txt",ios::in | ios::out);
    }
    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back(Edge(v,w));
        adjList[v].push_back(Edge(u,w));
        edge.push_back(Edge2(u,v,w));
        edge.push_back(Edge2(v,u,w));
    }


    void printGraph()
    {
        for(int u=0; u<V; u++)
        {
            int count=0;
            cout<<u<<" : ";
            for(auto e : adjList[u])
            {
                if(count==0)
                {
                    cout<<e.getv()<<"("<<e.getweight()<<")";
                    outfile<<e.getv()<<"("<<e.getweight()<<")";
                }
                else
                {
                    cout<<" --> "<<e.getv()<<"("<<e.getweight()<<")";
                    outfile<<" --> "<<e.getv()<<"("<<e.getweight()<<")";
                }
                count++;
            }
            cout<<endl;
            outfile<<endl;
        }
    }

    void removeEdge(int u, int v)
    {
        for(int i=0; i<adjList[u].size(); i++)
        {
            if(adjList[u][i].getv()==v)
            {
                swap(adjList[u][i], adjList[u][adjList[u].size()-1]);
                adjList[u].pop_back();
            }
        }
    }

    Edge* searchEdge(int u, int v)
    {
        for(auto e : adjList[u])
        {
            if(e.getv()==v)
                return &e;
        }
        return NULL;
    }

    void reweightEdge(int u, int v, int w)
    {
        for(int i=0; i<adjList[u].size(); i++)
        {
            if(adjList[u][i].getv()==v)
                adjList[u][i].setweight(w);
        }
    }

    bool isEdge(int u, int v)
    {
        for(auto e : adjList[u])
        {
            if(e.getv()==v)
                return true;
        }
        return false;
    }

    int getWeight(int u, int v)
    {
        for(auto e : adjList[u])
        {
            if(e.getv()==v)
                return e.getweight();
        }
        return INFINITY;
    }


    void mst_prim(int source)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>> q;

        for(int i=0; i<V; i++)
        {
            key[i] = INFINITY;
            parent[i]=-1;
            visited[i]=WHITE;
        }

        q.push(make_pair(0, source));
        key[source] = 0;


        while(!q.empty())
        {
            int u = q.top().second;
            q.pop();
            if(visited[u]==GRAY)
            {
                continue;
            }
            visited[u] = GRAY;

            for(auto i:adjList[u])
            {
                int v = i.getv();
                int w = abs(i.getweight());
                if(w < key[v])
                {
                    key[v] = w;
                    q.push(make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }
    }

    void print_prim_mst(int source)
    {

        cout<<"Prim's Algorithm : "<<endl;
        outfile<<"Prim's Algorithm : "<<endl;
        mst_w=0;
        mst_prim(source);
        for(int i=0; i<V; i++)
        {
            if(parent[i] != -1)
            {
                for(auto e : adjList[parent[i]])
                {
                    if(e.getv()==i)
                    {
                        mst_w += e.getweight();
                        break;
                    }
                }
            }
        }
        cout<<"MST weight = "<<mst_w<<endl;
        outfile<<"MST weight = "<<mst_w<<endl;

        cout<<"Root Node = "<<source<<endl;
        outfile<<"Root Node = "<<source<<endl;
        for(int i=0; i<V; i++)
        {
            if(i==source)
                ;
            else
            {
                cout<<parent[i]<<"\t"<<i<<endl;
                outfile<<parent[i]<<"\t"<<i<<endl;
            }
        }
    }

    int find_set(int i)
    {
        if(i==parent[i])
            return i;
        else
            return find_set(parent[i]);
    }

    void union_set(int u, int v)
    {
        parent[u]=parent[v];
    }

    void mst_kruskal()
    {
        for(int i=0; i<V; i++)
            parent[i]=i;
        mst_w=0;
        sort(edge.begin(), edge.end(), comp);

        for(int i=0; i<edge.size(); i++)
        {
            int a = find_set(edge[i].getu());
            int b = find_set(edge[i].getv());
            if(a != b)
            {
                T.push_back(edge[i]);
                mst_w += edge[i].getw();
                union_set(a, b);
            }
        }
    }

    void print_kruskal_mst()
    {

        cout<<"Kruskal Algorithm : "<<endl;
        outfile<<"Kruskal Algorithm : "<<endl;
        mst_kruskal();
        cout<<"MST weight = "<<mst_w<<endl;
        outfile<<"MST weight = "<<mst_w<<endl;
        for(int i=0; i<T.size(); i++)
        {
            cout<<T[i].getu()<<"\t"<<T[i].getv()<<endl;
            outfile<<T[i].getu()<<"\t"<<T[i].getv()<<endl;
        }
    }
};

int main()
{

    Graph g;
    ifstream infile;
    infile.open("input.txt");

    if(!infile.is_open())
    {
        cout<<"File input failed. Try again..."<<endl;
        exit(1);
    }

    int N, M;
    infile>>N>>M;
    g.setnVertices(N);

    for(int i=0; i<M; i++)
    {
        int u, v;
        int w;
        infile>>u>>v>>w;
        g.addEdge(u,v,w);
    }

    g.print_prim_mst(rand()%(N-1));
    g.print_kruskal_mst();
}

