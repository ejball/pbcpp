#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbAppMessages : public PbNoncopyable {
public:
  template <typename T> PbAppMessages & subscribe(T * handlers) {
    Subscriber<T> subscriber;
    if (handlers) {
      handlers->onAppMessagesSubscribe(subscriber);
    }
    app_message_set_context(handlers);
    app_message_register_inbox_received(subscriber._inboxReceived);
    app_message_register_inbox_dropped(subscriber._inboxDropped);
    app_message_register_outbox_sent(subscriber._outboxSent);
    app_message_register_outbox_failed(subscriber._outboxFailed);
    return *this;
  }

  PbAppMessages & open() {
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
    return *this;
  }

  PbDictionaryIteratorRef beginOutbox() {
    AppMessageResult result;
    return beginOutbox(result);
  }

  PbDictionaryIteratorRef beginOutbox(AppMessageResult & result) {
    DictionaryIterator * iterator;
    result = app_message_outbox_begin(&iterator);
    return PbDictionaryIteratorRef(iterator);
  }

  AppMessageResult sendOutbox() {
    return app_message_outbox_send();
  }

  template <typename T> class Subscriber : public PbNoncopyable {
  public:
    Subscriber() {
      _inboxReceived = nullptr;
      _inboxDropped = nullptr;
      _outboxSent = nullptr;
      _outboxFailed = nullptr;
    }

    Subscriber<T> & inboxReceived() {
      _inboxReceived = &handleInboxReceived;
      return *this;
    }

    Subscriber<T> & inboxDropped() {
      _inboxDropped = &handleInboxDropped;
      return *this;
    }

    Subscriber<T> & outboxSent() {
      _outboxSent = &handleOutboxSent;
      return *this;
    }

    Subscriber<T> & outboxFailed() {
      _outboxFailed = &handleOutboxFailed;
      return *this;
    }

  private:
    static void handleInboxReceived(DictionaryIterator * iterator, void * context) {
      reinterpret_cast<T *>(context)->onInboxReceived(PbDictionaryIteratorRef(iterator));
    }

    static void handleInboxDropped(AppMessageResult reason, void * context) {
      reinterpret_cast<T *>(context)->onInboxDropped(reason);
    }

    static void handleOutboxSent(DictionaryIterator * iterator, void * context) {
      reinterpret_cast<T *>(context)->onOutboxSent(PbDictionaryIteratorRef(iterator));
    }

    static void handleOutboxFailed(DictionaryIterator * iterator, AppMessageResult reason, void * context) {
      reinterpret_cast<T *>(context)->onOutboxFailed(PbDictionaryIteratorRef(iterator), reason);
    }

    friend PbAppMessages;
    AppMessageInboxReceived _inboxReceived;
    AppMessageInboxDropped _inboxDropped;
    AppMessageOutboxSent _outboxSent;
    AppMessageOutboxFailed _outboxFailed;
  };
};
