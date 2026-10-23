//Maxwell Koegler | COMSC 210 | lab 26
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <iterator>

using namespace std;

int main() {
    vector<string> v;
    list<string> l;
    set<string> s;
    string code;

    const int runs = 15;
    long long times [2][4][3] = {};
            //  ^ this is for current run, and accumulated totals

    for(int r  = 0; r < runs; r++) {

        v.clear();
        l.clear();
        s.clear();

        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end;

        ifstream fin("codes.txt");

        // Reading race
        start = chrono::high_resolution_clock::now();
        while(fin >> code) {
            v.push_back(code);
        }
        end = chrono::high_resolution_clock::now();
        times[0][0][0] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        fin.close();

        fin.open("codes.txt");
        start = chrono::high_resolution_clock::now();
        while(fin >> code) {
            l.push_back(code);
        }
        end = chrono::high_resolution_clock::now();
        times[0][0][1] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        fin.close();

        fin.open("codes.txt");
        start = chrono::high_resolution_clock::now();
        while(fin >> code) {
            s.insert(code);
        }
        end = chrono::high_resolution_clock::now();
        times[0][0][2] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        fin.close();

        start = chrono::high_resolution_clock::now(); //sorting
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                if (v[i] > v[j]) {
                    string temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }
        end = chrono::high_resolution_clock::now();
        times[0][1][0] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        start = chrono::high_resolution_clock::now();
        l.sort();
        end = chrono::high_resolution_clock::now();
        times[0][1][1] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        times[0][1][2] = -1;

        start = chrono::high_resolution_clock::now(); //inserting
        v.insert(v.begin() + v.size() / 2, "test");
        end = chrono::high_resolution_clock::now();
        times[0][2][0] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        list<string>::iterator li = l.begin();
        advance(li, l.size() / 2);
        start = chrono::high_resolution_clock::now();
        l.insert(li, "test");
        end = chrono::high_resolution_clock::now();
        times[0][2][1] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        start = chrono::high_resolution_clock::now();
        s.insert("test");
        end = chrono::high_resolution_clock::now();
        times[0][2][2] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        start = chrono::high_resolution_clock::now(); //deleting
        v.erase(v.begin() + v.size() / 2);
        end = chrono::high_resolution_clock::now();
        times[0][3][0] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        li = l.begin();
        advance(li, l.size() / 2);
        start = chrono::high_resolution_clock::now();
        l.erase(li);
        end = chrono::high_resolution_clock::now();
        times[0][3][1] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

        set<string>::iterator si = s.begin();
        advance(si, s.size() / 2);
        start = chrono::high_resolution_clock::now();
        s.erase(si);
        end = chrono::high_resolution_clock::now();
        times[0][3][2] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        times[0][3][2]= times[0][3][2] = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
        for(int i=0; i<4; i++){
            for(int j = 0; j < 3; j++) {
                if(times[0][i][j] != -1) {
                    times[1][i][j] += times[0][i][j];
                }
            }
        }
    }
    cout << "Number of simulations: " << runs << endl;
    string operations[4] = {"Read", "Sort", "Insert", "Delete"};
    cout << "Operation    Vector        List        Set" << endl;

    for (int i = 0; i < 4; i++) {
        cout << operations[i] << "        ";
        for (int j = 0; j < 3; j++) {
            cout << times[0][i][j] / runs << "        ";
        }
        cout << endl;
    }

    return 0;
}