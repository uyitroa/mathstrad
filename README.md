# A translator for mathematical terms.

## Build

Specify where icu4c include and lib folders are in ``CMakeLists.txt`` by modifying
```cmake
include_directories(/usr/local/Cellar/icu4c/70.1/include)
link_directories(/usr/local/Cellar/icu4c/70.1/lib)
```

To build:
```shell
cd path/to/mathstrad
mkdir output
cmake -S . -B output
cmake --build output --target mathstrad -j 3
```

To run:
```
cd output
./mathstrad
```

## Tests
Clone googletest git repo.

Specify googletest folder in ``tests/CMakeLists.txt`` by modifying
```cmake
add_subdirectory(lib/googletest)
```

### Build tests

Uncomment `enable_testing()` in `CMakeLists.txt`, then rebuild.


### Run tests
```shell
cd output
ctest
```