#include<bits/stdc++.h>
#define SIZE 100
#define V 4

using namespace std;



vector <bool> visited(SIZE, 0); //This stores the nodes which are blocked and visited.
vector <int> acq_keys; //As you acquire the keys, you add in this array.
int heuristic[SIZE];
int path_cost=0;
int src=0, tgt=V-1;
int path[SIZE]={-1}; //This stores the parent of each node.



typedef struct fringeNode{
    int fvalue; 
    int val;   //The val of the node.
    int parent_node; //The  node's parent. Used to find the path.
    
    bool operator () ( const fringeNode& m ) const
    {
        return m.val == val;
    }
}fringeNode;

//vector <fringeNode> abc;
/*int adj_mat[V][V] = {
            {9999,1   ,4   ,9999},
            {1   ,9999,9999,1   },
            {4   ,9999,9999,11  },
            {9999,1   ,11  ,9999}
        };
 
 bool blocked[V] = {0,1,0,0};
 bool keys[V][V] = {
     {0,0,0,0},
     {0,0,0,0},
     {0,1,0,0},
     {0,0,0,0}};
int adj_mat[8][8] = {{9999, 2, 9999, 9999, 9999, 3, 9999, 9999},
					 {2, 9999, 4, 9999, 5, 7, 9999, 9999},
					 {9999, 4, 9999, 25, 2, 9999, 9999, 5},
					 {9999, 9999, 25, 9999, 9999, 9999, 9999, 9999},
					 {9999, 5, 2, 9999, 9999, 5, 4, 8},
					 {3, 7, 9999, 9999, 5, 9999, 10, 9999},
					 {9999, 9999, 9999, 9999, 4, 10, 9999, 6},
					 {9999, 9999, 5, 9999, 8, 9999, 6, 9999}};
 
 bool blocked[8] = {0,0,1,0,1,0,0,0};
 bool keys[8][8] = {
				     {0,0,0,0,0,0,0,0},
				     {0,0,0,0,0,0,0,0},
				     {0,0,0,0,0,0,0,0},
				     {0,0,0,0,0,0,0,0},
				     {0,0,0,0,0,0,0,0},
				     {0,0,1,0,1,0,0,0},
				     {0,0,0,0,0,0,0,0},
				     {0,0,0,0,0,0,0,0}};*/
int adj_mat[V][V];
bool blocked[V]={0};
bool keys[V][V] ={0};

bool cmp (fringeNode a, fringeNode b)
{
   return a.fvalue < b.fvalue || (a.val == b.val && a.fvalue < b.fvalue);
}

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    
    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Destination\n");
    for (int i = 0; i < V; i++)
        printf("%d ---------------- %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int src)
{
    //int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i
    
    bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        heuristic[i] = INT_MAX, sptSet[i] = false;
    
    // Distance of source vertex from itself is always 0
    heuristic[src] = 0;
    
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the node iteration.
        int u = minDistance(heuristic, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = true;
        
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && adj_mat[u][v] && heuristic[u] != INT_MAX
                && heuristic[u]+adj_mat[u][v] < heuristic[v])
                heuristic[v] = heuristic[u] + adj_mat[u][v];
    }
    
    // print the constructed distance array
    printSolution(heuristic, V);
}

//NODE EXPAND FUNCTION
//Updates the PATH of the parent_node
// Add keys in acq_keys if node has keys
//Calculate f values of all nodes connected to parent_node and update the fringe list.
void node_expand(int parent_node,int parent_fvalue,int parent,int src, vector<fringeNode> &fringe_list)
{
    cout<<parent_node<<" "<< "expanded"<<endl;
    
    if(parent_node==src)
    {
        path[parent_node]=-1;
    }
    else{
        path[parent_node]=parent;
    }
    int i;
    
    int k=0;
    // Add keys in acq_keys if node has keys
    for(i=0;i<V;i++)
    {
        k=0;
        //vector<fringeNode> ::iterator it;
        //it=abc.begin();
        
        if(keys[parent_node][i]==1)
        {
            acq_keys.push_back(i);
        }
    }
    for(i=0;i<V;i++)
    {
        if(adj_mat[parent_node][i]!=9999)
        {
            if(visited[i]==0)
			{    
	            //path[i]=parent_node;
	            //CALCULATE  F VALUE (H+G)
	            
	            //f_value of child is = f_value of parent - heurestic value of parent + path cost of parent and child + heuristic of child
	            
	            int child_fvalue=parent_fvalue - heuristic[parent_node]+adj_mat[parent_node][i]+heuristic[i];
	            
	            //ADD IN FRINGE LIST
	            fringeNode temp;
	            temp.val=i;
	            temp.parent_node=parent_node;
	            temp.fvalue=child_fvalue;
	            
	            //Find if node already exists
	            vector<fringeNode> ::iterator it;
	            it=fringe_list.begin();
	            int j=0;
	            
	            while(it!=fringe_list.end())
	            {
		            if(fringe_list[j].val==i && fringe_list[j].fvalue>child_fvalue)
		            {
		                fringe_list[j].fvalue=child_fvalue;
		                fringe_list[j].parent_node=parent_node;
		                break;
		            }
	                it++;
	                j++;
	            }            
	            fringe_list.push_back(temp);
	            sort(fringe_list.begin(),fringe_list.end(),cmp);
            }
       }
    }
}

