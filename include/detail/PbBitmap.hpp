#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbBitmap : public PbBitmapRef, public PbNoncopyable {
public:
  PbBitmap() {}

  PbBitmap & createWithResource(uint32_t resourceId) {
    destroy();
    _handle = gbitmap_create_with_resource(resourceId);
    PB_ASSERT(_handle != nullptr);
    return *this;
  }

  void destroy() {
    if (_handle) {
      gbitmap_destroy(_handle);
      _handle = nullptr;
    }
  }

  ~PbBitmap() {
    destroy();
  }
};
