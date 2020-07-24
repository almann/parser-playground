# Inspired by https://github.com/simdjson/simdjson/blob/master/Dockerfile

FROM ubuntu:20.04

ARG USER_ID
ARG GROUP_ID
ARG WORKSPACE_DIR=/workspace
ARG DOCKERBUILD_DIR=docker-build

RUN apt-get update -qq
RUN DEBIAN_FRONTEND="noninteractive" apt-get -y install tzdata
RUN apt-get -y install g++ cmake ninja-build git

# These sparse files do not behave well for large UIDs
RUN rm /var/log/faillog /var/log/lastlog

# Let's not run as root
RUN addgroup --gid $GROUP_ID user; exit 0
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user; exit 0
RUN mkdir $WORKSPACE_DIR && chown $USER_ID.$GROUP_ID $WORKSPACE_DIR

USER user
WORKDIR $WORKSPACE_DIR

CMD rm -fr docker-build && \
    mkdir -p docker-build && \
    cd docker-build && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . && \
    ./bin/parser_playground && \
    ./bin/parser_playground "[!benchmark]"
