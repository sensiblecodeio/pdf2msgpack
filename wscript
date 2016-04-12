#! /usr/bin/env python3
top = '.'
out = 'build'

from waflib.TaskGen import after_method, feature


@feature('static_linking')
@after_method('apply_link')
def force_static_linking(self):
    env = self.link_task.env
    env.STLIB += env.LIB
    env.LIB = []
    env.STLIB_MARKER = '-static'
    env.SHLIB_MARKER = ''


def options(opt):
    opt.load('compiler_cxx')

    opt.add_option('--static', action='store_true', default=False,
                   help='Build static binaries')


def configure(ctx):
    ctx.load('compiler_cxx')

    ctx.check(features='cxx cxxprogram', cxxflags="--std=c++11")
    ctx.env.append_value("CXXFLAGS", [
        "-g",
        "-Wall",
        "-Wno-deprecated-register",
        "-Werror",
        "-ansi",
        "-fno-strict-aliasing",
        "-std=c++0x",
    ])

    if ctx.options.static:
        ctx.msg("Building static binaries", "yes")

        ctx.env.BUILD_STATIC = True

        ctx.check_cfg(package='poppler', uselib_store='poppler',
                      args=['--cflags', '--libs', '--static'])
        ctx.check_cxx(stlib="fontconfig", uselib_store='poppler')
        ctx.check_cxx(stlib="expat", uselib_store='poppler')
        ctx.check_cxx(stlib="freetype", uselib_store='poppler')
        ctx.check_cxx(stlib="z", uselib_store='poppler')

        ctx.check_cxx(stlib="png", uselib_store='poppler')
        ctx.check_cxx(stlib="jpeg", uselib_store='poppler')
        ctx.check_cxx(stlib="pthread", uselib_store='poppler')

    else:
        ctx.msg("Building dynamic binaries", "yes")

        ctx.check_cfg(package='poppler', uselib_store='poppler',
                      args=['--cflags', '--libs'])

    ctx.check_cxx(header_name="poppler/PDFDoc.h", use="poppler",
                  msg="Checking libpoppler-private-dev (poppler configured " +
                      "with --enable-xpdf-headers)")


def build(ctx):
    features = ""

    if ctx.env.BUILD_STATIC:
        features = 'static_linking'

    ctx.program(
        source=ctx.path.ant_glob('src/*.cpp'),
        target='pdf2msgpack',
        use="poppler",
        features=features,
        includes=["msgpack-c/include"],
    )
