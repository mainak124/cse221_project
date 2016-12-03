#include <linux/kernel.h>
#include <linux/module.h>
//#include <linux/smp.h>

int init_module(void)
{
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(0x00000011));
        asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x8000000f));

return 0;
}

