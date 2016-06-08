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
	docker build -t pdf2msgpack .

release: pdf2msgpack
	./release.sh


.PHONY: .FORCE build-container
