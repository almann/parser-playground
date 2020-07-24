# Parser Playground

A simple package to play around with parser techniques, especially around SIMD and
other platform specific intrinsics.  Also a place to experiment with decoding techniques
using labels as values (i.e. computed goto).

## Development

This project uses submodules to manage its dependencies.  If you did not do a recursive
clone, you can initialize the submodules:

```bash
$ git submodule init
$ git submodule update
```

Building the project can be done by:

```bash 
$ (mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . -- -j$(nproc))
```

## Docker

A `Dockerfile` is provided to make it easier to do repeatable builds.  This is heavily derived by
`simdjson`'s [`Dockerfile`][simdjson-docker].

```bash
# build the image
$ docker build -t parser_playground \
  --build-arg USER_ID=$(id -u) \
  --build-arg GROUP_ID=$(id -g) \
  $(pwd)

# run the build in a container using the image
$ docker run --interactive --tty --rm \
  --mount type=bind,source="$(pwd)",target=/workspace \
  parser_playground
```

## Additional References

* [SIMD Notes][simd-notes] - some of my notes around SIMD algorithms.

[simdjson-docker]: https://github.com/simdjson/simdjson/blob/master/Dockerfile
[simd-notes]: SIMD-NOTES.md