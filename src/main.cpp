#include <iostream>

#include <stdio.h>

#include <poppler/GlobalParams.h>
#include <poppler/Page.h>
#include <poppler/PDFDoc.h>
#include <poppler/DateInfo.h>
#include <poppler/UnicodeMap.h>
#include <poppler/UTF.h>

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
	printf("PDF version:    %d.%d\n", doc->getPDFMajorVersion(), doc->getPDFMinorVersion());

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

		// printInfoString(dict, "Creator",      "Creator:	", uMap);
		// printInfoString(dict, "Producer",     "Producer:       ", uMap);
		// printInfoString(dict, "CreationDate", "CreationDate:   ", uMap);
		// printInfoString(dict, "ModDate",      "ModDate:	", uMap);
	}
}

void dump_document(PDFDoc *doc) {
	OutputDev *dev = NULL;

	// dev = new DumpAsTextDev();
	dev = new DumpAsMsgPackDev(packer);

	// packer.pack("DOCUMENT");

	// Pages are one-based in this API. Beware, 0 based elsewhere.
	for (int i = 1; i < doc->getNumPages()+1; i++) {

		// packer.pack("PAGE");

		auto page = doc->getPage(i);

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
}
