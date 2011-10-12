#include "ppc_linux_os.hpp"
#include "ppc_syscall.hpp"
#include "ppc_processor.hpp"

namespace simsoc{

  const uint32_t PPC_LinuxOS::USER_STACK_LIMIT = 8 * 1024 * 1024;

  /** Constructor. */
  PPC_LinuxOS::PPC_LinuxOS(const char *name, PPC_Processor *_proc) :
    Module(name),
    proc(_proc),
    endianess(E_BIG_ENDIAN),
    memory_page_size(4096),
    current_system_call(0) {

    // Not thread safe
    // Test to be sure that only this instance will init mem-related
    // static variables. This is because I don't know if the code
    // inside this constructor will be called before
    // ClientIndependentSetup.
    if (! init_inst || init_inst == this)
      {
        init_inst = this;

        //mmap_base = 0xd4000000;
        mmap_base = 0x40000000;
        // Put this arbitrary value for 'mmap_end' because I don't
        // know what is the proper one. If you know so, please feel
        // free to change it!
        //mmap_end  = 0xefffffff;
        mmap_end  = 0x48000000;

        // INFO: There is currently a potential problem with the
        // allocated range for mmap. At the moment, there is no
        // check at all concerning the space allocated for the stack
        // (and, in particular, thread stacks). It may happen that
        // the address area used by some stacks is in the mmap
        // range, which will lead to serious problems. One solution
        // for this would be that those stacks are allocated
        // directly from the 'mmap' range.

#ifdef UNISIM_STL_CONTAINERS
        stl_containers_base = 0x30000000;
        stl_containers_size = 0x10000000;
#endif
      }
    linux_os = new PPC_SystemCall("PPC_SysCall",this);

    // Set the system calls mappings
    linux_os->SetSyscallId(string("exit"), 1);
    linux_os->SetSyscallId(string("read"), 3);
    linux_os->SetSyscallId(string("write"), 4);
    linux_os->SetSyscallId(string("open"), 5);
    linux_os->SetSyscallId(string("close"), 6);
    linux_os->SetSyscallId(string("unlink"), 10);
    linux_os->SetSyscallId(string("time"), 13);
    linux_os->SetSyscallId(string("lseek"), 19);
    linux_os->SetSyscallId(string("getpid"), 20);
    linux_os->SetSyscallId(string("getuid"), 24);
    linux_os->SetSyscallId(string("access"), 33);
    linux_os->SetSyscallId(string("kill"), 37);
    linux_os->SetSyscallId(string("rename"), 38);
    //tim
    linux_os->SetSyscallId(string("mkdir"), 39);
    //eotim
    //STF
    linux_os->SetSyscallId(string("rmdir"), 40);
    //EOSTF
    linux_os->SetSyscallId(string("dup"), 41);
    linux_os->SetSyscallId(string("times"), 43);
    linux_os->SetSyscallId(string("brk"), 45);
    linux_os->SetSyscallId(string("getgid"), 47);
    linux_os->SetSyscallId(string("geteuid"), 49);
    linux_os->SetSyscallId(string("getegid"), 50);
    linux_os->SetSyscallId(string("ioctl"), 54);
    linux_os->SetSyscallId(string("umask"), 60);
    linux_os->SetSyscallId(string("setrlimit"), 75);
    linux_os->SetSyscallId(string("getrlimit"), 76);
    linux_os->SetSyscallId(string("getrusage"), 77);
    //STF
    linux_os->SetSyscallId(string("gettimeofday"), 78);
    //EOSTF
    linux_os->SetSyscallId(string("mmap"), 90);
    linux_os->SetSyscallId(string("munmap"), 91);
    linux_os->SetSyscallId(string("truncate"), 92);
    linux_os->SetSyscallId(string("ftruncate"), 93);

#ifdef UNISIM_STL_CONTAINERS
    linux_os->SetSyscallId(string("unisim_malloc"), 95);
    linux_os->SetSyscallId(string("unisim_free"), 96);
    linux_os->SetSyscallId(string("unisim_realloc"), 97);
#endif

    linux_os->SetSyscallId(string("socketcall"), 102);
    linux_os->SetSyscallId(string("stat"), 106);
    linux_os->SetSyscallId(string("fstat"), 108);
    linux_os->SetSyscallId(string("uname"), 122);
    linux_os->SetSyscallId(string("mprotect"), 125);
    linux_os->SetSyscallId(string("llseek"), 140);
    linux_os->SetSyscallId(string("writev"), 146);
    //STF
    linux_os->SetSyscallId(string("pipe"), 42);
    linux_os->SetSyscallId(string("sysctl"), 149);
    //    linux_os->SetSyscallId(string("clone"), 120);
    linux_os->SetSyscallId(string("rt_sigqueueinfo"), 177);
    //EOSTF
    linux_os->SetSyscallId(string("rt_sigaction"), 173);
    linux_os->SetSyscallId(string("rt_sigprocmask"), 174);
    //tim
    linux_os->SetSyscallId(string("chown"), 181);
    //eotim
    linux_os->SetSyscallId(string("getcwd"),182);
    linux_os->SetSyscallId(string("ugetrlimit"), 190);
    linux_os->SetSyscallId(string("mmap2"), 192);
    //tim
    linux_os->SetSyscallId(string("stat64"), 195);
    //eotim
    linux_os->SetSyscallId(string("fstat64"), 197);
    //    linux_os->SetSyscallId(string("getuid32"), 199);
    //   linux_os->SetSyscallId(string("getgid32"), 200);
    //    linux_os->SetSyscallId(string("geteuid32"), 201);
    //    linux_os->SetSyscallId(string("getegid32"), 202);
    linux_os->SetSyscallId(string("fcntl64"), 204);
    linux_os->SetSyscallId(string("flistxattr"), 217);
    linux_os->SetSyscallId(string("futex"),221);
    linux_os->SetSyscallId(string("exit_group"), 234);
#if 0
    //
    // Pseudo syscalls
    //

    // Pthread syscalls (between 1000 and 1050 at the moment)

    linux_os->SetSyscallId(string("pthread_create"), SYSCALL_PTHREAD_CREATE);
    linux_os->SetSyscallId(string("pthread_exit"), SYSCALL_PTHREAD_EXIT);
    linux_os->SetSyscallId(string("pthread_join1"), SYSCALL_PTHREAD_JOIN1);
    linux_os->SetSyscallId(string("pthread_join2"), SYSCALL_PTHREAD_JOIN2);
    linux_os->SetSyscallId(string("pthread_self"), SYSCALL_PTHREAD_SELF);

    linux_os->SetSyscallId(string("pthread_mutex_init"), SYSCALL_PTHREAD_MUTEX_INIT);
    linux_os->SetSyscallId(string("pthread_mutex_destroy"), SYSCALL_PTHREAD_MUTEX_DESTROY);
    linux_os->SetSyscallId(string("pthread_mutex_lock"), SYSCALL_PTHREAD_MUTEX_LOCK);
    linux_os->SetSyscallId(string("pthread_mutex_trylock"), SYSCALL_PTHREAD_MUTEX_TRYLOCK);
    linux_os->SetSyscallId(string("pthread_mutex_unlock"), SYSCALL_PTHREAD_MUTEX_UNLOCK);

    linux_os->SetSyscallId(string("pthread_spin_init"), SYSCALL_PTHREAD_SPIN_INIT);
    linux_os->SetSyscallId(string("pthread_spin_destroy"), SYSCALL_PTHREAD_SPIN_DESTROY);
    linux_os->SetSyscallId(string("pthread_spin_trylock"), SYSCALL_PTHREAD_SPIN_TRYLOCK);
    linux_os->SetSyscallId(string("pthread_spin_unlock"), SYSCALL_PTHREAD_SPIN_UNLOCK);

    linux_os->SetSyscallId(string("pthread_cond_init"), SYSCALL_PTHREAD_CONDVAR_INIT);
    linux_os->SetSyscallId(string("pthread_cond_destroy"), SYSCALL_PTHREAD_CONDVAR_DESTROY);
    linux_os->SetSyscallId(string("pthread_cond_wait"), SYSCALL_PTHREAD_CONDVAR_WAIT);
    linux_os->SetSyscallId(string("pthread_cond_signal"), SYSCALL_PTHREAD_CONDVAR_SIGNAL);

    linux_os->SetSyscallId(string("pthread_key_create"), SYSCALL_PTHREAD_KEY_CREATE);
    linux_os->SetSyscallId(string("pthread_key_delete"), SYSCALL_PTHREAD_KEY_DELETE);
    linux_os->SetSyscallId(string("pthread_getspecific"), SYSCALL_PTHREAD_GETSPECIFIC);
    linux_os->SetSyscallId(string("pthread_setspecific"), SYSCALL_PTHREAD_SETSPECIFIC);
    linux_os->SetSyscallId(string("pthread_key_getdtor"), SYSCALL_PTHREAD_KEY_GETDTOR);

#ifdef CAPSULE
    linux_os->SetSyscallId(string("capsys_split"), SYSCALL_CAP_SPLIT);
    linux_os->SetSyscallId(string("capsys_divide"), SYSCALL_CAP_DIVIDE);
    linux_os->SetSyscallId(string("capsys_execute"), SYSCALL_CAP_EXECUTE);
    linux_os->SetSyscallId(string("capsys_exit"), SYSCALL_CAP_EXIT);
    linux_os->SetSyscallId(string("capsys_join"), SYSCALL_CAP_JOIN);
    linux_os->SetSyscallId(string("capsys_get_proc_id"), SYSCALL_CAP_GET_PROC);
    linux_os->SetSyscallId(string("capsys_thread_wakeup"), SYSCALL_CAP_THREAD_WAKEUP);
    linux_os->SetSyscallId(string("capsys_get_proc_state"), SYSCALL_CAP_GET_STATE);
    linux_os->SetSyscallId(string("capsys_set_proc_state"), SYSCALL_CAP_SET_STATE);
    linux_os->SetSyscallId(string("capsys_get_probing_proc_id"), SYSCALL_CAP_GET_PROBING_PROC);
    linux_os->SetSyscallId(string("capsys_get_available_thread"), SYSCALL_CAP_GET_AVAILABLE_THREAD);
#endif
#ifdef NOC_SUPPORT_PARALLELIZATION
#endif
#ifdef NOC_SUPPORT_PARALLELIZATION
    linux_os->SetSyscallId(string("npthread_create"), SYSCALL_NPTHREAD_CREATE);
    linux_os->SetSyscallId(string("npthread_execute"), SYSCALL_NPTHREAD_EXECUTE);
    linux_os->SetSyscallId(string("pthread_join"), SYSCALL_PTHREAD_JOIN);
#endif

    // Print syscalls

    linux_os->SetSyscallId(string("syscall_print_str"), 2000);
    linux_os->SetSyscallId(string("syscall_print_int"), 2001);
    linux_os->SetSyscallId(string("syscall_print"), 2002);
    linux_os->SetSyscallId(string("syscall_print_array"), 2003);

    // TimingEvent Syscalls
    linux_os->SetSyscallId(string("timingevent"), SYSCALL_TIMINGEVENT);
    linux_os->SetSyscallId(string("timingevent_start"), SYSCALL_TIMINGEVENT_START);
    linux_os->SetSyscallId(string("timingevent_stop"), SYSCALL_TIMINGEVENT_STOP);
    linux_os->SetSyscallId(string("timingevent_wave"), SYSCALL_TIMINGEVENT_WAVE);
    linux_os->SetSyscallId(string("output_dsp"), SYSCALL_OUTPUT_DSP);
    linux_os->SetSyscallId(string("fast_timingevent"), SYSCALL_FAST_TIMINGEVENT);

    linux_os->SetSyscallId(string("bin_dump_init"), SYSCALL_BIN_DUMP_INIT);
    linux_os->SetSyscallId(string("bin_dump_write"), SYSCALL_BIN_DUMP_WRITE);
    linux_os->SetSyscallId(string("bin_dump_close"), SYSCALL_BIN_DUMP_CLOSE);
#endif
  }

