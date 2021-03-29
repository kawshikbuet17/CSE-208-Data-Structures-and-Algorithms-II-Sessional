#define NIL -1
#define INF INT_MAX

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


class Graph
{
    int V;
    vector<Edge>*adjList;
    vector<vector<int>>residue;
    vector<int>parent;
    vector<int>visited;


    fstream outfile;



public:
    void setnVertices(int V)
    {
        this->V = V;
        adjList=new vector<Edge>[V];
        residue.resize(V, vector<int>(V));
        parent.resize(V);
        visited.resize(V);
        outfile.open("output.txt",ios::in | ios::out);
    }
    void addEdge(int u, int v, int w)
    {
        //cout<<"added edge = "<<u<<" "<<v<<" "<<w<<endl;

        residue[u][v] +=  w;
        int flag=0;
        for(auto i: adjList[u])
        {
            if(i.getv()==v)
            {
                flag=1;
            }
        }
        if(flag==1)
        {
            reweightEdge(u, v, residue[u][v]);
        }
        if(flag==0)
        {
            adjList[u].push_back(Edge(v,w));
            adjList[v].push_back(Edge(u,0));
        }

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



    int bfs(int s, int t)
    {

        //fill(parent.begin(), parent.end(), -1);
        for(int i=0; i<V; i++)
            parent[i] = -1;
        parent[s] = -2;

        queue<pair<int, int>> q;
        q.push({s, INF});



        while(!q.empty())
        {
            auto x = q.front();
            int current = x.first;
            int flow = x.second;
            q.pop();

            for(auto i : adjList[current])
            {
                int next = i.getv();
                if(parent[next] == -1 && residue[current][next])
                {
                    parent[next] = current;

                    int new_flow = min(flow, residue[current][next]);
                    if(next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }



    int maxflow(int s, int t)
    {
        int flow = 0;

        int new_flow;

        while(new_flow = bfs(s, t))
        {
            flow = flow + new_flow;
            int current = t;
            while(current != s)
            {
                int prev = parent[current];
                residue[prev][current] = residue[prev][current] - new_flow;
                residue[current][prev] = residue[current][prev] + new_flow;
                current = prev;
            }
        }
        return flow;
    }

    void print_maxflow(int s, int t)
    {
        int maximum_flow = maxflow(s, t);

        cout<<maximum_flow<<endl;
        outfile<<maximum_flow<<endl;

        for(int i=0; i<V; i++)
        {
            for(auto x : adjList[i])
            {
                if(x.getweight() != 0)
                {
                    int going = x.getweight()-residue[i][x.getv()];
                    int cap = x.getweight();
                    if(going<0)
                    {
                        cout<<i<<" "<<x.getv()<<" "<<0<<"/"<<cap<<endl;
                        outfile<<i<<" "<<x.getv()<<" "<<0<<"/"<<cap<<endl;
                    }

                    else
                    {
                        cout<<i<<" "<<x.getv()<<" "<<going<<"/"<<cap<<endl;
                        outfile<<i<<" "<<x.getv()<<" "<<going<<"/"<<cap<<endl;
                    }

                }
            }
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

    int s, t;
    infile>>s>>t;
    //cout<<g.maxflow(s, t)<<endl;
    g.print_maxflow(s, t);
}

