#include <iostream>
#include <vector>
#include <utility> // Para std::swap
#include <thread>
#include <algorithm>
using namespace std;

void bubbleSort(std::vector<int>& arr, int from, int to) {
    size_t n = to-from;
    for (size_t i = 0; i < n; ++i) {
        bool intercambiado = false;

        // Los últimos i elementos ya están en su posición final
        for (size_t j = from; j < to-i-1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                intercambiado = true;
            }
        }

        // Si no hubo intercambios en esta pasada, ya está ordenado
        if (!intercambiado) {
            break;
        }
    }
}

vector<int> merge(vector<int> izq, vector<int> der){
    vector<int> res;
    int i=0, j=0;
    for(; i<izq.size() && j<der.size();){
        if(izq[i]<der[j]){
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

int main() {
    std::vector<int> datos = {9, 4, 7, 1, 8, 3, 6, 2, 10, 5};

    int nThreads = 4;
    int n=datos.size();
    int traza= n/nThreads;
    int residuo=n% nThreads;
    vector<thread> ths(nThreads);
    vector<int> res(n);
    int tamaño=0;
    vector<int> fronteras;
    
        
    int from = 0;
    fronteras.push_back(from);
    for (int t = 0; t < nThreads; t++) {
        
        if(residuo>0){
            tamaño= traza+1;
            residuo--;
        }
        else { tamaño=traza;}
        
        int to = from + tamaño;
        ths[t] = thread(bubbleSort, ref(datos), from,to);
        
        fronteras.push_back(to);
        from=to;
        
    }
    
    for ( int i = 0; i < nThreads; i++ )
            ths[i].join();
    
    for(int k=0; k<nThreads-1;k++){
        vector<int> izq(datos.begin()+fronteras[0], datos.begin()+fronteras[k+1]);
        vector<int> der(datos.begin()+fronteras[k+1], datos.begin()+fronteras[k+2]);
        
        res=merge(izq,der);
        for(int i=0; i<res.size(); i++){
            datos[i]=res[i];
        }
        
    }
    
    for (int x : datos) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
