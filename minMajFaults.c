#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/slab.h>
#include<linux/seq_file.h>
#include<linux/sched.h>

static struct proc_dir_entry *entry=NULL;
static struct proc_dir_entry *dir=NULL;


static void *process_seq_start(struct seq_file *file, loff_t *pos)
{
	loff_t off = 0;
	struct task_struct *t;
	//dump_stack();
	printk(KERN_INFO "%s\n", __func__);
	for_each_process(t)
	{
		if (*pos == off++) 
		{
                        printk("%s: Success %d\n",__func__,*(int *)pos);
                        return t;
    		}
	}
	printk("%s: Complete\n", __func__);
	return NULL;
}

static void *process_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
  struct task_struct *t=next_task((struct task_struct *)v);
  
  //dump_stack();
  printk(KERN_INFO "%s\n", __func__);
  
  ++*pos;
  
  if(t==&init_task)
	return NULL;
  else
	return t;
}

static int process_seq_show(struct seq_file *file, void *v)
{
   static int i=1;
   int ret;
   struct task_struct  *t =v;

   //dump_stack();
   printk(KERN_INFO "%s\n", __func__);

   ret = seq_printf(file,"%d) Name: %s [PID:%d] :\n", i++, t->comm, t->pid);
   ret = seq_printf(file, "\tMinor Fault(s): %lu\n\tMajor Fault(s): %lu\n\n", t->min_flt, t->maj_flt);

   return ret;
}

static void process_seq_stop(struct seq_file *file, void *v)
{
	//dump_stack();
	printk(KERN_INFO "%s\n", __func__);
}

static struct seq_operations process_seq_ops = {
   .start = process_seq_start,
   .next   = process_seq_next,
   .stop   = process_seq_stop,
   .show   = process_seq_show,
};

static int process_seq_open(struct inode *inode, struct file *file)
{
	//dump_stack();
	printk(KERN_INFO "%s\n", __func__);
	return seq_open(file, &process_seq_ops);
}


static struct file_operations process_proc_fops ={
	.owner= THIS_MODULE,
	.open= process_seq_open,
	.read= seq_read,
	.llseek= seq_lseek,
	.release= seq_release,
};



static int __init process_init(void)
{
	dir=proc_mkdir("proc_test", NULL);
	
	printk(KERN_INFO "Hello world!");
	printk(KERN_INFO "%s\n", __func__);
	
	entry=create_proc_entry("test", S_IRUSR, dir);
	if(entry)
	{
		entry->proc_fops=&process_proc_fops;
		printk(KERN_INFO "Proc entry in /proc/proc_test/test added!!!");
	}
	else
		return -EINVAL;
	
	return 0;
}

static void __exit process_exit(void)
{
   dump_stack();
   printk(KERN_INFO "%s\n", __func__);
   
   remove_proc_entry("test", dir);
   remove_proc_entry("proc_test", NULL);
   
   printk(KERN_INFO "Bye bye cruel world!");
}

module_init(process_init);
module_exit(process_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Rishiraj Manwatkar | manwatkar.r@gmail.com");
