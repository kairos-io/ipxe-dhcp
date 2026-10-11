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

    # The clone is pinned so that a build of this commit always produces the
    # same binaries, and so that a change upstream cannot alter the published
    # image without a commit here. iPXE rewrote src/config/general.h on
    # 2026-01-16 and the published image silently lost HTTPS support, which is
    # kairos-io/kairos#5250. Renovate bumps IPXE_REF through the custom manager
    # in renovate.json.
    # renovate: datasource=git-refs depName=https://github.com/ipxe/ipxe
    ARG IPXE_REF=c86730a30547823e73a363d903a1510a4664a9b1

    RUN git clone https://github.com/ipxe/ipxe && \
        git -C ipxe checkout --detach "${IPXE_REF}"

    COPY ipxe-config/general.h ipxe/src/config/local/general.h

    RUN cd ipxe/src && make EMBED=/build/boot.ipxe
    SAVE ARTIFACT /build/ipxe/src/bin/ipxe.iso iso AS LOCAL build/${ISO_NAME}.iso
    SAVE ARTIFACT /build/ipxe/src/bin/ipxe.usb usb AS LOCAL build/${ISO_NAME}-usb.img
