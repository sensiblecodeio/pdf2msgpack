FROM alpine

RUN apk add --no-cache build-base poppler-dev python3

COPY . /src
WORKDIR /src

RUN ./waf configure
RUN ./waf build

ENTRYPOINT ["/src/build/pdf2msgpack"]
