class Pdf2msgpack < Formula
  desc "Efficiently export PDF content in an easily machine readable format"
  homepage "https://github.com/scraperwiki/pdf2msgpack"
  head "https://github.com/scraperwiki/pdf2msgpack.git"
  url "https://github.com/scraperwiki/pdf2msgpack/archive/v0.2.tar.gz"
  sha256 "302416b7bcd73eb0f3d66cd019525e10e2ebc53341dd0bee6edb91850ff61a5e"

  depends_on "pkg-config" => :build
  depends_on "python3"    => :build  # WAF
  depends_on "poppler"  # libpoppler-private-dev (`--enable-xpdf-headers`)

  def install
    system "./waf", "configure", "--prefix=#{prefix}",
                                 "--disable-syscall-filter",
                                 "--release"
    system "./waf", "install"
  end

  test do
    system "true"
  end
end
