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

//modified for simsoc

#ifndef PPC_LINUX_OS_HPP
#define PPC_LINUX_OS_HPP

#include <libsimsoc/module.hpp>
#include <libsimsoc/interfaces/endian.hh>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/uio.h>

#ifdef __linux__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif

#endif

namespace simsoc {

  class PPC_Processor;
  class PPC_SystemCall;

  typedef uint32_t address_t;
  typedef uint32_t reg_t;

  // 	original structure
    // 	struct iovec
    // 	{
    // 	  void *iov_base;
    // 	  size_t iov_len;
    // 	};

    struct powerpc_iovec_t {
      uint32_t iov_base;
      uint32_t iov_len;
    };

  class PPC_LinuxOS : public Module{
  public:
    PPC_SystemCall* linux_os;
    PPC_Processor* proc;

    /* Constructor/Destructor */
    PPC_LinuxOS(const char *name, PPC_Processor *_proc);
    ~PPC_LinuxOS();
    void start_of_simulation();

    /* Service interface methods */
    void ExecuteSystemCall(int id);

    /* CPU Linux OS Interface */
    void* ConvertStat(struct stat *);
    unsigned int StatSize(void);
    //STF
    void* ConvertTime(struct timeval *);
    unsigned int TimeSize(void);
    //EOSTF
#ifdef __linux__ 
    void* ConvertStat64(struct stat64 *);
#elif defined (__APPLE__)
    void* ConvertStat64(struct stat64 *);
#else
#error You have to tell how to deal with ConvertStat64 on your OS.
#endif
    unsigned int Stat64Size(void);
    void* ConvertTms(struct tms *);
    unsigned int TmsSize(void);

    void ConvertIovec(struct powerpc_iovec_t *);

    /* CPU OS Interface*/
    int GetSystemCallNumber();
    address_t GetMmapBase() const;
    address_t GetMmapEnd() const;
#ifdef UNISIM_STL_CONTAINERS
    address_t GetStlContainersBase() const;
    address_t GetStlContainersSize() const;
#endif
    reg_t GetPC() const;
    reg_t GetLR() const;
    address_t GetSP() const;
    address_t GetBrkPoint() const;
    address_t GetBrkStart() const;
    void SetBrkPoint(address_t brk_point);
    reg_t GetSystemCallParam(int id);
    void PerformExit(int ret);
    void SetSystemCallStatus(int ret, bool error);

    /* Endianess Interface */
    endian_type GetEndianess();

    /* Memoey Interface */
    void Reset();
    bool ReadMemory(address_t addr, void *buffer, uint32_t size);
    bool WriteMemory(address_t addr, const void *buffer, uint32_t size);

    static const uint32_t USER_STACK_LIMIT;
    void end_of_elaboration();

  protected:
    endian_type endianess;   ///< Endianess of the target architecture
    reg_t memory_page_size;  ///< Memory page size

  private:
    //Parameter<endian_type> param_endian;
    //Parameter<reg_t> param_memory_page_size;

    static address_t mmap_base;
    static address_t mmap_end;
    static address_t brk_point;
    static address_t brk_start;
    static void * init_inst;

#ifdef UNISIM_STL_CONTAINERS
    static address_t stl_containers_base;
    static uint32_t stl_containers_size;
#endif

    int current_system_call;

    // this structure supposes that the timespec was needed (__timespec_defined)
    // original structure
    // struct timespec
    //   {
    //     __time_t tv_sec;            /* Seconds.  */
    //     long int tv_nsec;           /* Nanoseconds.  */
    //   };
    struct powerpc_timespec_t {
      int32_t tv_sec;        /* Seconds.  */
      int32_t tv_nsec;       /* Nanoseconds.  */
    };

