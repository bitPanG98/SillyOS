FROM ubuntu:xenial
MAINTAINER GarbageCollections
RUN mkdir -p /workspace
VOLUME /workspace

#Install all the needed package
RUN apt-get -y update && apt-get -y install \
build-essential \
clang-6.0 \
llvm-6.0 \
lld-6.0 \
nasm \
git \
curl \
python \
python3 \
uuid-dev \
dosfstools \
mtools \
xorriso

RUN useradd -s /bin/bash dever
USER dever

WORKDIR /workspace

ENV PROJECT_ROOT=/workspace
ENV BUILD_DIR=/workspace/Build
ENV PATH="$PWD/CC/bin:$PATH"

CMD [ "/bin/bash" ]
