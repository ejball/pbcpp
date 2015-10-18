#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbClickRecognizerRef : public PbHandleRef<ClickRecognizerRef> {
public:
  PbClickRecognizerRef() {}

  explicit PbClickRecognizerRef(ClickRecognizerRef handle)
    : PbHandleRef(handle) {}
};
