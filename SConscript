# Import environment
Import('env', 'mode')

# Add include file absolute path
env.Append(CPPPATH = [env.Dir('.').abspath])

# Clone environment
env = env.Clone()

# Add specific compiler flags
env.AppendUnique(CCFLAGS = ['-std=c99'])

if mode == 'test':
  env.AppendUnique(CCFLAGS = ['--coverage'])

# Point out all source files
src = env.Split('''
  circularbuffer.c
''')

obj = []
obj += env.Object(src)

# Build a library
lib = env.Library('circularbuffer', obj)

# Return result to SConstruct
Return('lib')
