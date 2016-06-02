pdf2msgpack: build-container
	docker run \
		--rm \
		--entrypoint=cat \
		pdf2msgpack \
		/src/build/pdf2msgpack > pdf2msgpack.dbg
	chmod +x pdf2msgpack
	@echo "Wrote pdf2msgpack"

build-container: Dockerfile src/main.cpp
	docker build -t pdf2msgpack .

release: pdf2msgpack
	strip --strip-debug -o pdf2msgpack pdf2msgpack.dbg
	./release.sh


.PHONY: .FORCE build-container
