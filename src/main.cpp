#include <iostream>

#include <stdio.h>

#include <poppler/GlobalParams.h>
#include <poppler/Gfx.h>
#include <poppler/Page.h>
#include <poppler/PDFDoc.h>
#include <poppler/DateInfo.h>
#include <poppler/UnicodeMap.h>
#include <poppler/UTF.h>
#include <poppler/TextOutputDev.h>
#include <poppler/goo/GooList.h>

#include <msgpack.hpp>

#include "DumpAsMsgPackDev.h"
#include "DumpAsTextDev.h"

msgpack::packer<std::ostream> packer(&std::cout);


static std::string fmt(Object *o, UnicodeMap *uMap) {
	if (!o)
	return "<nil>";
	if (!o->isString())
	return "<not string>";

	auto s = o->getString();

	char buf[9];
	Unicode *u;
	auto len = TextStringToUCS4(s, &u);

	std::string out;
	out.reserve(static_cast<size_t>(len));

	for (auto i = 0; i < len; i++) {
		auto n = uMap->mapUnicode(u[i], buf, sizeof(buf));
		out.append(buf, n);
	}

	return out;
}

void dump_document_meta(PDFDoc *doc, UnicodeMap *uMap) {
	printf("Pages:	  %d\n", doc->getNumPages());
	printf("PDF version:	%d.%d\n", doc->getPDFMajorVersion(), doc->getPDFMinorVersion());

	Object info;
	doc->getDocInfo(&info);
	auto dict = info.getDict();

	printf("Keys: ");
	for (int i = 0; i < dict->getLength(); i++) {
		printf("%s, ", dict->getKey(i));
	}
	printf("\n");

	if (info.isDict()) {
		auto dict = info.getDict();
		Object o;
		std::cout << "Creator: " << fmt(dict->lookup("Creator", &o), uMap) << std::endl;

		// printInfoString(dict, "Creator",	  "Creator:	", uMap);
		// printInfoString(dict, "Producer",	 "Producer:	   ", uMap);
		// printInfoString(dict, "CreationDate", "CreationDate:   ", uMap);
		// printInfoString(dict, "ModDate",	  "ModDate:	", uMap);
	}
}

TextPage* page_to_text_page(Page *page) {
	auto dev = new TextOutputDev(NULL, gTrue, 0, gFalse, gFalse);

	auto gfx = page->createGfx(
		dev,
		72.0, 72.0, 0,
		gFalse, /* useMediaBox */
		gTrue, /* Crop */
		-1, -1, -1, -1,
		gFalse, /* printing */
		NULL, NULL
	);

	page->display(gfx);
	dev->endPage();

	auto text = dev->takeText();

	delete gfx;
	delete dev;

	return text;
}

int count_glyphs(GooList **word_list, int n_lines) {
	int total_glyphs = 0;

	for (int l = 0; l < n_lines; l++) {
		auto *words = word_list[l];
		total_glyphs += words->getLength() - 1; // spaces
		for (int j = 0; j < words->getLength(); j++) {
			auto *x = reinterpret_cast<TextWordSelection *>(words->get(j));
			auto *word = reinterpret_cast<TextWord*>(x->getWord());
			total_glyphs += word->getLength();
		}
	}
	return total_glyphs;
}

void dump_page(Page *page) {
	auto text = page_to_text_page(page);

	PDFRectangle selection = {
		x1: 0, y1: 0, x2: page->getCropWidth(), y2: page->getCropHeight(),
	};

	int n_lines;
	auto word_list = text->getSelectionWords(&selection, selectionStyleGlyph, &n_lines);

	int total_glyphs = count_glyphs(word_list, n_lines);

	packer.pack_array(total_glyphs);

	for (int l = 0; l < n_lines; l++) {
		GooList *line_words = word_list[l];

		for (int j = 0; j < line_words->getLength(); j++) {
			TextWordSelection *word_sel = (TextWordSelection *)line_words->get(j);
			TextWord *word = word_sel->getWord();

			for (int k = 0; k < word->getLength(); k++) {
				double x1, y1, x2, y2;
				word->getCharBBox(k, &x1, &y1, &x2, &y2);

				auto rect = std::make_tuple(x1, y1, x2, y2);
				packer.pack(std::make_tuple(rect, toUTF8(word, k)));
			}

			double x1, y1, x2, y2;
			double x3, y3, x4, y4;
			word->getBBox (&x1, &y1, &x2, &y2);

			if (j < line_words->getLength() - 1)
			{
				TextWordSelection *word_sel = (TextWordSelection *)line_words->get(j + 1);
				word_sel->getWord()->getBBox(&x3, &y3, &x4, &y4);
				// space is from one word to other and with the same height as
				// first word.
				x1 = x2;
				y1 = y1;
				x2 = x3;
				y2 = y2;

				auto rect = std::make_tuple(x1, y1, x2, y2);
				packer.pack(std::make_tuple(rect, " "));
			}

			delete word_sel;
		}

		delete line_words;
	}

	gfree(word_list);
	text->decRefCnt();
}

void dump_document(PDFDoc *doc) {
	int n_pages = doc->getNumPages();

	if (n_pages > 500)
		n_pages = 500;

	packer.pack_array(n_pages);

	// Pages are one-based in this API. Beware, 0 based elsewhere.
	for (int i = 1; i < n_pages+1; i++) {
		dump_page(doc->getPage(i));
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: pdf2msgpack <filename>\n");
		exit(1);
	}

	if (!globalParams) {
		globalParams = new GlobalParams();
	}

	UnicodeMap *uMap;
	if (!(uMap = globalParams->getTextEncoding())) {
		exit(127);
	}

	auto doc = new PDFDoc(new GooString(argv[1]));
	if (!doc) {
		exit(64);
	}

	if (!doc->isOk()) {
		fprintf(stderr, "Failed to open: %d\n", doc->getErrorCode());
		exit(63);
	}

	// dump_document_meta(doc, uMap);
	dump_document(doc);

	delete doc;
}
