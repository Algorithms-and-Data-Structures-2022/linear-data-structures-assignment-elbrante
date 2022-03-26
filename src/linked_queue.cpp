#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {
    if (size() == 0) {
      Node* node = new Node(value, nullptr);
      front_ = node;
      back_ = node;
    } else {
      Node* node = new Node(value, nullptr);
      (*back_).next = node;
      back_ = node;
    }
    size_++;
  }

  bool LinkedQueue::Dequeue() {
    if (!IsEmpty()) {
      Node* node = (*front_).next;
      delete front_;
      size_--;
      front_ = node;
      return true;
    }
    return false;
  }

  void LinkedQueue::Clear() {
    if (size() == 0) {
      return;
    }
    Node* node = (*front_).next;
    delete front_;
    front_ = nullptr;
    back_ = nullptr;
    for (int i = 1; i < size(); i++) {
      Node* node1 = node->next;
      delete node;
      node = node1;
    }
    size_ = 0;
  }

  std::optional<int> LinkedQueue::front() const {
    if (!IsEmpty()) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedQueue::back() const {
    if (!IsEmpty()) {
      return back_->value;
    }
    return std::nullopt;
  }

  bool LinkedQueue::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedQueue::size() const {
    return size_;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedQueue::LinkedQueue(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedQueue::toVector() const {
    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment