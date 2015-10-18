#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

template <typename TApp> class PbMain {
public:
  static int run() {
    _app = new TApp();
    app_event_loop();
    delete _app;
    return 0;
  }

  static TApp & app() {
    return *_app;
  }

  PbMain() = delete;

private:
  static TApp * _app;
};

template <typename TApp> TApp * PbMain<TApp>::_app;
