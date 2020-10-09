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
    vector<int>color;


    fstream outfile;



public:
    void setnVertices(int V)
    {
        this->V = V;
        adjList=new vector<Edge>[V+2];
        residue.resize(V+2, vector<int>(V+2));
        parent.resize(V+2);
        visited.resize(V);
        color.resize(V);
        outfile.open("output.txt",ios::in | ios::out);
    }

    void addEdge(int u, int v, int w)
    {

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
            adjList[u].push_back(Edge(v,residue[u][v]));
            adjList[v].push_back(Edge(u,0));
        }
    }

    void printGraph()
    {
        for(int u=0; u<V+2; u++)
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

    void reweightEdge(int u, int v, int w)
    {
        for(int i=0; i<adjList[u].size(); i++)
        {
            if(adjList[u][i].getv()==v)
                adjList[u][i].setweight(w);
        }
    }


    int bfs(int s, int t)
    {

        fill(parent.begin(), parent.end(), -1);
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


    bool dfs(int v, int c)
    {
        visited[v] = 1;
        color[v] = c;

        for(auto i : adjList[v])
        {
            int child = i.getv();
            if(visited[child] == 0)
            {
                if(dfs(child, c^1) == false)
                    return false;
            }
            else
            {
                if(color[v] == color[child])
                    return false;
            }
        }
        return true;
    }

    bool is_bipartite()
    {
        bool ans = true;
        for(int i=0; i<V; i++)
        {
            if(visited[i] == 0)
            {
                if(dfs(i, 1)==false)
                {
                    ans = false;
                    break;
                }
            }
        }
        return ans;
    }
    void removeEdge(int u, int v)
    {
        for(int i=0; i<adjList[u].size(); i++)
        {
            if(adjList[u][i].getv()==v)
            {
                adjList[u][i].setweight(0);
                residue[u][v] = 0;
            }
        }
    }

    void print_bipartite()
    {
        if(is_bipartite()==false)
        {
            cout<<"The graph is not bipartite"<<endl;
            outfile<<"The graph is not bipartite"<<endl;
            return;
        }

        for(int i=0; i<V; i++)
        {
            if(color[i]==1)
            {
                //cout<<"color = "<<color[i]<<endl;
                addEdge(V, i, 1);  // fine
            }
            else
            {
                //cout<<"color = "<<color[i]<<endl;
                addEdge(i, V+1, 1);   // fine
            }
        }

        for(int i=0; i<V; i++)
        {
            for(auto x : adjList[i])
            {
                if(color[i]==1 and color[x.getv()]==0 and x.getv() != V)  // V for if not source
                {
                     removeEdge(x.getv(), i);   //making weight zero
                }
            }
        }

        //printGraph();
        /*for(int i=0; i<V+2; i++)
        {
            for(int j=0; j<V+2; j++)
                cout<<residue[i][j]<<"\t";

            cout<<endl;
        }*/
        int maximum_flow = maxflow(V, V+1);
        cout<<maximum_flow<<endl;
        outfile<<maximum_flow<<endl;

        for(int i=0; i<V; i++)
        {
            for(auto x : adjList[i])
            {
                if(x.getweight()-residue[i][x.getv()]==1 and x.getv() != V+1)
                {
                    cout<<i<<" "<<x.getv()<<endl;
                    outfile<<i<<" "<<x.getv()<<endl;
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
        infile>>u>>v;
        g.addEdge(u,v,1);
        g.addEdge(v,u,1);
    }

    g.print_bipartite();
}


