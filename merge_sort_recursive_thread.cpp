#include <iostream>
#include <random>
#include<vector>
#include <chrono>
#include <fstream>
#include <thread>

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


void merge_sort(vector<int>& v, int from, int to){
    
    int mid=from + (to-from)/2;

    
    if(to-from<=1){
        return;
    }
    else{
        merge_sort(v,from,mid);
        merge_sort(v,mid,to);
    }
    vector<int> izq(v.begin()+from, v.begin()+mid);
    vector<int> der(v.begin()+mid, v.begin()+to);
    vector<int> res=merge(izq,der);
    int j=0;
    for(int i=from; i<to;i++, j++){
        v[i]=res[j];
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
    vector<int> r;
    merge_sort(v, 0, 3);
    merge_sort(v, 3, 6);
    
    */
    int nThreads = 4;
    int n= v.size();
    int traza=n/nThreads;
    int residuo=n%nThreads;
    int tamaño;
    vector<thread> ths(nThreads);
    vector<int> fronteras;
    vector<int> res(n);
    int from=0;
    fronteras.push_back(from);
    
    for(int i=0; i<nThreads; i++){
        if(residuo>0){
            tamaño=traza+1;
            residuo--;
        }
        else tamaño=traza;
        
        int to= from+tamaño;
        
        ths[i]=thread(merge_sort,ref(v), from, to);
        fronteras.push_back(to);
        from=to;
    }
    
    for(int j=0; j<ths.size(); j++)
        ths[j].join();
    
    for(int p=0; p< nThreads-1; p++){
        vector<int> izq(v.begin()+fronteras[0], v.begin()+fronteras[p+1]);
        vector<int> der(v.begin()+fronteras[p+1], v.begin()+fronteras[p+2]);
        res=merge(izq,der);
        
        for(int i=0; i<res.size();i++){
            v[i]=res[i];
        }
    }
    
    
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<',';
    }
    
    
    
    
    return 0;
}
