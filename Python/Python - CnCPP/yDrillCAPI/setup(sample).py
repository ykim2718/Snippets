from distutils.core import setup, Extension

setup(name="_sample",
      version="0.1",
      description="sample extension module",
      author="Kim, Yongshik",
      author_email="ykim7389@naver.com",
      url="http://...",
      ext_modules=[Extension("_sample", ["sample.c"])]
      )
