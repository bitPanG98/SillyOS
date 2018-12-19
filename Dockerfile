FROM ubuntu:latest
MAINTAINER GarbageCollections
RUN mkdir -p /workspace
VOLUME /workspace

#Install all the needed package
#clang-7.0 \
#llvm-7.0 \
#lld-7.0 \
RUN apt-get -y update && apt-get -y install \
build-essential \
llvm-toolchain \
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
