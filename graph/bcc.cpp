const int N = 2e5 + 10;

int n, m, q;
vector<int> adj[N];
int num[N], low[N], counter;
vector<pair<int, int>> edge, bridge, block[N];
int root;
bool artic[N];
int nblock;
int childroot;
int par[N];
int udh[N];

vector< int> bct[N];

void dfs_bcc(int v, int bef = -1) {
  num[v] = low[v] = counter++;
  for (int u: adj[v]) {
    if (num[u] == -1) {
      edge.emplace_back(v, u);
      if (v == root) childroot++;
      dfs_bcc(u, v);
      if (childroot > 1 && v == root) {
        artic[v] = 1;
        nblock++;
        while (edge.size() > 0) {
          auto it = edge.back();
          edge.pop_back();
          block[nblock].push_back(it);
          if (it == make_pair(v, u)) break;
        }
      }
      if (low[u] >= num[v] && v != root) {
        artic[v] = 1;
        nblock++;
        while (edge.size() > 0) {
          auto it = edge.back();
          edge.pop_back();
          block[nblock].push_back(it);
          if (it == make_pair(v, u)) break;
        }
      }
      if (low[u] > num[v]) bridge.emplace_back(v, u);
      low[v] = min(low[v], low[u]);
    } else if (bef != u && num[v] > num[u]) {
      low[v] = min(low[v], num[u]);
      edge.emplace_back(v, u);
    }
  }
}

void build_bct() {
  fill(num, num + n + 1, -1);
  for (int i = 1; i <= n; i++) {
    if (num[i] == -1) {
      root = i;
      childroot = 0;
      edge.clear();
      dfs_bcc(i);
      artic[i] = childroot > 1;
      if (edge.size() > 0) {
        nblock++;
        while (edge.size() > 0) {
          auto it = edge.back();
          edge.pop_back();
          block[nblock].push_back(it);
        }
      }
    }
  }
  for (int i = 1; i <= nblock; i++) {
    for (auto & x: block[i]) {
      if (artic[x.first]) {
        if (udh[nblock + x.first]) continue;
        udh[nblock + x.first] = 1;
        bct[i].push_back(nblock + x.first);
        bct[nblock + x.first].push_back(i);
      } else {
        par[x.first] = i;
      }
    }
    int last = block[i].back().second;
    if (artic[last]) {
      if (!udh[nblock + last]) {
        bct[i].push_back(nblock + last);
        bct[nblock + last].push_back(i);
      }
    } else {
      par[last] = i;
    }
    for (auto & x: block[i]) {
      if (artic[x.first]) udh[nblock + x.first] = 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (artic[i] || par[i] == 0) {
      par[i] = nblock + i;
    }
  }
}
