#!/bin/bash

if ! TAG=$(git describe --tags --exact);
then
    echo You must first tag a revision before releasing.
    exit 1
fi

hub release create -d -a pdf2msgpack -a pdf2msgpack.dbg "$TAG"
