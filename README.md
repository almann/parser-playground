# Parser Playground

A simple package to play around with parser techniques.

## Development

This project uses [`conan`][conan] to manage dependencies.  Some tips:

* [`pyenv`][pyenv]/[`pyenv-virtualenv`][pyenv-virtualenv] is nice to isolate the conan installation on Linux.
  * `pyenv virtualenv conan && pyenv activate conan && pip install -U conan`
  * In the project directory you can use `pyenv local conan` to automatically activate conan.
* Make sure the [GCC C++ ABI settings][conan-gcc-abi] for Conan is set to the latest.
    ```bash
    # Generates default profile detecting GCC and sets old ABI
    $ conan profile new default --detect

    # Sets libcxx to C++11 ABI
    $ conan profile update settings.compiler.libcxx=libstdc++11 default
    ```

Building the project can be done by:

```bash 
$ (mkdir -p build && cd build && conan install .. && cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release && cmake --build .)
```

### CLion

CLion has a handy [plugin][clion-conan] for integrating with `conan`.  You do have to map `conan` profiles to
CLion's CMake profiles.

For simple integration you can add the following profiles to `$HOME/.conan/profiles`

`clion-debug`:
```
include(default)

[settings]
build_type=Debug
```

`clion-release`:

```
include(default)

[settings]
build_type=Release
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

[conan]: https://docs.conan.io/en/latest/
[conan-gcc-abi]: https://docs.conan.io/en/latest/howtos/manage_gcc_abi.html
[clion-conan]: https://blog.jetbrains.com/clion/2019/05/getting-started-with-the-conan-clion-plugin/
[pyenv]: https://github.com/pyenv/pyenv
[pyenv-virtualenv]: https://github.com/pyenv/pyenv-virtualenv
[simdjson-docker]: https://github.com/simdjson/simdjson/blob/master/Dockerfile