    // this structure supposes that the powerpc file was compiled with
    //   the __USE_LARGEFILE64 and __USE_MISC
    // original structure
    //     # ifdef __USE_LARGEFILE64
    //     struct stat64
    //     {
    //         __dev_t st_dev;			/* Device.  */
    //         __ino64_t st_ino;			/* File serial number.	*/
    //         __mode_t st_mode;			/* File mode.  */
    //         __nlink_t st_nlink;			/* Link count.  */
    //         __uid_t st_uid;			/* User ID of the file's owner.	*/
    //         __gid_t st_gid;			/* Group ID of the file's group.*/
    //         __dev_t st_rdev;			/* Device number, if device.  */
    //         unsigned short int __pad2;
    //         __off64_t st_size;			/* Size of file, in bytes.  */
    //         __blksize_t st_blksize;		/* Optimal block size for I/O.  */
    //         __blkcnt64_t st_blocks;		/* Number 512-byte blocks allocated. */
    //     #ifdef __USE_MISC
    //         /* Nanosecond resolution timestamps are stored in a format
    //         equivalent to 'struct timespec'.  This is the type used
    //         whenever possible but the Unix namespace rules do not allow the
    //         identifier 'timespec' to appear in the <sys/stat.h> header.
    //         Therefore we have to handle the use of this header in strictly
    //         standard-compliant sources special.  */
    //         struct timespec st_atim;		/* Time of last access.  */
    //         struct timespec st_mtim;		/* Time of last modification.  */
    //         struct timespec st_ctim;		/* Time of last status change.  */
    //     # define st_atime st_atim.tv_sec	/* Backward compatibility.  */
    //     # define st_mtime st_mtim.tv_sec
    //     # define st_ctime st_ctim.tv_sec
    //     #else
    //         __time_t st_atime;			/* Time of last access.  */
    //         unsigned long int st_atimensec;	/* Nscecs of last access.  */
    //         __time_t st_mtime;			/* Time of last modification.  */
    //         unsigned long int st_mtimensec;	/* Nsecs of last modification.  */
    //         __time_t st_ctime;			/* Time of last status change.  */
    //         unsigned long int st_ctimensec;	/* Nsecs of last status change.  */
    //     #endif
    //         unsigned long int __unused4;
    //         unsigned long int __unused5;
    //     };
    //     # endif /* __USE_LARGEFILE64 */

    struct powerpc_stat64_t {
      uint64_t st_dev;			/* Device.  */
      uint64_t st_ino;			/* File serial number.	*/
      uint32_t st_mode;			/* File mode.  */
      uint32_t st_nlink;			/* Link count.  */
      uint32_t st_uid;			/* User ID of the file's owner.	*/
      uint32_t st_gid;			/* Group ID of the file's group.*/
      uint64_t st_rdev;			/* Device number, if device.  */
      uint16_t __pad2;
      uint64_t st_size;			/* Size of file, in bytes.  */
      uint32_t st_blksize;		/* Optimal block size for I/O.  */
      //uint32_t __blksize_pad;
      uint64_t st_blocks;		/* Number 512-byte blocks allocated. */
      /* Nanosecond resolution timestamps are stored in a format
         equivalent to 'struct timespec'.  This is the type used
         whenever possible but the Unix namespace rules do not allow the
         identifier 'timespec' to appear in the <sys/stat.h> header.
         Therefore we have to handle the use of this header in strictly
         standard-compliant sources special.  */
      struct powerpc_timespec_t st_atim;		/* Time of last access.  */
      struct powerpc_timespec_t st_mtim;		/* Time of last modification.  */
      struct powerpc_timespec_t st_ctim;		/* Time of last status change.  */
      uint32_t __unused4;
      uint32_t __unused5;
    };

    struct powerpc_stat_t
    {
      uint32_t st_dev;
      //uint32_t __pad1; // stf : real pad is 32bit because of alignment
      uint32_t st_ino;
      uint32_t st_mode;
      uint32_t st_nlink;
      uint32_t st_uid;
      uint32_t st_gid;
      int32_t st_rdev;
      //uint16_t __pad2;
      int32_t st_size;
      int32_t st_blksize;
      int32_t st_blocks;
      struct powerpc_timespec_t st_atim;
      struct powerpc_timespec_t st_mtim;
      struct powerpc_timespec_t st_ctim;
      uint32_t __unused4;
      uint32_t __unused5;
    };

    // 	original structure
    // 	struct tms
    // 	{
    // 	  clock_t tms_utime;          /* User CPU time.  */
    // 	  clock_t tms_stime;          /* System CPU time.  */
    // 	  clock_t tms_cutime;         /* User CPU time of dead children.  */
    // 	  clock_t tms_cstime;         /* System CPU time of dead children.  */
    // 	};
    struct powerpc_tms_t {
      int32_t tms_utime;      /* User CPU time.  */
      int32_t tms_stime;      /* System CPU time.  */

      int32_t tms_cutime;     /* User CPU time of dead children.  */
      int32_t tms_cstime;     /* System CPU time of dead children.  */
    };

    //STF TEMP
  private:
    void my_print_bin_stat(struct powerpc_stat_t *st);
    //EOSTF
  };
}//end of namespace simsoc
#endif
