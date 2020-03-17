#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY INT_MAX
#define WHITE 1
#define GRAY 2


#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
using namespace std;




class Graph
{
    int V;
    vector<pair<int, int>>adjList[1000];
    vector<int>distance;
    vector<int>parent;
    vector<int>visited;
    vector<int>path;




public:
    fstream outfile;

    void setnVertices(int V)
    {
        this->V = V;
        parent.resize(V);
        distance.resize(V);
        visited.resize(V);
        outfile.open("output.txt",ios::in | ios::out);
    }
    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back(make_pair(v, w));
    }

    void printPath(int vertex)
    {
        if(parent[vertex]==-1)
        {
            outfile<<vertex;
            return;
        }

        printPath(parent[vertex]);
        outfile<<" -> "<<vertex;
    }


    void dijkstra(int source)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>> q;

        for(int i=0; i<V; i++)
        {
            distance[i] = INFINITY;
            parent[i]=-1;
            visited[i]=WHITE;
        }

        q.push(make_pair(0, source));
        distance[source] = 0;


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
                int v = i.first;
                int w = abs(i.second);
                if(distance[u]+w < distance[v])
                {
                    distance[v] = distance[u]+w;
                    q.push(make_pair(distance[v], v));
                    parent[v] = u;
                }
            }
        }
    }

    void dijkstraDistance(int source, int destination)
    {
        outfile<<"Dijkstra Algorithm :"<<endl;
        dijkstra(source);
        outfile<<distance[destination]<<endl;
        printPath(destination);
        outfile<<endl;
    }

    void bellmanford(int source)
    {
        for(int i=0; i<V; i++)
        {
            distance[i] = INT_MAX;
            parent[i]=-1;
        }
        distance[source] = 0;

        for(int i=1; i<=V-1; i++)
        {
            for(int u=0; u<V; u++)
            {
                for(auto e : adjList[u])
                {
                    int v = e.first;
                    int w = e.second;
                    if(distance[u] != INT_MAX && distance[u]+w<distance[v])
                    {
                        distance[v] = distance[u]+w;
                        parent[v]=u;
                    }
                }
            }
        }
        for(int u=0; u<V; u++)
        {
            for(auto e : adjList[u])
            {
                int v = e.first;
                int w = e.second;
                if(distance[u] != INT_MAX && distance[u]+w<distance[v])
                {
                    outfile<<"Negative Cycle Detected"<<endl;
                }
            }
        }
    }

    void bellmanfordDistance(int source, int destination)
    {
        outfile<<"Bellmanford Algorithm :"<<endl;
        bellmanford(source);
        outfile<<distance[destination]<<endl;
        printPath(destination);
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
        int u, v, w;
        infile>>u>>v>>w;
        g.addEdge(u,v,w);

    }
    int S, D;
    infile>>S>>D;

    g.dijkstraDistance(S,D);
    g.bellmanfordDistance(S,D);
}



