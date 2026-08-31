> **Found a bug, or want to request a feature?** Open it on
> [kairos-io/kairos](https://github.com/kairos-io/kairos/issues), including
> issues about this repository. Every Kairos issue lives in one place, so you
> never have to work out which repository to file against.

This repository is used to build a generic ipxe iso image that boot from dhcp.

For example, when a [pixiecore instance](https://github.com/danderson/netboot/tree/master/pixiecore) is running on the same network, this iso
will get the boot files from it.

This iso is built using the ipxe script from the pixiecore project:

https://github.com/danderson/netboot/blob/master/pixiecore/boot.ipxe
