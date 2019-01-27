# Use environment
env = Environment()

# Add compiler flags
env.Append(CCFLAGS = ['-Wextra', '-Wall', '-Wpedantic', '-Werror'])

#  Google test program
test = []

test += SConscript('test/SConscript', variant_dir='build', duplicate=0, exports='env')

# Depend on the runner to ensure that it's built before running it - Note: using abspath.
test_alias = Alias('test', [test], test[0].abspath)

# Simply required.  Without it, 'test' is never considered out of date.
AlwaysBuild(test_alias)

# Alias for building all programs
Alias('all', [test])
