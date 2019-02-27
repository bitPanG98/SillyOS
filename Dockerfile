FROM ubuntu:disco
MAINTAINER GarbageCollections
RUN mkdir -p /workspace
VOLUME /workspace

#Install all the needed package
RUN apt-get -y update && apt-get -y install \
build-essential \
nasm \
git \
curl \
python \
python3 \
uuid-dev \
dosfstools \
mtools \
xorriso \
clang \
lld

RUN useradd -s /bin/bash dever
USER dever

WORKDIR /workspace

ENV PROJECT_ROOT=/workspace
ENV BUILD_DIR=/workspace/Build
ENV PATH="$PWD/CC/bin:$PATH"

CMD [ "/bin/bash" ]
