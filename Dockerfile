#
# Building Stage
#

FROM debian:12.7 AS build

RUN apt-get update --fix-missing && \
    apt-get upgrade -y && \
    apt-get install -yq tzdata && \
    ln -fs /usr/share/zoneinfo/America/Sao_Paulo /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

RUN apt-get install -yq \
    curl git zip unzip tar \
    pkg-config make cmake \
    clang clangd clang-format

COPY . .

RUN make clean && make configure && make build && make install

#
# Deployment Stage
#

FROM gcr.io/distroless/static-debian12:debug

COPY --from=build /out/build/debug/engine/tupa_engine /usr/local/bin
