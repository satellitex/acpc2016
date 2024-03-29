#include "testlib.h"

using namespace std;

const int N_MIN =      2;
const int N_MAX = 100000;
const int u_MIN =      1;
const int u_MAX = 100000;
const int v_MIN =      1;
const int v_MAX = 100000;

bool found;
vector<int> G[N_MAX];
int visited[N_MAX];

void dfs(int curr, int prev)
{
    visited[curr] = 0;
    for (int i = 0; i < (int)G[curr].size(); i++) {
	int to = G[curr][i];
        if (to == prev) continue;
	if (visited[to] == -1) {
	    dfs(to, curr);
	} else if(visited[to] == 0) {
	    found = true;
	    return;
	}
    }
    visited[curr] = 1;
}

void dfs2(int curr, int prev)
{
    visited[curr] = 1;
    for (int i = 0; i < (int)G[curr].size(); i++) {
        int to = G[curr][i];
        if (to == prev) continue;
        dfs2(to, curr);
    }
}

int N;
int u[N_MAX], v[N_MAX];

bool find_loop()
{
    found = 0;
    memset(visited, -1, sizeof(visited));
    for (int i = 0; i < N; i++) {
        if (visited[i] == -1) {
            dfs(i, -1);
        }
    }
    return found;
}

bool is_connected()
{
    memset(visited, 0, sizeof(visited));
    dfs2(0, -1);
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            return 0;
        }
    }
    return 1;
}

void input()
{
    N = inf.readInt(N_MIN, N_MAX);
    inf.readEoln();

    for (int i = 0; i < N-1; i++) {
        u[i] = inf.readInt(u_MIN, u_MAX, format("u[%d]", i + 1));
        
        inf.readSpace();
        
        v[i] = inf.readInt(v_MIN, v_MAX, format("v[%d]", i + 1));
        
        inf.readEoln();
        
        G[u[i] - 1].push_back(v[i] - 1);
        G[v[i] - 1].push_back(u[i] - 1);        
    }
    
    inf.readEof();   
}

void check()
{
    // self loop check
    bool exist_self_loop = 0;
    for (int i = 0; i < N-1; i++) {
        if (u[i] == v[i]) {
            exist_self_loop = 1;
            break;
        }
    }
    ensuref(!exist_self_loop, "Exist self loop");
    
    
    // loop check
    ensuref(!find_loop(), "Exist loop");

    
    // connected check
    ensuref(is_connected(), "Graph is not connected");
}

int main()
{
    registerValidation();

    input();

    check();
    
    return 0;
}
