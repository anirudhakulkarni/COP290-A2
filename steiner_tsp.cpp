#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>


vector<vector<int>> maze_mat;
pair<int, int> starting_point;
pair<int, int> ending_point;
vector<pair<int, int>> stone_coordinates;

using namespace std;

/*
    0 -> wall
    1 -> free path
    2 -> Stones
    3 - Start
    4 - end
*/
class Graph{

public:
    vector<int> adj[100];
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
        end = ending_point.first * cols + ending_point.second;
        for (auto stone_coor : stone_coordinates){
            stone_loc.push_back(stone_coor.first * cols + stone_coor.second);
            stones++;
        }
        for (int row = 1; row < rows - 1; row++){
            for (int col = 1; col < cols - 1; col++){
                //cout << maze[row][col] << " ";
                //cout << "here8" << endl;
                // cout << row << " " << col << " " << maze[row][col] << endl;
                // cout << row-1 << " " << col << " " << maze[row-1][col] << endl;
                // cout << row+1 << " " << col << " " << maze[row+1][col] << endl;
                // cout << row << " " << col-1 << " " << maze[row][col-1] << endl;
                // cout << row << " " << col+1 << " " << maze[row][col+1] << endl;
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
    void show_adj_list(){
        for (auto node : adj){
            for (auto val : node){
                cout << val << " ";
            }
            cout << endl;
        }
    }
    // void calulate_distances_bfs(int start, int *distances[][]){
    //     queue<int> temp;
    //     temp.push(start);
    //     bool visited[size] = {false};
    //     visited[start] = true;
    //     int curr_dist = 0;
    //     distances[start][start] = 0;
    //     while(!temp.empty()){
    //         int top = temp.front();
    //         temp.pop();
    //         for(auto x : adj[top]){
    //             if (!visited[x]){
    //                 temp.push(x);
    //                 distances[start][x] = distances[start][top]+1;
    //                 visited[x] = true;
    //             }
    //         }
    //     }
    // }
    void evaluate(){
        int distances[size][size];
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                distances[i][j] = -1;
            }
        }
        for (auto stone : stone_loc){
            //cout << "This is stone" << stone << endl;
            queue<int> temp;
            temp.push(stone);
            bool visited[size] = {false};
            visited[stone] = true;
            int curr_dist = 0;
            distances[stone][stone] = 0;
            while(!temp.empty()){
                int top = temp.front();
                temp.pop();
                for(auto x : adj[top]){
                    if (!visited[x]){
                        //cout << x <<  "->" << distances[stone][top]+1 << endl;
                        temp.push(x);
                        distances[stone][x] = distances[stone][top]+1;
                        visited[x] = true;
                    }
                }
            }
        }
        for (auto stone1 : stone_loc){
            for (auto stone2 : stone_loc){
                //cout << stone1 << " " << stone2 << " " << distances[stone1][stone2] << " " << distances[stone2][stone1] << endl;
                if (distances[stone1][stone2] == -1) {
                    //cout << stone1 << "<->" << stone2 << endl;
                    cout << "Stones not reachable from each other" << endl;
                    return;
                }
            }
        }
        // size(S) > 2;
        // C(S, i) = min (C(S - {i}, j) + dist(j, i));
        stone_loc.pop_back();
        stone_loc.pop_back();
        vector<int> order_to_traverse;
        int min_path = INT_MAX;
        do {
            
            int current_pathweight = 0;
            int k = start;
            for (int i = 0; i < stone_loc.size(); i++) {
                current_pathweight += distances[k][stone_loc[i]];
                k = stone_loc[i];
            }
            current_pathweight += distances[k][end];
            if (current_pathweight < min_path){
                min_path = current_pathweight;
                order_to_traverse.assign(stone_loc.begin(), stone_loc.end());
            }
            //min_path = min(min_path, current_pathweight);
    
        } while (
            next_permutation(stone_loc.begin(), stone_loc.end()));
        
        vector<pair<int, int>> output_coordinates;
        order_to_traverse.insert(order_to_traverse.begin(), start);
        order_to_traverse.push_back(end);
        //     cout << "Order to traverse => ";
        // for (auto x : order_to_traverse){
        //     cout << x << " ";
        // }
        cout << endl;
        for (int it = 0; it < order_to_traverse.size() - 1; it++){
            int stone = order_to_traverse[it];
            int final = order_to_traverse[it+1];
            //cout << "Milestone---" << stone << " " << final << endl;
            int parents[size] = {-2};
            queue<int> temp;
            temp.push(stone);
            bool visited[size] = {false};
            visited[stone] = true;
            parents[stone] = -1;
            while(!temp.empty()){
                int top = temp.front();
                temp.pop();
                for(auto x : adj[top]){
                    if (!visited[x]){
                        //cout << x <<  "->" << distances[stone][top]+1 << endl;
                        temp.push(x);
                        parents[x] = top;
                        visited[x] = true;
                        if (x == final){
                            vector<pair<int, int>> tempvec;
                            x = parents[x];
                            while(x!=-1){
                                //output_coordinates.insert(output_coordinates.begin(), make_pair(x / cols, x % cols));
                                //cout << x/ cols << " " << x % cols << endl
                                tempvec.push_back(make_pair(x / cols, x % cols));
                                x = parents[x];
                            }
                            reverse(tempvec.begin(), tempvec.end());
                            output_coordinates.insert( output_coordinates.end(), tempvec.begin(), tempvec.end() );
                            temp = queue<int>(); 
                            break; 
                        }
                    }
                }
            }
        }
        output_coordinates.push_back( make_pair(end/cols, end%cols) );
        //cout << "Hello" << endl;
        ofstream outstream("path.txt");
        for (auto coo : output_coordinates){
            outstream << coo.first << " " << coo.second << endl;
        }
        outstream.close();
    }
};
int main (int argc, char *argv[]) {
//   string line;
  //cout << "here1" << endl;

//   ifstream myfile (argv[argc - 1]);

//   vector<vector<int>> maze_mat;
//   //cout << "here2" << endl;
//   if (myfile.is_open())
//   {
//     while ( getline (myfile,line) )
//     {
//         vector<int> row_vec;
        

//             string word = "";
//         for (auto x : line) 
//         {
//             if (x == ' ')
//             {
//                 row_vec.push_back(stoi(word));
//                 word = "";
//             }
//             else {
//                 word = word + x;
//             }
//         }
//         row_vec.push_back(stoi(word));
//         maze_mat.push_back(row_vec);
//     }
//     myfile.close();
//     }
//     else cout << "Unable to open input file"; 
    //cout << "here2" << maze_mat.size() << " " << maze_mat[0].size() << endl;
    Graph G;
    G.constructGraph(maze_mat);
    //G.show_adj_list();
    G.evaluate();
    return 0;
}
