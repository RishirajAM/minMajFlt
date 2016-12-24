# minMajFlt
Linux kernel space module to display minor and major faults of all processes.

Demo:
- To compile the module, use "make -C /lib/modules/$(uname -r)/build M=$(pwd) modules".
- To insert the module, use "insmod minMajFlt.ko".
- After inserting the module, an Entry must be created under /proc/proc_test directory.
- Run "cat /proc/proc_test/test > ~/minMajFltList.txt".
- ~/minMajFltList.txt file contains the information extracted by our kernel space module.
- To remove the module, use "rmmod minMajFlt.ko".