  /** Destructor. */
  PPC_LinuxOS::~PPC_LinuxOS() {
  }

  void PPC_LinuxOS::start_of_simulation(){
    // Set brk_point
    brk_start = main_context().get_elf_brk();

    brk_start = brk_start +
      (TranslationPage::TR_PAGE_SIZE - (brk_start % TranslationPage::TR_PAGE_SIZE));

    brk_point = brk_start;

    info() << ": initial brk point at " << hex << brk_point << dec << endl;
  }

  /**
   * Request to LinuxOS to execute the current system call. */
  void PPC_LinuxOS::ExecuteSystemCall(int id) {
    current_system_call = id;
    linux_os->ExecuteSystemCall();
  }


  void PPC_LinuxOS::my_print_bin_stat(struct powerpc_stat_t *st){
    char *c = (char *)st;
    unsigned int k=0,i,j;
    for(i=0; i< sizeof(powerpc_stat_t); i++){
      unsigned int j=*c;
      printf("\e[1;31m%02x\e[0m ",j & 0xFF);
      c++;
      k=(k+1)%4;
      if(k==0) printf("\n");
    }
    printf("\n");
    fflush(stdout);
  }

  //STF
  /**
   * \brief Convert the native "tms" structure to the target architecture struct
   */
  void* PPC_LinuxOS::ConvertTime(struct timeval *tv)
  { struct powerpc_timespec_t *res;
    res = (powerpc_timespec_t *) malloc(sizeof(powerpc_timespec_t));
    bzero(res,sizeof(powerpc_timespec_t));
    if(GetEndianess() == E_BIG_ENDIAN)
      { res->tv_sec = Host2BigEndian((uint32_t)tv->tv_sec);
        res->tv_nsec = Host2BigEndian((uint32_t)tv->tv_usec);
      }
    else
      { res->tv_sec = Host2LittleEndian((uint32_t)tv->tv_sec);
        res->tv_nsec = Host2LittleEndian((uint32_t)tv->tv_usec);
      }
    return (void*)res;
  }
  //EOSTF

