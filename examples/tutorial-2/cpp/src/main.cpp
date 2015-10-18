#include "../../../include/pbcpp.cpp"

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
    // Create GBitmap, then set to created BitmapLayer
    _backgroundBitmap.createWithResource(RESOURCE_ID_IMAGE_BACKGROUND);
    _backgroundLayer.create(PbRect(0, 0, 144, 168))
      .bitmap(_backgroundBitmap);
    _window.addChild(_backgroundLayer);

    // Create time TextLayer
    _timeLayer.create(PbRect(5, 52, 139, 50))
      .backgroundColor(GColorClear)
      .textColor(GColorBlack)
      .text("00:00");

    // Create GFont
    _timeFont.load(RESOURCE_ID_FONT_PERFECT_DOS_48);

    // Apply to TextLayer
    _timeLayer.font(_timeFont)
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
  PbBitmapLayer _backgroundLayer;
  PbBitmap _backgroundBitmap;
  PbTextLayer _timeLayer;
  PbCustomFont _timeFont;
  PbString _timeText;
};

extern "C" int main() {
  return PbMain<App>::run();
}
