# pbcpp

A C++ library for writing Pebble watchfaces and apps.

## Goals

* **Efficiency.** Apps should be as efficient as their C equivalent. No virtual functions; no exception handling; minimal memory allocations.
* **Destructors.** Class destructors help clean up memory and resources automatically (RAII).
* **Less typing.** Object-oriented C++ requires less typing than object-oriented C. A fluent API can help even more.
* **No globals.** Global variables encourage poor coding practices, so I'd like to avoid them.
* **Fewer underscores.** I don't like typing so_many_underscores. I prefer camelCase.
* **Write C++.** It's been a long time since I wrote C++ for my day job; it is good to get familiar with it again.
* **Have fun.** I enjoy writing class libraries, and the constraints of the Pebble platform make it even more interesting.

## Apps using pbcpp

[![jsonface](https://raw.githubusercontent.com/ejball/jsonface/master/screenshot.png)](https://github.com/ejball/jsonface)
