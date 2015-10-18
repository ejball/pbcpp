#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbTickTimer : public PbNoncopyable {
public:
  template <typename T> void subscribe(TimeUnits tickUnits, T * handler) {
    if (handler) {
      void ** ptr = handlerPtr();
      PB_ASSERT(*ptr == nullptr);
      *ptr = handler;
      tick_timer_service_subscribe(tickUnits, &handleTickTimer<T>);
    } else {
      unsubscribe();
    }
  }

  void unsubscribe() {
    void ** ptr = handlerPtr();
    if (*ptr) {
      tick_timer_service_unsubscribe();
      *ptr = nullptr;
    }
  }

  ~PbTickTimer() {
    unsubscribe();
  }

private:
  template <typename T> static void handleTickTimer(struct tm * tick_time, TimeUnits units_changed) {
    reinterpret_cast<T *>(*handlerPtr())->onTick(*reinterpret_cast<const PbDateTimeInfo *>(tick_time), units_changed);
  }

  static void ** handlerPtr() {
    static void * handler = nullptr;
    return &handler;
  }
};
