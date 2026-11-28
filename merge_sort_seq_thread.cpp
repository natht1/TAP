#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include<thread>

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


void merge_sort(vector<int>& v,int from, int to){
    vector<int> res;
    int n = to;
    for(int ancho=1; ancho<n-from; ancho*=2){
        for(int i=from; i<n;i+=ancho*2 ){
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
        
}

int main(){
    
    vector<int> v={9, 4, 7, 1, 8, 3, 6, 2, 10, 5};
    
    /*
    
    cout<<"Vector desordenado:"<<endl;
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<',';
    }
    cout<<endl;
    cout<<"Vector ordenado:"<<endl;
    merge_sort(v,3,7);
    */
    
    int nThreads=4;
    int n= v.size();
    int traza= n/nThreads;
    int residuo= n%nThreads;
    vector<thread> ths(nThreads);
    vector<int> fronteras;
    vector<int> res(n);
    int from=0;
    int tamaño;
    fronteras.push_back(from);
    
    for(int i=0; i<nThreads;i++){
        
        if(residuo>0){
            tamaño=traza+1;
            residuo--;
        }
        else tamaño=traza;
        
        int to=from+tamaño;
        
        ths[i]=thread(merge_sort,ref(v), from, to);
        
        from=to;
        fronteras.push_back(from);
        
    }
    
    for(int j=0; j<nThreads; j++)
        ths[j].join();
    
    
    for(int j=0; j<nThreads-1; j++){
        
        vector<int> izq(v.begin()+fronteras[0], v.begin()+fronteras[j+1]);
        vector<int> der(v.begin()+fronteras[j+1], v.begin()+fronteras[j+2]);
        res=merge(izq,der);
        
        for(int o=0; o<res.size(); o++)
            v[o]=res[o];
        
    }
    
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<',';
    }
    
    
    
    
    return 0;
}
