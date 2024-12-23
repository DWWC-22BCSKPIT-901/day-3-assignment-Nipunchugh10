#include <iostream>
#include <cmath>
using namespace std;

const long long MOD = 1e9 + 7;

// Function for modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // Square the base
        exp /= 2;
    }
    return result;
}

// Function to compute the minimum non-zero product
long long minNonZeroProduct(int p) {
    if (p == 1) return 1;

    long long maxVal = (1LL << p) - 1;          // 2^p - 1
    long long secondMax = maxVal - 1;          // 2^p - 2
    long long numPairs = (1LL << (p - 1)) - 1; // 2^(p-1) - 1

    // Result = maxVal * (secondMax ^ numPairs) % MOD
    long long result = maxVal % MOD;
    result = (result * modExp(secondMax, numPairs, MOD)) % MOD;

    return result;
}

int main() {
    // Example Inputs
    int p1 = 1, p2 = 2, p3 = 3;

    cout << "Input: p = " << p1 << " -> Output: " << minNonZeroProduct(p1) << endl;
    cout << "Input: p = " << p2 << " -> Output: " << minNonZeroProduct(p2) << endl;
    cout << "Input: p = " << p3 << " -> Output: " << minNonZeroProduct(p3) << endl;

    return 0;
}
