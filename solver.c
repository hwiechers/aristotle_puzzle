#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// variables
int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s;

// pool of numbers
int elem[19] = {  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                 11, 12, 13, 14, 15, 16, 17, 18, 19 };
int indices[7] = { 0, 1, 2, 3, 4, 5, 6 };

int set = 0;

// move elem[i] to elem[j] and shift elem[i+1]...elem[j] forward
// requires i <= j
void moveback(int i, int j)
{
    int temp = elem[i];
    for (int x = i; x < j; x++) {
        elem[x] = elem[x + 1];
    }
    elem[j] = temp;
}

// swap elem[i] and elem[j]
void swap(int i, int j)
{
    int temp = elem[i];
    elem[i] = elem[j];
    elem[j] = temp;
}

// sets j, k, n, o, p, r, s to the next permutation
// returns true until the permutations run out then returns false
bool next_permutation(void)
{
    for (int x = 6; x >= 0; x--) {
        indices[x]++;

        if (indices[x] == 19) {
            if (!x) {
                return false;
            }
            moveback(x, 18);
            indices[x] = x;
            continue;
        }

        swap(x, indices[x]);
        break;
    }

    j = elem[0];
    k = elem[1];
    n = elem[2];
    o = elem[3];
    p = elem[4];
    r = elem[5];
    s = elem[6];

    return true;
}

// adds values to set
// returns true if value successfully added; false otherwise
bool add(int value)
{
    if (value > 19 || value < 1) {
        return false;
    }

    int bit = 1 << value;
    if (set & bit) {
        return false;
    }

    set |= bit;
    return true;
}

void print_board(void)
{
    printf("    %2i  %2i  %2i\n", a, b, c);
    printf("  %2i  %2i  %2i  %2i\n", d, e, f, g);
    printf("%2i  %2i  %2i  %2i  %2i\n", h , i, j, k, l);
    printf("  %2i  %2i  %2i  %2i\n", m, n, o, p);
    printf("    %2i  %2i  %2i\n\n", q, r, s);
}

int main(void) 
{
    clock_t start = clock();

    j = elem[0];
    k = elem[1];
    n = elem[2];
    o = elem[3];
    p = elem[4];
    r = elem[5];
    s = elem[6];

    do {
        set = 0;
        set |= 1 << j;
        set |= 1 << k;
        set |= 1 << n;
        set |= 1 << o;
        set |= 1 << p;
        set |= 1 << r;
        set |= 1 << s;

        b = j + n + o;
        if (!add(b)) { continue; }

        d = j + k + o;
        if (!add(d)) { continue; };

        q = 38 - r - s;
        if (!add(q)) { continue; };

        l = 38 - p - s;
        if (!add(l)) { continue; };

        g = 38 - k - o - r;
        if (!add(g)) { continue; };

        c = 38 - g - l;
        if (!add(c)) { continue; };

        a = 38 - b - c;
        if (!add(a)) { continue; };

        m = 38 - n - o - p;
        if (!add(m)) { continue; };

        h = 38 - m - q;
        if (!add(h)) { continue; };

        i = 38 - d - n - r;
        if (!add(i)) { continue; };

        f = 38 - b - k - p;
        if (!add(f)) { continue; };

        e = 38 - d - f - g;
        if (!add(e)) { continue; };

        print_board();
    } while (next_permutation());

    clock_t end = clock();

    double time_taken = (end-start)/(double)CLOCKS_PER_SEC ; 
    printf("Time taken: %.1fs\n", time_taken);
}
