#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbTextLayerRef : public PbHandleRef<TextLayer *>, public PbHasLayer<PbTextLayerRef> {
public:
  PbTextLayerRef() {}

  explicit PbTextLayerRef(TextLayer * handle)
    : PbHandleRef(handle) {}

  GSize contentSize() {
    return text_layer_get_content_size(_handle);
  }

  PbTextLayerRef & backgroundColor(GColor color) {
    text_layer_set_background_color(_handle, color);
    return *this;
  }

  PbTextLayerRef & font(PbFontRef font) {
    text_layer_set_font(_handle, font.handle());
    return *this;
  }

  PbTextLayerRef & overflowMode(GTextOverflowMode line_mode) {
    text_layer_set_overflow_mode(_handle, line_mode);
    return *this;
  }

  PbTextLayerRef & size(const GSize max_size) {
    text_layer_set_size(_handle, max_size);
    return *this;
  }

  PbTextLayerRef & text(const char * text) {
    text_layer_set_text(_handle, text);
    return *this;
  }

  PbTextLayerRef & textAlignment(GTextAlignment alignment) {
    text_layer_set_text_alignment(_handle, alignment);
    return *this;
  }

  PbTextLayerRef & textColor(GColor color) {
    text_layer_set_text_color(_handle, color);
    return *this;
  }

  PbLayerRef layer() {
    return PbLayerRef(text_layer_get_layer(_handle));
  }
};
