#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

template<class T>
class Pivot1{
    public:
    T* operator()(T* ar, int from, int to){
        return (ar+from);
    }
};

template<class T>
class Pivot2{
public:
    T* operator()(T* ar, int from, int to){
        T prom=0;
        for(int i=from; i<=to; i++){
            prom+=ar[i];
        }
        prom=prom/(to-from+1);
        
        T* candidato=nullptr;
        T distancia=0;
        for(int i=from; i<=to; i++){
            if(candidato==nullptr){
                candidato=(ar+i);
                distancia=abs(prom - *candidato);
                
            }
            else{
                if(abs(prom-*(ar+i))<distancia){
                    candidato=ar+i;
                    distancia=abs(prom - *candidato);
                }
            }
        }

        return (candidato);
    }
};

template<class T>
class Pivot3{
public:
    T* operator()(T* ar, int from, int to){
        T prom=(*(ar+from)+*(ar+to))/2;
        T* candidato=nullptr;
        T distancia=0;
        for(int i=from; i<=to; i++){
            if(candidato==nullptr){
                candidato=(ar+i);
                distancia=abs(prom - *candidato);
            }
            else{
                if(abs(prom-*(ar+i))<distancia){
                    candidato=ar+i;
                    distancia=abs(prom - *candidato);
                }
            }
        }
        
        return (candidato);
    
    }
};

template<class T>
class Pivot4{
public:
    T* operator()(T* ar, int from, int to){
        T* prom=(ar+(to+from)/2);
        return prom;
    }
};

template<class T>
class Minor{
    public:
    bool operator()(T a, T b){
        return a<b;
    }
};
template<class T>
class Greater{
    public:
    bool operator()(T a, T b){
        return a>b;
    }
};

template<class T, class C, class G, class P>
void quicksort(T* ar, int from, int to, C m, G g, P p){
    if(from<to){
        T* i=ar+from;
        T* j= ar+to-1;
        T* piv= p(ar,from,to);
        int pospiv=0;
        swap(*piv,*(ar+to));
        for(;i<=j;){
            if(g(*i,*(ar+to))){
                if(m(*j,*(ar+to))){
                    swap(*i,*j);
                    j--;
                    i++;
                }
                else j--;
            }
            else{i++;}
        }
        
        pospiv= (i-ar);
        swap(*(ar+pospiv),*(ar+to));
        
        
        quicksort(ar,pospiv+1,to,m,g,p);
        quicksort(ar,from,pospiv-1,m,g,p);
    }
}

int generarAleatorio(int min, int max) {
    // 'static' hace que se inicialice una sola vez en todo el programa
    static random_device rd;
    static mt19937 gen(rd());
    
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

template<class T>
void fillar(T* ar, int n){
    for(int i=0; i<n; i++){
        *(ar+i)=generarAleatorio(0,100);
    }
}

template<class T>
void copyar(T* arq, T* ar, int n){
    for(int i=0; i<n; i++){
        *(arq+i)=*(ar+i);
    }
}



int main()
{

    ofstream f("/Users/nani/Desktop/tiempos.csv");
    f << "n,pivot1,pivot2,pivot3,pivot4\n";
    for(int n=1000; n<= 50000; n+=1000){
        int* ar=new int[n], *ar1=new int[n], *ar2=new int[n], *ar3=new int[n];
        fillar(ar,n);
        copyar(ar1,ar,n);
        copyar(ar2,ar,n);
        copyar(ar3,ar,n);
        Minor<int> l;
        Greater<int> g;
        Pivot1<int> p1;
        Pivot2<int> p2;
        Pivot3<int> p3;
        Pivot4<int> p4;

        auto t0 = chrono::high_resolution_clock::now();
        quicksort(ar,0,n-1,l,g,p1);
        auto t1 = chrono::high_resolution_clock::now();
        quicksort(ar1,0,n-1,l,g,p2);
        auto t2 = chrono::high_resolution_clock::now();
        quicksort(ar2,0,n-1,l,g,p3);
        auto t3 = chrono::high_resolution_clock::now();
        quicksort(ar3,0,n-1,l,g,p4);
        auto t4 = chrono::high_resolution_clock::now();
        
        double ms1 = chrono::duration<double, milli>(t1 - t0).count();
        double ms2 = chrono::duration<double, milli>(t2 - t1).count();
        double ms3 = chrono::duration<double, milli>(t3 - t2).count();
        double ms4 = chrono::duration<double, milli>(t4 - t3).count();
        
        f << n << ',' << ms1 << ',' << ms2 << ',' << ms3 << ',' << ms4 << '\n';
        
        delete[] ar;
        delete[] ar1;
        delete[] ar2;
        delete[] ar3;
    }
    f.close();
    /*
    int* ar;
    int const n=10;
    ar= new int[n];
    fillar(ar,n);
    Minor<int> l;
    Greater<int> g;
    Pivot1<int> p1;
    Pivot2<int> p2;
    Pivot3<int> p3;
    Pivot4<int> p4;
    
    cout<<"Array sin ordenar"<<endl;
    for(int i=0; i<n; i++){
        cout<<*(ar+i)<<',';
    }
    cout<<endl;
        
    quicksort(ar,0,n-1,l,g,p2);

    cout<<"Array ordenada"<<endl;
    for(int i=0; i<n; i++){
        cout<<*(ar+i)<<',';
    }
    cout<<endl;
    */
    
    
    return 0;
}
