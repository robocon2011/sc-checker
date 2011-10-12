/*
 *  Copyright (c) 2007,
 *  Commissariat a l'Energie Atomique (CEA)
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   - Neither the name of CEA nor the names of its contributors may be used to
 *     endorse or promote products derived from this software without specific prior
 *     written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED.
 *  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Daniel Gracia Perez (daniel.gracia-perez@cea.fr)
 */

// Modified for SimSoc

#ifndef PPC_SYSCALL_HPP
#define PPC_SYSCALL_HPP


#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/times.h>
#include <sys/time.h>
#include <iomanip>
#include <sys/sysctl.h>


#include <libsimsoc/interfaces/endian.hh>
#include <libsimsoc/interfaces/address_space_allocator.hh>
#include <libsimsoc/module.hpp>

namespace simsoc{

  typedef uint32_t ADDRESS_TYPE;
  typedef uint32_t PARAMETER_TYPE;

  class PPC_LinuxOS;

  class PPC_SystemCall : public Module{
  public:

    /* Constructor/Destructor */
    PPC_SystemCall(const char *name,PPC_LinuxOS* _exp);
    ~PPC_SystemCall();

    /* Service interface methods */
    void SetSyscallId(const string &syscall_name, int syscall_id);
    void ExecuteSystemCall();

  protected:
    void mmap_common (PARAMETER_TYPE length, PARAMETER_TYPE prot, PARAMETER_TYPE type);

    typedef AddressSpaceAllocator<ADDRESS_TYPE> AddressSpaceAllocatorType;
    static AddressSpaceAllocatorType * addr_sp_alloc;

    endian_type endianess;  ///< Endianess of the connected processor
    bool verbose;           ///< Set the verbosity level
    PPC_LinuxOS* exp;

  private:
    bool Swap();
    void PerformSwap(void *buf,
                     int count);
    int StringLength(uint32_t addr);

    bool HasSyscall(const string &syscall_name);
    bool HasSyscall(int syscall_id);

    typedef PPC_SystemCall thistype;
    typedef void (thistype::*syscall_t)();

    map<string, syscall_t> syscall_name_map;
    map<int, string> syscall_name_assoc_map;
    map<int, syscall_t> syscall_impl_assoc_map;

    int current_syscall_id;
    string current_syscall_name;

    int redirected_fd_stdin;
    int redirected_fd_stdout;
    int redirected_fd_stderr;
    int syscall_param_offset;
    string prefix;

    void SetSyscallNameMap();

    //#include "linux_system_calls.hh"
    void LSC_unknown();
    void LSC_syscall();
    void LSC_exit();
    void LSC_read();
    void LSC_write();
    void LSC_open();
    void LSC_close();
    void LSC_lseek();
    //tim
    void LSC_mkdir();
    //eotim
    //STF
    void LSC_rmdir();
    void LSC_gettimeofday();
    //EOSTF
    void LSC_getpid();
    void LSC_getuid();
    void LSC_access();
    void LSC_times();
    void LSC_brk();
    void LSC_getgid();
    void LSC_geteuid();
    void LSC_getegid();
    //tim
    void LSC_chown();
    //eotim
    void LSC_getcwd();
    void LSC_umask();
    void LSC_munmap();
    void LSC_stat();
    void LSC_fstat();
    void LSC_uname();
    void LSC_llseek();
    void LSC_writev();
    void LSC_mmap();
    void LSC_mmap2();

#ifdef UNISIM_STL_CONTAINERS
    void LSC_unisim_malloc();
    void LSC_unisim_free();
    void LSC_unisim_realloc();
#endif

    void LSC_mprotect();
    //tim
    void LSC_truncate();
    void LSC_ftruncate();
    void LSC_stat64();
    //eotim
    void LSC_fstat64();
    void LSC_getuid32();
    void LSC_getgid32();
    void LSC_geteuid32();
    void LSC_getegid32();
    void LSC_flistxattr();
    void LSC_exit_group();
    void LSC_fcntl();
    void LSC_fcntl64();
    void LSC_dup();
    void LSC_ioctl();
    void LSC_ugetrlimit();
    void LSC_getrlimit();
    void LSC_setrlimit();
    void LSC_rt_sigaction();
    void LSC_getrusage();
    void LSC_unlink();
    void LSC_rename();
    void LSC_time();
    void LSC_socketcall();
    void LSC_rt_sigprocmask();
    void LSC_kill();
    //STF
    void LSC_sysctl();
    void LSC_pipe();
    void LSC_rt_sigqueueinfo();

#if 0
    /** \name Pthread pseudo-syscalls
     * \{
     */
    // They are documented in 'pthread_interface.hh'.
    void LSC_pthread_create();
    void LSC_pthread_exit();
    void LSC_pthread_join1();
    void LSC_pthread_join2();
    void LSC_pthread_self();
    void LSC_pthread_mutex_init();
    void LSC_pthread_mutex_destroy();
    void LSC_pthread_mutex_lock();
    void LSC_pthread_mutex_trylock();
    void LSC_pthread_mutex_unlock();
    void LSC_pthread_spin_init();
    void LSC_pthread_spin_destroy();
    void LSC_pthread_spin_trylock();
    void LSC_pthread_spin_unlock();
    void LSC_pthread_cond_init ();
    void LSC_pthread_cond_destroy ();
    void LSC_pthread_cond_wait();
    void LSC_pthread_cond_signal ();
    void LSC_pthread_key_create ();
    void LSC_pthread_key_delete ();
    void LSC_pthread_getspecific ();
    void LSC_pthread_setspecific ();
    void LSC_pthread_key_getdtor();
#ifdef CAPSULE
    void LSC_cap_split();              ///< "cap_split" pseudo-syscall
    void LSC_cap_divide();             ///< "cap_divide" pseudo-syscall
    void LSC_cap_execute();            ///< "cap_execute pseudo-syscall
    void LSC_cap_exit();               ///< "cap_exit" pseudo-syscall
    void LSC_cap_join();               ///< "cap_join" pseudo-syscall
    void LSC_cap_get_proc_id();
    void LSC_cap_thread_wakeup();
    void LSC_cap_get_proc_state();
    void LSC_cap_set_proc_state();
    void LSC_cap_get_probing_proc_id();
    void LSC_cap_get_available_thread();
#endif
#ifdef NOC_SUPPORT_PARALLELIZATION
    void LSC_npthread_create();        ///< "npthread_create" pseudo-syscall
    void LSC_npthread_execute();       ///< "npthread_execute" pseudo-syscall
    void LSC_pthread_join();
#endif

    /**
     * \}
     */

    void LSC_syscall_print_str();
    void LSC_syscall_print_int();
    void LSC_syscall_print();
    void LSC_syscall_print_array();

    void LSC_syscall_timingevent();
    void LSC_syscall_timingevent_start();
    void LSC_syscall_timingevent_stop();
    void LSC_syscall_timingevent_wave();
    void LSC_syscall_output_dsp();
    void LSC_syscall_fast_timingevent();

    void LSC_syscall_bin_dump_init();
    void LSC_syscall_bin_dump_write();
    void LSC_syscall_bin_dump_close();

    //EOSTF
#endif

    void LSC_futex();
  };

}//end of namespace simsoc
#endif

