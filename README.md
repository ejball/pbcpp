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

## Watchfaces using pbcpp

[![jsonface](https://raw.githubusercontent.com/ejball/jsonface/master/screenshot.png)](https://github.com/ejball/jsonface)

## Acknowledgements

Thanks to [FarzHemmati](https://forums.getpebble.com/discussion/11495/c-on-the-pebble), [wvenable](https://forums.getpebble.com/discussion/22437/c-compiler), and [LukeForeman](https://forums.getpebble.com/discussion/comment/154471/) for figuring out how to get C++ to work.
