all: submodules pdf2msgpack

pdf2msgpack: pdf2msgpack.dbg
	strip --strip-debug -o pdf2msgpack pdf2msgpack.dbg

pdf2msgpack.dbg: build-container
	docker run \
		--rm \
		--entrypoint=cat \
		pdf2msgpack \
		/src/build/pdf2msgpack > pdf2msgpack.dbg
	chmod +x pdf2msgpack.dbg
	@echo "Wrote pdf2msgpack.dbg"

build-container: Dockerfile src/main.cpp
	DOCKER_BUILDKIT=1 docker build -t pdf2msgpack .

release: pdf2msgpack
	./release.sh


fmt:
	clang-format -i src/*.cpp src/*.h

submodules: .FORCE
	git submodule update --init

.PHONY: .FORCE build-container submodules