  /**
   * \brief Convert the native "stat" structure to the target architecture struct
   */
  void *  PPC_LinuxOS::ConvertStat(struct stat *s) {
      struct powerpc_stat_t *res;
      res = (powerpc_stat_t *)malloc(sizeof(powerpc_stat_t));
      bzero(res,sizeof(powerpc_stat_t));

      if(GetEndianess() == E_BIG_ENDIAN) {
      /*
        res->st_dev = 0x123456789ABCDEF0ULL;
        res->st_ino = 0x24683579;
      */
      res->st_dev = Host2BigEndian((uint32_t)s->st_dev);
      res->st_ino = Host2BigEndian((uint32_t)s->st_ino);
      res->st_mode = Host2BigEndian((uint32_t)s->st_mode);
      res->st_nlink = Host2BigEndian((uint32_t)s->st_nlink);
      res->st_uid = Host2BigEndian((uint32_t)s->st_uid);
      res->st_gid = Host2BigEndian((uint32_t)s->st_gid);
      res->st_rdev = Host2BigEndian((int32_t)s->st_rdev);
      //        res->__pad2 = Host2BigEndian((uint16_t)s->__pad2);
      res->st_size = Host2BigEndian((int32_t)s->st_size);
      res->st_blksize = Host2BigEndian((int32_t)s->st_blksize);
      res->st_blocks = Host2BigEndian((int32_t)s->st_blocks);
#ifdef __linux__
      // Linux names are not really intuitive here
      res->st_atim.tv_sec = Host2BigEndian((int32_t)s->st_atim.tv_sec);
      res->st_atim.tv_nsec = Host2BigEndian((int32_t)s->st_atim.tv_nsec);
      res->st_mtim.tv_sec = Host2BigEndian((int32_t)s->st_mtim.tv_sec);
      res->st_mtim.tv_nsec = Host2BigEndian((int32_t)s->st_mtim.tv_nsec);
      res->st_ctim.tv_sec = Host2BigEndian((int32_t)s->st_ctim.tv_sec);
      res->st_ctim.tv_nsec = Host2BigEndian((int32_t)s->st_ctim.tv_nsec);
#else
      res->st_atim.tv_sec = Host2BigEndian((int32_t)s->st_atimespec.tv_sec);
      res->st_atim.tv_nsec = Host2BigEndian((int32_t)s->st_atimespec.tv_nsec);
      res->st_mtim.tv_sec = Host2BigEndian((int32_t)s->st_mtimespec.tv_sec);
      res->st_mtim.tv_nsec = Host2BigEndian((int32_t)s->st_mtimespec.tv_nsec);
      res->st_ctim.tv_sec = Host2BigEndian((int32_t)s->st_ctimespec.tv_sec);
      res->st_ctim.tv_nsec = Host2BigEndian((int32_t)s->st_ctimespec.tv_nsec);
#endif
    } else {
      res->st_dev = Host2LittleEndian((uint64_t)s->st_dev);
      res->st_ino = Host2LittleEndian((uint32_t)s->st_ino);
      res->st_mode = Host2LittleEndian((uint32_t)s->st_mode);
      res->st_nlink = Host2LittleEndian((uint32_t)s->st_nlink);
      res->st_uid = Host2LittleEndian((uint32_t)s->st_uid);
      res->st_gid = Host2LittleEndian((uint32_t)s->st_gid);
      res->st_rdev = Host2LittleEndian((int64_t)s->st_rdev);
      //        res->__pad2 = Host2LittleEndian((uint16_t)s->__pad2);
      res->st_size = Host2LittleEndian((int64_t)s->st_size);
      res->st_blksize = Host2LittleEndian((int32_t)s->st_blksize);
      res->st_blocks = Host2LittleEndian((int64_t)s->st_blocks);
#ifdef __linux__
      // Linux names are not really intuitive here
      res->st_atim.tv_sec = Host2LittleEndian((int32_t)s->st_atim.tv_sec);
      res->st_atim.tv_nsec = Host2LittleEndian((int32_t)s->st_atim.tv_nsec);
      res->st_mtim.tv_sec = Host2LittleEndian((int32_t)s->st_mtim.tv_sec);
      res->st_mtim.tv_nsec = Host2LittleEndian((int32_t)s->st_mtim.tv_nsec);
      res->st_ctim.tv_sec = Host2LittleEndian((int32_t)s->st_ctim.tv_sec);
      res->st_ctim.tv_nsec = Host2LittleEndian((int32_t)s->st_ctim.tv_nsec);
#else
      res->st_atim.tv_sec = Host2LittleEndian((int32_t)s->st_atimespec.tv_sec);
      res->st_atim.tv_nsec = Host2LittleEndian((int32_t)s->st_atimespec.tv_nsec);
      res->st_mtim.tv_sec = Host2LittleEndian((int32_t)s->st_mtimespec.tv_sec);
      res->st_mtim.tv_nsec = Host2LittleEndian((int32_t)s->st_mtimespec.tv_nsec);
      res->st_ctim.tv_sec = Host2LittleEndian((int32_t)s->st_ctimespec.tv_sec);
      res->st_ctim.tv_nsec = Host2LittleEndian((int32_t)s->st_ctimespec.tv_nsec);
#endif
    }
    res->__unused4 = 0;
    res->__unused5 = 0;

    //my_print_bin_stat(res);

    return (void *)res;
  }

