pdf2msgpack: build-container
	docker run \
		--rm \
		--entrypoint=cat \
		pdf2msgpack \
		/src/build/pdf2msgpack > pdf2msgpack
	chmod +x pdf2msgpack
	@echo "Wrote pdf2msgpack"

build-container: Dockerfile src/main.cpp
	docker build -t pdf2msgpack .

.PHONY: .FORCE build-container
