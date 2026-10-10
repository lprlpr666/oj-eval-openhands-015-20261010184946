#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    unordered_map<string, set<int>> mp;
    string cmd, idx; long long val; // value fits int
    for(int i=0;i<n;++i){
        cin>>cmd>>idx;
        if(cmd=="insert"){
            cin>>val;
            auto &s = mp[idx];
            s.insert((int)val);
        } else if(cmd=="delete"){
            cin>>val;
            auto it = mp.find(idx);
            if(it!=mp.end()){
                it->second.erase((int)val);
                if(it->second.empty()) mp.erase(it);
            }
        } else if(cmd=="find"){
            auto it = mp.find(idx);
            if(it==mp.end() || it->second.empty()){
                cout<<"null\n";
            } else {
                bool first=true;
                for(int v: it->second){
                    if(!first) cout<<' ';
                    first=false;
                    cout<<v;
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}
