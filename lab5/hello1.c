// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Ryabokon Varya");
MODULE_DESCRIPTION("Lab 5 - Hello1");
MODULE_LICENSE("Dual BSD/GPL");

struct event_list {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(event_list_head);

void print_hello(void)
{
	struct event_list *element = kmalloc(sizeof(struct event_list), GFP_KERNEL);
	if (!element)
		return;

	element->start_time = ktime_get();
	pr_info("Hello, World!\n");
	element->end_time = ktime_get();

	list_add_tail(&element->list, &event_list_head);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct event_list *md, *tmp;

	list_for_each_entry_safe(md, tmp, &event_list_head, list) {
		pr_info("Time elapsed: %lld ns\n", ktime_to_ns(ktime_sub(md->end_time, md->start_time)));
		list_del(&md->list);
		kfree(md);
	}
}

module_exit(hello1_exit);