void node_add(int val)
{
    visited[val]=1;
}

int main()
{
    int i, j;
    ifstream myfile;
	string file="abc.txt";
	//int i, j;
	//priority_queue<node, vector<node>, ComparisonClass>::iterator it;
	myfile.open(file.c_str());
	if(!myfile)
	{
	     cout << "File does not exist." << endl;
	}
	
	for(i = 0; i < V; i++)
	{
	     for(j = 0; j < V; j++ )
		{
		    myfile >> adj_mat[i][j];
			//cout << g.adj[i][j] << " ";
		}	
		//cout << "\n";
	}
	myfile.close();
    
    
    cout << "How many nodes have locks?\n";
	int nol;
	cin>> nol;
	cout << "Which nodes?\n";
	for(int i=0;i<nol;i++)
	{
		int temp;
		cin >> temp;
		blocked[temp]=1;
	}
	cout << "Name of lock and the node which has the key?";
	for(int i=0;i<nol;i++)
	{
		int temp1,temp2;
		cin >> temp1 >> temp2;
		keys[temp2][temp1]=1;
	}
    
    // HEURISTIC ARRAY
   	dijkstra(tgt);
    vector <fringeNode> fringe_list;
    
    fringeNode temp;
    temp.val=src;
    temp.parent_node=-1;
    temp.fvalue=heuristic[src];
    fringe_list.push_back(temp);
    fringeNode temp1;
    int count=0;
    while(temp1.val!=tgt)
    {
    	count++;
        temp1 = fringe_list.front();
		cout << "****************************************************\n";
        cout<<"POP"<<endl;
        cout<<"temp1.val: " << temp1.val<< endl;
		cout << "temp1.parent_node: " <<temp1.parent_node << endl;
		cout << "temp1.fvalue: " << temp1.fvalue<<endl;
        cout << "****************************************************\n";
        fringe_list.erase(fringe_list.begin());
    
        // Check if already visited
        if(visited[temp1.val]==0)
        {
            // Check if blocked
           if( blocked[temp1.val]==1)
           {
            // Check if key there
               vector <int>::iterator it;
               it=find(acq_keys.begin(),acq_keys.end(),temp1.val);
               if(it!=acq_keys.end())
               {
                   //Unlock the node and remove the key
                   blocked[temp1.val]=0;
                   acq_keys.erase(it);
                   
                   //Expand the node                   
                   node_expand(temp1.val, temp1.fvalue,temp1.parent_node,src,fringe_list);
                   
                   //Add node to visited
                   node_add(temp1.val);
               }
            }
           else
           {
               //Expand the node                   
               node_expand(temp1.val, temp1.fvalue,temp1.parent_node,src,fringe_list);                   
           }
        }
        if(count > 20)
        	break;
    }
    cout << "FINAL COST IS : " << temp1.fvalue << endl;
    path[tgt]=temp1.parent_node;
    //cout<<"jhsbjds"<<endl;
    int k=0;
    cout << "NODE" << "          " << "PARENT" << endl;
    while(k<V)
    {
        cout<<k<<" "<<path[k]<<endl;
        k++;
    }
    stack <int> a;
    a.push(tgt);
    
    while(path[tgt]!=src)
    {
        a.push(path[tgt]);
        tgt=path[tgt];
        
    }
    a.push(src);
    cout<<"PATH is"<<endl;
    while(a.empty()==0)
    {
        cout<<a.top()<<" ";
        a.pop();
    }    
    return 0;
}
