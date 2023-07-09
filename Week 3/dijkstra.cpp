// 210. Course Schedule II

class Solution {
private:
    bool kahnAlgo(vector<vector<int>> &adj, int n, vector<int> &indegree, vector<int> &ans)
    {
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0){
                q.push(i);
            }
        }
        int count = 0;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (auto a : adj[curr])
            {
                indegree[a] -= 1;
                if (indegree[a] == 0)
                    q.push(a);
            }
            ans.push_back(curr);
            count++;
        }
        if (count != n)
            return false;
        return true;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = prerequisites.size();
        vector<vector<int>> adj(numCourses); 
        vector<int> indegree(numCourses, 0); 

        for (int i = 0; i < n; i++)
        {
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
            indegree[prerequisites[i][0]] += 1;
        }

        vector<int> ans;
        if (kahnAlgo(adj, numCourses, indegree, ans))
            return ans;
        return {};
    }
};


// q2: Alien Dictionary

string findOrder(string dict[], int N, int K) {
    //code here
    vector<int> adj[K];
        
    for(int i=0;i<=N-2;i++){
        string s1=dict[i];
        string s2=dict[i+1];

        int mini=min(s1.size(),s2.size());
        for(int j=0;j<mini;j++){
            if(s1[j]!=s2[j]){
                adj[s1[j]-'a'].push_back(s2[j]-'a');
                break;
            }
        }
    }   
    int n=K;
    vector<int> indeg(n);
    for(int i=0;i<n;i++){
        for(auto it: adj[i]){
            indeg[it]++;
        }
    }
    queue<int> q;
    for(int i=0;i<n;i++){
        if(indeg[i]==0){
            q.push(i);
        }
    }
    vector<int> ans;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        ans.push_back(node);
        for(auto it:adj[node]){
            indeg[it]--;
            if(indeg[it]==0){
                q.push(it);
            }
        }        
    }
    string ans2="";
    for(int i=0;i<n;i++){
        ans2=ans2+char(ans[i]+'a');
    }
    return ans2;    
}

// q3: Dijkstra’s Algorithm
#include <iostream>
using namespace std;
#include <limits.h>

#define V 9
int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printSolution(int dist[])
{
	cout << "Vertex \t Distance from Source" << endl;
	for (int i = 0; i < V; i++)
		cout << i << " \t\t\t\t" << dist[i] << endl;
}

void dijkstra(int graph[V][V], int src)
{
	int dist[V]; 

	bool sptSet[V]; 
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < V; v++)
			if (!sptSet[v] && graph[u][v]
				&& dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}
	printSolution(dist);
}

int main()
{
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	dijkstra(graph, 0);

	return 0;
}


// q4: Floyd Warshall Algorithm
#include <bits/stdc++.h>
using namespace std;

#define V 4
#define INF 99999
void printSolution(int dist[][V]);
void floydWarshall(int dist[][V])
{
	int i, j, k;
	for (k = 0; k < V; k++) {
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])
					&& (dist[k][j] != INF
						&& dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	printSolution(dist);
}

void printSolution(int dist[][V])
{
	cout << "The following matrix shows the shortest "
			"distances"
			" between every pair of vertices \n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					<< " ";
			else
				cout << dist[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	int graph[V][V] = { { 0, 5, INF, 10 },
						{ INF, 0, 3, INF },
						{ INF, INF, 0, 1 },
						{ INF, INF, INF, 0 } };

	floydWarshall(graph);
	return 0;
}
