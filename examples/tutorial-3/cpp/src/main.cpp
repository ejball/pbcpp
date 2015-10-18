#include "../../../include/pbcpp.cpp"

using namespace pbcpp;

static const uint32_t KEY_TEMPERATURE = 0;
static const uint32_t KEY_CONDITIONS = 1;

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

    // Register callbacks
    _appMessages.subscribe(this);

    // Open AppMessage
    _appMessages.open();
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

    // Create temperature Layer
    _weatherLayer.create(PbRect(0, 130, 144, 25))
      .backgroundColor(GColorClear)
      .textColor(GColorWhite)
      .textAlignment(GTextAlignmentCenter)
      .text("Loading...");

    // Create second custom font, apply it and add to Window
    _weatherFont.load(RESOURCE_ID_FONT_PERFECT_DOS_20);
    _weatherLayer.font(_weatherFont);
    _window.addChild(_weatherLayer);

    // Make sure the time is displayed from the start
    updateTime();
  }

  void onAppMessagesSubscribe(PbAppMessages::Subscriber<App> & subscriber) {
    subscriber.inboxReceived().inboxDropped().outboxSent().outboxFailed();
  }

  void onInboxReceived(PbDictionaryIteratorRef iterator) {
    // Store incoming information
    PbString temperature;
    PbString conditions;

    // For all items
    for (auto t : PbDictionaryReader(iterator)) {
      // Which key was received?
      switch (t.key()) {
      case KEY_TEMPERATURE:
        temperature.assignFormat("%dC", static_cast<int>(t.int32()));
        break;
      case KEY_CONDITIONS:
        conditions.assign(t.c_str());
        break;
      default:
        PB_LOG_ERROR("Key %d not recognized!", static_cast<int>(t.key()));
        break;
      }
    }

    // Assemble full string and display
    _weatherText.assignFormat("%s, %s", temperature.c_str(), conditions.c_str());
    _weatherLayer.text(_weatherText.c_str());
  }

  void onInboxDropped(AppMessageResult reason) {
    PB_LOG_ERROR("Message dropped!");
  }

  void onOutboxFailed(PbDictionaryIteratorRef iterator, AppMessageResult reason) {
    PB_LOG_ERROR("Outbox send failed!");
  }

  void onOutboxSent(PbDictionaryIteratorRef iterator) {
    PB_LOG_ERROR("Outbox send success!");
  }

  void onTick(const PbDateTimeInfo & dateTimeInfo, TimeUnits unitsChanged) {
    updateTime();

    // Get weather update every 30 minutes
    if (dateTimeInfo.minute() % 30 == 0) {
      // Begin dictionary
      auto iter = _appMessages.beginOutbox();

      // Add a key-value pair
      iter.writeUInt8(0, 0);

      // Send the message!
      _appMessages.sendOutbox();
    }
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

  PbAppMessages _appMessages;
  PbTickTimer _tickTimer;
  PbWindow _window;
  PbBitmapLayer _backgroundLayer;
  PbBitmap _backgroundBitmap;
  PbTextLayer _timeLayer;
  PbCustomFont _timeFont;
  PbString _timeText;
  PbTextLayer _weatherLayer;
  PbCustomFont _weatherFont;
  PbString _weatherText;
};

extern "C" int main() {
  return PbMain<App>::run();
}
