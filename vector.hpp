#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> class Vectorklase {
    public:

    typedef T value_type;
    typedef std::allocator<T> allocator_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef typename std::allocator_traits<allocator_type>::pointer pointer;
    typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    T* allocate(size_t);
    void deallocate(T*, size_t);
    void construct(T*, const T&);
    void destroy(T*);

    Vectorklase() {create();}
    explicit Vectorklase(size_type n, const T& val=T{}) {create(n, val);}
    Vectorklase(const Vectorklase& v) {create(v.begin(), v.end());}
    Vectorklase& operator=(const Vectorklase& v);
    ~Vectorklase() {uncreate();}

    // iterator begin() {return data;}
    // const_iterator begin() const {return data;}
    // iterator end() {return avail;}
    // const_iterator end() const {return avail;}
    // iterator insert(iterator pos, const T& v);

    //member funkcijos
    allocator_type get_allocator() const {return alloc;}
    void assign(size_type n, const T& v);

    //element access
    T& at(size_type pos){
        if(pos>=0 && pos<size()){
            return data[pos];
        }
        else{
            throw std::out_of_range("Out of range");
        }
    }
    const T& at(size_type pos) const{
        if(pos>=0 && pos<size()){
            return data[pos];
        }
        else{
            throw std::out_of_range("Out of range");
        }
    }
    T& operator[](size_type i) {return data[i];}
    const T& operator[](size_type i) const {return data[i];}
    T& front() {return data[0];}
    const T& front() const {return data[0];}
    T& back() {return data[size()-1];}
    const T& back() const {return data[size()-1];}
    T* data_access() {return data;}
    const T* data_access() const {return data;}

    //iterators
    iterator begin() {return data;}
    const_iterator begin() const {return data;}
    iterator end() {return avail;}
    const_iterator end() const {return avail;}
    reverse_iterator rbegin() {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

    //capacity
    bool empty(){return begin()==end();}
    size_type size() const {return avail-data;}
    size_type max_size() const {return alloc.max_size();}
    void reserve(size_type new_cap);
    size_type capacity() const {return limit-data;}
    void shrink_to_fit();

    //modifiers
    void clear();
    void push_back(const T& v);
    void push_back(const T&& v);
    void pop_back();
    void resize(size_type n, const T& v);
    template <class... Args> void emplace_back(Args&&... args){
    alloc.construct(avail++, std::forward<Args>(args)...);
    }
    void swap(Vectorklase<T> &v);
    iterator erase(iterator pos){
        if(pos<begin() || pos>end()){
            throw std::out_of_range("Out of range");
        }
        if(pos==end()){
            return end();
        }
        alloc.destroy(pos);
        avail=uninitialized_copy(pos+1, end(), pos);
        return pos;
    }
    iterator insert(iterator pos, const T& v){
        if(pos<data||pos>end()){
            return data;
        }
        else{
            int i=std::distance(data, pos);
            if(end()==limit) grow();
            push_back(*(end()-1));
            for(size_t j=size()-1; j>i; j--){
                data[j]=data[j-1];
            }
            data[i]=v;
            return &data[v];
        }
    }

    iterator insert(iterator pos, size_type n, const T& v){
        for(size_t i=0; i<n; i++){
            pos=insert(pos, v);
        }
        return pos;
    }
    
    template <class... Args>
    iterator emplace(iterator pos, Args&&... args){
        if(pos<begin() || pos>end()){
            throw std::out_of_range("Out of range");
        }
        size_type n=1;
        if(size()+n>capacity()){
            size_type old=pos-begin();
            grow(capacity()+count, true);
            pos=old+begin();
        }
        for(iterator i=avail-1; i>=pos; i--){
            alloc.construct(i+n, *i);
        }
        avail=avail+n;
        alloc.construct(pos, std::forward<Args>(args)...);
        return pos;
    }

    //non-member funkcijos
    bool operator==(Vectorklase<T>& v){
        return this->size()==v.size()&&std::equal(this->begin(), this->end(), v.begin());
    }
    bool operator!=(Vectorklase<T>& v){
        return !(*this==v);
    }
    bool operator<(Vectorklase<T>& v){
        return std::lexicographical_compare(this->begin(), this->end(), v.begin(), v.end());
    }
    bool operator<=(Vectorklase<T>& v){
        return !(v<*this);
    }
    bool operator>(Vectorklase<T>& v){
        return v<*this;
    }
    bool operator>=(Vectorklase<T>& v){
        return !(*this<v);
    }
    private:
        iterator data;
        iterator avail;
        iterator limit;

        allocator<T> alloc;

        void create();
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);
        template <class InputIt>
        void create(InputIt, InputIt);

        void uncreate();

        void grow();
        void unchecked_append(const T&);

};


template <class T>
Vectorklase<T>& Vectorklase<T>::operator=(const Vectorklase& v){
    if(&v!=this){
        uncreate();
        create(v.begin(), v.end());
    }
    return *this;
}

template<class ForwardIt, class T>
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value);

template<class InputIt, class ForwardIt>
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first);

template <class T> void Vectorklase<T>::create(){
    data=avail=limit=nullptr;
}

template <class T> void Vectorklase<T>::create(size_type n, const T& val){
    data=alloc.allocate(n);
    limit=avail=data+n;
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vectorklase<T>::create(const_iterator i, const_iterator j){
    data=alloc.allocate(j-i);
    limit=avail=uninitialized_copy(i, j, data);
}

template <class T> void Vectorklase<T>::uncreate(){
    if(data){
        iterator it=avail;
        while(it != data){
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit-data);
    }
    data=limit=avail=nullptr;
}

template <class T> void Vectorklase<T>::grow(){
    size_type new_size = max(2*(limit-data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}

template <class T> void Vectorklase<T>::unchecked_append(const T& val){
    alloc.construct(avail++, val);
}

//member funkcijos

template <class T> void Vectorklase<T>::clear(){
    iterator i=avail;
    while(i!=data) alloc.destroy(--i);
    avail=data;
}

template <class T> void Vectorklase<T>::push_back(const T& v){
    if(avail==limit){
        grow();
    }
    unchecked_append(v);
}

template <class T> void Vectorklase<T>::pop_back(){
    iterator i=avail;
    alloc.destroy(--i);
    avail=i;
}

template <class T> void Vectorklase<T>::resize(size_type n, const T& v){
    if(size()>n){
        erase(begin()+n, end());
    }
    if(size()<n){
        size_type old_avail=end()-begin();
        if(capacity()<n){
            grow(n, true);
        }
        avail=begin()+n;
        uninitialized_fill(begin()+old_avail, avail, v);
    }
}

template <class T> void Vectorklase<T>::swap(Vectorklase<T>& v){
    std::swap(data, v.data);
    std::swap(avail, v.avail);
    std::swap(limit, v.limit);
}

template <class T> void Vectorklase<T>::assign(size_type n, const T& v){
    uncreate();
    create(n, v);
}

template <class T> void Vectorklase<T>::shrink_to_fit(){
    grow(size());
}
