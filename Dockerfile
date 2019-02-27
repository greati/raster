FROM alpine:3.9

RUN apk update && \
    apk upgrade && \
    apk add --no-cache \
    g++ \
    make \
    git \
    cmake > 3.13.0

RUN mkdir /source /build
ADD ./sources /sources
WORKDIR build 
RUN cmake /sources && cmake --build .


