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

    opt.add_option('--sanitize', action='store', default=False,
                   help='Use -fsanitize={leak,address,undefined}')

    opt.add_option('--release', action='store_true', default=False,
                   help='Enable optimizations')


def configure(ctx):
    ctx.load('compiler_cxx')

    ctx.check(features='cxx cxxprogram', cxxflags="--std=c++11")

    ctx.env.append_value("CXXFLAGS", [
        "-g",
        "-Wall",
        "-Werror",
        "-ansi",
        "--std=c++11",
    ])

    if ctx.options.release:
        ctx.env.append_value("CXXFLAGS", ["-O2"])

    if ctx.options.sanitize:
        ctx.msg("Enable sanitizer", ctx.options.sanitize)
        param = "-fsanitize={}".format(ctx.options.sanitize)
        ctx.env.append_value("CXXFLAGS", [param])
        ctx.env.append_value("LINKFLAGS", [param])

    if ctx.options.static:
        ctx.msg("Building static binaries", "yes")

        ctx.env.BUILD_STATIC = True

        ctx.check_cfg(package='poppler', uselib_store='poppler',
                      args=['--cflags', '--libs', '--static'])

        poppler_stlib = "fontconfig expat freetype lcms2 openjp2 jpeg png bz2 z pthread"
        for lib in poppler_stlib.split():
            ctx.check_cxx(stlib=lib, uselib_store='poppler')

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
        source=ctx.path.ant_glob('src/*.c*'),
        target='pdf2msgpack',
        use="poppler",
        features=features,
        includes=["msgpack-c/include"],
    )
