#include <iostream>
#include <vector>
#include "vector.hpp"
#include "timer.hpp"

using namespace std;

void assigntest(){
    vector<int> vektorius;
    cout<<"Assign testas su normaliu vektoriumi"<<endl;
    vektorius.assign(5, 10);
    cout<<endl<<"Rezultatai"<<endl;
    cout<<"Vektoriaus dydis:"<<vektorius.size()<<endl;
    cout<<"Vektoriuje esantys skaiciai:"<<endl;
    for(int i=0; i<vektorius.size(); i++){
        cout<<vektorius[i]<<endl;
    }
    cout<<endl;
    Vectorklase<int> savasvektorius;
    cout<<"Assign testas su savu vektoriumi"<<endl;
    savasvektorius.assign(5, 10);
    cout<<endl<<"Rezultatai"<<endl;
    cout<<"Vektoriaus dydis:"<<savasvektorius.size()<<endl;
    cout<<"Vektoriuje esantys skaiciai:"<<endl;
    for(int i=0; i<savasvektorius.size(); i++){
        cout<<savasvektorius[i]<<endl;
    }
}

void pushbacktest(){
    vector<int> vektorius;
    cout<<"Push_back testas su normaliu vektoriumi"<<endl;
    int n=1000000;
    Timer timer;
    timer.reset();
    for(int i=0; i<n; i++){
        vektorius.push_back(i);
    }
    double elapsed=timer.elapsed();
    cout<<endl<<"Rezultatai"<<endl;
    cout<<"Testas su "<<n<<" elementu truko "<<elapsed<<"s"<<endl;
    Vectorklase<int> savasvektorius;
    cout<<"Push_back testas su savu vektoriumi"<<endl;
    timer.reset();
    for(int i=0; i<n; i++){
        savasvektorius.push_back(i);
    }
    double elapsed2=timer.elapsed();
    cout<<endl<<"Rezultatai"<<endl;
    cout<<"Testas su "<<n<<" elementu truko "<<elapsed2<<"s"<<endl;
}

int main(){
    assigntest();
    pushbacktest();
}
