#include "../../../../include/pbcpp.cpp"

using namespace pbcpp;

class App {
public:
  App() {
    // Create main Window element and assign to pointer
    _window.create();

    // Set handlers to manage the elements inside the Window
    _window.subscribe(this);

    // Show the Window on the watch, with animated=true
    _window.open();

    // Register with TickTimerService
    _tickTimer.subscribe(MINUTE_UNIT, this);
  }

  void onWindowSubscribe(PbWindow::Subscriber<App> & subscriber) {
    subscriber.load();
  }

  void onWindowLoad() {
    // Create time TextLayer
    _timeLayer.create(PbRect(0, 55, 144, 50))
      .backgroundColor(GColorClear)
      .textColor(GColorBlack)
      .text("00:00");

    // Improve the layout to be more like a watchface
    _timeLayer.font(PbFontRef::fromSystem(FONT_KEY_BITHAM_42_BOLD))
      .textAlignment(GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    _window.addChild(_timeLayer);

    // Make sure the time is displayed from the start
    updateTime();
  }

  void onTick(const PbDateTimeInfo & dateTimeInfo, TimeUnits unitsChanged) {
    updateTime();
  }

private:
  void updateTime() {
    // Get the current time
    PbDateTime now = PbDateTime::now();

    // Write the current hours and minutes into the buffer
    if (clock_is_24h_style()) {
      // Use 2h hour format
      _timeText.assignDateTimeFormat(sizeof("00:00"), "%H:%M", now.localInfo());
    } else {
      // Use 12 hour format
      _timeText.assignDateTimeFormat(sizeof("00:00"), "%I:%M", now.localInfo());
    }

    // Display this time on the TextLayer
    _timeLayer.text(_timeText.c_str());
  }

  PbTickTimer _tickTimer;
  PbWindow _window;
  PbTextLayer _timeLayer;
  PbString _timeText;
};

extern "C" int main() {
  return PbMain<App>::run();
}
