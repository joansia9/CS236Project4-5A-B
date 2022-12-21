#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>//for reverse DFS
//reverse(iteratorVec.begin , iteratorVec.end)

using namespace std;

class Graph {
private:
    //node              //set of nodes it points to
    map<unsigned int, set<unsigned int>> graph;
    //R0 : R1 R2 R3
    //node              //set of nodes it points to
    map<unsigned int, set<unsigned int>> reversed_graph;
    //R1 : R0
    //R2 : R0
    //R3 : R0
    unsigned int node; //circles and edges are the arrows
    //bool isVisited; //Also store a boolean 'is_visited' flag for each node

    //node          //isVisited?
    map<unsigned int, bool> isVisited;

    //vectors for dfs functions
    vector<unsigned int> post_order;
    vector<set<int>> sccs;

    unsigned int size = 0;
public:
    //constructor
    Graph() = default;
    //destructor
    ~Graph() = default;

    //Get these maps
    map<unsigned int,set<unsigned int>> Get_Edges() {
        return graph;
    }
    map<unsigned int, set<unsigned int>> Get_Reversed_Edges() {
        return reversed_graph;
    }

    //getters
    unsigned int Get_Node(){
        return node;
        //Do not store the node id as a string; do store as an int
    }
    vector<unsigned int>Get_Post_Order(){
        return post_order;
    }
    vector<set<int>>Get_Sccs(){
        return sccs;
    }
    int Get_Size(){
        return size;
    }


    //setters
    void Set_Node(int node){
        this->node = node;
    }
    void Set_Post_Order(vector<unsigned int> post_order){
        this->post_order = post_order;
    }
    void Set_Sccs(vector<set<int>> sccs){
        this->sccs = sccs;
    }
    void Set_Size(unsigned int size){
        for (unsigned int i = 0; i < size; i++){
            graph[i] = set<unsigned int>();
            reversed_graph[i] = set<unsigned int>();
        }
    }

    //adders
    void Add_Edge(unsigned int from, unsigned int to) {
        graph[from].insert(to);
        reversed_graph[to].insert(from);
    }
    void Add_Node(unsigned int node) {
        graph[node];
        reversed_graph[node];
    }

    //===========================HARDER FUNCTIONS======================================

    //TODO: trust the algorithim psuedocode
    //Make all of the functions dfs, dfsForest, etc. in the graph class
    //dfs
    set<int> Dfs(int node) {
        set<int> output;
        isVisited[node] = true;

        //for each node ADJACENT to the given node
        for (unsigned int i : graph[node]){

            //if the node has NOT been visited
            if(!isVisited[i]) {
                //run DFS on the node
                //RECURSIVE NATURE!! be sure to always check this!
                set<int> result = Dfs(i);
                //add result to the output
                output.insert(result.begin(), result.end());
            }
        }
        //add the node to the post order
        post_order.push_back(node);
        output.insert(node);

        return output;
    }

    //You should have a two different dfsForest functions:
        // one for finding the POST-ORDER
    void Dfs_Forest() {
        //isVisited = false because all nodes were unvisited
        for (auto i : graph) {
            isVisited[i.first] = false;
        }
        //for each node in the graph
        for(auto i : graph) {
            //if the node has not been visited
            if (!isVisited[i.first]) {
                //run DFS on the node
                Dfs(i.first);
            }
        }

        //return forest;
    }
        // and one for finding SCCs
    void Dfs_Forest_Sccs(vector<unsigned int> post_order) {
        vector<unsigned int> empty;

        //mark each node as unvisited
        for (auto i : graph){
            isVisited[i.first] = false;
        }

        //reverse the post_order list
        reverse(post_order.begin(),post_order.end());

        //debug
        /*
        cout << "DFS forest SCCs (reverse)" << endl;
        for (auto i : post_order){
            cout << i;
            if (i != *post_order.rbegin()){
                cout <<",";
            }

        }
         */
        cout << endl;

        //for each Nod N in post order
        for (auto i : post_order) {
        //if N is unvisited
            if(!isVisited[i]) {
            //create a new set
            set<int> SCC;
            //run DFS2 on N, with S as the set of nodes in the current SCC
            Dfs2(i, SCC);
            //add S to the list of SCCs
            sccs.push_back(SCC);
            }
        }


        //DAG patterns
        //1. DAGs never have beack adges
        //2. for every (a,b) in a DAG, post(b) < post(a)
        //3. the vertex with highest post-order number is a source (every DAG has a source)
        //4. The vertex with lowest post-order number is a sink (every DAG has a sink)


    }
    void Dfs2(int node, set<int> &scc){
        //set to have been seen already
        isVisited[node] = true;
        //add node to set
        scc.insert(node);
        //go through node
        for (int i : graph[node]){
            //if it is not visited
            if(!isVisited[i]){
                //recursive nature
                Dfs2(i, scc);
            }
        }
    }


    //print function
    string toString() {
        stringstream ss;
        for(auto & it : graph)
        {
            ss << "R" << it.first << ":";
            for(auto & it2 : it.second)
            {
                ss << "R" << it2;
                //only print the comma if it is not the last element
                if(it2 != *it.second.rbegin())
                {
                    ss << ",";
                }
            }
            ss << endl;
        }
        return ss.str();
    }


};

#endif //PROJECT_1_GRAPH_H

//post order psuedo code
/*
 * //in the private variables
        //map<vertex,int> preorder
        //map<vertex,int> postorder
        //int clock = 1


        //procedure DepthFirstSearch(vertex v)
        //mark v
        //preorder[v]=clock; clock++
        //for each vertex w adjacent from v
            //if w is not marked
            //DepthFirstSearch(w)
        //postorder[v] = clock;
        //clock++
        //return
 */