  /**
   * \brief Return the size of the "stat" struct on target architecture
   */
  unsigned int PPC_LinuxOS::StatSize() {
    return sizeof(powerpc_stat_t);
  }
  //STF
  /**
   * \brief Return the size of the "timespec" struct on target architecture
   */
  unsigned int PPC_LinuxOS::TimeSize() {
    return sizeof(powerpc_timespec_t);
  }
  //EOSTF

  /**
   * \brief Convert the native "stat64" structure to the target architecture struct
   */
  void *
#ifdef __linux__
  PPC_LinuxOS::ConvertStat64(struct stat64 *s)
#elif defined (__APPLE__)
  PPC_LinuxOS::ConvertStat64(struct stat64 *s)
#elif defined (__FreeBSD__)
    PPC_LinuxOS::ConvertStat64(struct stat *s)
#else
#error You have to tell how to deal with ConvertStat64 with your OS.
#endif
  {
    // this implementation supposes that the host is a x86 with __USE_LARGEFILE64
    //   and __USE_MISC

    struct powerpc_stat64_t *res;

    res = (powerpc_stat64_t *)malloc(sizeof(powerpc_stat64_t));
    if(GetEndianess() == E_BIG_ENDIAN) {
      res->st_dev = Host2BigEndian((uint64_t)s->st_dev);
      res->st_ino = Host2BigEndian((uint64_t)s->st_ino);
      res->st_mode = Host2BigEndian((uint32_t)s->st_mode);
      res->st_nlink = Host2BigEndian((uint32_t)s->st_nlink);
      res->st_uid = Host2BigEndian((uint32_t)s->st_uid);
      res->st_gid = Host2BigEndian((uint32_t)s->st_gid);
      res->st_rdev = Host2BigEndian((int64_t)s->st_rdev);
      //res->__pad2 = Host2BigEndian((uint16_t)s->__pad2);
      res->st_size = Host2BigEndian((int64_t)s->st_size);
      res->st_blksize = Host2BigEndian((int32_t)s->st_blksize);
      res->st_blocks = Host2BigEndian((int64_t)s->st_blocks);
#ifdef __linux__
      res->st_atim.tv_sec = Host2BigEndian((int32_t)s->st_atim.tv_sec);
      res->st_atim.tv_nsec = Host2BigEndian((int32_t)s->st_atim.tv_nsec);
      res->st_mtim.tv_sec = Host2BigEndian((int32_t)s->st_mtim.tv_sec);
      res->st_mtim.tv_nsec = Host2BigEndian((int32_t)s->st_mtim.tv_nsec);
      res->st_ctim.tv_sec = Host2BigEndian((int32_t)s->st_ctim.tv_sec);
      res->st_ctim.tv_nsec = Host2BigEndian((int32_t)s->st_ctim.tv_nsec);
#else
      res->st_atim.tv_sec = Host2BigEndian((int32_t)s->st_atimespec.tv_sec);
      res->st_atim.tv_nsec = Host2BigEndian((int32_t)s->st_atimespec.tv_nsec);
      res->st_mtim.tv_sec = Host2BigEndian((int32_t)s->st_mtimespec.tv_sec);
      res->st_mtim.tv_nsec = Host2BigEndian((int32_t)s->st_mtimespec.tv_nsec);
      res->st_ctim.tv_sec = Host2BigEndian((int32_t)s->st_ctimespec.tv_sec);
      res->st_ctim.tv_nsec = Host2BigEndian((int32_t)s->st_ctimespec.tv_nsec);
#endif
    } else {
      res->st_dev = Host2LittleEndian((uint64_t)s->st_dev);
      //      res->st_ino = Host2LittleEndian((uint32_t)s->__st_ino);
      res->st_mode = Host2LittleEndian((uint32_t)s->st_mode);
      res->st_nlink = Host2LittleEndian((uint32_t)s->st_nlink);
      res->st_uid = Host2LittleEndian((uint32_t)s->st_uid);
      res->st_gid = Host2LittleEndian((uint32_t)s->st_gid);
      res->st_rdev = Host2LittleEndian((int64_t)s->st_rdev);
      //      res->__pad2 = Host2LittleEndian((uint16_t)s->__pad2);
      res->st_size = Host2LittleEndian((int64_t)s->st_size);
      res->st_blksize = Host2LittleEndian((int32_t)s->st_blksize);
      res->st_blocks = Host2LittleEndian((int64_t)s->st_blocks);
#ifdef __linux__
      res->st_atim.tv_sec = Host2LittleEndian((int32_t)s->st_atim.tv_sec);
      res->st_atim.tv_nsec = Host2LittleEndian((int32_t)s->st_atim.tv_nsec);
      res->st_mtim.tv_sec = Host2LittleEndian((int32_t)s->st_mtim.tv_sec);
      res->st_mtim.tv_nsec = Host2LittleEndian((int32_t)s->st_mtim.tv_nsec);
      res->st_ctim.tv_sec = Host2LittleEndian((int32_t)s->st_ctim.tv_sec);
      res->st_ctim.tv_nsec = Host2LittleEndian((int32_t)s->st_ctim.tv_nsec);
#else
      res->st_atim.tv_sec = Host2LittleEndian((int32_t)s->st_atimespec.tv_sec);
      res->st_atim.tv_nsec = Host2LittleEndian((int32_t)s->st_atimespec.tv_nsec);
      res->st_mtim.tv_sec = Host2LittleEndian((int32_t)s->st_mtimespec.tv_sec);
      res->st_mtim.tv_nsec = Host2LittleEndian((int32_t)s->st_mtimespec.tv_nsec);
      res->st_ctim.tv_sec = Host2LittleEndian((int32_t)s->st_ctimespec.tv_sec);
      res->st_ctim.tv_nsec = Host2LittleEndian((int32_t)s->st_ctimespec.tv_nsec);
#endif
    }
    res->__unused4 = 0;
    res->__unused5 = 0;
    return (void *)res;
  }

