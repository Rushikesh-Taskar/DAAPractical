#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int INF=INT_MAX;
const int N=5;

class Node
{
public:
    vector<pair<int, int>> path;
    int mat[N][N];
    int cost;
    int vertex;
    int level;
};

Node* newNode(int matrix_parent[N][N], vector<pair<int, int>> const &path,int level, int i, int j)
{
    Node* node = new Node;
    node->path = path;

    if (level != 0)
    {
        node->path.push_back(make_pair(i, j));
    }

    memcpy(node->mat, matrix_parent,sizeof(node->mat));

    for (int k = 0; level != 0 && k < N; k++)
    {
        node->mat[i][k] = INF;
        node->mat[k][j] = INF;
    }

    node->mat[j][i] = INF; // mat[j][0] 
    node->level = level;
    node->vertex = j;
    return node;
}

void reduce_row(int mat[N][N], int row[N])
{
    fill_n(row, N, INF); 

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            row[i] = min(row[i],mat[i][j]);
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] != INF && row[i] != INF)
            {
                mat[i][j] -= row[i];
            }  
        }  
    }
}
void reduce_column(int mat[N][N], int col[N])
{
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            col[j] = min(col[j],mat[i][j]);
        } 
    }
        
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] != INF && col[j] != INF)
            {
                mat[i][j] -= col[j];
            }
        }      
    }   
}

// current cost r 
int cost_calculation(int mat[N][N])
{
    int cost = 0;

    int row[N];
    reduce_row(mat, row);

    int col[N];
    reduce_column(mat, col);

    for (int i = 0; i < N; i++)
    {
        cost += (row[i] != INT_MAX) ? row[i] : 0,
        cost += (col[i] != INT_MAX) ? col[i] : 0;
    }
    return cost;
}

void printPath(vector<pair<int, int>> const &list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout<<list[i].first+1 << " -> "<< list[i].second + 1 << endl;
    }    
}

// for sorting 
class cmp 
{
public:
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

void TSP(int adjacensyMatrix[N][N])
{
    priority_queue<Node*,vector<Node*>, cmp> pq;
    vector<pair<int, int>> v;

    Node* root = newNode(adjacensyMatrix, v, 0, -1, 0);
    root->cost = cost_calculation(root->mat);
    pq.push(root);
    
    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();
        int i = min->vertex;
        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));
            printPath(min->path);
            cout<<"minimum cost required is "<< min->cost<<endl;
            return;
        }
        for (int j = 0; j < N; j++)
        {
            if (min->mat[i][j] != INF)
            {
                Node* child = newNode(min->mat, min->path,min->level + 1, i, j);
                child->cost = min->cost + min->mat[i][j] + cost_calculation(child->mat);
                pq.push(child);
            }
        }
        delete min;
    }
    return;
}

int main()
{
    int adjacensyMatrix[N][N] =
    {
        { INF, 20, 30, 10, 11 },
        { 15,  INF, 16,  4,  2 },
        { 3,   5,  INF, 2,  4 },
        { 19,   6,   18,   INF, 3 },
        { 16,   4,   7,   16, INF }
    };

    TSP(adjacensyMatrix);

    return 0;
}
