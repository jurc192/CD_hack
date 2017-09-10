#include <linux/init.h>     // A to res rabiš tukaj?
#include <linux/module.h>   // Rabiš za vsak modul
#include <linux/kernel.h>   // Za KERN_INFO

static int hello(void) {
  printk("Hello mydriver2!\n");
  return 0;
}

static void exitmodule(void) {
  printk("<1> Bye mydriver2!\n");
}


// Start & stop funkcije lahko definiraš (po)svoje in jih kličeš tu:
module_init(hello);
module_exit(exitmodule);

MODULE_LICENSE("GPL");
