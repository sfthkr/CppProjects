#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <iostream>

class queue_error: std::runtime_error{
public:
  using std::runtime_error::runtime_error;
};

template<typename T, unsigned int N>
class Queue {

public:
    static_assert(N > 0, "Queue must have space for at least 1 value");

    void enqueue(T value);
    T dequeue();
    bool empty() const;
    bool full() const;
    void clear();
    T& front();
    const T& front() const;

    template<unsigned int M>
    Queue<T, N+M> copy_and_expand() const;

    unsigned int size() const {
        return count;
    }

    template<typename U, unsigned int M>
    friend class Queue;

private:
    T data[N]{};
    unsigned int head{0};
    unsigned int tail{0};
    unsigned int count{0};
};

template<typename T, unsigned int N>
void Queue<T, N>::enqueue(T value){

    if(!this->full()){
        data[tail] = value;
        tail = (tail+1)%N;
        count++;
    }
    else{
        throw queue_error{"Cannot enqueue into full queue"};
    }
}

template<typename T, unsigned int N>
T Queue<T, N>::dequeue(){

    if(!this->empty()){
        T ret_data {std::move(data[head])};
        head = (head+1)%N;
        count--;
        return ret_data;
    }
    else{
        throw queue_error{"Cannot dequeue from empty queue"};
    }    

}

template<typename T, unsigned int N>
bool Queue<T, N>::empty() const{

    return count <= 0;
}

template<typename T, unsigned int N>
bool Queue<T, N>::full() const{

    return count >= N;
}

template<typename T, unsigned int N>
void Queue<T, N>::clear(){

    head = tail = count = 0;
}

template <typename T, unsigned N>
T& Queue<T, N>::front()
{
    //return const_cast<T&>(static_cast<Queue<T, N> const*>(this)->front());  
    if(!this->empty()){
        return data[head];
    }
    else{
        throw queue_error{"Cannot front from empty queue"};
    }  
}

template<typename T, unsigned int N>
const T& Queue<T, N>::front() const{

    if(!this->empty()){
        return data[head];
    }
    else{
        throw queue_error{"Cannot front from empty queue"};
    }  
}

template<typename T, unsigned int N>
template<unsigned int M>
Queue<T, N+M> Queue<T, N>::copy_and_expand() const {

    Queue<T, N+M> new_static_queue;
    for(int i = 0; i < this->size(); ++i){
        new_static_queue.data[i] = this->data[(head+i)%N];
    }
    new_static_queue.tail = this->size();
    new_static_queue.count = this->size();
    return new_static_queue;
}