  /**
   * \brief Returns the size ot the "stat64" struct on target architecture
   */
  unsigned int PPC_LinuxOS::Stat64Size() {
    return sizeof(powerpc_stat64_t);
  }

  /**
   * \brief Convert the native "tms" structure to the target architecture struct
   */
  void * PPC_LinuxOS::ConvertTms(struct tms *t) {
    struct powerpc_tms_t *res;

    res = (powerpc_tms_t *)malloc(sizeof(powerpc_tms_t));
    if(GetEndianess() == E_BIG_ENDIAN) {
      res->tms_utime = Host2BigEndian((int32_t)t->tms_utime);
      res->tms_stime = Host2BigEndian((int32_t)t->tms_stime);
      res->tms_cutime = Host2BigEndian((int32_t)t->tms_cutime);
      res->tms_cstime = Host2BigEndian((int32_t)t->tms_cstime);
    } else {
      res->tms_utime = Host2LittleEndian((int32_t)t->tms_utime);
      res->tms_stime = Host2LittleEndian((int32_t)t->tms_stime);
      res->tms_cutime = Host2LittleEndian((int32_t)t->tms_cutime);
      res->tms_cstime = Host2LittleEndian((int32_t)t->tms_cstime);
    }

    return (void *)res;
  }

  void PPC_LinuxOS::ConvertIovec(struct powerpc_iovec_t* iov) {
    if(GetEndianess() == E_BIG_ENDIAN) {
      iov->iov_base = BigEndian2Host(iov->iov_base);
      iov->iov_len = BigEndian2Host(iov->iov_len);
    } else {
      iov->iov_base = LittleEndian2Host(iov->iov_base);
      iov->iov_len = LittleEndian2Host(iov->iov_len);
    }
  }

