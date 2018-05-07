FROM ubuntu:xenial
MAINTAINER GC
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
mtools

WORKDIR /workspace

CMD [ "/bin/bash" ]
