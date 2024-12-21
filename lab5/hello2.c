// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <hello1.h>

MODULE_AUTHOR("Ryabokon Varya");
MODULE_DESCRIPTION("Lab 5 - Hello2");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int greets = 1;
module_param(greets, uint, 0444);
MODULE_PARM_DESC(greets, "Ammount of times 'Hello, World!' will be printed in console");

extern void print_hello(void);

static int __init hello2_init(void)
{
	int i;

	if (greets == 0 || (greets >= 5 && greets <= 10))
		pr_warn("'greets' is either 0 or in range 5-10\n");

	if (greets > 10) {
		pr_err("'greets' can`t be larger then 10\n");
		return -EINVAL;
	}

	for (i = 0; i < greets; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Module hello2 unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

