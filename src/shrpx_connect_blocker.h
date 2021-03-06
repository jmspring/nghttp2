/*
 * nghttp2 - HTTP/2 C Library
 *
 * Copyright (c) 2014 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SHRPX_CONNECT_BLOCKER_H
#define SHRPX_CONNECT_BLOCKER_H

#include "shrpx.h"

#include <event2/event.h>

namespace shrpx {

class ConnectBlocker {
public:
  ConnectBlocker();
  ~ConnectBlocker();

  int init(event_base *evbase);
  // Returns true if making connection is not allowed.
  bool blocked() const;
  // Call this function if connect operation succeeded.  This will
  // reset sleep_ to minimum value.
  void on_success();
  // Call this function if connect operation failed.  This will start
  // timer and blocks connection establishment for sleep_ seconds.
  void on_failure();

private:
  event *timerev_;
  int sleep_;
};

} // namespace

#endif // SHRPX_CONNECT_BLOCKER_H
