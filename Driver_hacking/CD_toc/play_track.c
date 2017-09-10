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


   struct cdrom_ti track;

  track.cdti_trk0 = 1;	/* start track */
	track.cdti_ind0 = 1;	/* start index */
	track.cdti_trk1 = 2;	/* end track */
  track.cdti_ind1 = 0; /* end index */

   if (ioctl(cdrom,CDROMPLAYTRKIND, &track)<0) {
        perror("ioctl");
        printf("Can't play track!\n");
        return 1;
   }

   // zapri, de-alociraj file descriptor
   close(cdrom);
}
