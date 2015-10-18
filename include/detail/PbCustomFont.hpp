#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbCustomFont : public PbFontRef, public PbNoncopyable {
public:
  PbCustomFont() {}

  PbCustomFont & load(uint32_t resourceId) {
    unload();
    _handle = fonts_load_custom_font(resource_get_handle(resourceId));
    return *this;
  }

  void unload() {
    if (_handle) {
      fonts_unload_custom_font(_handle);
      _handle = nullptr;
    }
  }

  ~PbCustomFont() {
    unload();
  }
};
