#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbTupleRef : public PbHandleRef<Tuple *> {
public:
  PbTupleRef() {}

  explicit PbTupleRef(Tuple * handle)
    : PbHandleRef(handle) {}

  uint32_t key() const {
    return _handle->key;
  }

  TupleType type() const {
    return _handle->type;
  }

  uint16_t length() const {
    return _handle->length;
  }

  const uint8_t * data() const {
    return _handle->value->data;
  }

  const char * c_str() const {
    return _handle->value->cstring;
  }

  uint8_t uint8() const {
    return _handle->value->uint8;
  }

  uint16_t uint16() const {
    return _handle->value->uint16;
  }

  uint32_t uint32() const {
    return _handle->value->uint32;
  }

  int8_t int8() const {
    return _handle->value->int8;
  }

  int16_t int16() const {
    return _handle->value->int16;
  }

  int32_t int32() const {
    return _handle->value->int32;
  }
};
