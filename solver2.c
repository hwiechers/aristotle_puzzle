#include <libgen.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int swap(int array[], int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int print(int array[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%i ", array[i]);
    }
    printf("\n");
}

int moveforward(int array[], int i, int j)
{
    int temp = array[j];
    for (int k = j; k > i; k--) 
        array[k] = array[k - 1];
    array[i] = temp;
}

int moveback(int array[], int i, int j)
{
    int temp = array[i];
    for (int k = i; k < j; k++) 
        array[k] = array[k + 1];
    array[j] = temp;
}

bool check(int a, int h, int c, int l, int q, int s, int o)
{
    bool valid = h > a && 
                 c > h &&
                 l > a && l != h && l != c &&
                 q > a && q != h && q != c && q != l &&
                 s > a && s != h && s != c && s != l && s != q &&
                 o != a && o != h && o != c && o != l & o != q && o != s;

    if (!valid) {
        printf("INVALID: ");
        printf("%i %i %i %i %i %i %i\n", a, h, c, l, q, s, o);
    }

    return valid;
}

// adds values to set
// returns true if value successfully added; false otherwise
bool add(int* set, int value)
{
    if (value > 19 || value < 1) {
        return false;
    }

    int bit = 1 << value;
    if (*set & bit) {
        return false;
    }

    *set |= bit;
    return true;
}

bool try_solve(int a, int h, int c, int l, int q, int s, int o, 
               int solution[const 19])
{
    int set = 0;
    set |= 1 << a;
    set |= 1 << h;
    set |= 1 << c;
    set |= 1 << l;
    set |= 1 << q;
    set |= 1 << s;
    set |= 1 << o;

    int b = 38 - a - c;
    if (!add(&set, b)) return false;

    int g = 38 - c - l;
    if (!add(&set, g)) return false;

    int p = 38 - l - s;
    if (!add(&set, p)) return false;

    int r = 38 - q - s;
    if (!add(&set, r)) return false;

    int m = 38 - q - h;
    if (!add(&set, m)) return false;

    int d = 38 - h - a;
    if (!add(&set, d)) return false;

    int n = 38 - m - o - p;
    if (!add(&set, n)) return false;

    int i = 38 - d - n - r;
    if (!add(&set, i)) return false;

    int e = 38 - b - i - m;
    if (!add(&set, e)) return false;

    int f = 38 - g - e - d;
    if (!add(&set, f)) return false;

    int k = 38 - p - f - b;
    if (!add(&set, k)) return false;

    int j = 38 - h - i - k - l;
    if (!add(&set, j)) return false;

    solution[0] = a;
    solution[1] = b;
    solution[2] = c;
    solution[3] = d;
    solution[4] = e;
    solution[5] = f;
    solution[6] = g;
    solution[7] = h;
    solution[8] = i;
    solution[9] = j;
    solution[10] = k;
    solution[11] = l;
    solution[12] = m;
    solution[13] = n;
    solution[14] = o;
    solution[15] = p;
    solution[16] = q;
    solution[17] = r;
    solution[18] = s;

    return true;
}

void rotate(int val[const 19]) 
{
    int temp;

    temp = val[0];
    val[0] = val[2];
    val[2] = val[11];
    val[11] = val[18];
    val[18] = val[16];
    val[16] = val[7];
    val[7] = temp;

    temp = val[1];
    val[1] = val[6];
    val[6] = val[15];
    val[15] = val[17];
    val[17] = val[12];
    val[12] = val[3];
    val[3] = temp;

    temp = val[4];
    val[4] = val[5];
    val[5] = val[10];
    val[10] = val[14];
    val[14] = val[13];
    val[13] = val[8];
    val[8] = temp;
}

void mirror(int val[const 19])
{
    swap(val, 3, 1);
    swap(val, 8, 5);
    swap(val, 13, 10);
    swap(val, 17, 15);
    swap(val, 7, 2);
    swap(val, 12, 6);
    swap(val, 16, 11);
}

void print_board(int val[const 19])
{
    printf("    %2i  %2i  %2i\n", val[0], val[1], val[2]);
    printf("  %2i  %2i  %2i  %2i\n", val[3], val[4], val[5], val[6]);
    printf("%2i  %2i  %2i  %2i  %2i\n", val[7] , val[8], val[9], 
                                        val[10], val[11]);
    printf("  %2i  %2i  %2i  %2i\n", val[12], val[13], val[14], val[15]);
    printf("    %2i  %2i  %2i\n\n", val[16], val[17], val[18]);
}

void print_solution(int val[const 19], bool all)
{
    print_board(val);
    if (all) {
        for (int i = 0; i < 5; i++) {
            rotate(val);
            print_board(val);
        }
        mirror(val);
        print_board(val);
        for (int i = 0; i < 5; i++) {
            rotate(val);
            print_board(val);
        }
    }
}

int main (int argc, char *argv[])
{
    bool valid_args = false;
    bool show_all = false;
    if (argc == 1) {
        valid_args = true;
    } else if (argc == 2 && !strcmp(argv[1], "--all")) {
        valid_args = true;
        show_all = true;
    }

    if (!valid_args) {
        printf ("usage: %s [--all]\n", basename(argv[0]));
        return 1;
    }

    clock_t start = clock();

    int numbers[] = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 
                      11, 12, 13, 14, 15, 16, 17, 18, 19 }; 
    int total_tested = 0;
    int solution[19];

    for (int a = 1; a <= 14; a++) {

        int hs = a;
        int he = 17;
        int hx = hs;
        while(true) {

            int cs = a + 1;
            int ce = 18;
            int cx = hx + 1;    
            moveforward(numbers, cs, cx);
            while(true) {

                int ls = a + 2;
                int le = 18;
                int lx = ls;
                while (true) {

                    int qs = a + 3;
                    int qe = 18;
                    int qx = qs;
                    while (true) {

                        int ss = a + 4;
                        int se = 18;
                        int sx = ss;
                        while (true) { 

                            for (int o = 1; o < a; o++) {
                                if (try_solve(a, numbers[hs], numbers[cs], 
                                              numbers[ls], numbers[qs], 
                                              numbers[ss], o,
                                              solution))
                                    print_solution(solution, show_all);
                                total_tested++;
                            }

                            for (int ox = a + 5; ox < 19; ox++) {
                                if (try_solve(a, numbers[hs], numbers[cs], 
                                              numbers[ls], numbers[qs], 
                                              numbers[ss], numbers[ox],
                                              solution))
                                    print_solution(solution, show_all);
                                total_tested++;
                            }
                            
                            if (sx >= se) break;
                            sx++;
                            swap(numbers, ss, sx);
                        }
                        moveback(numbers, ss, se);

                        if (qx >= qe) break;
                        qx++;
                        swap(numbers, qs, qx);
                    }
                    moveback(numbers, qs, qe);

                    if (lx >= le) break;
                    lx++;
                    swap(numbers, ls, lx);
                }
                moveback(numbers, ls, le);

                if (cx >= ce) break;
                cx++;
                swap(numbers, cs, cx);
            }
            moveback(numbers, cs, ce);

            if (hx >= he) break;
            hx++;
            swap(numbers, hs, hx);
        }
        moveback(numbers, hs, he);

    }

    printf("Total tested: %i\n", total_tested);

    clock_t end = clock();

    double time_taken = (end-start)/(double)CLOCKS_PER_SEC ; 
    printf("Time taken: %.1fs\n", time_taken);
    return 0;
}
