#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
long long find_cost(long long l, long long r, const vector<long long>& w,
                    int n, int k) {
    long long ans;
    while (l <= r) {
        // cautam binar cea mai mare greutate pentru cost minim
        // de la cel mai mare element al sirului pana la
        // suma tuturor elementelor
        long long mid = l + ((r - l) / 2);
        int feribots = 1;
        long long partial_cost = 0;
        for ( int i = 0; i < n; i ++ ) {
            if ( partial_cost + w[i] > mid ) {
                feribots ++;
                partial_cost = w[i];
            } else {
                // daca depasim costul mid, incepem sa incarcam
                // alt feribot
                partial_cost += w[i];
            }
        }
        // daca depasim numarul de feriboturi disponibile
        // crestem suma minima
        if ( feribots > k ) {
            l = mid + 1;
        } else {
        // scadem suma maxima
            r = mid - 1;
            ans = mid;
        }
    }
    return ans;
}

long long cross(const vector<long long>& w, int k) {
    int n = w.size();
    long long l = 0, r = 0;
    for ( int i = 0; i < n; i ++ ) {
        l = max(l, w[i]);
        r += w[i];
    }
    long long answer = find_cost(l, r, w, n, k);
    return answer;
}

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    int N, K;
    fin >> N >> K;
    vector<long long> weights(N, 0);
    for ( int i = 0; i < N; i ++ ) {
        fin >> weights[i];
    }

    auto res = cross(weights, K);
    fout << res << "\n";

    return 0;
}
