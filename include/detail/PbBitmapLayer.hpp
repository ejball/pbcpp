#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbBitmapLayer : public PbHasLayer<PbBitmapLayer>, public PbNoncopyable {
public:
  PbBitmapLayer()
    : _handle(nullptr) {
  }

  PbBitmapLayer & create(GRect frame) {
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

  PbBitmapLayer & alignment(GAlign alignment) {
    bitmap_layer_set_alignment(_handle, alignment);
    return *this;
  }

  PbBitmapLayer & backgroundColor(GColor color) {
    bitmap_layer_set_background_color(_handle, color);
    return *this;
  }

  PbBitmapLayer & bitmap(PbBitmap & bitmap) {
    bitmap_layer_set_bitmap(_handle, bitmap.handle());
    return *this;
  }

  PbBitmapLayer & compositingMode(GCompOp mode) {
    bitmap_layer_set_compositing_mode(_handle, mode);
    return *this;
  }

  BitmapLayer * handle() {
    return _handle;
  }

  PbLayerRef layer() {
    return PbLayerRef(bitmap_layer_get_layer(_handle));
  }

  ~PbBitmapLayer() {
    destroy();
  }

private:
  BitmapLayer * _handle;
};
