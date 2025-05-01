// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };

  Node* head;
  Node* tail;
  size_t size;

 public:
  TPQueue() : head(nullptr), tail(nullptr), size(0) {}

  ~TPQueue() { clear(); }

  void push(const T& item) {
    Node* newNode = new Node(item);

    // Если очередь пуста или новый элемент имеет высший приоритет
    if (!head || item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      if (!tail) tail = head;
    } else {
      // Ищем место для вставки
      Node* current = head;
      while (current->next && current->next->data.prior >= item.prior) {
        current = current->next;
      }

      newNode->next = current->next;
      current->next = newNode;

      // Обновляем tail если вставили в конец
      if (!newNode->next) {
        tail = newNode;
      }
    }
    size++;
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }

    Node* temp = head;
    T item = head->data;
    head = head->next;

    if (!head) {
      tail = nullptr;
    }

    delete temp;
    size--;
    return item;
  }

  const T& front() const {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    return head->data;
  }

  const T& back() const {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    return tail->data;
  }

  bool isEmpty() const { return head == nullptr; }

  size_t getSize() const { return size; }

  void clear() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    size = 0;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
