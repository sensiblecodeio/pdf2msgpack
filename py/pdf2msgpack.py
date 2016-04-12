import msgpack


def documents_from_stream(stream):
    unpacker = msgpack.Unpacker(stream)

    for metadata in unpacker:
        yield Document(unpacker, metadata)


class Document(object):

    def __init__(self, unpacker, metadata):
        self._unpacker = unpacker
        self.metadata = metadata
        self.page_count = next(unpacker)

    def __iter__(self):
        return self

    def __next__(self):
        metadata = next(self._unpacker)
        if metadata == b"EndOfDocument":
            raise StopIteration

        return Page(self._unpacker, metadata)

    def __repr__(self):
        return '<Document page_count={}>'.format(self.page_count)


class Page(object):

    def __init__(self, unpacker, metadata):
        self.metadata = metadata

        self.ops = {}

        for op in unpacker:
            print("Read op {}".format(op))
            if op == b"EndOfPage":
                break

            op_type, *args = op
            self.ops.setdefault(op_type, []).append(args)

    def __repr__(self):
        return "<Page ops={}>".format(len(self.ops))
