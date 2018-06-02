#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

template<typename T> class vector {
  private:
    T* arr;
    int curr_size;
    void initArray (int);
  public:
    vector(int);
    vector();
    ~vector();

    void push_back(T);
    void erase(int);
    int size();

    T& operator[](int);
};

template<typename T> void vector<T>::initArray(int size) {
  arr = new T[size];
}

template<typename T> vector<T>::vector(int size) {
  curr_size = size;
  initArray(size);
}

template<typename T> vector<T>::vector() {
  curr_size = 0;
  initArray(0);
}

template<typename T> vector<T>::~vector() {
  delete[] arr;
}

template<typename T> void vector<T>::push_back(T value) {
  T* tmp = new T[curr_size+1];

  for(int i=0; i<curr_size; i++) tmp[i] = arr[i];
  tmp[curr_size] = value;

  delete[] arr;
  arr = tmp;
  curr_size++;
}

template<typename T> void vector<T>::erase(int n) {
  if(n > curr_size) return;

  T* tmp = new T[curr_size];
  for(int i=0; i<curr_size; i++) tmp[i] = i < n ? arr[i] : arr[i+1];

  arr = tmp;

  curr_size--;
}

template<typename T> T& vector<T>::operator[](int i) {
  return arr[i];
}

template<typename T> int vector<T>::size() {
  return curr_size;
}

#endif