class Pdf2msgpack < Formula
  desc "Efficiently export PDF content in an easily machine readable format"
  homepage "https://github.com/scraperwiki/pdf2msgpack"
  url "https://github.com/scraperwiki/pdf2msgpack/archive/v0.3.0.tar.gz"
  sha256 "7ec23dac37fcaf09adef3cafc0cad2ac4bdee93c7de59516af267202b9458fd5"
  head "https://github.com/scraperwiki/pdf2msgpack.git"

  depends_on "pkg-config" => :build
  depends_on "python3"    => :build # WAF
  depends_on "poppler" # libpoppler-private-dev (`--enable-xpdf-headers`)

  def install
    system "./waf", "configure", "--prefix=#{prefix}",
                                 "--disable-syscall-filter",
                                 "--release"
    system "./waf", "install"
    share.install "example"
  end

  test do
    system "#{bin}/pdf2msgpack", "#{share}/example/example.pdf"
  end
end
