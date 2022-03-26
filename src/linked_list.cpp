#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    size_ = 0;
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
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

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 or index > size()) {
      return false;
    }
    if (index == 0) {
      front_ = new Node(value, front_);
      if (IsEmpty()) {
        back_ = front_;
      }
      size_++;
      return true;
    }
    if (index == size()) {
      Add(value);
      return true;
    }
    Node* node = FindNode(index - 1);
    Node* newNode = new Node(value, node->next);
    (*node).next = newNode;
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    Node* node = FindNode(index);
    if (node != nullptr) {
      (*node).value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 or index >= size()) {
      return std::nullopt;
    }
    if (index == 0) {
      Node* node = front_->next;
      int value = front_->value;
      delete front_;
      front_ = node;
      size_--;
      return value;
    }
    Node* previousNode = FindNode(index - 1);
    Node* node = previousNode->next;
    (*previousNode).next = node->next;
    int val;
    val = node->value;
    delete node;
    node = nullptr;
    if (index == size() - 1) {
      back_ = previousNode;
    }
    size_--;
    return val;
  }

  void LinkedList::Clear() {
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

  std::optional<int> LinkedList::Get(int index) const {
    Node* node = FindNode(index);
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    int i{0};
    while (i < size()) {
      if (node->value == value) {
        return i;
      }
      node = node->next;
      i++;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return IndexOf(value).has_value();
  }

  bool LinkedList::IsEmpty() const {
    return size() == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return (*front_).value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return (*back_).value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size()) {
      return nullptr;
    }
    Node* node{front_};
    for (int i = 0; i < size(); i++) {
      if (i == index) {
        return node;
      }
      node = node->next;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

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

  std::vector<int> LinkedList::toVector() const {

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