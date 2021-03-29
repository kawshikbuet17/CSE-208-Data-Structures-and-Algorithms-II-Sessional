#include<stdio.h>
#include<stdlib.h>
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
    double w;
public:
    Edge(int v, double w)
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
    double getweight()
    {
        return w;
    }
};


class Graph
{
    int V, neg =0;
    vector<Edge>*adjList;
    vector<int>distance;
    vector<int>parent;
    vector<int>visited;
    vector<int>path;

    double **distanceMatrix;
    int **parentMatrix;

public:
    void setnVertices(int V)
    {
        this->V = V;
        adjList=new vector<Edge>[V+1];
        parent.resize(V+1);
        distance.resize(V+1);
        visited.resize(V+1);
        distanceMatrix = (double **)malloc(V * sizeof(double *));
        parentMatrix = (int **)malloc(V * sizeof(int *));
        for (int i=0; i<V; i++)
        {
            distanceMatrix[i] = (double *)malloc(V * sizeof(double));
            parentMatrix[i] = (int *)malloc(V * sizeof(int));
        }

        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                distanceMatrix[i][j]=INFINITY;
                parentMatrix[i][j]=NIL;
            }
        }
    }
    void addEdge(int u, int v, double w)
    {
        adjList[u].push_back(Edge(v,w));
    }


    void printGraph()
    {
        for(int u=0; u<V; u++)
        {
            int count=0;
            cout<<u+1<<" : ";
            for(auto e : adjList[u])
            {
                if(count==0)
                    cout<<e.getv()+1<<"("<<e.getweight()<<")";
                else
                    cout<<" --> "<<e.getv()+1<<"("<<e.getweight()<<")";
                count++;
            }
            cout<<endl;
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

    void reweightEdge(int u, int v, double w)
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

    double getWeight(int u, int v)
    {
        for(auto e : adjList[u])
        {
            if(e.getv()==v)
                return e.getweight();
        }
        return INFINITY;
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
                int v = i.getv();
                int w = abs(i.getweight());
                if(distance[u]+w < distance[v])
                {
                    distance[v] = distance[u]+w;
                    q.push(make_pair(distance[v], v));
                    parent[v] = u;
                }
            }
        }
    }


    void bellmanford(int source)
    {
        for(int i=0; i<V+1; i++)
        {
            distance[i] = INT_MAX;
            parent[i]=-1;
        }
        distance[source] = 0;

        for(int i=1; i<=V+1-1; i++)
        {
            for(int u=0; u<V+1; u++)
            {
                for(auto e : adjList[u])
                {
                    int v = e.getv();
                    int w = e.getweight();
                    if(distance[u] != INT_MAX && distance[u]+w<distance[v])
                    {
                        distance[v] = distance[u]+w;
                        parent[v]=u;
                    }
                }
            }
        }
        for(int u=0; u<V+1; u++)
        {
            for(auto e : adjList[u])
            {
                int v = e.getv();
                int w = e.getweight();
                if(distance[u] != INT_MAX && distance[u]+w<distance[v])
                {
                    cout<<"Negative Cycle Detected"<<endl;
                    neg = 1;
                }
            }
        }
    }

    void floydWarshall()
    {
        cleanSPInfo();

        for(int i=0; i<V; i++)
        {
            distanceMatrix[i][i]=0;
            parentMatrix[i][i]=NIL;
        }

        for(int i=0; i<V; i++)
        {
            for(auto e : adjList[i])
            {
                distanceMatrix[i][e.getv()] = e.getweight();
                parentMatrix[i][e.getv()] = i;
            }
        }

        for(int k=0; k<V; k++)
        {
            for(int i=0; i<V; i++)
            {
                for(int j=0; j<V; j++)
                {

                    if(distanceMatrix[i][j]<=distanceMatrix[i][k]+distanceMatrix[k][j])
                        {
                            distanceMatrix[i][j] = distanceMatrix[i][j];
                            parentMatrix[i][j] = parentMatrix[i][j];
                        }
                    else
                        {
                            distanceMatrix[i][j] = distanceMatrix[i][k]+distanceMatrix[k][j];
                            parentMatrix[i][j] = parentMatrix[k][j];
                        }
                }
            }
        }
    }

    void johnsonsAlgo()
    {
        cleanSPInfo();
        for(int i=0; i<V; i++)
        {
            distanceMatrix[i][i]=0;
            parentMatrix[i][i]=NIL;
        }

        for(int i=0; i<V; i++)
        {
            for(auto e : adjList[i])
            {
                distanceMatrix[i][e.getv()] = e.getweight();
                parentMatrix[i][e.getv()] = i;
            }
        }


        for(int i=0; i<V; i++)
        {
            addEdge(V, i, 0);
        }


        bellmanford(V);
        if(neg==1)
        {
            return;
        }
        vector<double>h;
        h.resize(V+1);
        for(int i=0; i<V+1; i++)
            {
                h[i] = distance[i];
            }
        for(int i=0; i<V; i++)
        {
            for(auto e : adjList[i])
            {
                reweightEdge(i, e.getv(), e.getweight() + h[i] - h[e.getv()]);
            }
        }

        for(int i=0; i<V; i++)
        {
            dijkstra(i);
            for(int j=0; j<V; j++)
            {
                distanceMatrix[i][j] = distance[j];
                parentMatrix[i][j] = parent[j];
            }
        }
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                distanceMatrix[i][j] = distanceMatrix[i][j] - h[i] + h[j];
            }
        }

        for(int i=0; i<V; i++)
        {
            for(auto e : adjList[i])
            {
                reweightEdge(i, e.getv(), e.getweight() - h[i] + h[e.getv()]);
            }
        }
    }

    void printDistanceMatrix()
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(distanceMatrix[i][j]==INFINITY)
                    cout<<"INF ";
                else
                    cout<<distanceMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void printPredecessorMatrix()
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                if(parentMatrix[i][j]==NIL)
                    cout<<"NIL ";
                else
                    cout<<parentMatrix[i][j]+1<<" ";
            }
            cout<<endl;
        }
    }

    double getShortestPathWeight(int u ,int v)
    {
        cout<<distanceMatrix[u][v]<<endl;
    }

    void printShortestPath(int u, int v)
    {
        if(u==v)
        {
            cout<<u+1<<" ";
        }
        else if(parentMatrix[u][v]==NIL)
        {
            cout<<"no shortest path from "<<u+1 <<" to "<<v+1<<endl;
        }
        else
        {
            printShortestPath(u, parentMatrix[u][v]);
            cout<<" --> "<<v+1<<"("<<distanceMatrix[parentMatrix[u][v]][v]<<")";
        }
    }

    void cleanSPInfo()
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                distanceMatrix[i][j]=INFINITY;
                parentMatrix[i][j]=NIL;
            }
        }
    }
};

