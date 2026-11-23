#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> merge(vector<int> izq, vector<int> der){
    vector<int> res;
    int i=0, j=0;
    for(; i<izq.size() && j<der.size();){
        if(izq[i]<=der[j]){
            res.push_back(izq[i]);
            i++;
        }
        else{
            res.push_back(der[j]);
            j++;
        }
    }
    for(;j<der.size() || i<izq.size();){
            if(i==izq.size()){
                res.push_back(der[j]);
                j++;
            }
            else{
                res.push_back(izq[i]);
                i++;
            }
        }
    return res;
}


vector<int> merge_sort(vector<int> v){
    vector<int> res;
    int n = v.size();
    for(int ancho=1; ancho<n; ancho*=2){
        for(int i=0; i<n;i+=ancho*2 ){
            int mid=i+ancho;
            int fin=std::min(mid+ancho, n);
            if(i+ancho>=n){
                break;
            }
            else{
                vector<int> izq(v.begin()+i, v.begin()+mid);
                vector<int> der(v.begin()+mid, v.begin()+fin);
                res=merge(izq,der);
            }

            for(int l=i, k=0; k<res.size(); l++, k++){
                v[l]=res[k];
            }
        }
    }
    
    return v;
    
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
