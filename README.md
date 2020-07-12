# Parser Playground

A simple package to play around with parser techniques.

## Development

* [`zlib`][zlib] and its headers need to be available on the system.

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
$ docker run --interactive --tty --rm --mount type=bind,source="$(pwd)",target=/workspace parser_playground
```

[zlib]: https://zlib.net/
[simdjson-docker]: https://github.com/simdjson/simdjson/blob/master/Dockerfile