#pragma once

#ifndef PBCPP_HPP
#define PBCPP_HPP

extern "C" {
#define _NEWLIB_ALLOCA_H
#include <pebble.h>
#undef open
}

#include <algorithm>
#include <memory>
#include <new>

#define PB_LOG_ERROR(fmt, args...) app_log(APP_LOG_LEVEL_ERROR, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_WARNING(fmt, args...) app_log(APP_LOG_LEVEL_WARNING, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_INFO(fmt, args...) app_log(APP_LOG_LEVEL_INFO, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_DEBUG(fmt, args...) app_log(APP_LOG_LEVEL_DEBUG, __FILE_NAME__, __LINE__, fmt, ## args)
#define PB_LOG_VERBOSE(fmt, args...) app_log(APP_LOG_LEVEL_DEBUG_VERBOSE, __FILE_NAME__, __LINE__, fmt, ## args)

#define PB_ASSERT(X) do { if (!(X)) { PB_LOG_ERROR("Assertion failure!"); free((void *)1); } } while(false)

namespace pbcpp {
#include "detail/PbNoncopyable.hpp"
#include "detail/PbSystem.hpp"
#include "detail/PbDateTimeInfo.hpp"
#include "detail/PbDateTime.hpp"
#include "detail/PbRect.hpp"
#include "detail/PbString.hpp"
#include "detail/PbHandleRef.hpp"
#include "detail/PbFontRef.hpp"
#include "detail/PbCustomFont.hpp"
#include "detail/PbBitmapRef.hpp"
#include "detail/PbBitmap.hpp"
#include "detail/PbLayerRef.hpp"
#include "detail/PbHasLayer.hpp"
#include "detail/PbClickRecognizerRef.hpp"
#include "detail/PbWindowRef.hpp"
#include "detail/PbWindow.hpp"
#include "detail/PbBitmapLayerRef.hpp"
#include "detail/PbBitmapLayer.hpp"
#include "detail/PbTextLayerRef.hpp"
#include "detail/PbTextLayer.hpp"
#include "detail/PbTickTimer.hpp"
#include "detail/PbTupleRef.hpp"
#include "detail/PbDictionaryIteratorRef.hpp"
#include "detail/PbDictionaryReader.hpp"
#include "detail/PbAppMessages.hpp"
#include "detail/PbMain.hpp"
}

#endif
