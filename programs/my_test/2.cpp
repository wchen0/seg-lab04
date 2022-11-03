#include <iostream>
#include <cstdio>

using namespace std;

int a[200005];

int main(void) {
    int n = 32, t, largest = 220;
    
    for(int i = 1; i <= n; i++) {
        cin >> t;
        if(largest < t) largest = t;
        if(a[i - 1] + t < 0) a[i] = 0;
        else a[i] = a[i - 1] + t;
    }

    int m = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > m) m = a[i];
    }

    if(m != 0) cout << m << endl;
    else cout << largest << endl;

    return 0;
}
