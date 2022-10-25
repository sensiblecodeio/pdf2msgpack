# syntax = docker/dockerfile:experimental

FROM alpine:3.16.2 AS cachebase
RUN mkdir -p /tmp/ccache \
 && chown nobody:nogroup /tmp/ccache

FROM alpine:3.16.2

ARG BUILD_CONCURRENCY=4

RUN --mount=type=cache,target=/etc/apk/cache,id=apk-cache \
    --mount=type=cache,target=/var/lib/apk,id=apk-lib \
    \
    apk add \
      autoconf \
      automake \
      build-base \
      bzip2-dev \
      bzip2-static \
      cmake \
      ccache \
      expat-dev \
      expat-static \
      gettext-dev \
      gettext-static \
      git \
      gperf \
      libjpeg-turbo-dev \
      libjpeg-turbo-static \
      libpng-dev \
      libpng-static \
      libtool \
      linux-headers \
      py-lxml \
      py-six \
      python2 \
      python3 \
      util-linux-dev \
      zlib-dev \
      zlib-static

ENV PATH=/usr/lib/ccache/bin:$PATH \
    CCACHE_DIR=/tmp/ccache

COPY --chown=nobody:nogroup ./vendor /src/vendor
WORKDIR /src
USER nobody:nogroup

RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    cd vendor/git.savannah.gnu.org/r/freetype/freetype2.git/ \
 && NOCONFIGURE=1 ./autogen.sh \
 # workaround for docker #9547 (Text file busy) \
 && sync \
 && mkdir build && cd build \
 && ../configure --prefix=$PWD/install --enable-static \
 && make -j${BUILD_CONCURRENCY} \
 && make install

ENV PKG_CONFIG_PATH="/src/vendor/git.savannah.gnu.org/r/freetype/freetype2.git/build/install/lib/pkgconfig:$PKG_CONFIG_PATH" \
    LINKFLAGS="-L/src/vendor/git.savannah.gnu.org/r/freetype/freetype2.git/build/install/lib $LINKFLAGS" \
    # Required for poppler cmake \
    FREETYPE_DIR=/src/vendor/git.savannah.gnu.org/r/freetype/freetype2.git/build/install


RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    cd vendor/anongit.freedesktop.org/git/fontconfig \
 && NOCONFIGURE=1 ./autogen.sh \
 && mkdir build && cd build \
 && ../configure --prefix=$PWD/install --enable-static \
 && make -j${BUILD_CONCURRENCY} \
 && make install

ENV PKG_CONFIG_PATH="/src/vendor/anongit.freedesktop.org/git/fontconfig/build/install/lib/pkgconfig:$PKG_CONFIG_PATH" \
    LINKFLAGS="-L/src/vendor/anongit.freedesktop.org/git/fontconfig/build/install/lib $LINKFLAGS"


RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    cd vendor/github.com/mm2/Little-CMS/ \
 && mkdir build && cd build \
 && ../configure --prefix=$PWD/install --enable-static \
 && make -j${BUILD_CONCURRENCY} \
 && make install

ENV PKG_CONFIG_PATH="/src/vendor/github.com/mm2/Little-CMS/build/install/lib/pkgconfig:$PKG_CONFIG_PATH" \
    LINKFLAGS="-L/src/vendor/github.com/mm2/Little-CMS/build/install/lib $LINKFLAGS"


RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    cd vendor/github.com/uclouvain/openjpeg/ \
 && mkdir build && cd build \
 && cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$PWD/install \
 && make -j${BUILD_CONCURRENCY} \
 && make install

ENV PKG_CONFIG_PATH="/src/vendor/github.com/uclouvain/openjpeg/build/install/lib64/pkgconfig:$PKG_CONFIG_PATH" \
    CXXFLAGS="-I/src/vendor/github.com/uclouvain/openjpeg/build/install/include $CXXFLAGS" \
    LDFLAGS="-L/src/vendor/github.com/uclouvain/openjpeg/build/install/lib64 $LDFLAGS" \
    LINKFLAGS="-L/src/vendor/github.com/uclouvain/openjpeg/build/install/lib64 $LINKFLAGS" \
    OpenJPEG_DIR="/src/vendor/github.com/uclouvain/openjpeg/build/install/lib64/cmake/openjpeg-2.5"


RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    cd vendor/anongit.freedesktop.org/git/poppler/poppler.git \
 && mkdir build && cd build \
 && cmake .. \
          -DCMAKE_INSTALL_PREFIX=$PWD/install \
          -DENABLE_GLIB:BOOL=OFF \
          -DENABLE_CPP:BOOL=OFF \
          -DENABLE_UTILS:BOOL=OFF \
          -DBUILD_SHARED_LIBS:BOOL=OFF \
          -DENABLE_UNSTABLE_API_ABI_HEADERS:BOOL=ON \
          -DCMAKE_BUILD_TYPE:STRING=release \
          -DENABLE_LIBOPENJPEG:STRING=openjpeg2 \
 && make V=1 -j${BUILD_CONCURRENCY} \
 && make install

ENV PKG_CONFIG_PATH="/src/vendor/anongit.freedesktop.org/git/poppler/poppler.git/build/install/lib64/pkgconfig:$PKG_CONFIG_PATH" \
    LINKFLAGS="-L/src/vendor/anongit.freedesktop.org/git/poppler/poppler.git/build/install/lib64 $LINKFLAGS" \
    CXXFLAGS="-I/src/vendor/anongit.freedesktop.org/git/poppler/poppler.git/build/install/include $CXXFLAGS"


COPY --chown=nobody:nogroup ./src /src/src
COPY --chown=nobody:nogroup waf wscript .

RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    ./waf configure --static --release || { cat build/config.log; exit 1; }

RUN --mount=type=cache,src=/tmp/ccache,target=/tmp/ccache,id=ccache,from=cachebase \
    \
    ./waf build

ENTRYPOINT ["/src/build/pdf2msgpack"]
