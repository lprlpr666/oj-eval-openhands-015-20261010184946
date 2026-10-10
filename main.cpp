#include <bits/stdc++.h>
using namespace std;

const int BUCKETS = 20;
const string DATA_PREFIX = "bucket_"; // files: bucket_0.txt ...

int bucket_id(const string &idx) {
    static hash<string> hasher;
    return (int)(hasher(idx) % BUCKETS);
}

string bucket_path(int id) {
    return DATA_PREFIX + to_string(id) + ".txt";
}

void ensure_buckets() {
    for (int i = 0; i < BUCKETS; ++i) {
        ofstream ofs(bucket_path(i), ios::app); // create if not exists
    }
}

void insert_entry(const string &idx, int val) {
    int id = bucket_id(idx);
    string path = bucket_path(id);
    // check duplicate
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string stored_idx; int stored_val;
        ss >> stored_idx >> stored_val;
        if (stored_idx == idx && stored_val == val) return; // duplicate
    }
    fin.close();
    ofstream fout(path, ios::app);
    fout << idx << ' ' << val << '\n';
}

void delete_entry(const string &idx, int val) {
    int id = bucket_id(idx);
    string path = bucket_path(id);
    string tmp = path + ".tmp";
    ifstream fin(path);
    ofstream fout(tmp);
    string line;
    bool removed = false;
    while (getline(fin, line)) {
        stringstream ss(line);
        string stored_idx; int stored_val;
        ss >> stored_idx >> stored_val;
        if (!removed && stored_idx == idx && stored_val == val) {
            removed = true; // skip
            continue;
        }
        fout << stored_idx << ' ' << stored_val << '\n';
    }
    fin.close();
    fout.close();
    if (removed) {
        rename(tmp.c_str(), path.c_str());
    } else {
        remove(tmp.c_str());
    }
}

void find_entries(const string &idx) {
    int id = bucket_id(idx);
    string path = bucket_path(id);
    ifstream fin(path);
    vector<int> vals;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string stored_idx; int stored_val;
        ss >> stored_idx >> stored_val;
        if (stored_idx == idx) vals.push_back(stored_val);
    }
    if (vals.empty()) {
        cout << "null\n";
        return;
    }
    sort(vals.begin(), vals.end());
    for (size_t i = 0; i < vals.size(); ++i) {
        if (i) cout << ' ';
        cout << vals[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ensure_buckets();
    int n; if(!(cin>>n)) return 0;
    string cmd, idx; long long val;
    for(int i=0;i<n;++i){
        cin>>cmd>>idx;
        if(cmd=="insert"){
            cin>>val; insert_entry(idx,(int)val);
        } else if(cmd=="delete"){
            cin>>val; delete_entry(idx,(int)val);
        } else if(cmd=="find"){
            find_entries(idx);
        }
    }
    return 0;
}
