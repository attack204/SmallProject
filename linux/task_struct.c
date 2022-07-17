struct task_struct
{
    volatile long state; //说明了该进程是否可以执行，还是可中断等信息
    unsigned long flags; // flags 是进程号，在调用fork()时给出
    int sigpending; // 进程上是否有待处理的信号

    mm_segment_t addr_limit;  //进程地址空间,区分内核进程与普通进程在内存存放的位置不同  //0-0xBFFFFFFF for user-thead    //0-0xFFFFFFFF for kernel-thread
    //调度标志,表示该进程是否需要重新调度,若非0,则当从内核态返回到用户态,会发生调度
    volatile long need_resched;
    int lock_depth;    //锁深度
    long nice;       //进程的基本时间片

    //进程的调度策略,有三种,实时进程:SCHED_FIFO,SCHED_RR, 分时进程:SCHED_OTHER
    unsigned long policy;
    struct mm_struct *mm;    //进程内存管理信息

    int processor;
    //若进程不在任何CPU上运行, cpus_runnable 的值是0，否则是1 这个�在运行队列被锁时更新
    unsigned long cpus_runnable, cpus_allowed;
    struct list_head run_list;   //指向运行队列的指针
    unsigned long sleep_time;   //进程的睡眠时间

    //用于将系统中所有的进程连成一个双向循环链表, 其根是init_task
    struct task_struct *next_task, *prev_task;
    struct mm_struct *active_mm;
    struct list_head local_pages;      //指向本地页面
    unsigned int allocation_order, nr_local_pages;
    struct linux_binfmt *binfmt;      //进程所运行的可执行文件的格式
    int exit_code, exit_signal;
    int pdeath_signal;           //父进程终止时向子进程发送的信号
    unsigned long personality;
    //Linux可以运行由其他UNIX操作系统生成的符合iBCS2标准的程序
    int did_exec:1;
    pid_t pid;          //进程标识符,用来代表一个进程
    pid_t pgrp;        //进程组标识,表示进程所属的进程组
    pid_t tty_old_pgrp;      //进程控制终端所在的组标识
    pid_t session;             //进程的会话标识
    pid_t tgid;
    int leader;    //表示进程是否为会话主管
    struct task_struct *p_opptr,*p_pptr,*p_cptr,*p_ysptr,*p_osptr;
    struct list_head thread_group;          //线程链表
    struct task_struct *pidhash_next;    //用于将进程链入HASH表
    struct task_struct **pidhash_pprev;
    wait_queue_head_t wait_chldexit;      //供wait4()使用
    struct completion *vfork_done;         //供vfork() 使用


    unsigned long rt_priority;       //实时优先级，用它计算实时进程调度时的weight值


    //it_real_value，it_real_incr用于REAL定时器，单位为jiffies, 系统根据it_real_value

    //设置定时器的第一个终止时间. 在定时器到期时，向进程发送SIGALRM信号，同时根据

    //it_real_incr重置终止时间，it_prof_value，it_prof_incr用于Profile定时器，单位为jiffies。

    //当进程运行时，不管在何种状态下，每个tick都使it_prof_value值减一，当减到0时，向进程发送

    //信号SIGPROF，并根据it_prof_incr重置时间.
    //it_virt_value，it_virt_value用于Virtual定时器，单位为jiffies。当进程运行时，不管在何种

    //状态下，每个tick都使it_virt_value值减一当减到0时，向进程发送信号SIGVTALRM，根据

    //it_virt_incr重置初值。

    unsigned long it_real_value, it_prof_value, it_virt_value;
    unsigned long it_real_incr, it_prof_incr, it_virt_value;
    struct timer_list real_timer;        //指向实时定时器的指针
    struct tms times;                      //记录进程消耗的时间
    unsigned long start_time;          //进程创建的时间

    //记录进程在每个CPU上所消耗的用户态时间和核心态时间
    long per_cpu_utime[NR_CPUS], per_cpu_stime[NR_CPUS];


    //内存缺页和交换信息:

    //min_flt, maj_flt累计进程的次缺页数（Copy on　Write页和匿名页）和主缺页数（从映射文件或交换

    //设备读入的页面数）； nswap记录进程累计换出的页面数，即写到交换设备上的页面数。
    //cmin_flt, cmaj_flt, cnswap记录本进程为祖先的所有子孙进程的累计次缺页数，主缺页数和换出页面数。

    //在父进程回收终止的子进程时，父进程会将子进程的这些信息累计到自己结构的这些域中
    unsigned long min_flt, maj_flt, nswap, cmin_flt, cmaj_flt, cnswap;
    int swappable:1; //表示进程的虚拟地址空间是否允许换出
    //进程认证信息
    //uid,gid为运行该进程的用户的用户标识符和组标识符，通常是进程创建者的uid，gid

    //euid，egid为有效uid,gid
    //fsuid，fsgid为文件系统uid,gid，这两个ID号通常与有效uid,gid相等，在检查对于文件

    //系统的访问权限时使用他们。
    //suid，sgid为备份uid,gid
    uid_t uid,euid,suid,fsuid;
    gid_t gid,egid,sgid,fsgid;
    int ngroups;                  //记录进程在多少个用户组中
    gid_t groups[NGROUPS];      //记录进程所在的组

    //进程的权能，分别是有效位集合，继承位集合，允许位集合
    kernel_cap_t cap_effective, cap_inheritable, cap_permitted;

    int keep_capabilities:1;
    struct user_struct *user;
    struct rlimit rlim[RLIM_NLIMITS];    //与进程相关的资源限制信息
    unsigned short used_math;         //是否使用FPU
    char comm[16];                      //进程正在运行的可执行文件名
    int link_count, total_link_ count;  //文件系统信息

    //NULL if no tty 进程所在的控制终端，如果不需要控制终端，则该指针为空
    struct tty_struct *tty;
    unsigned int locks;
    //进程间通信信息
    struct sem_undo *semundo;       //进程在信号灯上的所有undo操作
    struct sem_queue *semsleeping;   //当进程因为信号灯操作而挂起时，他在该队列中记录等待的操作
    //进程的CPU状态，切换时，要保存到停止进程的task_struct中
    struct thread_struct thread;
    struct fs_struct *fs;           //文件系统信息
    struct files_struct *files;    //打开文件信息
    spinlock_t sigmask_lock;   //信号处理函数
    struct signal_struct *sig;   //信号处理函数
    sigset_t blocked;                //进程当前要阻塞的信号，每个信号对应一位
    struct sigpending pending;      //进程上是否有待处理的信号
    unsigned long sas_ss_sp;
    size_t sas_ss_size;
    int (*notifier)(void *priv);
    void *notifier_data;
    sigset_t *notifier_mask;
    u32 parent_exec_id;
    u32 self_exec_id;

    spinlock_t alloc_lock;
    void *journal_info;
};
�
