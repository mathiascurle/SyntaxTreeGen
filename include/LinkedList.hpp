#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/*
* Generic single linked list with first and last in, and first out
* Get and remove at index
* Set and put at index
* print function and operator<< overload
* Copy constructor and copy assignment operator
* Needs T type to have <<operator, will crash otherwise
*/

template <typename T> class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  void push_back(T x);
  void push_front(T x);
  void put(int idx, T x);
  void set(int idx, T x);

  T get(int idx);
  T pop();
  T remove(int idx);

  int size();
  void print();

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os,
                                  const LinkedList<U> &list); // << operator
  LinkedList(const LinkedList<T> &other);               // Copy constructor
  LinkedList<T> &operator=(const LinkedList<T> &other); // Copy assignment

private:
  void first_push(T x);

private:
  typedef struct Node {
    T data;
    Node *next;
  } Node;

  int m_iSize;

  Node *m_first;
  Node *m_last;
};

template <typename T> LinkedList<T>::LinkedList() {
  m_first = NULL;
  m_last = NULL;
  m_iSize = 0;
}

template <typename T> LinkedList<T>::~LinkedList() {
  Node *temp = m_first;
  Node *nxt = temp;
  while (temp != NULL) {
    nxt = temp->next;
    delete temp;
    temp = nxt;
  }
}

template <typename T> void LinkedList<T>::push_back(T x) {
  if (!m_last) {
    first_push(x);
  } else {
    Node *newNode = new Node;
    newNode->data = x;
    newNode->next = NULL;
    m_last->next = newNode;
    m_last = newNode;
  }
  m_iSize++;
}

template <typename T> void LinkedList<T>::push_front(T x) {
  if (!m_first) {
    first_push(x);
  } else {
    Node *newNode = new Node;
    newNode->data = x;
    newNode->next = m_first;
    m_first = newNode;
  }
  m_iSize++;
}

template <typename T> void LinkedList<T>::put(int idx, T x) {
  if (idx > m_iSize || idx < 0) {
    throw std::out_of_range("Index " + std::to_string(idx) +
                            " out of bounds in put()");
  }
  if (m_iSize == 0) {
    first_push(x);
  } else {
    if (idx == 0) {
      push_front(x);
    } else if (idx == m_iSize) {
      push_back(x);
    } else {
      Node *newNode = new Node;
      newNode->data = x;
      Node *temp = m_first;
      for (int i = 1; i < idx; i++) {
        temp = temp->next;
      }
      newNode->next = temp->next;
      temp->next = newNode;
    }
  }
  m_iSize++;
}

template <typename T> void LinkedList<T>::set(int idx, T x) {
  if (idx >= m_iSize || idx < 0) {
    throw std::out_of_range("Index " + std::to_string(idx) +
                            " out of bounds in set()");
  } else {
    Node *temp = m_first;
    for (int i = 0; i < idx; i++) {
      temp = temp->next;
    }
    temp->data = x;
  }
}

template <typename T> T LinkedList<T>::get(int idx) {
  if (idx >= m_iSize || idx < 0) {
    throw std::out_of_range("Index " + std::to_string(idx) +
                            " out of bounds in get()");
  } else {
    Node *temp = m_first;
    for (int i = 0; i < idx; i++) {
      temp = temp->next;
    }
    return temp->data;
  }
}

template <typename T> T LinkedList<T>::pop() {
  if (m_iSize == 0) {
    throw std::underflow_error("Cannot pop from an empty list");
  }
  T returnValue = m_first->data;
  if (m_iSize > 1) {
    Node *temp = m_first->next;
    delete m_first;
    m_first = temp;
  } else if (m_iSize == 1) {
    delete m_first;
    delete m_last;
    m_first = NULL;
    m_last = NULL;
  }
  m_iSize--;
  return returnValue;
}

template <typename T> T LinkedList<T>::remove(int idx) {
  if (idx >= m_iSize || idx < 0) {
    throw std::out_of_range("Index " + std::to_string(idx) +
                            " out of bounds in remove()");
  } else {
    if (idx == 0) {
      m_iSize--;
      return pop();
    } else {
      Node *temp = m_first;
      Node *prev = m_first;
      for (int i = 0; i < idx; i++) {
        prev = temp;
        temp = temp->next;
      }
      T returnValue = temp->data;
      prev->next = temp->next;
      delete temp;
      m_iSize--;
      return returnValue;
    }
  }
}

template <typename T> void LinkedList<T>::print() {
  std::stringstream ss;
  ss << "[";
  Node *temp = m_first;
  while (temp != m_last) {
    ss << temp->data << ", ";
    temp = temp->next;
  }
  ss << m_last->data << "]";
  std::string out = ss.str();
  std::cout << out << std::endl;
}

template <typename T> int LinkedList<T>::size() { return m_iSize; }

template <typename T> void LinkedList<T>::first_push(T x) {
  m_first = new Node;
  m_first->data = x;
  m_first->next = NULL;
  m_last = m_first;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list) {
  typename LinkedList<T>::Node *temp = list.m_first;
  os << "[";
  while (temp != list.m_last) {
    os << temp->data << ", ";
    temp = temp->next;
  }
  os << list.m_last->data << "]";
  return os;
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other)
    : m_first(nullptr), m_last(nullptr), m_iSize(0) {
  Node *temp = other.m_first;
  while (temp != nullptr) {
    push_back(temp->data);
    temp = temp->next;
  }
}

// Copy assignment operator
template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
  if (this != &other) {
    // Clean up existing list
    while (m_first != nullptr) {
      Node *next = m_first->next;
      delete m_first;
      m_first = next;
    }
    m_last = nullptr;
    m_iSize = 0;
    // Deep copy
    Node *current = other.m_first;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }
  return *this;
}
