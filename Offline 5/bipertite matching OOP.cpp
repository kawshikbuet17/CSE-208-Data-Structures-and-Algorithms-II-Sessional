
#define NIL -1
#define INF INT_MAX
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
        //cout<<"setnVertices call hoise"<<endl;
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
        //cout<<"added edge = "<<u<<" "<<v<<" "<<w<<endl;
        adjList[u].push_back(Edge(v,w));
        residue[u][v] +=  w;
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

    int bfs(int s, int t)
    {

        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;

        queue<pair<int, int>> q;
        q.push({s, INF});



        while(!q.empty())
        {
            int current = q.front().first;
            int flow = q.front().second;
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
            flow += new_flow;
            int current = t;
            while(current != s)
            {
                int prev = parent[current];
                residue[prev][current] -= new_flow;
                residue[current][prev] += new_flow;
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

    bool is_bipertite()
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

    void print_bipertite()
    {
        if(is_bipertite()==false)
        {
            cout<<"The graph is not bipartite"<<endl;
            return;
        }

        for(int i=0; i<V; i++)
        {
            //cout<<"color "<<i<<" = "<<color[i]<<"\n";  //fine
            //cout<<color[i]<<"\t";
            //cout<<"visited "<<i<<" = "<<visited[i]<<"\n";  //fine
            if(color[i]==1)
                addEdge(V, i, 1);  // fine
            else
                addEdge(i, V+1, 1);   // fine
        }

        for(int i=0; i<V; i++)
        {
            for(auto x : adjList[i])
            {
                if(color[i]==1 and color[x.getv()]==0)
                {
                     removeEdge(x.getv(), i);
                }

            }
        }

        cout<<maxflow(V, V+1)<<endl;

        for(int i=0; i<V; i++)
        {
            for(auto x : adjList[i])
            {
                if(x.getweight()-residue[i][x.getv()]==1 and x.getv() != V+1)
                    cout<<i<<" "<<x.getv()<<endl;
            }
        }
    }
};

int main()
{
    Graph g;
    ifstream infile;
    infile.open("in6.txt");

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

    g.print_bipertite();
}

