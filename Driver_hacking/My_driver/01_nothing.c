#include <linux/module.h>   // Rabiš za vsak modul
#include <linux/kernel.h>   // Za KERN_INFO

/* Vsak modul mora imeti start funkcijo (init_module).
Ta se izvede, ko vstaviš modul v kernel z insmod */
int init_module(void)
{
  printk(KERN_INFO "Hello world! \n");
  return 0;
}


/* In vsak modul rabi stop funkcijo (cleanup_module).
Ta se izvede preden se modul odstrani z rmmod */
void cleanup_module(void)
{
  printk(KERN_INFO "Goodbye world\n");
}
