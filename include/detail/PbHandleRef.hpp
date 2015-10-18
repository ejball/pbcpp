#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

template <typename T> class PbHandleRef {
public:
  PbHandleRef()
    : _handle(nullptr) {
  }

  explicit PbHandleRef(T handle)
    : _handle(handle) {
  }

  T handle() {
    return _handle;
  }

  bool operator==(PbHandleRef<T> other) const {
    return _handle == other._handle;
  }

  bool operator!=(PbHandleRef<T> other) const {
    return _handle != other._handle;
  }

protected:
  T _handle;
};
