// Uporabi knjižnico libCDio?
// Neki pomembnega je tui IOctl
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

   /* Open the CDROM device. The linux/cdrom.h header file specifies that
   ** it must be given the O_NONBLOCK flag when opening. My tests showed
   ** that if this isn't done, this program will not work.
   *
   ** Under Linux, the O_NONBLOCK flag indicates that one wants to open
   ** but does not necessarily have the intention to read or write.
   ** This is typically used to open devices in order to get a file descriptor
   ** for use with ioctl(2).
   */

   // open() vs fopen() !! open = syscall, fopen = c standardna knjiznica
   /* open() creates or opens a file. It creates a file descriptor (lowest possible)

      int open(const char *pathname, int flags, OPTIONAL: mode_t mode);
        pathname: relative or absolute path to file, "string".
        flags: in wich way you want to open the file. Read, write, both...
        HOW TO OR or PASS flags as function argument
        mode: if creating a new file- what permissions will this file have

        open(pathname: "dev/cdrom" , flags: 00000000 | 00004000)
        KAJ JE TA ZAPIS Z 0 in 4?! int? biti? hex?  ==> OCTAL!
        ZATO KER NAJMANJ PROSTORA PORABIŠ ZA ZASTAVICE!!!
        0_RDONLY in 0_NONBLOCK so definirani v fcntl.h -

   */
   if ((cdrom = open(CDDEVICE,O_RDONLY | O_NONBLOCK)) < 0) {
        perror("open");
        printf("Ne morem odpret naprave!\n");
        // exit(1); zakaj to uporabljat?
        return 1;
   }

/* Use ioctl to send the CDROMEJECT command to the device

   v /usr/include/linux/cdrom.h so definirane komande za CD-rom interface.
   jaz uporabljam eno od cdrom ioctl komand:
        CDROMEJECT		0x5309    Ejects the cdrom media

   vecio operacij lahko izvedes z read, write, lseek. Kar nemores je ponavadi
   odvisno od narave naprave. Da nebi imela vsaka naprava svojih posebnih funkcij
   je to standarizirano preko ioctl funkcije in razlicnih "code numbers"
   za razlicne taske, ki so device specific.

   int ioctl(file_descriptor, command, ...)

   file_descriptor: kateri file/device (glede fd) hoces upravljat
   command: ioctl komanda, ki je device specific. Definirane so v header fajlih
            v mojem primeru cdrom.h. Notri je enkodirana informacija in al out,
            kaj hoces nrdit in kaj naj ti funkcija vrne ipd.

   The kernel generally dispatches an ioctl call straight to the device driver,
   which can interpret the request number and data in whatever way required.
   The writers of each driver document request numbers for that particular driver
   and provide them as constants in a header file.

*/

  struct cdrom_mcn output;


   if (ioctl(cdrom,CDROM_GET_MCN, &output)<0) {
        perror("ioctl");
        printf("Ne morem dobit universal product kode!\n");

        // exit(1); zakaj to uporabljat?
        return 1;
   }
   else printf("Output:\n");


   for (int i = 0; i < 14; i++) {
     printf("%d", output.medium_catalog_number[i]);
     printf(" ");
   }
   printf("\n");

   // zapri, de-alociraj file descriptor
   close(cdrom);
}
