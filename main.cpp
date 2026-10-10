#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

// Directory to store per-index files
const string DATA_DIR = "data";

void ensure_data_dir() {
    if (!fs::exists(DATA_DIR)) {
        fs::create_directory(DATA_DIR);
    }
}

string file_path(const string &idx) {
    // Sanitize index for filename
    string safe = idx;
    for (char &c : safe) {
        if (c == '/' || c == '\\' || c == '\0') c = '_';
    }
    return DATA_DIR + "/" + safe + ".txt";
}

void insert_entry(const string &idx, int val) {
    string path = file_path(idx);
    vector<int> vals;
    if (fs::exists(path)) {
        ifstream fin(path);
        int x;
        while (fin >> x) vals.push_back(x);
    }
    // avoid duplicate
    if (find(vals.begin(), vals.end(), val) != vals.end()) return;
    vals.push_back(val);
    sort(vals.begin(), vals.end());
    ofstream fout(path, ios::trunc);
    for (int x : vals) fout << x << '\n';
}

void delete_entry(const string &idx, int val) {
    string path = file_path(idx);
    if (!fs::exists(path)) return;
    string tmp_path = path + ".tmp";
    ifstream fin(path);
    ofstream fout(tmp_path);
    int x;
    bool removed = false;
    while (fin >> x) {
        if (!removed && x == val) {
            removed = true; // skip this value
            continue;
        }
        fout << x << '\n';
    }
    fin.close();
    fout.close();
    if (removed) {
        // replace original with temp
        fs::remove(path);
        fs::rename(tmp_path, path);
    } else {
        // no deletion, remove temp
        fs::remove(tmp_path);
    }
}

void find_entries(const string &idx) {
    string path = file_path(idx);
    if (!fs::exists(path)) {
        cout << "null\n";
        return;
    }
    vector<int> vals;
    ifstream fin(path);
    int x;
    while (fin >> x) vals.push_back(x);
    if (vals.empty()) {
        cout << "null\n";
        return;
    }
    // vals already sorted
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) cout << ' ';
        cout << vals[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ensure_data_dir();
    int n;
    if (!(cin >> n)) return 0;
    string cmd, idx;
    long long val;
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
