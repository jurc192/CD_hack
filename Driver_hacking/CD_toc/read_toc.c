// Read TOC header of the CD
// Useful info: https://leapster.org/linux/cdrom/

// compile: gcc -o ejector ejector.c
// run: ./ejector

// #include <stdlib.h> za exit()
#include <stdio.h>  // za printf()
#include <unistd.h> // za close() ; POSIX OS API, neki sistemskega
#include <sys/ioctl.h>  // za ioctl()
#include <fcntl.h>  // status flag definitions za open(); O_RDONLY, O_NONBLOCK
#include <linux/cdrom.h>  // za CDrom ioctl definicije ukazov. Uniform -
                          // -interface between software and CD drivers!

#define CDDEVICE "/dev/cdrom"           /* CDROM device */

char * AudioStatusString(__u8 status) {
  switch (status) {
    case CDROM_AUDIO_INVALID:
        return "CDROM_AUDIO_INVALID";
    case CDROM_AUDIO_PLAY:
        return "CDROM_AUDIO_PLAY";
    case CDROM_AUDIO_PAUSED:
        return "CDROM_AUDIO_PAUSED";
    case CDROM_AUDIO_COMPLETED:
        return "CDROM_AUDIO_COMPLETED";
    case CDROM_AUDIO_ERROR:
        return "CDROM_AUDIO_ERROR";
    case CDROM_AUDIO_NO_STATUS:
        return "CDROM_AUDIO_NO_STATUS";
    default:
        return "Unknown status";
  }
}

int main(int argc,char **argv)
{

   int cdrom;                           /* CDROM device file descriptor */

   if ((cdrom = open(CDDEVICE,O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open");
        printf("Ne morem odpret naprave!\n");
        // exit(1); zakaj to uporabljat?
        return 1;
   }


   /* Commands for IOCTL (defined in cdrom.h) */

   // data type returned by ioctl
  struct cdrom_tochdr tocheader;

   if (ioctl(cdrom,CDROMREADTOCHDR, &tocheader)<0) {
        perror("ioctl");
        printf("Can't read TOC header!\n");

        return 1;
   }

   /* Output printing */
   printf("Start track: %d\n", tocheader.cdth_trk0);
   printf("End track: %d\n", tocheader.cdth_trk1);


   struct cdrom_tocentry tocentry;

   // Loop trough all tracks and display their info
   for (int track= tocheader.cdth_trk0; track <= tocheader.cdth_trk1; track++) {

     // To moraš definirat, če hočeš da dela CDROMREADTOCENTRY -alla input parametri
     // cdte_format MSF is minute second frame. Each second is 75 frames - defined in
     // cdrom.h @331
     tocentry.cdte_format = CDROM_MSF;
     tocentry.cdte_track = track;

     if (ioctl(cdrom, CDROMREADTOCENTRY, &tocentry)<0) {
          perror("ioctl");
          printf("Can't read TOC entry!\n");
          return 1;
     }

    //  printf("Track no. %d:\n", track);
    //  printf("Minute-Second-Frame: %d:%d frame %d\n", tocentry.cdte_addr.msf.minute, tocentry.cdte_addr.msf.second, tocentry.cdte_addr.msf.frame);
   }


  /***************************************************************************
  * # Getting subchannel data
  **************************************************************************/

  /* This struct is used by the CDROMSUBCHNL ioctl */
  // struct cdrom_subchnl
  // {
  // 	__u8	cdsc_format;
  // 	__u8	cdsc_audiostatus;
  // 	__u8	cdsc_adr:	4;
  // 	__u8	cdsc_ctrl:	4;
  // 	__u8	cdsc_trk;
  // 	__u8	cdsc_ind;
  // 	union cdrom_addr cdsc_absaddr;
  // 	union cdrom_addr cdsc_reladdr;
  // };

  struct cdrom_subchnl subchannel;

  subchannel.cdsc_format = CDROM_MSF;

  if (ioctl(cdrom,CDROMSUBCHNL, &subchannel)<0) {
       perror("ioctl");
       printf("Can't read subchannel data!\n");

       return 1;
  }

  printf("Track: %d\n", subchannel.cdsc_trk);
  printf("Index: %d\n\n", subchannel.cdsc_ind);

  printf("Absolute address: %d:%d frame %d\n", subchannel.cdsc_absaddr.msf.minute, subchannel.cdsc_absaddr.msf.second, subchannel.cdsc_absaddr.msf.frame);
  printf("Relative address: %d:%d frame %d\n", subchannel.cdsc_reladdr.msf.minute, subchannel.cdsc_reladdr.msf.second, subchannel.cdsc_reladdr.msf.frame);
  printf("Audio status: %s\n", AudioStatusString(subchannel.cdsc_audiostatus));


   // zapri, de-alociraj file descriptor
   close(cdrom);
}
