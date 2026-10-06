VERSION 0.6

version:
    FROM alpine
    RUN apk add git

    COPY . ./

    RUN echo $(git describe --exact-match --tags || echo "v0.0.0-$(git log --oneline -n 1 | cut -d" " -f1)") > VERSION

    SAVE ARTIFACT VERSION VERSION

iso:
    FROM ubuntu
    COPY . /build
    ARG ISO_NAME=ipxe-dhcp

    RUN apt update
    RUN apt install -y -o Acquire::Retries=50 \
                           mtools syslinux isolinux gcc-arm-none-eabi git make gcc liblzma-dev mkisofs xorriso
                           # jq docker
    WORKDIR /build
    ARG ISO_NAME=ipxe-dhcp
    COPY +version/VERSION ./
    ARG VERSION=$(cat VERSION)

    RUN git clone https://github.com/ipxe/ipxe

    COPY ipxe-config/general.h ipxe/src/config/local/general.h

    RUN cd ipxe/src && make EMBED=/build/boot.ipxe
    SAVE ARTIFACT /build/ipxe/src/bin/ipxe.iso iso AS LOCAL build/${ISO_NAME}.iso
    SAVE ARTIFACT /build/ipxe/src/bin/ipxe.usb usb AS LOCAL build/${ISO_NAME}-usb.img
