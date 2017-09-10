IOCTL: https://stackoverflow.com/questions/15807846/ioctl-linux-device-driver

# SENDING RANDOM STUFF TO IOCTL
- tried to send different commands from cdrom.h
  - CDROM START, CDROMSTOP does something, but nothing
  - CDROM PAUSE -> error; Operation not supported
  - CDROM_GET_MCN reads something. All CDs same number, no CD different number

# TRYING TO READ TOC HEADER
- first we tried CDROMREADTOCHDR and it works (no of tracks)
- display info about each track
https://www.kernel.org/doc/Documentation/ioctl/cdrom.txt useful stuff
- tocentry.cdte_format = ???;
  - najprej probali format LBA - meh
  - probamo še format MSF- Minute-Second-Frame

# TRYING TO PLAY A SONG
- where does it output data?
- trying to use PLAYMSF doesn't work - ioctl: operation not supported
- using PLAYTRKIND - the same

# CAN YOU DISPLAY LIST OF SUPPORTED OPERATIONS?
- probably not

# GETTING OUTPUT OF THE DRIVE
## SUBCHANNEL DATA
https://en.wikipedia.org/wiki/Compact_Disc_subcode
- it works! Reads current track and absolute and relative time.
- if you play a song and run  the command it tells you info about song you played

## READING AUDIO w/ READAUDIO
- it works!
- with CDREADAUDIO you can read the audo from the CD
- write bytes to file and play that data with aplay cmd utility (basic audio player)

# GETTING ONE LEVEL LOWER - DEVICE DRIVER
- https://unix.stackexchange.com/questions/97676/how-to-find-the-driver-module-associated-with-a-device-on-linux
- location /sys/bus/scsi/driver/sr
- got the source from linux (linus torvalds github) kernel
  @[https://github.com/torvalds/linux/blob/master/drivers/cdrom/cdrom.c]

- drawing a diagram what happens from eject.c -> drivers.
- ioctl switch statement is in linux/drivers/cdrom/cdrom.c
- we come to sr.h -> SCSI stuff
