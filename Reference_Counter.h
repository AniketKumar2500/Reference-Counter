#if !defined(Reference_Counter_H)
#define Reference_Counter_H
template <typename T>
class SmartPointer {
 public:
  SmartPointer(T* ptr) : ptr_(ptr), ref_count_(new int(1)) {}

  SmartPointer(const SmartPointer<T>& other) :
      ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++(*ref_count_);
  }

  SmartPointer<T>& operator=(const SmartPointer<T>& other) {
    if (this != &other) {
      if (--(*ref_count_) == 0) {
        delete ptr_;
        delete ref_count_;
      }
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++(*ref_count_);
    }
    return *this;
  }

  ~SmartPointer() {
    if (--(*ref_count_) == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }

 private:
  T* ptr_;
  int* ref_count_;
};

#endif // Refrence_Counter_H
