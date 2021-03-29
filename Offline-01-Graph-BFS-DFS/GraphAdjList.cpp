#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define YELLOW 4
#define GREEN 5
#define RED 6

#include<bits/stdc++.h>
using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item )
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length )
        return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE )
        return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
        return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)
        return true;
    else
        return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list)
        delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *parent;
    int *d;
    int *color;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the
    void bfswithoutprint(int source);
    void dfs(int source);
    void dfs();

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    d=new int[16000];
    parent=new int[16000];
    color=new int[16000];

    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0)
        delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed)
        adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return; //vertex out of range
    this->nEdges++ ;
    adjList[u].removeItem(v) ;
    if(!directed)
        adjList[v].removeItem(u) ;


}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    else
        return false;
}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    int c =0;
    for (int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i) != NULL_VALUE)
            c++;
    }
    return c;
}

int Graph::getInDegree(int u)
{
    int c = 0;
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[i].searchItem(u) != NULL_VALUE)
            c++;
    }
    return c;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for (int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i) != NULL_VALUE)
            cout<<i<<"\t";
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i)!=NULL_VALUE && adjList[v].searchItem(i)!=NULL_VALUE)
            return true;
    }
    return false;

}

void Graph::bfs(int s)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    int m;
    for(int u=0; u<nVertices; u++)
    {
        color[u]=WHITE;
        d[u]=INFINITY;
        parent[u]=NULL_VALUE;
    }

    color[s]=GRAY;
    d[s]=0;
    parent[s]=NULL_VALUE;
    Queue q;
    q.enqueue(s);
    while(!q.empty())
    {
        m=q.dequeue();
        printf("%d ",m);
        for(int i=0; i<nVertices; i++)
        {
            if(adjList[m].searchItem(i)!= NULL_VALUE)
            {
                if(color[i]==WHITE)
                {
                    color[i]=GRAY;
                    d[i]=d[m]+1;
                    parent[i]=m;
                    q.enqueue(i);
                }
            }
        }
        color[m]=BLACK;
    }
    cout<<endl;
}

void Graph::bfswithoutprint(int s)
{
    int m;
    for(int u=0; u<nVertices; u++)
    {
        color[u]=WHITE;
        d[u]=INFINITY;
        parent[u]=NULL_VALUE;
    }

    color[s]=GRAY;
    d[s]=0;
    parent[s]=NULL_VALUE;
    Queue q;
    q.enqueue(s);
    while(!q.empty())
    {
        m=q.dequeue();
        //printf("%d ",m);
        for(int i=0; i<nVertices; i++)
        {
            if(adjList[m].searchItem(i)!= NULL_VALUE)
            {
                if(color[i]==WHITE)
                {
                    color[i]=GRAY;
                    d[i]=d[m]+1;
                    parent[i]=m;
                    q.enqueue(i);
                }
            }
        }
        color[m]=BLACK;
    }
}
void Graph::dfs()
{
    for(int u=0; u<nVertices; u++)
    {
        color[u]=YELLOW;
        //d[u]=0;
        parent[u]=NULL_VALUE;
    }
}


void Graph::dfs(int u)
{
    color[u] = GREEN;
    cout<<u<<" ";
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i)!= NULL_VALUE)
        {
            if(color[i]==YELLOW)
            {
                //cout<<i<<" ";
                parent[i] = u;
                dfs(i);

            }

        }
    }
    color[u] = RED;

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return d[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    delete[] adjList ;
    delete[] parent;
    delete[] d;
    delete[] color;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    srand(time(NULL)) ;
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;

    cout<<"Press \n1. Test \n2. BFS Statistics\n"<<endl;
    cin>>choice;
    if(choice==1)
    {
        Graph g(dir);
        printf("Enter number of vertices: ");
        scanf("%d", &n);
        g.setnVertices(n);

        while(1)
        {
            printf("1. Add edge. \n");
            printf("2. Remove edge. \n");
            printf("3. Get degree. \n");
            printf("4. adjacent vertices. \n");
            printf("5. hasCommonAdjacent. \n");
            printf("6. edge present check. \n");
            printf("7. BFS . \n");
            printf("8. DFS . \n");
            printf("9. Get distance. \n");
            printf("10. Print Graph. \n");
            printf("11. Exit. \n");

            int ch;
            scanf("%d",&ch);
            if(ch==1)
            {
                int u, v;
                printf("Add edge between: \n");
                scanf("%d%d", &u, &v);
                g.addEdge(u, v);
            }
            else if(ch==2)
            {
                int u, v;
                printf("Remove the edge between: \n");
                scanf("%d%d", &u, &v);
                g.removeEdge(u, v);
            }
            else if(ch==3)
            {
                int u, c;
                printf("the degree of the vertex: ");
                cin >> u;
                cout<<"1. outdegree "<<endl;
                cout<<"2. indegree "<<endl;
                cin>>c;
                if(c==1)
                    cout << g.getOutDegree(u)<<endl;
                else
                    cout<<g.getInDegree(u)<<endl;

            }
            else if(ch==4)
            {
                int u;
                cout << "the adjacent vertices  of vertex: " << endl;
                cin >> u;
                g.printAdjVertices(u);
            }
            else if(ch==5)
            {
                int u, v;
                cout << "common adjacent between two vertexs" << endl;
                cout << "the two vertexes are: ";
                scanf("%d %d", &u, &v);
                if(g.hasCommonAdjacent(u, v))
                {
                    cout << "is present" << endl;
                }
                else
                {
                    cout << "isn't present" << endl;
                }

            }
            else if(ch==6)
            {
                int u, v;
                printf("the edge present check between vertex: ");
                scanf("%d%d", &u, &v);
                if(g.isEdge(u, v))
                {
                    cout << "is present" << endl;
                }
                else
                {
                    cout << "isn't present" << endl;
                }

            }
            else if(ch==7)
            {
                int u;
                cout << "Source: ";
                cin >> u;
                g.bfs(u);
            }
            else if(ch==8)
            {
                int u;
                cout << "Source: ";
                cin >> u;
                g.dfs();
                g.dfs(u);
                cout<<endl;
            }
            else if(ch==9)
            {
                int u, v;
                printf("the shortest path distance between two vertexes and the vertexes are: ");
                cin >> u >> v;
                int d = g.getDist(u, v);
                cout << "the distance is : " << d << endl;
            }
            else if(ch==10)
            {
                g.printGraph();
            }
            else if(ch==11)
            {
                break;
            }
        }
    }
    else
    {
        int vertices[] = {1000, 2000, 4000, 8000, 16000 };
        for(int i=0; i<sizeof(vertices)/sizeof(vertices[0]); i++)
        {
            int sv = vertices[i];

            Graph g1(dir);
            g1.setnVertices(sv);

            for(int j=sv; j<=(sv*sv-sv)/8; j*=2)
            {
                for(int ii=0; ii<j; ii++)
                {
                    int v1 = rand()%sv;
                    int v2 = rand()%(sv/2)+rand()%(sv/5)+rand()%(sv/7)+rand()%(sv/13);
                    if(v2>=sv)
                    v2=rand()%sv;
                    g1.addEdge(v1,v2);
                }

                auto t = 0;
                auto t1 = chrono::high_resolution_clock::now();
                for(int k=0; k<10; k++)
                {
                    /*if(sv==100 &&j==100)
                    {
                        g1.printGraph();
                        //g1.bfs(rand()%100);
                        break;
                    }*/
                    g1.bfswithoutprint(rand()%sv);
                }
                auto t2 = chrono::high_resolution_clock::now();
                t = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
                t=t/10;
                cout<<"V = "<<sv<<"\tE = "<<j<<"\tBFStime(microsec) = "<<t<<""<<endl;
            }
        }
    }
    cout << endl;
}


