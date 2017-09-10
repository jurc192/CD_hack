// Read TOC header of the CD
// Useful info: https://leapster.org/linux/cdrom/

// compile: gcc -o ejector ejector.c
// run: ./ejector

#include <stdlib.h>
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

   struct cdrom_read_audio audio;

   audio.addr_format = CDROM_MSF;
   audio.addr.msf.minute=1;
   audio.addr.msf.second=1;
   audio.addr.msf.frame=1;
   audio.nframes = 75;

   // Supposedly this is our audio
   unsigned int buffsize = 2352 * audio.nframes;
   __u8* buffer = (__u8*) malloc(buffsize);
   audio.buf = buffer;

   if (ioctl(cdrom, CDROMREADAUDIO, &audio)<0) {
        perror("ioctl");
        printf("Can't read audio!\n");
        return 1;
   }


   // Write the buffer to a file
   //  size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *a_file);
   FILE* audiofile = fopen("output.wav", "w");

   for (int i= 0; i < buffsize; i++) {
     fputc(buffer[i], audiofile);
   }

   fclose(audiofile);
   // play with aplay cmd util

   // zapri, de-alociraj file descriptor
   close(cdrom);
}
