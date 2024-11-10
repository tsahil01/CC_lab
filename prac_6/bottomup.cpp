#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Grammar {
    char p[20];
    char prod[20];
} g[10];

int main() {
    int i, stpos, j, k, l, m, o, p, f, r;
    int np, tspos, cr;
    char sc, ts[10];
    char ip[10];
    char stack[10];

    cout << "\nEnter Number of productions: ";
    cin >> np;

    cout << "\nEnter productions:\n";
    for (i = 0; i < np; i++) {
        cin >> ts;
        strncpy(g[i].p, ts, 1);
        strcpy(g[i].prod, &ts[3]);
    }

    cout << "\nEnter Input: ";
    cin >> ip;

    int lip = strlen(ip);
    stpos = 0;
    i = 0;

    cout << "\n\nStack\tInput\tAction";

    do {
        r = 1;

        while (r != 0) {
            cout << "\n";
            for (p = 0; p < stpos; p++) {
                cout << stack[p];
            }
            cout << "\t";

            for (p = i; p < lip; p++) {
                cout << ip[p];
            }

            if (r == 2) {
                cout << "\tReduced";
            } else {
                cout << "\tShifted";
            }
            r = 0;

            for (k = 0; k < stpos; k++) {
                f = 0;

                for (l = 0; l < 10; l++) {
                    ts[l] = '\0';
                }

                tspos = 0;
                for (l = k; l < stpos; l++) {
                    ts[tspos] = stack[l];
                    tspos++;
                }

                for (m = 0; m < np; m++) {
                    cr = strcmp(ts, g[m].prod);

                    if (cr == 0) {
                        for (l = k; l < 10; l++) {
                            stack[l] = '\0';
                        }
                        stpos = k;

                        strcat(stack, g[m].p);
                        stpos++;
                        r = 2;
                    }
                }
            }
        }

        sc = ip[i];
        stack[stpos] = sc;
        i++;
        stpos++;

    } while (strlen(stack) != 1 && stpos < lip);

    if (strlen(stack) == 1) {
        cout << "\nString accepted!";
    } else {
        cout << "\nString not accepted!";
    }

    return 0;
}
