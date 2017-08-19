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

Here is a description of the wire format.

At the top level the document is not a list but consecutive objects written to
the stream.

```
document (consecutive objects): <wire version : int> <metadata> <page>...

metadata (dict): {
  "Pages": int,
  "FileName": str,
  "XFA": dict,
  "FontInfo": [<fontinfo : dict>...],
  (other string fields supplied in PDF),
}

page (dict): {
  "Size": [<width : int>, <height : int>],
  "Glyphs": [<glyph>...],
  "Paths": [<pathitem>...],
}

pathitem (list): [<type : (EO_FILL|STROKE|FILL|SET_STROKE_COLOR|
                           SET_STROKE_WIDTH|SET_FILL_COLOR)>,
                  [<pathdata>...]]

pathdata (list): depending on pathitem type
  EO_FILL, FILL, STROKE: pathcoord
  SET_FILL_COLOR: [<r : uint8>, <g : uint8>, <b : uint8>]
  SET_STROKE_WIDTH: <width : float>

pathcoord (2 list or 6 list):
  point: [<x : float>, <y : float>]
  quadratic curve: [<a : float>, <b : float>, <c : float>, <d : float>, <e : float>, <f : float>]

fontinfo (dict): {<Name> <Type> <Encoding> <Embedded> <Subset> <ToUnicode>}
```

# Licence

`pdf2msgpack` is licensed under the GPLv2.
