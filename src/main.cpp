#include <iostream>
#include <limits>
#include <sstream>

#include <stdio.h>

#include <sys/stat.h>

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

#include "util.hpp"

#include "DumpPathsAsMsgPackDev.h"
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
	std::map<std::string, std::string> m;

	Object info;
	doc->getDocInfo(&info);
	if (info.isDict()) {
		auto dict = info.getDict();

		for (int i = 0; i < dict->getLength(); i++) {
			Object o;
			m[dict->getKey(i)] = fmt(dict->getVal(i, &o), uMap);
		}
	}

	// Use packer.pack_map rather than pack(m) so we can write pages as an integer.
	packer.pack_map(1 + m.size());

	packer.pack("Pages");
	packer.pack(doc->getNumPages());

	for (auto i : m) {
		packer.pack(i.first);
		packer.pack(i.second);
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

int count_glyphs(GooList **lines, int n_lines) {
	int total_glyphs = 0;

	for (int i = 0; i < n_lines; i++) {
		auto *words = lines[i];
		total_glyphs += words->getLength() - 1; // spaces
		for (int j = 0; j < words->getLength(); j++) {
			auto *x = reinterpret_cast<TextWordSelection *>(words->get(j));
			auto *word = reinterpret_cast<TextWord*>(x->getWord());
			total_glyphs += word->getLength();
		}
	}
	return total_glyphs;
}

void dump_glyphs(GooList **lines, int n_lines) {
	// Lines
	for (int i = 0; i < n_lines; i++) {
		GooList *line_words = lines[i];

		// Words
		for (int j = 0; j < line_words->getLength(); j++) {
			auto word_sel = reinterpret_cast<TextWordSelection*>(line_words->get(j));
			TextWord *word = word_sel->getWord();

			// Glyphs
			for (int k = 0; k < word->getLength(); k++) {
				double x1, y1, x2, y2;
				word->getCharBBox(k, &x1, &y1, &x2, &y2);

				auto rect = std::make_tuple(x1, y1, x2, y2);
				packer.pack(std::make_tuple(rect, toUTF8(word, k)));
			}

			double x1, y1, x2, y2;
			double x3, y3, x4, y4;
			word->getBBox (&x1, &y1, &x2, &y2);

			// Spaces
			if (j < line_words->getLength() - 1) {
				auto word_sel = reinterpret_cast<TextWordSelection*>(line_words->get(j + 1));
				word_sel->getWord()->getBBox(&x3, &y3, &x4, &y4);
				// space is from one word to other and with the same height as
				// first word.

				x1 = x2;
				// y1 = y1; (implicit)
				x2 = x3;
				// y2 = y2; (implicit)

				auto rect = std::make_tuple(x1, y1, x2, y2);
				packer.pack(std::make_tuple(rect, " "));
			}
		}
	}
}

void free_word_list(GooList **lines, int n_lines) {
	for (int i = 0; i < n_lines; i++) {
		deleteGooList(lines[i], TextWordSelection);
	}
	gfree(lines);
}

void dump_page_glyphs(Page *page) {
	auto text = page_to_text_page(page);

	const auto inf = std::numeric_limits<double>::infinity();

	PDFRectangle whole_page(-inf, -inf, inf, inf);

	int n_lines;
	auto word_list = text->getSelectionWords(&whole_page, selectionStyleGlyph, &n_lines);

	int total_glyphs = count_glyphs(word_list, n_lines);

	packer.pack_array(total_glyphs);
	dump_glyphs(word_list, n_lines);

	free_word_list(word_list, n_lines);
	text->decRefCnt();
}

void dump_page_paths(Page *page) {
	auto dev = new DumpPathsAsMsgPackDev();

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

	dev->pack(std::cout);

	delete gfx;
	delete dev;
}

void dump_page(Page *page) {
	packer.pack_array(2);
	dump_page_glyphs(page);
	dump_page_paths(page);
}

class Options {
public:
	std::string filename;
	int start, end;

	Options() : filename(""), start(0), end(0) {}

	bool range_specified() const {
		return start != 0 && end != 0;
	}

	int page_count() const {
		// Note: range is inclusive on the right.
		return end - start + 1;
	}
};

void dump_document(PDFDoc *doc, const Options &options) {
	packer.pack_array(options.page_count());

	// Pages are one-based in this API. Beware, 0 based elsewhere.
	for (int i = options.start; i <= options.end; i++) {
		dump_page(doc->getPage(i));
	}
}

std::string parse_page_range(std::string value, Options *options) {
	uint8_t c;

	std::istringstream stream(value);
	stream >> options->start >> c >> options->end;

	auto negative = options->start < 1 || options->end < options->start;

	// Must parse whole value.
	if (c != '-' || stream.bad() || !stream.eof() || negative) {
		options->start = options->end = 0;
		return "invalid format for pages: specify like 1-10";
	}

	return "";
}

bool file_exists(std::string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string parse_options(int argc, char *argv[], Options *options) {
	for (int i = 1; i < argc; ++i) {
		char const* arg = argv[i];

		if ((arg[0] == '-') && (strcmp(arg, "-") != 0)) {
			++arg;
			if (arg[0] == '-') {
				// Accept -arg and --arg
				++arg;
			}
			char* parameter = const_cast<char*>(strchr(arg, '='));
			if (parameter) {
				*parameter++ = 0;
			}

			if (strcmp(arg, "pages") == 0) {
				if (parameter == nullptr) {
					return "--pages must be specified as --pages=a-b";
				}
				auto err = parse_page_range(parameter, options);
				if (err != "") {
					return err;
				}
			} else {
				if (file_exists(arg) && options->filename == "") {
					// It's a filename.
					options->filename = arg;
					continue;
				}
				return std::string("unknown parameter specified: ") + arg;
			}
		} else if (options->filename == "") {
			options->filename = arg;
		} else {
			return std::string("unknown parameter specified: ") + arg;
		}
	}

	if (options->filename == "") {
		return "no input file specified";
	}

	return "";
}

void usage() {
	std::cerr << "usage: pdf2msgpack [--pages=a-b] <filename>" << std::endl;
}

int main(int argc, char *argv[]) {

	Options options;
	auto err = parse_options(argc, argv, &options);
	if (err != "") {
		std::cerr << "Error: " << err << std::endl;
		usage();
		exit(1);
	}

	if (!globalParams) {
		globalParams = new GlobalParams("/usr/share/poppler");
	}

	UnicodeMap *uMap;
	if (!(uMap = globalParams->getTextEncoding())) {
		exit(127);
	}

	auto doc = new PDFDoc(new GooString(options.filename.c_str()));
	if (!doc) {
		std::cerr << "Problem loading document." << std::endl;
		exit(64);
	}

	if (!doc->isOk()) {
		std::cerr << "Failed to open: " << doc->getErrorCode() << std::endl;
		exit(63);
	}

	if (!options.range_specified()) {
		options.start = 1;
		options.end = doc->getNumPages();
	} else if (options.start > doc->getNumPages() ||
			   options.end > doc->getNumPages()) {
		std::cerr << "Error: specified page range"
				  << " (" << options.start << " - " << options.end << ")"
				  << " exceeds document length"
				  << " (" << doc->getNumPages() << ")" << std::endl;
		usage();
		exit(1);
	}

	// This version number should be incremented whenever the output format
	// is changed in a way which will break existing parsers.
	const int output_format_version = 0;
	packer.pack(output_format_version);

	dump_document_meta(doc, uMap);
	dump_document(doc, options);

	delete doc;
}
