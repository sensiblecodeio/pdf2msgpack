# About

`pdf2msgpack` is designed to efficiently dump information from a PDF in a portable format which is easy to consume without heavyweight PDF libraries.

At the moment it dumps glyphs (a rectangle and text) and path information.

# `pdf2msgpack` is Alpha Software

`pdf2msgpack` is used internally at The Sensible Code company. It's still quite young and the output might change significantly.

# Installation

To configure and build, run:

```
./waf configure
./waf build
```

There is an accompanying docker file which enables building a static binary.

To build the static binary, just ensure submodules are checked out and
invoke `make`.

```
git submodule update --init
make
```

# Running

```
./pdf2msgpack <pdf-file>
```

# Output

`pdf2msgpack` writes its output to [msgpack](http://msgpack.org), which is a convenient, fast serialization format with libraries available in many languages.

The format is in flux and the best way to find out about it is to run `pdf2msgpack` and look at the output in python with `msgpack.load()`.
