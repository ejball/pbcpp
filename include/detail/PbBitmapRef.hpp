#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbBitmapRef : public PbHandleRef<GBitmap *> {
public:
  PbBitmapRef() {}

  explicit PbBitmapRef(GBitmap * handle)
    : PbHandleRef(handle) {}
};
