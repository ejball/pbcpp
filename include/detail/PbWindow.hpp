#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbWindow : public PbWindowRef, public PbNoncopyable {
public:
  PbWindow() {}

  PbWindow & create() {
    destroy();
    _handle = window_create();
#ifdef PBL_PLATFORM_APLITE
    window_set_fullscreen(_handle, true);
#endif
    return *this;
  }

  void destroy() {
    if (_handle) {
      window_destroy(_handle);
      _handle = nullptr;
    }
  }

  ~PbWindow() {
    destroy();
  }
};
