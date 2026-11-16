#include <iostream>
#include <random>
#include<vector>
#include <chrono>
#include <fstream>

using namespace std;
vector<int> destino;

vector<int> merge(vector<int> izq, vector<int> der){
    vector<int> destino;
    int i=0, j=0;
    for(; i<izq.size() && j< der.size();){
        if(izq[i]<=der[j]){
            destino.push_back(izq[i]);
            i++;
        }
        else{
            destino.push_back(der[j]);
            j++;
        }
    }
    for(;j<der.size() || i<izq.size();){
        if(i==izq.size()){
            destino.push_back(der[j]);
            j++;
        }
        else{
            destino.push_back(izq[i]);
            i++;
        }
    }
    
    return destino;
}


vector<int> merge_sort(vector<int> v){
    
    int mid=v.size()/2;
    
    vector<int> izq(v.begin(), v.begin() + mid);
    vector<int> der(v.begin()+mid, v.end());
    
    if(v.size()<=1){
        return v;
    }
    else{
        izq=merge_sort(izq);
        der=merge_sort(der);
        return merge(izq,der);
    }
    
    
    
}

int main(){
    
    vector<int> v={6,7,8,3,4,6,7,0,10,19};
    cout<<"Vector desordenado:"<<endl;
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<',';
    }
    cout<<endl;
    cout<<"Vector ordenado:"<<endl;
    vector<int> r;
    r=merge_sort(v);
    for(int i=0; i<r.size(); i++){
        cout<<r[i]<<',';
    }
    
    
    
    
    return 0;
}
