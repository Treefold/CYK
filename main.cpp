#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>

using namespace std;

int nrNT, _s;
map <string, int> T; /// Terminals' new names
map <string, int> NT; /// NonTerminals's new names
set <pair <int, int> > TR; /// Relation A -> a
set <pair <int, pair <int, int> > > NTR; /// Relation A -> BC

ifstream in ("date.in");
void read()
{
    int n, i;
    string a, b, c;
    in >> n;
    for (i = 1; i <= n; ++i) {
        in >> a;
        T.insert ({a, i});
    }
    in >> nrNT;
    for (i = 1; i <= nrNT; ++i) {
        in >> a;
        NT.insert ({a, i});
    }
    in >> n;
    for (i = 0; i < n; ++i) {
        in >> a >> b;
        if (T.find (b) != T.end()) {TR.insert ({NT[a], T[b]});}
        else {in >> c; NTR.insert ({NT[a], {NT[b], NT[c]}});}
    }
}

int main()
{
    read();
    int n, m, k, l, i, j, good, _t;
    string t;
    set <pair <int, int> >:: iterator TRi, TRf = TR.end();
    set <pair <int, pair <int, int> > >:: iterator NTRi, NTRf = NTR.end();
    in >> m;
    for (j = 0; j < m; ++j) {
        good = 1;
        in >> n;
        set <int> mat[n+1][n+1];
        for (i = 1; i <= n ; ++i) {
            in >> t;
            if (T.find(t) != T.end()) {
                _t = T[t];
                for (TRi = TR.begin(); TRi != TRf; ++TRi) {
                    if (TRi->second == _t) {
                        mat[1][i].insert (TRi->first);
                    }
                }
            } else {good = 0;}
        }
        if (!good) {cout << "Nu\n"; continue;}

        for (l = 2; l <= n; ++l) { /// length
            for (i = 1; i <= n-l+1; ++i) { /// starting point
                for (k = 1; k < l; ++k) { /// partion
                    for (NTRi = NTR.begin(); NTRi != NTRf; ++NTRi) {
                            if (mat[k][i].find(NTRi->second.first) != mat[k][i].end() && mat[l-k][i+k].find(NTRi->second.second) != mat[l-k][i+k].end()) {
                            mat[l][i].insert (NTRi->first);
                        }
                    }
                }
            }
        }

        cout << ((mat[n][1].find (1) != mat[n][1].end() ) ? "Yes\n" : "No\n");
    }

    in.close();
    return 0;
}
