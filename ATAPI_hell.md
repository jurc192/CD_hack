IOCTL: https://stackoverflow.com/questions/15807846/ioctl-linux-device-driver

# SENDING RANDOM STUFF TO IOCTL
- tried to send different commands from cdrom.h
  - CDROM START, CDROMSTOP does something, but nothing
  - CDROM PAUSE -> error; Operation not supported
  - CDROM_GET_MCN reads something. All CDs same number, no CD different number

# TRYING TO READ TOC HEADER
