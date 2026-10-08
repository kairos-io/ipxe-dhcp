/*
 * Build configuration for the iPXE binaries this repository publishes.
 *
 * iPXE includes config/local/general.h as the last line of
 * config/general.h, after the per-platform overrides, so a setting here
 * is the final word and survives upstream reformatting of the defaults.
 * The clone in the Earthfile is not pinned, so that matters: the sed this
 * file replaces silently stopped matching when iPXE rewrote
 * config/general.h on 2026-01-16, and the published ISO lost HTTPS.
 *
 * See https://ipxe.org/buildcfg and kairos-io/kairos#5250.
 */

/* iPXE disables HTTPS on pcbios, which is the platform this repository
 * builds (bin/ipxe.iso and bin/ipxe.usb). Turn it back on so the embedded
 * script can chainload from an https:// URL.
 */
#undef DOWNLOAD_PROTO_HTTPS
#define DOWNLOAD_PROTO_HTTPS
