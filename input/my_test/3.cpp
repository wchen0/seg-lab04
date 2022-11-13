#include <cstdio>
#include <iostream>

using namespace std;

int A[1];

int main(void) {
    int n = 32, t, L = 0x80000000;
    for(int i = 1; i <= n; i++) {
        cin >> t;
        if(L < t) L = t;
        if(A[i - 1] + t < 0) A[i] = 0;
        else A[i] = A[i - 1] + t;
    }

    int m = 0;
    for(int i = 1; i <= n; i++) {
        if(A[i] > m) m = A[i];
    }

    if(m != 0) cout << m << endl;
    else cout << L << endl;

    return 0;
}
