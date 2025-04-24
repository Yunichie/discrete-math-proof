#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned long long ull;

void sieve(ull limit, ull **primes, ull *prime_count) {
    if (limit < 2) {
        *primes = NULL;
        *prime_count = 0;
        return;
    }

    ull sieve_size = (limit + 1) / 2;
    char *sieve = (char*)malloc((sieve_size + 7) / 8);
    memset(sieve, 0xFF, (sieve_size + 7) / 8);

    sieve[0] &= ~(1 << 0); // 1 is not prime

    for (ull i = 1; i <= (ull)(sqrt(limit)) / 2; ++i) {
        if (sieve[i >> 3] & (1 << (i & 7))) {
            ull prime = 2 * i + 1;
            for (ull j = i + prime; j < sieve_size; j += prime) sieve [j >> 3] &= ~(1 << (j &7));
        }
    }
    
    *prime_count = (limit >= 2) ? 1 : 0;
    for (ull i = 1; i < sieve_size; ++i) {
        if (sieve[i >> 3] & (1 << (i & 7))) (*prime_count)++;
    }

    *primes = malloc(*prime_count * sizeof(ull));
    ull index = 0;
    if (limit >= 2) (*primes)[index++] = 2;
    for (ull i = 1; i < sieve_size; ++i) {
        if (sieve[i >> 3] & (1 << (i & 7))) (*primes)[index++] = 2 * i + 1;
    }

    free(sieve);
}

int is_prime(ull n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    ull sqrt_n = (ull)sqrt(n);
    ull *base_primes;
    ull base_count;

    sieve(sqrt_n, &base_primes, &base_count);
    
    for (ull i = 0; i < base_count; ++i) {
        if (n % base_primes[i] == 0) {
            free(base_primes);
            return 0;
        }
    }

    free(base_primes);
    return 1;
}

int main() {
    ull n;
    scanf("%llu", &n);

    for (int i = 0; i < n; i++) {
        ull x;
        scanf("%llu", &x);
        printf(is_prime(x) ? "YES\n" : "NO\n");
    }

    return 0;
}