int main()
{

    Graph g;

    int N, M;
    cin>>N>>M;
    g.setnVertices(N);


    for(int i=0; i<M; i++)
    {
        int u, v;
        double w;
        cin>>u>>v>>w;
        g.addEdge(u-1,v-1,w);
    }
    cout<<"Graph Created."<<endl;

    while(1)
    {
        cout<<"1.    Clear the values of the distance and parent matrices. (call clearSPvalues())"<<endl;
        cout<<"2.    Implement Floyd-Warshall Algorithm"<<endl;
        cout<<"3.    Implement Johnsons Algorithm"<<endl;
        cout<<"4.    print the weight of the shortest path and also the path itself along with edge weights from u to v"<<endl;
        cout<<"5.    Prints the graph in adjacency list form along with edge weights"<<endl;
        cout<<"6.    Prints the distance matrix D (call printDistanceMatrix())"<<endl;
        cout<<"7.    Prints predecessor matrix P(call printPredecessorMatrix())"<<endl;
        cout<<">> ";
        int c;
        cin>>c;

        if(c==1)
        {
            g.cleanSPInfo();
            cout<<"APSP matrices cleared"<<endl;
        }

        else if(c==2)
        {
            g.floydWarshall();
            cout<<"Floyd-Warshall algorithm implemented"<<endl;
        }

        else if(c==3)
        {
            g.johnsonsAlgo();
            cout<<"Johnson’s algorithm implemented"<<endl;
        }

        else if(c==4)
        {
            cout<<"Enter source and destination"<<endl;
            int s,d;
            cin>>s>>d;
            cout<<"shortest path weight : ";
            g.getShortestPathWeight(s-1,d-1);
            cout<<"shortest path :"<<endl;
            g.printShortestPath(s-1,d-1);
            cout<<endl;
        }

        else if(c==5)
        {
            cout<<"Graph :"<<endl;
            g.printGraph();
            cout<<endl;
        }

        else if(c==6)
        {
            cout<<"Distance Matrix :"<<endl;
            g.printDistanceMatrix();
        }

        else if(c==7)
        {
            cout<<"Predecessor Matrix :"<<endl;
            g.printPredecessorMatrix();
        }
        else
        {
            cout<<"Program Ended..."<<endl;
            break;
        }


    }
}





