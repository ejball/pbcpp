#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbTextLayer : public PbTextLayerRef, public PbNoncopyable {
public:
  PbTextLayer() {}

  PbTextLayer & create(const PbRect & frame) {
    destroy();
    _handle = text_layer_create(frame);
    return *this;
  }

  void destroy() {
    if (_handle) {
      text_layer_destroy(_handle);
      _handle = nullptr;
    }
  }

  ~PbTextLayer() {
    destroy();
  }
};
