#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbFontRef : public PbHandleRef<GFont> {
public:
  PbFontRef() {}

  PbFontRef(GFont handle)
    : PbHandleRef(handle) {}

  static PbFontRef fromSystem(const char * fontKey) {
    return PbFontRef(fonts_get_system_font(fontKey));
  }
};
