FROM ubuntu:xenial
MAINTAINER GarbageCollections
RUN mkdir -p /workspace
VOLUME /workspace
#Install all the needed package
RUN apt-get -y update && apt-get -y install build-essential \
nasm \
git \
uuid-dev \
libmpc-dev \
libgmp-dev \
libmpfr-dev \
curl \
python \
python3 \
dosfstools \
mtools \
xorriso

RUN useradd -s /bin/bash dever
USER dever

WORKDIR /workspace

CMD [ "/bin/bash" ]
