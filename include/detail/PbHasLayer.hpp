#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

template <typename TDerived> class PbHasLayer {
public:
  template <typename THasLayer> TDerived & addChild(THasLayer & layer) {
    TDerived & derived = static_cast<TDerived &>(*this);
    derived.layer().addChild(layer.layer());
    return derived;
  }
};
