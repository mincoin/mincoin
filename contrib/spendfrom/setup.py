from distutils.core import setup
setup(name='mncspendfrom',
      version='1.0',
      description='Command-line utility for mincoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@bitcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
