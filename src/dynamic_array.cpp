#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity_]{}; //инициализация нулями
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;

    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (size_ < capacity_) {
        data_[size_] = value;
        size_ += 1;
    } else if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
      data_[size_] = value;
      size_ += 1;
    }
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < 0 or index > size_) {
      return false;
    }
    if (size_ >= capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    for (int i = size_ - 1; i >= index; i--) {
      data_[i + 1] = data_[i];
    }
    data_[index] = value;
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= 0 and index < size_) {
      data_[index] = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index >= 0 and index < size_) {
      int value_index = data_[index];
      for (int i = index + 1; i < size_; i++) {
        data_[i - 1] = data_[i];
      }
      size_ -= 1;
      return value_index;
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if(index >= 0 and index < size_) {
      return data_[index];
    }

    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {

    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return i;
      }
    }

    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity > capacity_) {
      int* datanew = new int[new_capacity];
      for (int i = 0; i < capacity_; i++)
        datanew[i] = data_[i];
      capacity_ = new_capacity;
      data_ = datanew;
      return true;
    }
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment