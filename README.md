# Vector

Vectorklase – eksperimentinė vector klasė.
* [Vectorklase::push_back](#vectorklasepush_back)
* [Vectorklase::assign](#vectorklaseassign)
* [Vectorklase::clear](#vectorklaseclear)
* [Vectorklase::pop_back](#vectorklasepop_back)
* [Vectorklase::resize](#vectorklaseresize)

# Funkcijų pavyzdžiai
## Vectorklase::push_back
Funkcija prideda nurodytą reikšmę į konteinerio pabaigą.
### Realizacija
```
void push_back(const T& v);
void push_back(const T&& v);
```
### Pavyzdys
```
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
    cout<<"Testas su "<<n<<" elementu uztruko "<<elapsed<<"s"<<endl;
    Vectorklase<int> savasvektorius;
    cout<<endl<<"Push_back testas su savu vektoriumi"<<endl;
    timer.reset();
    for(int i=0; i<n; i++){
        savasvektorius.push_back(i);
    }
    double elapsed2=timer.elapsed();
    cout<<endl<<"Rezultatai"<<endl;
    cout<<"Testas su "<<n<<" elementu uztruko "<<elapsed2<<"s"<<endl;
}
```
### Rezultatas
```
Push_back testas su normaliu vektoriumi

Rezultatai
Testas su 1000000 elementu uztruko 0.015957s

Push_back testas su savu vektoriumi

Rezultatai
Testas su 1000000 elementu uztruko 0.027925s
```
### Užduočių atlikimo laiko palyginimas su std::vector (sekundėmis)
|             | 10000    | 1000000  | 10000000 | 100000000 |
|-------------|-------   |----------|----------|-----------|
| std::vector | 0.000998 | 0.01496 | 0.128655|  1.24766 |
| Vectorklase | 0        | 0.014959| 0.197471| 1.3833   |

Rezultatai yra gan identiški, tačiau didėjant užduočiai pastebimas std::vector pranašumas.

## Vectorklase::assign
Pakeičia senus elementus naujai paskirtomis reikšmėmis. Jei reikia, pakeičia vektoriaus dydį.

### Realizacija
```
void assign(size_type n, const T& v);
```
### Pavyzdys
```
void assigntest(){
    vector<int> vektorius;
    cout<<"Assign testas su normaliu vektoriumi"<<endl;
    vektorius.assign(5, 10);
    cout<<"Rezultatai"<<endl;
    cout<<"Vektoriaus dydis:"<<vektorius.size()<<endl;
    cout<<"Vektoriuje esantys skaiciai:"<<endl;
    for(int i=0; i<vektorius.size(); i++){
        cout<<vektorius[i]<<endl;
    }
    cout<<endl;
    Vectorklase<int> savasvektorius;
    cout<<"Assign testas su savu vektoriumi"<<endl;
    savasvektorius.assign(5, 10);
    cout<<"Rezultatai"<<endl;
    cout<<"Vektoriaus dydis:"<<savasvektorius.size()<<endl;
    cout<<"Vektoriuje esantys skaiciai:"<<endl;
    for(int i=0; i<savasvektorius.size(); i++){
        cout<<savasvektorius[i]<<endl;
    }
}
```
### Rezultatai
```
Assign testas su normaliu vektoriumi
Rezultatai
Vektoriaus dydis:5
Vektoriuje esantys skaiciai:
10
10
10
10
10

Assign testas su savu vektoriumi
Rezultatai
Vektoriaus dydis:5
Vektoriuje esantys skaiciai:
10
10
10
10
10
```

## Vectorklase::clear
Funkcija ištrina vektoriaus elementus, palieka nulinį konteinerį.
### Realizacija
```
void clear();
```

## Vectorklase::pop_back

Funkcija panaikina vektoriaus paskutinį elementą, taip sumažindama konteinerio dydį vienetu.
### Realizacija
```
void pop_back();
```

## Vectorklase::resize
Funkcija pakeičia konteinerio dydį į n elementų.
### Realizacija
```
void resize(size_type n, const T& v);
```
