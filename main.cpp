#include <bits/stdc++.h>
using namespace std;

const string DATA_FILE = "data.txt";

// Ensure data file exists
void ensure_file() {
    std::ofstream ofs(DATA_FILE, ios::app);
    // just open/close to create if not exists
}

bool entry_exists(const string &idx, int val) {
    ifstream fin(DATA_FILE);
    string i; int v;
    while (fin >> i >> v) {
        if (i == idx && v == val) return true;
    }
    return false;
}

void insert_entry(const string &idx, int val) {
    if (entry_exists(idx, val)) return; // avoid duplicate
    ofstream fout(DATA_FILE, ios::app);
    fout << idx << ' ' << val << '\n';
}

void delete_entry(const string &idx, int val) {
    ifstream fin(DATA_FILE);
    string tmp_file = DATA_FILE + ".tmp";
    ofstream fout(tmp_file);
    string i; int v;
    bool removed = false;
    while (fin >> i >> v) {
        if (!removed && i == idx && v == val) {
            removed = true; // skip this line
            continue;
        }
        fout << i << ' ' << v << '\n';
    }
    fin.close();
    fout.close();
    std::filesystem::rename(tmp_file, DATA_FILE);
}

void find_entries(const string &idx) {
    ifstream fin(DATA_FILE);
    vector<int> vals;
    string i; int v;
    while (fin >> i >> v) {
        if (i == idx) vals.push_back(v);
    }
    if (vals.empty()) {
        cout << "null\n";
        return;
    }
    sort(vals.begin(), vals.end());
    for (size_t j = 0; j < vals.size(); ++j) {
        if (j) cout << ' ';
        cout << vals[j];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ensure_file();
    int n; if(!(cin >> n)) return 0;
    string cmd, idx; long long val;
    for (int i = 0; i < n; ++i) {
        cin >> cmd >> idx;
        if (cmd == "insert") {
            cin >> val;
            insert_entry(idx, (int)val);
        } else if (cmd == "delete") {
            cin >> val;
            delete_entry(idx, (int)val);
        } else if (cmd == "find") {
            find_entries(idx);
        }
    }
    return 0;
}
