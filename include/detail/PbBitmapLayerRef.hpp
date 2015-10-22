#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbBitmapLayerRef : public PbHandleRef<BitmapLayer *>, public PbHasLayer<PbBitmapLayerRef> {
public:
  PbBitmapLayerRef() {}

  explicit PbBitmapLayerRef(BitmapLayer * handle)
    : PbHandleRef(handle) {}

  PbBitmapLayerRef & alignment(GAlign alignment) {
    bitmap_layer_set_alignment(_handle, alignment);
    return *this;
  }

  PbBitmapLayerRef & backgroundColor(GColor color) {
    bitmap_layer_set_background_color(_handle, color);
    return *this;
  }

  PbBitmapLayerRef & bitmap(PbBitmapRef bitmap) {
    bitmap_layer_set_bitmap(_handle, bitmap.handle());
    return *this;
  }

  PbBitmapLayerRef & compositingMode(GCompOp mode) {
    bitmap_layer_set_compositing_mode(_handle, mode);
    return *this;
  }

  PbLayerRef layer() {
    return PbLayerRef(bitmap_layer_get_layer(_handle));
  }
};
