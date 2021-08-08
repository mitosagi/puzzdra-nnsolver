from distutils.core import setup, Extension
# [Why is python setup.py saying invalid command 'bdist_wheel' on Travis CI? - Stack Overflow](https://stackoverflow.com/questions/34819221/why-is-python-setup-py-saying-invalid-command-bdist-wheel-on-travis-ci/50314071#50314071)
import setuptools

module = Extension('puzzpy',
                    include_dirs=['extern/pybind11/include'],
                    extra_compile_args=['-fopenmp'],
                    extra_link_args=['-fopenmp'],
                    sources=['puzzpy.cpp'])

setup(name='Puzzpy',
      version='1.0',
      description='This is a demo package',
      ext_modules=[module])