  /**
   * \brief Return the size of the "tms" struct on target architecture
   */
  unsigned int PPC_LinuxOS::TmsSize() {
    return sizeof(powerpc_tms_t);
  }

  /**
   * \brief Get the current systemcall number
   */
  int PPC_LinuxOS::GetSystemCallNumber() {
    return current_system_call;
  }

  /**
   * \brief Retreive the mmap base address
   */
  address_t PPC_LinuxOS::GetMmapBase() const {
    return mmap_base;
  }

  /**
   * \brief Retrieve the mmap max address (not included).
   */
  address_t PPC_LinuxOS::GetMmapEnd() const {
    return mmap_end;
  }

#ifdef UNISIM_STL_CONTAINERS
  /**
   * \brief Retreive the stl containers base address
   */
  address_t PPC_LinuxOS::GetStlContainersBase() const {
    return stl_containers_base;
  }

  /**
   * \brief Retreive the stl containers base size
   */
  address_t PPC_LinuxOS::GetStlContainersSize() const {
    return stl_containers_size;
  }
#endif

  address_t PPC_LinuxOS::GetSP() const {
    return proc->cpu.gpr[1];
  }

  reg_t PPC_LinuxOS::GetPC() const{
    return proc->cpu.pc;
  }

  reg_t PPC_LinuxOS::GetLR() const{
    return proc->cpu.lr;
  }

