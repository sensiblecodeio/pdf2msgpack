package main

import (
	"io"
	"log"
	"os"

	"github.com/kr/pretty"

	"github.com/scraperwiki/pdf2msgpack/go/p2m"
)

func main() {
	r, err := p2m.NewReader(os.Stdin)
	if err != nil {
		log.Fatal(err)
	}

	log.Printf("FileName: %q", r.Meta.FileName)
	log.Printf("Pages: %d", r.Meta.Pages)
	log.Printf("Creator: %q", r.Meta.Creator)
	log.Printf("Producer: %q", r.Meta.Producer)

	if r.Meta.FontInfo != nil {
		for _, fi := range *r.Meta.FontInfo {
			pretty.Println(fi)
		}
	}

	var p p2m.Page
loop:
	for {
		err := r.Next(&p)
		switch err {
		default:
			log.Fatal(err)
		case io.EOF:
			break loop
		case nil:
		}

		log.Printf("Page i=%v s=%v len(paths)=%d len(glyphs)=%d", p.Number, p.Size, len(p.Paths), len(p.Glyphs))
	}
}
