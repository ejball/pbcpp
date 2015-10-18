#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbWindowRef : public PbHandleRef<Window *>, public PbHasLayer<PbWindowRef> {
public:
  PbWindowRef() {}

  explicit PbWindowRef(Window * handle)
    : PbHandleRef(handle) {}

  PbWindowRef & open() {
    window_stack_push(_handle, true);
    return *this;
  }

  PbLayerRef layer() {
    return PbLayerRef(window_get_root_layer(_handle));
  }

  PbWindowRef & backgroundColor(GColor color) {
    window_set_background_color(_handle, color);
    return *this;
  }

  template <typename T> PbWindowRef & subscribe(T * handlers) {
    Subscriber<T> subscriber;
    if (handlers) {
      handlers->onWindowSubscribe(subscriber);
    }
    window_set_user_data(_handle, handlers);
    window_set_window_handlers(_handle, subscriber._windowHandlers);
    return *this;
  }

  template <typename T> PbWindowRef & clickConfig(T * handlers) {
    window_set_click_config_provider_with_context(_handle, &provideClickConfig<T>, handlers);
    return *this;
  }

  template <typename T> class Subscriber : public PbNoncopyable {
  public:
    Subscriber() {
      _windowHandlers.load = nullptr;
      _windowHandlers.unload = nullptr;
      _windowHandlers.appear = nullptr;
      _windowHandlers.disappear = nullptr;
    }

    Subscriber<T> & load() {
      _windowHandlers.load = &handleLoad;
      return *this;
    }

    Subscriber<T> & unload() {
      _windowHandlers.unload = &handleUnload;
      return *this;
    }

    Subscriber<T> & appear() {
      _windowHandlers.appear = &handleAppear;
      return *this;
    }

    Subscriber<T> & disappear() {
      _windowHandlers.disappear = &handleDisappear;
      return *this;
    }

  private:
    static void handleLoad(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowLoad();
    }

    static void handleUnload(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowUnload();
    }

    static void handleAppear(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowAppear();
    }

    static void handleDisappear(Window * window) {
      reinterpret_cast<T *>(window_get_user_data(window))->onWindowDisappear();
    }

    friend PbWindowRef;
    WindowHandlers _windowHandlers;
  };

  template <typename T> class ClickConfig : public PbNoncopyable {
  public:
    ClickConfig() {}

    ClickConfig<T> & singleClickUp() {
      window_single_click_subscribe(BUTTON_ID_UP, &handleSingleClickUp);
      return *this;
    }

    ClickConfig<T> & singleClickDown() {
      window_single_click_subscribe(BUTTON_ID_DOWN, &handleSingleClickDown);
      return *this;
    }

    ClickConfig<T> & singleClickSelect() {
      window_single_click_subscribe(BUTTON_ID_SELECT, &handleSingleClickSelect);
      return *this;
    }

    ClickConfig<T> & singleClickBack() {
      window_single_click_subscribe(BUTTON_ID_BACK, &handleSingleClickBack);
      return *this;
    }

  private:
    static void handleSingleClickUp(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickUp(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickDown(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickDown(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickSelect(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickSelect(PbClickRecognizerRef(recognizer));
    }

    static void handleSingleClickBack(ClickRecognizerRef recognizer, void * context) {
      reinterpret_cast<T *>(context)->onSingleClickBack(PbClickRecognizerRef(recognizer));
    }
  };

private:
  template <typename T> static void provideClickConfig(void * context) {
    ClickConfig<T> config;
    reinterpret_cast<T *>(context)->onClickConfig(config);
  }
};
