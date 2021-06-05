from distutils.core import setup, Extension

module1 = Extension('puzzpy',
                    include_dirs = ['extern/pybind11/include'],
                    extra_compile_args = ['-shared','-std=c++11', '-fopenmp', '-fPIC','$(python3 -m pybind11 --includes)'],
                    sources = ['puzzpy.cpp'])

setup (name = 'Puzzpy',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])