  /**
   * \brief Retreive the breakpoint
   */
  address_t PPC_LinuxOS::GetBrkPoint() const {
    return brk_point;
  }

  address_t PPC_LinuxOS::GetBrkStart() const {
    return brk_start;
  }

  /**
   * \brief Set the breakpoint
   */
  void PPC_LinuxOS::SetBrkPoint(address_t brk_point) {
    this->brk_point = brk_point;
  }

  /**
   *  \brief Retreive one of the system call parameters
   */
  reg_t PPC_LinuxOS::GetSystemCallParam(int id) {
    reg_t val;
    val = proc->cpu.gpr[id+3];
    return val;
  }

  /**
   *  \brief Raised upon reaching the "exit" syscall
   */
  void PPC_LinuxOS::PerformExit(int ret) {
    info() << " Program exited with code " << ret << endl;
    exit(ret);
  }

  /**
   *  \brief Set the exit status of the system call
   */
  void PPC_LinuxOS::SetSystemCallStatus(int ret, bool error) {
    reg_t val;
    if(error){
      proc->cpu.cr |= (1<<28); // CR0[SO] <- 1
    }
    else{
      proc->cpu.cr &= ~(1 << 28); // CR0[SO] <- 0
    }
    val = (reg_t)ret;
    proc->cpu.gpr[3] = val;
  }

