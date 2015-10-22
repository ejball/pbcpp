#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

struct PbRect : public GRect {
public:
  PbRect() {
    memset(this, 0, sizeof(PbRect));
  }

  explicit PbRect(const GRect & rect) {
    memcpy(this, &rect, sizeof(GRect));
  }

  PbRect(int16_t x, int16_t y, int16_t w, int16_t h) {
    origin.x = x;
    origin.y = y;
    size.w = w;
    size.h = h;
  }

  int16_t left() const {
    return origin.x;
  }

  PbRect & left(int16_t value) {
    origin.x = value;
    return *this;
  }

  int16_t top() const {
    return origin.y;
  }

  PbRect & top(int16_t value) {
    origin.y = value;
    return *this;
  }

  int16_t width() const {
    return size.w;
  }

  PbRect & width(int16_t value) {
    size.w = value;
    return *this;
  }

  int16_t height() const {
    return size.h;
  }

  PbRect & height(int16_t value) {
    size.h = value;
    return *this;
  }
};
