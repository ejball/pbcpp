#include "../../../include/pbcpp.cpp"

using namespace pbcpp;

class App {
public:
  App() {
    // Create main Window
    _window.create()
      .subscribe(this)
      .clickConfig(this)
      .open();
  }

  void onWindowSubscribe(PbWindow::Subscriber<App> & subscriber) {
    subscriber.load();
  }

  void onClickConfig(PbWindow::ClickConfig<App> & config) {
    config.singleClickUp().singleClickSelect().singleClickDown();
  }

  void onSingleClickUp(PbClickRecognizerRef recognizer) {
    _textLayer.text("Up pressed!");
  }

  void onSingleClickSelect(PbClickRecognizerRef recognizer) {
    _textLayer.text("Select pressed!");
  }

  void onSingleClickDown(PbClickRecognizerRef recognizer) {
    _textLayer.text("Down pressed!");
  }

  void onWindowLoad() {
    PbRect windowBounds = _window.layer().bounds();

    // Create output TextLayer
    _textLayer.create(PbRect(5, 0, windowBounds.width() - 5, windowBounds.height()))
      .font(PbFontRef::fromSystem(FONT_KEY_GOTHIC_24))
      .text("No button pressed yet.")
      .overflowMode(GTextOverflowModeWordWrap);
    _window.addChild(_textLayer);
  }

private:
  PbWindow _window;
  PbTextLayer _textLayer;
};

extern "C" int main() {
  return PbMain<App>::run();
}
