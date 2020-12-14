long long dp[N][N];
void compute(int l, int r, int optl, int optr, int id){
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<long long, int> best = {INF, -1};

    for (int i=optl;i<=min(optr, mid);i++){
        best = min(best, {dp[id - 1][i - 1] + C(i, mid), i});
    }
    dp[id][mid] = best.first;
    compute(l, mid - 1, optl, best.second, id);
    compute(mid + 1, r, best.second, optr, id);
}