# Import environment
Import('env')

# Add include file absolute path
env.Append(CPPPATH = [env.Dir('.').abspath])

# Clone environment
env = env.Clone()

# Add specific compiler flags
env.AppendUnique(CCFLAGS = ['-std=c99'])

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
