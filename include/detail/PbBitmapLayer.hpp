#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbBitmapLayer : public PbBitmapLayerRef, public PbNoncopyable {
public:
  PbBitmapLayer() {}

  PbBitmapLayer & create(const GRect & frame) {
    destroy();
    _handle = bitmap_layer_create(frame);
    return *this;
  }

  void destroy() {
    if (_handle) {
      bitmap_layer_destroy(_handle);
      _handle = nullptr;
    }
  }

  ~PbBitmapLayer() {
    destroy();
  }
};
