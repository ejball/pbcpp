# pbcpp

A C++ library for writing Pebble watchfaces and apps.

## Goals

* **Efficiency.** Apps should be as efficient as their C equivalent. No virtual functions; no exception handling; minimal memory allocations.
* **Destructors.** Class destructors help clean up memory and resources automatically (RAII).
* **Less typing.** Object-oriented C++ requires less typing than object-oriented C. A fluent API can help even more.
* **No globals.** Global variables encourage poor coding practices, so I'd like to avoid them.
* **Fewer underscores.** I don't like typing so_many_underscores. I prefer camelCase.
* **Avoid macros.** C-style macros should rarely be necessary in C++ code.
* **Write C++.** It's been a long time since I wrote C++ for my day job; it is good to get familiar with it again.
* **Have fun.** I enjoy writing class libraries, and the constraints of the Pebble platform make it even more interesting.

## Watchfaces using pbcpp

### jsonface

[![jsonface](https://raw.githubusercontent.com/ejball/jsonface/master/screenshot-aplite.png)](https://github.com/ejball/jsonface) [![jsonface](https://raw.githubusercontent.com/ejball/jsonface/master/screenshot-basalt.png)](https://github.com/ejball/jsonface) [![jsonface](https://raw.githubusercontent.com/ejball/jsonface/master/screenshot-chalk.png)](https://github.com/ejball/jsonface)

## Overview

To use pbcpp, follow the lead of one of the [example projects](examples), which contain C and C++ versions of various tutorials on the [Pebble Developer](http://developer.getpebble.com/) site. Basically, you'll need to make a few changes to your [`wscript`](examples/hello-pebble/cpp/wscript), rename [`main.c`](examples/hello-pebble/c/src/main.c) to [`main.cpp`](examples/hello-pebble/c/src/main.cpp), and `#include "path/to/pbcpp.hpp"` at the top.

## Acknowledgements

Thanks to [FarzHemmati](https://forums.getpebble.com/discussion/11495/c-on-the-pebble), [wvenable](https://forums.getpebble.com/discussion/22437/c-compiler), and [LukeForeman](https://forums.getpebble.com/discussion/comment/154471/) for figuring out how to get C++ to work.
