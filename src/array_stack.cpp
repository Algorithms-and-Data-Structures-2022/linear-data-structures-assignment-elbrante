#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity];
    for (int i = 0; i < capacity; i++) {
      data_[i] = 0;
    }
  }

  ArrayStack::~ArrayStack() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  void ArrayStack::Push(int value) {
    if (size() == capacity()) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_++] = value;
  }

  bool ArrayStack::Pop() {
    if (IsEmpty()) {
      return false;
    }
    size_--;
    return true;
  }

  void ArrayStack::Clear() {
    size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {
    if (!IsEmpty()) {
      return data_[size_ - 1];
    }
    return std::nullopt;
  }

  bool ArrayStack::IsEmpty() const {
    return size_ == 0;
  }

  int ArrayStack::size() const {
    return size_;
  }

  int ArrayStack::capacity() const {
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    if (new_capacity <= capacity_) {
      return false;
    }

    int* newData = new int[new_capacity];
    for (int i = 0; i < size_; i++) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    newData = nullptr;
    capacity_ = new_capacity;

    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
