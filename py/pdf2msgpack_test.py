import io

import msgpack

example_stream = [
    # DocumentMetadata
    {"Creator": "Example PDF"},
    # PageCount
    1,
    # PageMetadata
    {"Rotation": 0, "CropBox": (0, 0, 100, 100)},
    # GraphicsOperation
    ["G", 0, 0, 10, 10, "H"],
    "EndOfPage",
    "EndOfDocument",
]


def write_document(doc):
    buf = io.BytesIO()

    packer = msgpack.Packer()

    def pack(item):
        buf.write(packer.pack(item))

    for element in doc:
        pack(element)

    return buf


def test_load_document():

    buf = write_document(example_stream)
    buf = io.BytesIO(buf.getvalue())

    import pdf2msgpack

    for doc in pdf2msgpack.documents_from_stream(buf):
        print(doc)
        for page in doc:
            print(page)
            print(page.ops)

    # print("Wrote {}".format(len(buf.getbuffer())))
