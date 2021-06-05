from distutils.core import setup, Extension

module = Extension('puzzpy',
                    include_dirs=['extern/pybind11/include'],
                    extra_compile_args=['-fopenmp'],
                    extra_link_args=['-fopenmp'],
                    sources=['puzzpy.cpp'])

setup(name='Puzzpy',
      version='1.0',
      description='This is a demo package',
      ext_modules=[module])
