#include <linux/module.h>
#include <linux/kernel.h>

int disable_cache(void) {
	uint32_t x;
	asm volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (x));
	x &= 0xfffffffb;
	asm volatile ("mcr p15, 0, %0, c1, c0, 0" :: "r" (x));
	printk (KERN_INFO "L1 data and L2 cache have been turned off.\n");
	return 0;
}

int enable_cache(void) {
	uint32_t x;
	asm volatile ("mrc p15, 0, %0, c1, c0, 0" : "=r" (x));
	x |= 0x4;
	asm volatile ("mcr p15, 0, %0, c1, c0, 0" :: "r" (x));
	printk (KERN_INFO "L1 data and L2 cache have been turned on.\n");
	return 0;
}

MODULE_AUTHOR("Wizards of OS");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Enables user-mode access to ARMv7 PMU counters");
MODULE_VERSION("0:0.1-dev");
module_init(disable_cache);
module_exit(enable_cache);
