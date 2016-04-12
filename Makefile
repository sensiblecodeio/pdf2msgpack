example: build .FORCE
	docker run \
		--rm \
		-v $$PWD/example/example.pdf:/example.pdf \
		pdf2msgpack /example.pdf > out.std 2> out.err
	@echo "Wrote example output to out.std and out.err."

build:
	docker build -t pdf2msgpack .

.PHONY: .FORCE
