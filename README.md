# Circular Buffer
This repository contains a circular buffer or a ring buffer implementation in C code suitable for embedded systems. The implementation using a single empty cell to detect the buffer "full" case; for supporting a single producer thread and single consumer thread without OS lock primitive. The code follows the Google C++ Style Guide with one exception that instead of 2 spaces it use 4 spaces.

## Unittest

The added unittest uses the googletest framework and the SCons build system.

### Follow the steps below for building the unittest

1. Install the scons, if you run on an Ubuntu machine:

   ```sudo apt install scons```

2. Go to https://github.com/google/googletest and clone the git repo besides the circularbuffer repo.

3. Create a directory called *build_gtest* beside the circularbuffer and googletest repos.

4. Now you shall have the following directory structure:
 ```
   <your path>
       | build_gtest
       | circularbuffer
       | googletest
 ```
5. Change directory to the new directory ```build_gtest```.

6. Build the google test framework:

   ```<your path>/build_gtest$ cmake ../googletest/googletest/```

   ```<your path>/build_gtest$ make```

7. Change directory to ```<your path>/circularbuffer```.

8. Build, run and clean the units test with the scons command:

   ```<your path>/circularbuffer$ scons test```

   ```<your path>/circularbuffer$ scons test -c```

9. Optional build, run and clean the units test with the commands:

   ```<your path>/circularbuffer$ scons```

   ```<your path>/circularbuffer$ ./build/circularbuffer-gtest```

   ```<your path>/circularbuffer$ scons -c```