  /**
   *  \brief Get the endianess of the target architecture
   */
  endian_type PPC_LinuxOS::GetEndianess() {
    return proc->mmu.is_bigendian()?E_BIG_ENDIAN:E_LITTLE_ENDIAN;
  }

  /**
   * \brief Memory interface : Reset
   */
  void PPC_LinuxOS::Reset() {
    //return exp->Reset();
  }

  /**
   * \brief Memory interface : Read from memory
   */
  bool PPC_LinuxOS::ReadMemory(address_t addr, void *buffer, uint32_t size) {
    uint32_t i;
    for (i=0; i<size ; i++) {
      *((uint8_t*)buffer+i)=proc->mmu.read_byte(addr);
      ++addr;
    }
    if (i<size)
      debug()<<"=====> can access : false\n";
    return i==size;
  }


  /**
   * \brief Memory interface : Write to memory
   */
  bool PPC_LinuxOS::WriteMemory(address_t addr, const void *buffer, uint32_t size) {
    uint32_t i=0;
    for (; i!=size; ++i)
      proc->mmu.write_byte(addr++,*((uint8_t*)buffer+i));
    return i==size;
  }

  void PPC_LinuxOS::end_of_elaboration(){
    if(mmap_end >= (proc->get_sp() + USER_STACK_LIMIT)){
      warning()<<"mmap end address overlaps user mode stack"<<endl;
    }

    proc->mmu.get_dmi_at_address(mmap_base);
  }

  // Static members
  address_t PPC_LinuxOS::mmap_base = 0;
  address_t PPC_LinuxOS::mmap_end = 0;
  address_t PPC_LinuxOS::brk_point = 0;
  address_t PPC_LinuxOS::brk_start = 0;
  void * PPC_LinuxOS::init_inst = NULL;

#ifdef UNISIM_STL_CONTAINERS
  address_t PPC_LinuxOS::stl_containers_base = 0;
  uint32_t PPC_LinuxOS::stl_containers_size = 0;
#endif
}

