#include "../../../include/pbcpp.cpp"

using namespace pbcpp;

class App {
public:
  App() {
    _textLayer.create(PbRect(0, 0, 144, 40))
      .text("Hello, Pebble!");
    _window.create()
      .addChild(_textLayer)
      .open();
  }
private:
  PbWindow _window;
  PbTextLayer _textLayer;
};

extern "C" int main() {
  return PbMain<App>::run();
}
