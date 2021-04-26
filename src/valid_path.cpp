#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>


vector<vector<int>> maze_mat;
pair<int, int> starting_point;

using namespace std;


class Graph{

public:
    vector<int> adj[100000];
    int start, end, stones, cols, rows, size;
    vector<int> stone_loc;
    void constructGraph(vector<vector<int>> maze){
        //cout << "here4" << endl;
        size = maze.size() * maze[0].size();
        rows = maze.size();
        cols = maze[0].size();
        stones = 0;
        //cout << "here5" << endl;
        for (int it = 0; it < size; it ++){
            adj[it].clear();
            //cout << "here6" << endl;
        }
        //cout << "here7" << endl;
        //cout << rows << " " << cols << endl;
        start = starting_point.first * cols + starting_point.second;
        for (int row = 1; row < rows - 1; row++){
            for (int col = 1; col < cols - 1; col++){
                if (maze[row][col] > 0){
                    if (maze[row][col-1] > 0){
                        adj[row*cols + col].push_back(row*cols + col-1);
                    }
                    if (maze[row][col+1] > 0){
                        adj[row*cols + col].push_back(row*cols + col+1);
                    }
                    if (maze[row+1][col] > 0){
                        adj[row*cols + col].push_back((row+1)*cols + col);
                    }
                    if (maze[row-1][col] > 0){
                        adj[row*cols + col].push_back((row-1)*cols + col);
                    }
                }
            }   
        }
        //cout << endl;
        stone_loc.push_back(end);
        stone_loc.push_back(start);
    }
    void valid_locs(){
            queue<int> temp;
            temp.push(start);
            ofstream outstream("valid_path.txt");
            bool visited[size] = {false};
            visited[start] = true;
            outstream << start / cols << " " << start % cols << endl;
            while(!temp.empty()){
                int top = temp.front();
                temp.pop();
                for(auto x : adj[top]){
                    if (!visited[x]){
                        outstream << x / cols << " " << x % cols << endl;
                        temp.push(x);
                        visited[x] = true;
                    }
                }
            }
        outstream.close();
    }
};




int main(){
    Graph G;
    G.constructGraph(maze_mat);
    //G.show_adj_list();
    G.valid_locs();
    return 0;
}

