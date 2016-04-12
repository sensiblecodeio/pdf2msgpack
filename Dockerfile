FROM alpine

RUN apk add --no-cache poppler-dev
RUN apk add --no-cache python3
RUN apk add --no-cache build-base

COPY . /src
WORKDIR /src

RUN ./waf configure
RUN ./waf build

ENTRYPOINT ["/src/build/pdf2msgpack"]
