#include "ppc_syscall.hpp"
#include "ppc_linux_os.hpp"
#include <sys/mman.h>
#include <sys/uio.h>
using namespace std;

namespace simsoc{
  template <> PPC_SystemCall::AddressSpaceAllocatorType * PPC_SystemCall::addr_sp_alloc = NULL;

  /** Constructor. */
  PPC_SystemCall::PPC_SystemCall(const char *name,PPC_LinuxOS* _exp) :
    Module(name),
    endianess(E_BIG_ENDIAN),
    exp(_exp),
    redirected_fd_stdin(0),
    redirected_fd_stdout(1),
    redirected_fd_stderr(2),
    syscall_param_offset(0),
    prefix(""){
    /* Associate system calls implementations with their names. */
    SetSyscallNameMap();
    if (!addr_sp_alloc){
      ADDRESS_TYPE base = exp -> GetMmapBase ();
      ADDRESS_TYPE end = exp -> GetMmapEnd ();
      AddressSpaceAllocator<ADDRESS_TYPE>::RangeType init_range (base, end);

      addr_sp_alloc = new AddressSpaceAllocator<ADDRESS_TYPE>(init_range);
      info()<<"mmap address space is initialized to be "<<hex<<base<<" to "<<end<<endl;
    }
#ifdef UNISIM_STL_CONTAINERS
    if(! unisim_stl_container){
      ADDRESS_TYPE base = exp -> GetStlContainersBase();
      ADDRESS_TYPE size = exp -> GetStlContainersSize();
      unisim_stl_container = new UnisimStlContainerAllocator<ADDRESS_TYPE>(base,size);
    }
#endif
  }

  /** Destructor. */
  PPC_SystemCall::~PPC_SystemCall() {
  }

  /**
   * Checks that an implementation exists for a syscall name.
   *
   * @param syscall_name the name of the syscall to check.
   * @return True if the syscall exists.
   */
  bool PPC_SystemCall::HasSyscall(const string &syscall_name) {
    return syscall_name_map.find(syscall_name) != syscall_name_map.end();
  }

  /**
   * Checks that an id has been associated to a system call implementation.
   *
   * @param syscall_id id to check.
   * @return True if syscall_id has been associated to an implementation.
   */
  bool PPC_SystemCall::HasSyscall(int syscall_id) {
    return syscall_impl_assoc_map.find(syscall_id) != syscall_impl_assoc_map.end();
  }

  /**
   * Associates an id (integer) to a the implementation of the syscall specified by syscall_name.
   *
   * @param syscall_name
   * @param syscall_id
   */
  void PPC_SystemCall::SetSyscallId(const string &syscall_name, int syscall_id) {
    syscall_t syscall_impl;
    if(HasSyscall(syscall_name)) {
      if(HasSyscall(syscall_id)) {
        stringstream s;
        s << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << endl;
        s << "syscall_id already associated to syscall \"" << syscall_name_assoc_map[syscall_id] << "\"" << endl;
        s << "  you wanted to associate it to " << syscall_name << endl;
        //throw std::runtime_error(s.str().c_str());
        error()<<s<<endl;
        exit(1);
      }
      syscall_name_assoc_map[syscall_id] = syscall_name;
      syscall_impl_assoc_map[syscall_id] = syscall_name_map[syscall_name];
    } else {
      stringstream s;
      s << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << endl;
      s << "Unimplemented system call (" << syscall_name << ")";
      //throw std::runtime_error(s.str().c_str());
      error()<<s<<endl;
      exit(1);
    }
  }

  /**
   * Gets from the cpu calling this method the syscall id to execute and emulates it if it exists.
   */
  void PPC_SystemCall::ExecuteSystemCall() {
    int x = exp->GetSystemCallNumber();
    if (HasSyscall(x)) {
      current_syscall_id = x;
      current_syscall_name = syscall_name_assoc_map[x];
      //STF
      info() << "## "<< x << " ## " << current_syscall_name << endl;
      //EOSTF
      syscall_t y = syscall_impl_assoc_map[x];
      (this->*y)();
    } else{
      /*throw UnimplementedSystemCall(__FUNCTION__,
        __FILE__,
        __LINE__,
        x);
      */
      error()<<"Unimplemented System Call: "<<x<<endl;
      exit(1);
    }
  }

  /**
   * Checks if the endianess of the host and the target system differs.
   */
  bool PPC_SystemCall::Swap() {
#if BYTE_ORDER == BIG_ENDIAN
    if(exp->GetEndianess() == E_BIG_ENDIAN) return false;
    else return true;
#else
    if(exp->GetEndianess() == E_BIG_ENDIAN) return true;
    else return false;
#endif
  }

  void PPC_SystemCall::PerformSwap(void *buf,int count) {
    int size = count;

    if(count > 0) {
      char *dst_base, *dst;
      char *src;

      dst = (char *)malloc(sizeof(char) * count);
      dst_base = dst;
      src = (char *)buf + count - 1;

      do {
	*dst = *src;
      } while(src--, dst++, --count);
      memcpy(buf, dst_base, size);
      free(dst_base);
    }
  }

  int PPC_SystemCall::StringLength(ADDRESS_TYPE addr) {
    int len = 0;
    char buffer;

    while(1) {
      exp->ReadMemory(addr, &buffer, 1);
      if(buffer == 0) return len;
      len++;
      addr += 1;
    }
  }

  void PPC_SystemCall::LSC_unknown() {
    info() << "Unimplemented system call #" << current_syscall_id << endl;
    exp->SetSystemCallStatus(-1, true);
  }


  void PPC_SystemCall::LSC_syscall()
  {
    info() << "sycall system call #" << current_syscall_id << endl;
    int new_syscall_number = exp->GetSystemCallParam(syscall_param_offset+0);
    info() << "  #sc=" << new_syscall_number << endl;
    info() << "  " << syscall_name_assoc_map[new_syscall_number] << endl;
    syscall_t impl = syscall_impl_assoc_map[new_syscall_number];
    syscall_param_offset=1;
    (this->*impl)();
    syscall_param_offset=0;
    //    cerr << "  " << &impl << "  " << LSC_pthread_create << endl ;
    /*
      map<string, syscall_t> syscall_name_map;
      map<int, string> syscall_name_assoc_map;
      map<int, syscall_t> syscall_impl_assoc_map;
    */
    exp->SetSystemCallStatus(-1, true);
  }

  void PPC_SystemCall::LSC_exit() {
    string name = "exit";
    int ret;

    ret = exp->GetSystemCallParam(syscall_param_offset+0);
    info() << "exit() ret = " << hex << ret << dec << endl;
    exp->PerformExit(ret);
  }


  void PPC_SystemCall::LSC_read() {
    string name = "read";
    int fd;
    size_t count;
    ADDRESS_TYPE buf_addr;
    void *buf;
    size_t ret;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    buf_addr = exp->GetSystemCallParam(syscall_param_offset+1);
    count = (size_t) exp->GetSystemCallParam(syscall_param_offset+2);

    buf = malloc(count);

    info() << "read(fd=" << fd << ", buf_addr=" << hex << buf_addr << dec
           << ", count=" << count << ")" << endl;

    if(buf) {
      //STF
      //			ret = read(fd, buf, count);
      if(fd==0) ret = read(redirected_fd_stdin, buf, count);
      else      ret = read(fd, buf, count);
      //journal.NotifyRead(fd, buf, count);
      //EOSTF
      if(ret > 0) exp->WriteMemory(buf_addr, buf, ret);
      free(buf);
    } else {
      ret = (size_t)-1;
    }

    info() << "read() return " << ret << endl;

    exp->SetSystemCallStatus(ret, ret < 0);
  }


  void PPC_SystemCall::LSC_write() {
    int fd;
    size_t count;
    void *buf;
    ADDRESS_TYPE buf_addr;
    size_t ret;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    buf_addr = exp->GetSystemCallParam(syscall_param_offset+1);
    count = (size_t)exp->GetSystemCallParam(syscall_param_offset+2);
    buf = malloc(count);

    ret = (size_t)-1;

    if(buf) {
      exp->ReadMemory(buf_addr, buf, count);
      //STF
      if(fd==1)
        { if(prefix.length()>0) write(redirected_fd_stdout, prefix.c_str(), prefix.length());
          ret = write(redirected_fd_stdout, buf, count);
        }
      else if(fd==2)
        { if(prefix.length()>0) write(redirected_fd_stderr, prefix.c_str(), prefix.length());
          ret = write(redirected_fd_stderr, buf, count);
        }
      else
        { ret = write(fd, buf, count);
        }
      /*
        if((fd == 1 || fd == 2)) {
        char *tbuf = new char[count + 1];
        memcpy(tbuf, buf, count);
        tbuf[count] = '\0';
        string *str = new string(tbuf);
        cout << (*str);
        cout << flush;
        ret = count;
        delete str;
        } else {
        ret = write(fd, buf, count);
        }
      */
      //journal.NotifyWrite(fd, buf, count);
      //EOSTF
      free(buf);
    } else {
      ret = (size_t)-1;
    }

    info() << "write(fd=" << fd << ", buf=" << hex << buf_addr << dec
           << ", count=" << count << ") return " << ret << endl;

    exp->SetSystemCallStatus(ret, ret < 0);
  }


  void PPC_SystemCall::LSC_open() {
    ADDRESS_TYPE addr;
    int pathnamelen;
    char *pathname;
    int flags;
    mode_t mode;
    int64_t ret;

    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(addr);
    pathname = (char *) malloc(pathnamelen + 1);
    exp->ReadMemory(addr, pathname, pathnamelen + 1);
    flags = exp->GetSystemCallParam(syscall_param_offset+1);
    mode = exp->GetSystemCallParam(syscall_param_offset+2);

    //cerr << "open syscall(" << pathname << "," << hex << (flags | O_NONBLOCK) << dec << "," << oct << mode << dec << ")\n" << endl;
    const uint32_t PPC_O_LARGEFILE = 0x10000;
#ifdef O_LARGEFILE // FIXME: add a #else case
    if((flags & PPC_O_LARGEFILE) && (O_LARGEFILE != PPC_O_LARGEFILE)){
      flags &= ~PPC_O_LARGEFILE;
      flags |= O_LARGEFILE;
    }
#endif

    ret = open(pathname, flags/* | O_NONBLOCK*/, mode);

    //cerr << "ret=" << ret << "\n" << endl;

    //STF
    //journal.NotifyOpen(ret, pathname, flags, mode);
    //EOSTF


    info() << "open(pathname=\"" << pathname << "\", flags=" << hex << flags
           << ", mode=" << mode << dec << ") return " << ret << endl;

    free(pathname);
    exp->SetSystemCallStatus(ret, (ret < 0));
  }


  void PPC_SystemCall::LSC_close() {
    int fd;
    int ret;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    ret = close(fd);
    //STF
    //journal.NotifyClose(fd);
    //EOSTF
    info() << "close(fd=" << fd << ") return " << ret << endl;
    exp->SetSystemCallStatus(ret, ret < 0);
  }

  void PPC_SystemCall::LSC_lseek() {
    int fildes;
    off_t offset;
    int whence;
    off_t ret;

    fildes = exp->GetSystemCallParam(syscall_param_offset+0);
    offset = exp->GetSystemCallParam(syscall_param_offset+1);
    whence = exp->GetSystemCallParam(syscall_param_offset+2);
    ret = lseek(fildes, offset, whence);
    info() << "lseek(fildes=" << fildes << ", offset=" << offset
           << ", whence=" << whence << ") return " << ret << endl;

    if (ret == (off_t)-1)
      exp->SetSystemCallStatus(errno, true);
    else
      exp->SetSystemCallStatus(ret, false);
  }

  void PPC_SystemCall::LSC_getpid() {
    pid_t ret;

    ret = (pid_t) 1000;
    info() << "getpid() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }

  void PPC_SystemCall::LSC_getuid() {
    uid_t ret;

    ret = getuid();
    info() << "getuid() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }

  void PPC_SystemCall::LSC_access() {
    ADDRESS_TYPE addr;
    int pathnamelen;
    char *pathname;
    mode_t mode;
    int ret;

    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(addr);
    pathname = (char *) malloc(pathnamelen + 1);
    exp->ReadMemory(addr, pathname, pathnamelen + 1);
    mode = exp->GetSystemCallParam(syscall_param_offset+1);
    ret = access(pathname, mode);
    info()<< "access(pathname=\"" << pathname
          << "\", mode=" << hex << mode << dec << ") return " << ret << endl;
    free(pathname);
    exp->SetSystemCallStatus(ret, ret < 0);
  }


  void PPC_SystemCall::LSC_times() {
    ADDRESS_TYPE buf_addr;
    struct tms buf;
    void *new_buf;
    clock_t ret;

    ret = times(&buf);
    new_buf = exp->ConvertTms(&buf);
    buf_addr = exp->GetSystemCallParam(syscall_param_offset+0);
    exp->WriteMemory(buf_addr, new_buf, exp->TmsSize());
    info() << "times(buf=" << hex << buf_addr << dec << ") return " << ret << endl;
    exp->SetSystemCallStatus(ret, ret != (clock_t) -1);
  }


  void PPC_SystemCall::LSC_brk() {
#if 1
    ADDRESS_TYPE new_brk_point;

    new_brk_point = exp->GetSystemCallParam(syscall_param_offset+0);

    if(new_brk_point > exp->GetBrkPoint())
      exp->SetBrkPoint(new_brk_point);

    info() << "brk(new_brk_point=" << hex << new_brk_point
           << ") return " << exp->GetBrkPoint() << dec << endl;
    exp->SetSystemCallStatus(exp->GetBrkPoint(),false);
#else
    ADDRESS_TYPE brk,start_brk,old_brk;
    brk = exp->GetSystemCallParam(syscall_param_offset+0);
    start_brk = exp->GetBrkStart();
    old_brk = exp->GetBrkPoint();
    if( brk<start_brk || brk>exp->GetSP()){
      exp->SetSystemCallStatus(exp->GetBrkPoint(),false);
      info() << "brk out of boudary:"<<hex<<brk<<endl;
      return;
    }

    if(brk==old_brk){
      exp->SetSystemCallStatus(exp->GetBrkPoint(),false);
      return;
    }

    if(brk<=old_brk){
      exp->SetBrkPoint(brk);
      exp->SetSystemCallStatus(exp->GetBrkPoint(),false);
      info() << "decrease brk to be:" << hex<<brk<<endl;
      return;
    }

    exp->SetBrkPoint(brk);
    info() << "brk(new_brk_point=" << hex << brk
    << ") return " << hex << exp->GetBrkPoint() << dec << endl;

    exp->SetSystemCallStatus(exp->GetBrkPoint(),false);
#endif
  }


  void PPC_SystemCall::LSC_getgid() {
    gid_t ret;

    ret = getgid();
    info() << "getgid() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }


  void PPC_SystemCall::LSC_geteuid() {
    uid_t ret;

    ret = geteuid();
    info() << "geteuid() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }


  void PPC_SystemCall::LSC_getegid() {
    gid_t ret;

    ret = getegid();
    info() << "getegid() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }



  void PPC_SystemCall::LSC_umask() {
    mode_t ret;
    mode_t mode;
    mode = exp->GetSystemCallParam(syscall_param_offset+0);
    ret = umask(mode);
    info() << "umask() return " << ret << endl;
    exp->SetSystemCallStatus(ret,false);
  }



  void PPC_SystemCall::LSC_munmap() {
    info() << "Entering 'munmap' system call." << endl;

    if (sizeof(PARAMETER_TYPE) != sizeof(ADDRESS_TYPE))
      {
        error() << "FATAL ERROR: ADDRESS_TYPE and PARAMETER_TYPE mismatch in LSC_munmap()." << endl;
        exit (1);
      }

    ADDRESS_TYPE start = (ADDRESS_TYPE) (exp -> GetSystemCallParam (0));
    ADDRESS_TYPE size = (ADDRESS_TYPE) (exp -> GetSystemCallParam (1));
    info() << "request to free length "<<hex<<size<<" from start: "<<hex<<start<<endl;
    AddressSpaceAllocator<ADDRESS_TYPE>::RangeType range (start, size+start);
    if ( addr_sp_alloc -> FreeRange (range)){
      exp -> SetSystemCallStatus (0, false);
      info()<<"munmap success for [ "<<hex<<start<<" , "<<hex<<size+start<<" ]"<<endl;
      char* buf = (char*)calloc(size,sizeof(char));
      exp->WriteMemory(start,buf,size);
      delete buf;

    }
    else{
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) EINVAL, true);
      info()<<"munmap failed for start: "<<hex<<start<<" and size: "<<hex<<size<<endl;
    }
  }


  //tim

  void PPC_SystemCall::LSC_stat()
  {
    int ret;
    info() << "stat ****************************************************" << endl;

#ifdef linux
    ADDRESS_TYPE buf_address;
    struct stat *buf;
    ADDRESS_TYPE pathname_address;
    int pathnamelen;
    char* pathname;

    pathname_address = (ADDRESS_TYPE) exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(pathname_address);
    pathname = (char *)malloc(pathnamelen + 1);
    if(pathname){
      exp->ReadMemory(pathname_address, pathname, pathnamelen + 1);
      info() << pathname << endl;
      info() << pathnamelen << endl;

      buf_address = (ADDRESS_TYPE) exp->GetSystemCallParam(syscall_param_offset+1);
      buf = (struct stat *)malloc(sizeof(struct stat));
      if(buf){
        ret = stat(pathname, buf);
        char *newbuf = (char *)(exp->ConvertStat(buf));
#if 0
        char *c = newbuf;
        int k=0,i,j;
        for(i=0; i< (int)exp->StatSize(); i++){
          unsigned int j=*c;
          printf("\e[1;32m%02x\e[0m ",j & 0xFF);
          c++;
          k=(k+1)%4;
          if(k==0) printf("\n");
        }
        printf("\n");
        fflush(stdout);
#endif
        exp->WriteMemory(buf_address, newbuf, exp->StatSize());
        free(newbuf);
        free(buf);
      }else
        ret = -1;
    } else
      ret = -1;

    info() << "pathname = " << pathname << ", buf_address = 0x" << hex << buf_address << dec << ", ret = 0x" << hex << ret << dec << endl;
    if(pathname) free(pathname);
    exp->SetSystemCallStatus(ret,ret < 0);
#else
      ret = -1;
      exp->SetSystemCallStatus(ret,true);
#endif

  }
  //eotim

  void PPC_SystemCall::LSC_fstat() {
    int ret;
    int fd;
    ADDRESS_TYPE buf_address;
    struct stat *buf;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    buf_address = exp->GetSystemCallParam(syscall_param_offset+1);
    buf = (struct stat *)malloc(sizeof(struct stat));

    if(buf) {
      ret = fstat(fd, buf);
      if(ret >= 0) {
        char *newbuf = (char *)(exp->ConvertStat(buf));
        exp->WriteMemory(buf_address, newbuf, exp->StatSize());
        free(newbuf);
        free(buf);
      } else
        ret = -1;

      info() << "stat(fd=" << fd
             << ", buf_addr=" << hex << buf_address << dec
             << ") return " << ret << endl;
      exp->SetSystemCallStatus((PARAMETER_TYPE)ret,ret < 0);
    }
  }

  // Value used by Linux
  static const unsigned my_utsname_length = 65;

  struct my_utsname
  {
    /* Name of the implementation of the operating system.  */
    char sysname[my_utsname_length];

    /* Name of this node on the network.  */
    char nodename[my_utsname_length];

    /* Current release level of this implementation.  */
    char release[my_utsname_length];
    /* Current version level of this release.  */
    char version[my_utsname_length];

    /* Name of the hardware type the system is running on.  */
    char machine[my_utsname_length];
  };


  void PPC_SystemCall::LSC_uname()
  {
    // Fill in our structure
    struct my_utsname uname;
    strcpy (uname.sysname, "Linux");
    strcpy (uname.nodename, "unisim_emulator");
    strcpy (uname.release, "2.6.22");
    strcpy (uname.version, "UNISIM syscall emulation");
    strcpy (uname.machine, "UNISIM simulator hardware");

    // Write info into program's address space
    uint32_t res_addr = exp -> GetSystemCallParam (0);
    exp -> WriteMemory (res_addr, &uname, sizeof(uname));

    info() << "uname(res_addr=" << hex << res_addr << dec << ") returns 0" << endl;
    exp->SetSystemCallStatus(0, false);
  }



  void PPC_SystemCall::LSC_llseek() {
    int fd;
    uint32_t offset_high;
    uint32_t offset_low;
    PARAMETER_TYPE result_addr;
    uint64_t lseek_ret64;
    off_t lseek_ret;
    int whence;
    int ret;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    offset_high = exp->GetSystemCallParam(syscall_param_offset+1);
    offset_low = exp->GetSystemCallParam(syscall_param_offset+2);
    result_addr = exp->GetSystemCallParam(syscall_param_offset+3);
    whence = exp->GetSystemCallParam(syscall_param_offset+4);
    info() << "llseek(fd=" << fd
           << ", offset=" << (((int64_t) offset_high << 32) | (int64_t) offset_low)
           << ", result_addr=" << hex << result_addr << dec
           << ", whence=" << whence << ")" << endl;
    if(offset_high == 0 || offset_high==0xffffffff) {
      lseek_ret = lseek(fd, (int32_t)offset_low, whence);
      if(lseek_ret >= 0) {
        lseek_ret64 = lseek_ret;
        if(Swap())
          PerformSwap(&lseek_ret64, sizeof(lseek_ret64));
        exp->WriteMemory(result_addr, &lseek_ret64, sizeof(lseek_ret64));
        exp->SetSystemCallStatus((PARAMETER_TYPE)lseek_ret, false);
      } else {
        exp->SetSystemCallStatus((PARAMETER_TYPE)errno, true);
      }
    } else {
      exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL), true);
    }
  }


  void PPC_SystemCall::LSC_writev() {
    int fd;
    size_t iovcnt;
    ADDRESS_TYPE iov_addr;
    struct powerpc_iovec_t *iov;
    size_t ret;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    iov_addr = exp->GetSystemCallParam(syscall_param_offset+1);
    iovcnt = (size_t)exp->GetSystemCallParam(syscall_param_offset+2);
    iov = (struct powerpc_iovec_t*)malloc(sizeof(struct powerpc_iovec_t)*iovcnt);

    if(iov) {
      ret = 0;
      exp->ReadMemory(iov_addr,iov,sizeof(struct powerpc_iovec_t)*iovcnt);

      ADDRESS_TYPE buf_addr;
      size_t len;
      char* buf;
      for(size_t i=0;i<iovcnt;i++){
        exp->ConvertIovec(&iov[i]);
        buf_addr = (ADDRESS_TYPE)iov[i].iov_base;
        len = iov[i].iov_len;
        buf = (char*)malloc(len);
        if(buf){
          exp->ReadMemory(buf_addr,buf,len);
          if(fd==1)
            { if(prefix.length()>0) write(redirected_fd_stdout, prefix.c_str(), prefix.length());
              ret += write(redirected_fd_stdout, buf, len);
            }
          else if(fd==2)
            { if(prefix.length()>0) write(redirected_fd_stderr, prefix.c_str(), prefix.length());
              ret += write(redirected_fd_stderr, buf, len);
            }
          else
            { ret += write(fd, buf, len);
            }
          free(buf);
        }else{
          ret = (size_t)-1;
          break;
        }
      }
      free(iov);
    } else {
      ret = (size_t)-1;
    }

    info() << "writev(fd=" << fd << ", iov=" << hex << iov_addr << dec
           << ", count=" << iovcnt << ") return " << ret << endl;

    exp->SetSystemCallStatus(ret, ret < 0);
  }


  void PPC_SystemCall::mmap_common(PARAMETER_TYPE length, PARAMETER_TYPE prot,PARAMETER_TYPE type) {
    // Warn when shared maps are asked for.
    if (type & 0xf == 1) // MAP_SHARED
      {
        static bool warned = false;

        if (verbose && ! warned)
          {
            info() << "INFO: 'mmap' syscall called with MAP_SHARED set." << endl;
            info() << "In all such cases, will default to MAP_PRIVATE, since MAP_SHARED is irrelevant in UNISIM." << endl;
            warned = true;
          }

        type = (type & ~1) | 2;
      }

    bool proceed = true;

    // Type check
    if (type & 0xf != 2) // MAP_PRIVATE
      {
        error() << "WARNING: Invalid map type for 'mmap' syscall!" << endl;
        proceed = false;
      }

    // Additional warnings about some flags not relevant/not implemented.

    if (! type & 0x20) // MAP_ANONYMOUS (MAP_FILE is 0 on Linux PPC)
      {
        static bool warned = false;

        if (verbose && ! warned)
          {
            warning() << "WARNING: 'mmap' file-backed not implemented in UNISIM." << endl;
            warning() << "In all such cases, 'mmap' will fail." << endl;
            warned = true;
          }

        proceed = false;
      }

    if (type & 0x10) // MAP_FIXED
      {
        static bool warned = false;

        if (verbose && ! warned)
          {
            warning() << "WARNING: A fixed address was asked for in 'mmap'." << endl;
            warning() << "This is not implemented in UNISIM yet..." << endl;
            warning() << "In all such cases, 'mmap' will fail." << endl;
            warned = true;
          }

        proceed = false;
      }

    if (! proceed)
      {
        error() << "'mmap' returning EINVAL in errno..." << endl;
        exp -> SetSystemCallStatus ((PARAMETER_TYPE) EINVAL, true);
        return;
      }

    if (type & 0xc0) // MAP_LOCKED | MAP_NORESERVE
      {
        static bool warned = false;

        if (verbose && ! warned)
          {
            warning() << "'mmap' called with flags related to swap / physical memory." << endl;
            warning() << "In all such cases, these flags will be ignored." << endl;
            warned = true;
          }
      }

    if (verbose && type & ~0xff)
      {
        warning() << "'mmap' called with rarely used / system flags." << endl;
        warning() << "Proceeding anyway, ignoring them. Expect strange behavior." << endl;
      }

    if (prot != 7)
      {
        static bool warned = false;

        if (verbose && ! warned)
          {
            warning() << "'mmap' called with protections not being PROT_READ|PROT_WRITE|PROT_EXEC." << endl;
            warning() << "Protections are not implemented in UNISIM." << endl;
             warning() << "Programs will be able to do any operation on the returned memory range." << endl;
             warning() << "Not warning you again about that..." << endl;
            warned = true;
          }
      }

    // Allocates address space
    AddressSpaceAllocator<ADDRESS_TYPE>::RangeType range;
    if (addr_sp_alloc -> AllocRange (length, range)){
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) range.start, false);
      info()<<"mmap success for [ "<<hex<<range.start<<" , "<<hex<<range.start+length<<" ]"<<endl;
    }
    else{
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) ENOMEM, true);
      info()<<"mmap fail for length: "<<hex<<length<<endl;
    }
  }



  void PPC_SystemCall::LSC_mmap() {
    info()<< "Entering 'mmap' system call." << endl;

    if (sizeof(PARAMETER_TYPE) != sizeof(ADDRESS_TYPE))
      {
        error() << "FATAL ERROR: ADDRESS_TYPE and PARAMETER_TYPE mismatch in LSC_mmap()." << endl;
        exit (1);
      }

    PARAMETER_TYPE type = exp -> GetSystemCallParam (3);
    PARAMETER_TYPE prot = exp -> GetSystemCallParam (2);
    PARAMETER_TYPE length = exp -> GetSystemCallParam (1);

    mmap_common (length, prot, type);
  }



  void PPC_SystemCall::LSC_mmap2() {
    info() << "Entering 'mmap2' system call." << endl;

    if (sizeof(PARAMETER_TYPE) != sizeof(ADDRESS_TYPE))
      {
        error() << "FATAL ERROR: ADDRESS_TYPE and PARAMETER_TYPE mismatch in LSC_mmap2()." << endl;
        exit (1);
      }

    PARAMETER_TYPE type = exp -> GetSystemCallParam (3);
    PARAMETER_TYPE prot = exp -> GetSystemCallParam (2);
    PARAMETER_TYPE length = exp -> GetSystemCallParam (1);

    mmap_common (length, prot, type);
  }

#ifdef UNISIM_STL_CONTAINERS

  void PPC_SystemCall::LSC_unisim_malloc() {
    info() << "Entering 'unisim_malloc' system call." << endl;

    ADDRESS_TYPE length = exp -> GetSystemCallParam (0);
    ADDRESS_TYPE addr;

    if (unisim_stl_container -> AllocRange (length,addr ))
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) addr, false);
    else
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) ENOMEM, true);
  }


  void PPC_SystemCall::LSC_unisim_free() {
    info() << "Entering 'unisim_free' system call." << endl;

    ADDRESS_TYPE addr = exp -> GetSystemCallParam (0);
    ADDRESS_TYPE lenth = exp -> GetSystemCallParam (1);

    if (unisim_stl_container -> FreeRange (addr,lenth ))
      exp -> SetSystemCallStatus (0, false);
    else
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) EINVAL, true);
  }


  void PPC_SystemCall::LSC_unisim_realloc(){
    info() << "Entering 'unisim_realloc' system call." << endl;

    ADDRESS_TYPE oldaddr = exp -> GetSystemCallParam (0);
    ADDRESS_TYPE oldsize = exp -> GetSystemCallParam (1);
    ADDRESS_TYPE oldtail = exp -> GetSystemCallParam (2);
    ADDRESS_TYPE newsize = exp -> GetSystemCallParam (3);
    ADDRESS_TYPE return_addr;

    void * buffer;

    if(newsize<= oldsize)
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) oldaddr, false);

    if (unisim_stl_container -> ReallocRange (oldaddr,newsize,return_addr ))
      {
        if(oldaddr!=return_addr)
          {
            buffer = malloc(oldsize);
            exp->ReadMemory(oldaddr, buffer, oldsize);
            exp->WriteMemory(return_addr, buffer, oldsize);
            free(buffer);
          }
        if(oldtail != 0)
          {
            buffer = malloc(oldtail);
            exp->ReadMemory(oldaddr, buffer, oldtail);
            exp->WriteMemory(return_addr+oldsize, buffer, oldtail);
            free(buffer);
          }
        exp -> SetSystemCallStatus ((PARAMETER_TYPE) return_addr, false);
      }
    else
      exp -> SetSystemCallStatus ((PARAMETER_TYPE) ENOMEM, true);
  }
#endif

  void PPC_SystemCall::LSC_mprotect()
  {
    static bool warned = false;

    if (verbose && ! warned)
      {
        warning() << "'mprotect' syscall called, but UNISIM doesn't check access rights." << endl;
        warning() << "INFO: This and subsequent calls to 'mprotect' will be silently ignored." << endl;
        warning() << "No address range check is performed!!" << endl;
        warned = true;
      }

    exp -> SetSystemCallStatus (0, false);
  }


  void PPC_SystemCall::LSC_truncate() {
    int ret;
    ADDRESS_TYPE pathname_address;
    int pathnamelen;
    char* pathname;
    size_t length;

    pathname_address = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(pathname_address);
    pathname = (char *)malloc(pathnamelen + 1);
    if(pathname) {
      exp->ReadMemory(pathname_address, pathname, pathnamelen + 1);
      length = exp->GetSystemCallParam(syscall_param_offset+1);
      ret = truncate(pathname, length);
      free(pathname);
    }
    else {
      ret = -1;
    }
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret, ret < 0);
  }


  void PPC_SystemCall::LSC_ftruncate() {
    int ret;
    int fd;
    size_t length;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    length = exp->GetSystemCallParam(syscall_param_offset+1);
    ret = ftruncate(fd, length);
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret, ret < 0);
  }


  void PPC_SystemCall::LSC_fstat64() {
    int ret;

#ifdef linux
    int fd;
    ADDRESS_TYPE buf_address;
    struct stat64 *buf;

    fd = exp->GetSystemCallParam(syscall_param_offset+0);
    buf_address = exp->GetSystemCallParam(syscall_param_offset+1);
    buf = (struct stat64 *)malloc(sizeof(struct stat64));
    if(buf) {
      ret = fstat64(fd, buf);
      char *newbuf = (char *)(exp->ConvertStat64(buf));
      exp->WriteMemory(buf_address, newbuf, exp->Stat64Size());
      free(newbuf);
      free(buf);
    } else
      ret = -1;
    info() << "fd = " << fd << ", buf_address = " << hex << buf_address << dec
           << ", ret = " << hex << ret << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,ret < 0);
#else // linux
    ret = -1;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,true);
#endif // linux
  }

  void PPC_SystemCall::LSC_getuid32() {
    uid_t ret;

    ret = getuid();
    info() << "getuid32() return " << hex << ((PARAMETER_TYPE)ret) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,false);
  }



  void PPC_SystemCall::LSC_getgid32() {
    gid_t ret;

    ret = getgid();
    info() << "setuid32() return " << hex << ((PARAMETER_TYPE)ret) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,false);
  }

  void PPC_SystemCall::LSC_geteuid32() {
    uid_t ret;

    ret = geteuid();
    info() << "geteuid32() ret = " << hex << ((PARAMETER_TYPE)ret) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,false);
  }



  void PPC_SystemCall::LSC_getegid32() {
    gid_t ret;

    ret = getegid();
    info() << "getegid32() ret = " << hex << ((PARAMETER_TYPE)ret) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,false);
  }



  void PPC_SystemCall::LSC_flistxattr() {
    error() << "TODO: " << __FUNCTION__ << ":"
         << __FILE__ << ":" << __LINE__ << endl;
  }

  void PPC_SystemCall::LSC_exit_group() {
    info() << "exit_group() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }

  void PPC_SystemCall::LSC_fcntl() {
    int64_t ret;

    ret = fcntl(exp->GetSystemCallParam(syscall_param_offset+0),
                exp->GetSystemCallParam(syscall_param_offset+1),
                exp->GetSystemCallParam(syscall_param_offset+2));
    info() << "fcntl() ret = " <<  ((PARAMETER_TYPE)ret)  << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret,ret < 0);
  }


  void PPC_SystemCall::LSC_fcntl64() {
    //STF
    //uint32_t p0 = exp->GetSystemCallParam(syscall_param_offset+0);
    //uint32_t p1 = exp->GetSystemCallParam(syscall_param_offset+1);
    //cerr << "fcntl64: fd=" << p0 << " cmd=" << p1 << endl;
    //EOSTF
    info() << "fcntl64() ret = 0x" << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_dup() {
    int ret;
    int oldfd = exp->GetSystemCallParam(syscall_param_offset+0);

    ret = dup(oldfd);
    info() << "dup() old fd = " << oldfd << ", new fd = " << ((PARAMETER_TYPE)ret) << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)ret, ret < 0);
  }


  void PPC_SystemCall::LSC_ioctl() {
    info() << "ioctl() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_ugetrlimit() {
    info() << "ugetrlimit() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_getrlimit() {
    info() << "getrlimit() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_setrlimit() {
    info() << "setrlimit() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_rt_sigaction() {
    //STF
    info() << "STF//SYSCALL//rt_sigaction" << endl;
    //EOSTF
    info() << "ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_getrusage() {
    info() << "getrusage() ret = 0x" << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  void PPC_SystemCall::LSC_unlink() {
    error() << "Unimplemented syscall : LSC_unlink() ! \n" << endl;
    info() << "ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }


  //stf

  void PPC_SystemCall::LSC_rename()
  { ADDRESS_TYPE addr1,addr2;
    int pathnamelen1,pathnamelen2;
    char *pathname1,*pathname2;
    int64_t ret;

    addr1 = exp->GetSystemCallParam(syscall_param_offset+0);
    addr2 = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen1 = StringLength(addr1);
    pathnamelen2 = StringLength(addr2);
    pathname1 = (char *) malloc(pathnamelen1 + 1);
    pathname2 = (char *) malloc(pathnamelen2 + 1);
    exp->ReadMemory(addr1, pathname1, pathnamelen1 + 1);
    exp->ReadMemory(addr2, pathname2, pathnamelen2 + 1);
    ret = rename(pathname1, pathname2);
    info() << "rename(pathname=\"" << pathname1 << "\",\"" << pathname2 << "\" ) return " << ret << endl;
    free(pathname1);
    free(pathname2);
    exp->SetSystemCallStatus(ret, (ret < 0));
  }



  void PPC_SystemCall::LSC_time()
  { info() << "time() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    ADDRESS_TYPE time_t_addr = (ADDRESS_TYPE) exp->GetSystemCallParam(syscall_param_offset+0);
    time_t t1,t2;

    // cerr << "t1=" << t1 << endl;
    // cerr << "t2=" << t2 << endl;
    // cerr << "sizeof(t2)=" << sizeof(t2) << endl;
    // cerr << "time_t_addr=0x" << hex << time_t_addr << dec << endl;

    t1 = time(&t2);
    uint32_t t2b = t2;

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { t2b = Host2BigEndian(t2b);
      }
    else
      { t2b = Host2LittleEndian(t2b);
      }
    exp->WriteMemory(time_t_addr, &t2b, sizeof(t2));
    exp->SetSystemCallStatus(t1, t1 == -1);
  }


  void PPC_SystemCall::LSC_gettimeofday()
  { ADDRESS_TYPE tv_addr = (ADDRESS_TYPE) exp->GetSystemCallParam(syscall_param_offset+0);
    ADDRESS_TYPE tz_addr = (ADDRESS_TYPE) exp->GetSystemCallParam(syscall_param_offset+1);
    int res = -1;
    if(tz_addr!=0)
      { error() << "Error: Syscall GETTTIMEOFDAY with second argument not null." << endl;
      }
    else
      { struct timeval tv;
        res = gettimeofday(&tv,NULL);

        void *tv_res = exp->ConvertTime(&tv);
        exp->WriteMemory(tv_addr, tv_res, exp->TimeSize());
      }
    exp->SetSystemCallStatus(res, res == -1);
  }

  //EOSTF


  void PPC_SystemCall::LSC_socketcall() {
    info() << "socketcall() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL), true);
  }


  void PPC_SystemCall::LSC_rt_sigprocmask() {
    //STF
    info() << "STF//SYSCALL//rt_sigprocmask" << endl;
    //EOSTF
    info() << "sigprocmask() ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL), true);
  }


  void PPC_SystemCall::LSC_kill() {
    //STF
    info() << "STF//SYSCALL//KILL" << endl;
    //EOSTF
    info() << "kill() ret = " << hex << ((PARAMETER_TYPE)0) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)0, false);
  }
  //STF

  void PPC_SystemCall::LSC_sysctl()
  { int ret = 0;
    // Allocating fields
    uint32_t sysctl_nlen = exp->GetSystemCallParam(syscall_param_offset+1);

    uint32_t emulator_name_address;
    uint32_t emulator_oldval_address = exp->GetSystemCallParam(syscall_param_offset+2);
    uint32_t emulator_oldlen_address = exp->GetSystemCallParam(syscall_param_offset+3);
    uint32_t emulator_newval_address = exp->GetSystemCallParam(syscall_param_offset+4);
    uint32_t sysctl_newlen           = exp->GetSystemCallParam(syscall_param_offset+5);

    uint32_t sysctl_oldlen;
    exp->ReadMemory(exp->GetSystemCallParam(syscall_param_offset+0), &emulator_name_address, sizeof(int));
    exp->ReadMemory(emulator_oldlen_address, &sysctl_oldlen, sizeof(int));

    int *sysctl_name = (int*) malloc(sysctl_nlen*sizeof(int));
    char *sysctl_newval = NULL;
    char *sysctl_oldval = NULL;

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { sysctl_oldlen = Host2BigEndian(sysctl_oldlen);
      }
    else
      { sysctl_oldlen = Host2BigEndian(sysctl_oldlen);
      }

    if(sysctl_oldlen>0)
      { sysctl_oldval = (char*)malloc(sysctl_oldlen);
        strcpy(sysctl_oldval,"");
      }
    if(sysctl_newlen>0)
      { sysctl_newval = (char*)malloc(sysctl_newlen);
        exp->ReadMemory(emulator_newval_address, sysctl_newval, sysctl_newlen);
      }

    if(sysctl_name)
      {
        if(exp->GetEndianess() == E_BIG_ENDIAN)
          { emulator_name_address = Host2BigEndian(emulator_name_address);
          }
        else
          { emulator_name_address = Host2LittleEndian(emulator_name_address);
          }
        exp->ReadMemory(emulator_name_address, sysctl_name, sizeof(int)*sysctl_nlen);
        if(exp->GetEndianess() == E_BIG_ENDIAN)
          { for(unsigned int i=0; i<sysctl_nlen; i++)
              { sysctl_name[i] = Host2BigEndian(sysctl_name[i]);
              }
          }
        else
          { for(unsigned int i=0; i<sysctl_nlen; i++)
              { sysctl_name[i] = Host2LittleEndian(sysctl_name[i]);
              }
          }

        //convert to size_t for 64 hosts...
        size_t sysctl_ol = sysctl_oldlen;
        size_t sysctl_nl = sysctl_newlen;

        ret = sysctl(sysctl_name, sysctl_nl, sysctl_oldval, &sysctl_ol, sysctl_newval, sysctl_newlen);

        //convert to size_t for 64 hosts...
        sysctl_oldlen = sysctl_ol;
        sysctl_newlen = sysctl_nl;

        //      cerr << "STF//SYSCALL//SYSCTL { name={ ";
        //      for(int i=0; i<sysctl_nlen; i++)
        //      { cerr << sysctl_name[i] << " ";
        //      }
        //      cerr << "} nlen=" << sysctl_nlen << " oldval='" << sysctl_oldval << "' oldlen=" << sysctl_oldlen << " newval=";
        //      if(sysctl_newval) cerr << "'" << sysctl_newval << "'";
        //      else cerr << "(null)";
        //      cerr << " newlen=" << sysctl_newlen << " }" << endl;

        //Syscall is done, let's pass by output values to the simualated memory
        exp->WriteMemory(emulator_oldval_address, sysctl_oldval, sysctl_oldlen);
        if(exp->GetEndianess() == E_BIG_ENDIAN)
          { sysctl_oldlen = Host2BigEndian(sysctl_oldlen);
          }
        else
          { sysctl_oldlen = Host2LittleEndian(sysctl_oldlen);
          }
        exp->WriteMemory(emulator_oldlen_address, &sysctl_oldlen, sizeof(int));
        //Freeing malloced resources
        free(sysctl_name);
        if(sysctl_oldlen>0) free(sysctl_oldval);
        if(sysctl_newlen>0) free(sysctl_newval);
      }
    exp->SetSystemCallStatus(ret, ret < 0);
  }


  void PPC_SystemCall::LSC_pipe()
  { uint32_t p0 = exp->GetSystemCallParam(syscall_param_offset+0);
    int fds[2];

    int ret = pipe(fds);

    info() << "STF//SYSCALL//PIPE => " << fds[0] << "," << fds[1] << endl;

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { fds[0] = Host2BigEndian(fds[0]);
        fds[1] = Host2BigEndian(fds[1]);
      }
    else
      { fds[0] = Host2LittleEndian(fds[0]);
        fds[1] = Host2LittleEndian(fds[1]);
      }

    exp->WriteMemory(p0, fds, 2*sizeof(uint32_t));

    exp->SetSystemCallStatus(ret, (ret < 0));
  }


  void PPC_SystemCall::LSC_rt_sigqueueinfo()
  { int ret=0;
    static int my_nb_call=0;
    my_nb_call++;
    if(my_nb_call>10)
      { error() << "stopping: too much rt_sigqueueinfo" << endl;
        exit(1);
      }
    info() << "STF//SYSCALL//rt_sigqueueinfo" << endl;
    uint32_t p0 = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t p1 = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t p2 = exp->GetSystemCallParam(syscall_param_offset+2);

    info() << "p0 = " << hex << p0 << dec << endl;
    info() << "p1 = " << p1 << endl;
    info() << "p2 = " << hex << p2 << dec << endl;

    exp->SetSystemCallStatus(ret, (ret < 0));
    //      exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);

    //    exit(1);

  }

  //STF

  void PPC_SystemCall::LSC_rmdir()
  { ADDRESS_TYPE addr;
    int pathnamelen;
    char *pathname;
    int64_t ret;
    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(addr);
    pathname = (char *) malloc(pathnamelen + 1);
    exp->ReadMemory(addr, pathname, pathnamelen + 1);
    ret = rmdir(pathname);
    info() << "rmdir(pathname=\"" << pathname << "\") return " << ret << endl;
    free(pathname);
    exp->SetSystemCallStatus(ret, (ret < 0));
  }
  //EOSTF

  //tim

  void PPC_SystemCall::LSC_mkdir()
  { ADDRESS_TYPE addr;
    int pathnamelen;
    char *pathname;
    mode_t mode;
    int64_t ret;

    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(addr);
    pathname = (char *) malloc(pathnamelen + 1);
    exp->ReadMemory(addr, pathname, pathnamelen + 1);
    mode = exp->GetSystemCallParam(syscall_param_offset+1);
    ret = mkdir(pathname, mode);
    info() << "mkdir(pathname=\"" << pathname << "\", mode=0x" << mode << dec << ") return " << ret << endl;
    free(pathname);
    exp->SetSystemCallStatus(ret, (ret < 0));
  }


  void PPC_SystemCall::LSC_chown()
  { ADDRESS_TYPE addr;
    int pathnamelen;
    char *pathname;
    uid_t uid;
    gid_t gid;
    int ret;
    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(addr);
    pathname = (char *) malloc(pathnamelen + 1);
    exp->ReadMemory(addr, pathname, pathnamelen + 1);
    uid = exp->GetSystemCallParam(syscall_param_offset+1);
    gid = exp->GetSystemCallParam(syscall_param_offset+2);
    ret = chown(pathname, uid, gid);
    free(pathname);
    exp->SetSystemCallStatus(ret, ret < 0);
  }

  void PPC_SystemCall::LSC_getcwd()
  {
    ADDRESS_TYPE addr;
    size_t size;
    char* buf;

    int pathnamelen;
    char *pathname;
    int ret;

    addr = exp->GetSystemCallParam(syscall_param_offset+0);
    size = exp->GetSystemCallParam(syscall_param_offset+1);
    buf = (char*)malloc(size);
    if(buf){
      if(getcwd(buf,size)!=NULL){
        exp->WriteMemory(addr, buf, size);
        ret=addr;
      }else
        ret=0;
      free(buf);
    }else
      ret = 0;
    exp->SetSystemCallStatus(ret, ret <= 0);
  }


  void PPC_SystemCall::LSC_stat64()
  { int ret;
#ifdef linux
    ADDRESS_TYPE buf_address;
    struct stat64 *buf;
    ADDRESS_TYPE pathname_address;
    int pathnamelen;
    char* pathname;

    pathname_address = exp->GetSystemCallParam(syscall_param_offset+0);
    pathnamelen = StringLength(pathname_address);
    pathname = (char *)malloc(pathnamelen + 1);
    if(pathname)
      { exp->ReadMemory(pathname_address, pathname, pathnamelen + 1);
        buf_address = exp->GetSystemCallParam(syscall_param_offset+1);
        buf = (struct stat64 *)malloc(sizeof(struct stat64));
        if(buf)
          { ret = stat64(pathname, buf);
            char *newbuf = (char *)(exp->ConvertStat64(buf));
            exp->WriteMemory(buf_address, newbuf, exp->Stat64Size());
            free(newbuf);
            free(buf);
          } else ret = -1;
      } else ret = -1;
    info() << "pathname = " << pathname << ", buf_address = " << hex << buf_address << dec << ", ret = " << hex << ret << dec << endl;
    if(pathname) free(pathname);
    exp->SetSystemCallStatus(ret,ret < 0);
#else
    ret = -1;
    exp->SetSystemCallStatus(ret,true);
#endif
  }
  //eotim

  // ------------------------------------------------------------------------------
#if 0

  void PPC_SystemCall::LSC_pthread_create() /*bbb*/
  { //  int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
    PthreadCheck ();

    uint32_t param_thread_addr   = exp -> GetSystemCallParam(syscall_param_offset+0);
    uint32_t param_attr          = exp -> GetSystemCallParam(syscall_param_offset+1);
    uint32_t param_start_routine = exp -> GetSystemCallParam(syscall_param_offset+2);
    uint32_t param_arg           = exp -> GetSystemCallParam(syscall_param_offset+3);

    cerr << "pthread_create:" << endl;
    cerr << "  param_thread_addr=   " << hex << param_thread_addr << dec << endl;
    cerr << "  param_attr=          " << hex << param_attr << dec << endl;
    cerr << "  param_start_routine= " << hex << param_start_routine << dec << endl;
    cerr << "  param_arg=           " << hex << param_arg << dec << endl;


    uint32_t thread_id = 0;
    int32_t ret;

    // We don't use param_attr at the moment. 'pthread_create' only
    // has default behavior.
    ret = pthread_port -> pthread_create(&thread_id, NULL,
                                         param_start_routine, param_arg);


    // We MUST take endianness into account here, because we can get
    // back pthread_t as a direct argument in pthread_join.
    thread_id = Host2Target (exp -> GetEndianess (), thread_id);
    exp -> WriteMemory(param_thread_addr, &thread_id, sizeof(thread_id));

    // Return code

    // The 'false' passed here deserves an explanation. The second
    // parameter to 'SetSystemCallStatus' indicates whether the system
    // call failed or not (which means setting a bit in the 'cr0'
    // register on the PowerPC). If set to true, something subtle
    // happens: the glibc doesn't return the same return code as the
    // system call, but rather -1, setting 'errno' to the former
    // value. Thus, this flag doesn't indicate failure really, but
    // triggers a mechanism whereby the return code is put in errno
    // and the system call returns -1. For pthread calls, errno is
    // never set; instead, return codes have to be returned
    // directly. Thus, the 'false'.
    exp -> SetSystemCallStatus(ret, false);
  }


  void PPC_SystemCall::LSC_pthread_exit()
  { // void pthread_exit(void *value_ptr);
    PthreadCheck ();

    uint32_t value_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    pthread_port -> pthread_exit(value_ptr);
  }


  void PPC_SystemCall::LSC_pthread_self()
  { // pthread_t pthread_self(void);
    PthreadCheck ();

    int32_t ret = pthread_port -> pthread_self();
    // 'pthread_self' can't fail.
    exp -> SetSystemCallStatus(ret, false);
  }



  void PPC_SystemCall::LSC_pthread_join1()
  { // int pthread_join(pthread_t thread, void **value_ptr);
    PthreadCheck ();

    uint32_t thread = exp -> GetSystemCallParam(syscall_param_offset+0);

    int32_t ret = pthread_port -> pthread_join1(thread);
    exp -> SetSystemCallStatus (ret, false);
  }


  void PPC_SystemCall::LSC_pthread_join2()
  { // int pthread_join(pthread_t thread, void **value_ptr);
    PthreadCheck ();

    uint32_t thread = exp -> GetSystemCallParam(syscall_param_offset+0);

    uint32_t ret = pthread_port -> pthread_join2(thread);
    exp -> SetSystemCallStatus (ret, false);
  }


  void PPC_SystemCall::LSC_pthread_mutex_init()
  { // int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
    PthreadCheck ();

    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    // Not used at present
    // uint32_t attr_ptr  = exp -> GetSystemCallParam(syscall_param_offset+1);

    pthread_mutex_t mutex;

    // We don't take into account endianness, because pthread_mutex_t
    // is an opaque type.
    int32_t ret = pthread_port -> pthread_mutex_init(& mutex, NULL);

    // Writing result into memory
    exp -> WriteMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // Return code
    exp -> SetSystemCallStatus(ret, false);
  }


  void PPC_SystemCall::LSC_pthread_mutex_destroy()
  { // int pthread_mutex_destroy(pthread_mutex_t *mutex);
    PthreadCheck ();

    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);

    pthread_mutex_t mutex;
    exp -> ReadMemory (mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // We don't take into account endianness, because pthread_mutex_t
    // is an opaque type.
    int32_t ret = pthread_port -> pthread_mutex_destroy (& mutex);

    exp -> WriteMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // Return code
    exp -> SetSystemCallStatus(ret, false);
  }


  void PPC_SystemCall::LSC_pthread_mutex_trylock()
  {
    PthreadCheck ();

    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    pthread_mutex_t mutex;
    int32_t ret;

    exp -> ReadMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // We don't take into account endianness, because pthread_mutex_t
    // is an opaque type.
    ret = pthread_port -> pthread_mutex_trylock (& mutex);
    exp -> WriteMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // Return code
    exp -> SetSystemCallStatus(ret, false);
  }


  void PPC_SystemCall::LSC_pthread_mutex_lock()
  {
    PthreadCheck ();

    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    pthread_mutex_t mutex;
    int32_t ret;

    //cerr << "LSC_thread_mutex_locking @="<<hex<<mutex_ptr <<endl;
    exp -> ReadMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));
    //cerr << hex<<" tmp @="<<&mutex<< dec<<" lock="<< mutex.__data.__lock <<endl;

    // We don't take into account endianness, because pthread_mutex_t
    // is an opaque type.
    ret = pthread_port -> pthread_mutex_lock (& mutex, mutex_ptr);
    exp -> WriteMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));
    //cerr << "LSC_thread_mutex_locked lock="<<dec << mutex.__data.__lock <<endl;

    // Return code
    exp -> SetSystemCallStatus(ret, false);
  }


  void PPC_SystemCall::LSC_pthread_mutex_unlock()
  {
    PthreadCheck ();

    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    pthread_mutex_t mutex;
    int32_t ret;

    //cerr << "LSC_thread_mutex_unlocking @="<<hex<<mutex_ptr <<endl;
    exp -> ReadMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));
    //cerr << hex<<" tmp @="<<&mutex<< dec<<" lock="<< mutex.__data.__lock <<endl;

    // We don't take into account endianness, because pthread_mutex_t
    // is an opaque type.
    ret = pthread_port -> pthread_mutex_unlock (& mutex, mutex_ptr);
    exp -> WriteMemory(mutex_ptr, & mutex, sizeof(pthread_mutex_t));
    //cerr << "LSC_thread_mutex_unlocked lock="<<dec << mutex.__data.__lock <<endl;

    // Return code
    exp -> SetSystemCallStatus(ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_spin_init()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t spin_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    uint32_t pshared = exp -> GetSystemCallParam (1);

    // Fetching from simulator's memory
    pthread_spinlock_t spin_lock;

    if (pshared == PTHREAD_PROCESS_SHARED)
      {
        warning() << "WARNING: 'pthread_spin_init' called with PTHREAD_PROCESS_SHARED." << endl;
        warning() << "This option has no meaning in UNISIM since there is only one program/process executing at once." << endl;
        pshared = PTHREAD_PROCESS_PRIVATE;
      }

    exp -> ReadMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Executing call
    pthread_port -> pthread_spin_init (& spin_lock, pshared);

    // Writing result into memory
    exp -> WriteMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Return code
    exp -> SetSystemCallStatus(0, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_spin_destroy()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t spin_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Fetching from simulator's memory
    pthread_spinlock_t spin_lock;
    exp -> ReadMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_spin_destroy (& spin_lock);

    // Writing result into memory
    exp -> WriteMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_spin_trylock()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t spin_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Fetching from simulator's memory
    pthread_spinlock_t spin_lock;
    exp -> ReadMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_spin_trylock (& spin_lock);

    // Writing result into memory
    exp -> WriteMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_spin_unlock()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t spin_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Fetching from simulator's memory
    pthread_spinlock_t spin_lock;
    exp -> ReadMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_spin_unlock (& spin_lock);

    // Writing result into memory
    exp -> WriteMemory (spin_ptr, (void *) & spin_lock, sizeof(pthread_spinlock_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_cond_init()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t cond_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    // 'attr_ptr' is ignored at present
    // uint32_t attr_ptr = exp -> GetSystemCallParam(syscall_param_offset+1);

    // Fetching from simulator's memory
    pthread_cond_t cond_var;
    exp -> ReadMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_cond_init (& cond_var, NULL);

    // Writing result into memory
    exp -> WriteMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_cond_destroy()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t cond_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Fetching from simulator's memory
    pthread_cond_t cond_var;
    exp -> ReadMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_cond_destroy (& cond_var);

    // Writing result into memory
    exp -> WriteMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  void PPC_SystemCall::LSC_pthread_cond_wait()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t cond_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    uint32_t mutex_ptr = exp -> GetSystemCallParam(syscall_param_offset+1);

    // Fetching from simulator's memory
    pthread_cond_t cond_var;
    pthread_mutex_t mutex;
    exp -> ReadMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));
    exp -> ReadMemory (mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_cond_wait (& cond_var, & mutex,
                                                     cond_ptr, mutex_ptr);

    // Writing result into memory
    exp -> WriteMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));
    exp -> WriteMemory (mutex_ptr, & mutex, sizeof(pthread_mutex_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_cond_signal()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t cond_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    uint32_t broadcast = exp -> GetSystemCallParam (1);

    // Fetching from simulator's memory
    pthread_cond_t cond_var;
    exp -> ReadMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Executing call
    int32_t ret = pthread_port -> pthread_cond_signal (& cond_var, cond_ptr, broadcast != 0);

    // Writing result into memory
    exp -> WriteMemory (cond_ptr, & cond_var, sizeof(pthread_cond_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_key_create()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t key_ptr = exp -> GetSystemCallParam(syscall_param_offset+0);
    uint32_t dest_func = exp -> GetSystemCallParam(syscall_param_offset+1);

    // Executing call
    pthread_key_t key;
    int32_t ret = pthread_port -> pthread_key_create (& key, dest_func);

    // We MUST take endianness into account here, because we'll get
    // the key back as a direct argument to other key-related syscalls.
    key = Host2Target (exp -> GetEndianess (), key);

    // Writing result into memory
    exp -> WriteMemory (key_ptr, & key, sizeof(pthread_key_t));

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_key_delete()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t key = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Executing call
    int32_t ret = pthread_port -> pthread_key_delete (key);

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_getspecific()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t key = exp -> GetSystemCallParam(syscall_param_offset+0);

    // Executing call
    uint32_t ret = pthread_port -> pthread_getspecific (key);

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  template <class ADDRESS_TYPE, class PARAMETER_TYPE>
  void PPC_SystemCall::LSC_pthread_setspecific()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t key = exp -> GetSystemCallParam (0);
    uint32_t val = exp -> GetSystemCallParam (1);

    // Executing call
    int32_t ret = pthread_port -> pthread_setspecific (key, val);

    // Setting syscall result
    exp -> SetSystemCallStatus (ret, false);
  }

  void PPC_SystemCall::LSC_pthread_key_getdtor()
  {
    // Pthread service presence check
    PthreadCheck ();

    // Retrieving args
    uint32_t info_ptr = exp -> GetSystemCallParam (0);

    // Calling syscall
    __pthread_internal_dtor_call_t info;
    int32_t ret = pthread_port -> pthread_key_getdtor (& info);

    // Writing into memory
    if (ret)
      {
        // 'info' has been filled.
        // Take endianness into account.
        info.dtor = Host2Target (exp -> GetEndianess (), info.dtor);
        info.val = Host2Target (exp -> GetEndianess (), info.val);

        // Final write
        exp -> WriteMemory (info_ptr, & info, sizeof(info));
      }

    // Result
    exp -> SetSystemCallStatus (ret, false);
  }

#ifdef CAPSULE

  void PPC_SystemCall::LSC_cap_split()
  { PthreadCheck ();
    pthread_port -> capsys_split();
  }


  void PPC_SystemCall::LSC_cap_divide()
  {
    PthreadCheck ();

    uint32_t param_thread_addr   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t param_group_addr  = exp->GetSystemCallParam(syscall_param_offset+1);

    uint32_t thread_id = 0;
    uint32_t group_id = 0;

    //cerr << "STF//SYSCALL//cap_divide" << endl;
    //cerr << "  param_thread        = 0x" << hex << param_thread_addr << dec << endl;
    //cerr << "  param_group         = 0x" << hex << param_group_addr << dec << endl;
    pthread_port-> capsys_divide(&thread_id,&group_id);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { thread_id = Host2BigEndian(thread_id);
        group_id = Host2BigEndian(group_id);
      }
    else
      { thread_id = Host2LittleEndian(thread_id);
        group_id = Host2LittleEndian(group_id);
      }

    exp->WriteMemory(param_thread_addr, &thread_id, sizeof(uint32_t));
    exp->WriteMemory(param_group_addr, &group_id, sizeof(uint32_t));
  }


  void PPC_SystemCall::LSC_cap_execute()
  {
    PthreadCheck ();

    uint32_t thread_id = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t group_id = exp->GetSystemCallParam(syscall_param_offset+1);

    //cerr << "STF//SYSCALL//cap_execute" << endl;
    //cerr << "  thread_id  = 0x" << hex << thread_id << dec << endl;
    //cerr << "  group_id   = 0x" << hex << group_id << dec << endl;
    pthread_port-> capsys_execute(thread_id,group_id);
  }


  void PPC_SystemCall::LSC_cap_exit()
  { PthreadCheck ();
    pthread_port -> capsys_exit();
  }


  void PPC_SystemCall::LSC_cap_join()
  { PthreadCheck ();
    pthread_port -> capsys_join();
  }


  void PPC_SystemCall::LSC_cap_get_proc_id()
  { PthreadCheck ();
    uint32_t proc_addr   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t proc;
    pthread_port -> capsys_get_proc_id(&proc);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { proc = Host2BigEndian(proc);
      }
    else
      { proc = Host2LittleEndian(proc);
      }
    exp->WriteMemory(proc_addr, &proc, sizeof(uint32_t));
  }


  void PPC_SystemCall::LSC_cap_get_probing_proc_id()
  { PthreadCheck ();
    uint32_t proc_addr   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t proc;
    pthread_port -> capsys_get_probing_proc_id(&proc);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { proc = Host2BigEndian(proc);
      }
    else
      { proc = Host2LittleEndian(proc);
      }
    exp->WriteMemory(proc_addr, &proc, sizeof(uint32_t));
  }



  void PPC_SystemCall::LSC_cap_get_proc_state()
  { PthreadCheck ();
    uint32_t proc         = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t state_addr   = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t state;
    pthread_port -> capsys_get_proc_state(proc,&state);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { state = Host2BigEndian(state);
      }
    else
      { state = Host2LittleEndian(state);
      }
    exp->WriteMemory(state_addr, &state, sizeof(uint32_t));
  }


  void PPC_SystemCall::LSC_cap_set_proc_state()
  { PthreadCheck ();
    uint32_t proc    = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t state   = exp->GetSystemCallParam(syscall_param_offset+1);
    pthread_port -> capsys_set_proc_state(proc,state);
  }


  void PPC_SystemCall::LSC_cap_thread_wakeup()
  { PthreadCheck ();
    uint32_t proc   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t thread = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t group  = exp->GetSystemCallParam(syscall_param_offset+2);
    uint32_t ctxt   = exp->GetSystemCallParam(syscall_param_offset+3);

    pthread_port -> capsys_thread_wakeup(proc,thread,group,(uint32_t *)ctxt);
  }



  void PPC_SystemCall::LSC_cap_get_available_thread()
  { PthreadCheck ();
    uint32_t proc_addr   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t state_addr   = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t proc,state;
    pthread_port -> capsys_get_available_thread(&proc,&state);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { proc = Host2BigEndian(proc);
        state = Host2BigEndian(state);
      }
    else
      { proc = Host2LittleEndian(proc);
        state= Host2LittleEndian(state);
      }
    exp->WriteMemory(proc_addr, &proc, sizeof(uint32_t));
    exp->WriteMemory(state_addr, &state, sizeof(uint32_t));
  }

#endif //CAPSULE
#ifdef NOC_SUPPORT_PARALLELIZATION

  void PPC_SystemCall::LSC_npthread_create()
  {
    PthreadCheck ();

    uint32_t param_thread_addr   = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t param_pthread_addr  = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t param_pcore_addr  = exp->GetSystemCallParam(syscall_param_offset+2);
    uint32_t param_attr          = exp->GetSystemCallParam(syscall_param_offset+3);

    uint32_t thread_id = 0;
    uint32_t pthread_id = 0;
    uint32_t pcore_id = 0;

    //cerr << "STF//SYSCALL//pthread_create" << endl;
    //cerr << "  param_thread        = 0x" << hex << param_thread << dec << endl;
    //cerr << "  param_pthread       = 0x" << hex << param_pthread << dec << endl;
    //cerr << "  param_attr          = 0x" << hex << param_attr << dec << endl;
    pthread_port->npthread_create(&thread_id,&pthread_id,&pcore_id,param_attr);

    if(exp->GetEndianess() == E_BIG_ENDIAN)
      { thread_id = Host2BigEndian(thread_id);
        pthread_id = Host2BigEndian(pthread_id);
        pcore_id = Host2BigEndian(pcore_id);
      }
    else
      { thread_id = Host2LittleEndian(thread_id);
        pthread_id = Host2LittleEndian(pthread_id);
        pcore_id = Host2LittleEndian(pcore_id);
      }

    exp->WriteMemory(param_thread_addr, &thread_id, sizeof(uint32_t));
    exp->WriteMemory(param_pthread_addr, &pthread_id, sizeof(uint32_t));
    exp->WriteMemory(param_pcore_addr, &pcore_id, sizeof(uint32_t));
  }


  void PPC_SystemCall::LSC_npthread_execute()
  {
    PthreadCheck ();

    uint32_t thread_id  = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t pthread_id = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t pcore_id   = exp->GetSystemCallParam(syscall_param_offset+2);

    //cerr << "STF//SYSCALL//pthread_execute" << endl;
    //cerr << "  thread_id  = 0x" << hex << thread_id << dec << endl;
    //cerr << "  pthread_id = 0x" << hex << pthread_id << dec << endl;
    //cerr << "  pcore_id   = 0x" << hex << pcore_id << dec << endl;
    pthread_port->npthread_execute(thread_id,pthread_id,pcore_id);
  }

  void PPC_SystemCall::LSC_pthread_join()
  { // int pthread_join(pthread_t thread, void **value_ptr);
    if(!pthread_port)
      { error() << "Error: Syscall service can't handle pthread syscalls if no pthread service is connected ! " << pthread_port << endl;
        exit(1);
      }
    uint32_t thread = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t value_ptr_ptr = exp->GetSystemCallParam(syscall_param_offset+1);
    //cerr << "STF//SYSCALL//pthread_join" << endl;
    pthread_port->pthread_join(thread, value_ptr_ptr);
  }
#endif //NOC_SUPPORT_PARALLELIZATION


  /**
   * \brief Pretty-printer syscall to perform a printf in one
   * simulated instruction instead of thousands.
   */
  void PPC_SystemCall::LSC_syscall_print_str()
  {
    uint32_t str_ptr = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t size = exp->GetSystemCallParam(syscall_param_offset+1)+1;
    char *buf = (char *)malloc(sizeof(char) * (1+size));
    exp->ReadMemory(str_ptr, buf, size);
    cerr << buf;
    free(buf);
  }


  void PPC_SystemCall::LSC_syscall_print_int()
  { uint32_t value = exp->GetSystemCallParam(syscall_param_offset+0);
    cerr << value;
  }


  void PPC_SystemCall::LSC_syscall_print()
  {
    uint32_t thread_id = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t str_ptr = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t size = exp->GetSystemCallParam(syscall_param_offset+2)+1;
    uint32_t value = exp->GetSystemCallParam(syscall_param_offset+3);
    char str[1024];
    exp->ReadMemory(str_ptr, str, size);
    info() << timestamp() << ": \e[1;31m" << thread_id << ": " << str << " 0x" << hex << value << dec << "\e[0m" << endl;
  }


  void PPC_SystemCall::LSC_syscall_print_array()
  {
    uint32_t thread_id = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t str_ptr   = exp->GetSystemCallParam(syscall_param_offset+1);
    uint32_t str_size  = exp->GetSystemCallParam(syscall_param_offset+2)+1;
    uint32_t array_ptr = exp->GetSystemCallParam(syscall_param_offset+3);
    uint32_t size       = exp->GetSystemCallParam(syscall_param_offset+4);
    uint32_t val;
    char str[1024];
    exp->ReadMemory(str_ptr, str, str_size);
    info() << "--- " << str << " -------------------------- (" << timestamp() << ")" << endl;
    for(int i=0; i<size; i++)
      { exp->ReadMemory(array_ptr, &val, sizeof(uint32_t));
        if(exp->GetEndianess() == E_BIG_ENDIAN)
          { val = Host2BigEndian(val);
          }
        else
          { val = Host2LittleEndian(val);
          }
        info() << right << hex << setw(6) << val << dec;
        array_ptr += sizeof(uint32_t);
      }
    info() << dec << endl;
    info() << "--------------------------------" << endl;
  }

  // ------------------------------------------------------------------------------


  void PPC_SystemCall::LSC_syscall_fast_timingevent()
  {
    uint32_t str_ptr = exp->GetSystemCallParam(syscall_param_offset+0);
    char str[1024];
    exp->ReadMemory(str_ptr, str, 1024);
    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    else info() << "\e[1;36mTIMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_timingevent()
  {
    uint32_t str_ptr = exp->GetSystemCallParam(syscall_param_offset+0);
    uint32_t size = exp->GetSystemCallParam(syscall_param_offset+1)+1;
    char str[1024];
    exp->ReadMemory(str_ptr, str, size);
    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    else info() << "\e[1;36mTITMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_timingevent_start()
  {
    const char *str = "start";
    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    else info() << "\e[1;36mTITMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_timingevent_stop()
  { const char *str = "stop";
    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    else info() << "\e[1;36mTITMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_timingevent_wave()
  { const char *str = "wave";
    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    else info() << "\e[1;36mTITMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_output_dsp()
  {
    char val_str[80];
    int fd = exp->GetSystemCallParam(syscall_param_offset+0);
    ADDRESS_TYPE buf_ptr = exp->GetSystemCallParam(syscall_param_offset+1);
    size_t size = exp->GetSystemCallParam(syscall_param_offset+2);
    uint32_t *buf = (uint32_t*)malloc(size*sizeof(uint32_t));
    exp->ReadMemory(buf_ptr, buf, size*sizeof(uint32_t));
    for(int i=0;i<size;i++)
      { uint32_t val=buf[i];
        if(exp->GetEndianess() == E_BIG_ENDIAN)
          { val = BigEndian2Host(val);
          }
        else
          { val = LittleEndian2Host(val);
          }
        sprintf(val_str,"%d\n",val);
        write(fd,val_str,strlen(val_str));
      }
    free(buf);
    //    char str[1024];
    //    exp->ReadMemory(str_ptr, str, size);
    //    if(timingevent_port) timingevent_port->report_event(timestamp(),str);
    //    else cerr << "\e[1;36mTITMING EVENT: \e[0m" << str << " : " << timestamp() << endl;
  }


  void PPC_SystemCall::LSC_syscall_bin_dump_init()
  {
    int id = max_bin_dumps_id;
    max_bin_dumps_id++;
    uint32_t str_ptr = exp->GetSystemCallParam(syscall_param_offset+0);
    char str[1024];
    exp->ReadMemory(str_ptr, str, 1024);

    FILE *f = fopen(str, "w");
    bin_dumps[id] = f;

    //    cerr << "LSC_syscall_bin_dump_init returning " << id << " for " << str << endl;

    exp -> SetSystemCallStatus(id, /*iserror=*/false);
  }


  void PPC_SystemCall::LSC_syscall_bin_dump_write()
  {
    int id = exp->GetSystemCallParam(syscall_param_offset+0);
    ADDRESS_TYPE buf_ptr = exp->GetSystemCallParam(syscall_param_offset+1);
    size_t size = exp->GetSystemCallParam(syscall_param_offset+2);

    //    cerr << "LSC_syscall_bin_dump_write(" << id << "," << hex << buf_ptr << dec << "," << size << ")" << endl;

    uint32_t *buf = (uint32_t*)malloc(size);
    exp->ReadMemory(buf_ptr, buf, size);

    fwrite(buf,1,size,bin_dumps[id]);
    free(buf);
  }


  void PPC_SystemCall::LSC_syscall_bin_dump_close()
  {
    int id = exp->GetSystemCallParam(syscall_param_offset+0);
    fclose(bin_dumps[id]);
    //    cerr << "LSC_syscall_bin_dump_close(" << id << ")" << endl;
  }

  // ------------------------------------------------------------------------------

  //EOSTF
#endif

  void PPC_SystemCall::LSC_futex() {
    info() << "futex ret = " << hex << ((PARAMETER_TYPE)(-EINVAL)) << dec << endl;
    exp->SetSystemCallStatus((PARAMETER_TYPE)(-EINVAL),true);
  }

  void PPC_SystemCall::SetSyscallNameMap() {
    syscall_name_map[string("unknown")] = &thistype::LSC_unknown;
    syscall_name_map[string("syscall")] = &thistype::LSC_syscall;
    syscall_name_map[string("exit")] = &thistype::LSC_exit;
    syscall_name_map[string("read")] = &thistype::LSC_read;
    syscall_name_map[string("write")] = &thistype::LSC_write;
    syscall_name_map[string("open")] = &thistype::LSC_open;
    syscall_name_map[string("close")] = &thistype::LSC_close;
    syscall_name_map[string("lseek")] = &thistype::LSC_lseek;
    //tim
    syscall_name_map[string("mkdir")] = &thistype::LSC_mkdir;
    //eotim
    //STF
    syscall_name_map[string("rmdir")] = &thistype::LSC_rmdir;
    syscall_name_map[string("gettimeofday")] = &thistype::LSC_gettimeofday;
    //EOSTF
    syscall_name_map[string("getpid")] = &thistype::LSC_getpid;
    syscall_name_map[string("getuid")] = &thistype::LSC_getuid;
    syscall_name_map[string("access")] = &thistype::LSC_access;
    syscall_name_map[string("times")] = &thistype::LSC_times;
    syscall_name_map[string("brk")] = &thistype::LSC_brk;
    syscall_name_map[string("getgid")] = &thistype::LSC_getgid;
    syscall_name_map[string("geteuid")] = &thistype::LSC_geteuid;
    syscall_name_map[string("getegid")] = &thistype::LSC_getegid;
    //tim
    syscall_name_map[string("chown")] = &thistype::LSC_chown;
    //eotim
    syscall_name_map[string("getcwd")] = &thistype::LSC_getcwd;
    syscall_name_map[string("umask")] = &thistype::LSC_umask;
    syscall_name_map[string("munmap")] = &thistype::LSC_munmap;
    syscall_name_map[string("stat")] = &thistype::LSC_stat;
    syscall_name_map[string("fstat")] = &thistype::LSC_fstat;
    syscall_name_map[string("uname")] = &thistype::LSC_uname;
    syscall_name_map[string("llseek")] = &thistype::LSC_llseek;
    syscall_name_map[string("writev")] = &thistype::LSC_writev;
    syscall_name_map[string("mmap")] = &thistype::LSC_mmap;
    syscall_name_map[string("mmap2")] = &thistype::LSC_mmap2;

#ifdef UNISIM_STL_CONTAINERS
    syscall_name_map[string("unisim_malloc")] = &thistype::LSC_unisim_malloc;
    syscall_name_map[string("unisim_free")] = &thistype::LSC_unisim_free;
    syscall_name_map[string("unisim_realloc")] = &thistype::LSC_unisim_realloc;
#endif //UNISIM_STL_CONTAINERS

    syscall_name_map[string("mprotect")] = &thistype::LSC_mprotect;
    syscall_name_map[string("truncate")] = &thistype::LSC_truncate;
    syscall_name_map[string("ftruncate")] = &thistype::LSC_ftruncate;
    //tim
    syscall_name_map[string("stat64")] = &thistype::LSC_stat64;
    //eotim
    syscall_name_map[string("fstat64")] = &thistype::LSC_fstat64;
    syscall_name_map[string("getuid32")] = &thistype::LSC_getuid32;
    syscall_name_map[string("getgid32")] = &thistype::LSC_getgid32;
    syscall_name_map[string("geteuid32")] = &thistype::LSC_geteuid32;
    syscall_name_map[string("getegid32")] = &thistype::LSC_getegid32;
    syscall_name_map[string("fcntl64")] = &thistype::LSC_fcntl64;
    syscall_name_map[string("flistxattr")] = &thistype::LSC_flistxattr;
    syscall_name_map[string("exit_group")] = &thistype::LSC_exit_group;
    syscall_name_map[string("fcntl")] = &thistype::LSC_fcntl;
    syscall_name_map[string("dup")] = &thistype::LSC_dup;
    syscall_name_map[string("ioctl")] = &thistype::LSC_ioctl;
    syscall_name_map[string("ugetrlimit")] = &thistype::LSC_ugetrlimit;
    syscall_name_map[string("getrlimit")] = &thistype::LSC_getrlimit;
    syscall_name_map[string("setrlimit")] = &thistype::LSC_setrlimit;
    syscall_name_map[string("rt_sigaction")] = &thistype::LSC_rt_sigaction;
    syscall_name_map[string("getrusage")] = &thistype::LSC_getrusage;
    syscall_name_map[string("unlink")] = &thistype::LSC_unlink;
    syscall_name_map[string("rename")] = &thistype::LSC_rename;
    syscall_name_map[string("time")] = &thistype::LSC_time;
    syscall_name_map[string("socketcall")] = &thistype::LSC_socketcall;
    syscall_name_map[string("rt_sigprocmask")] = &thistype::LSC_rt_sigprocmask;
    syscall_name_map[string("kill")] = &thistype::LSC_kill;
    //STF
    syscall_name_map[string("sysctl")] = &thistype::LSC_sysctl;
    syscall_name_map[string("pipe")] = &thistype::LSC_pipe;
    syscall_name_map[string("rt_sigqueueinfo")] = &thistype::LSC_rt_sigqueueinfo;

#if 0
    syscall_name_map[string("pthread_create")] = &thistype::LSC_pthread_create;
    syscall_name_map[string("pthread_exit")] = &thistype::LSC_pthread_exit;
    syscall_name_map[string("pthread_join1")] = &thistype::LSC_pthread_join1;
    syscall_name_map[string("pthread_join2")] = &thistype::LSC_pthread_join2;
    syscall_name_map[string("pthread_self")] = &thistype::LSC_pthread_self;
    syscall_name_map[string("pthread_mutex_init")] = &thistype::LSC_pthread_mutex_init;
    syscall_name_map[string("pthread_mutex_destroy")] = &thistype::LSC_pthread_mutex_destroy;
    syscall_name_map[string("pthread_mutex_lock")] = &thistype::LSC_pthread_mutex_lock;
    syscall_name_map[string("pthread_mutex_trylock")] = &thistype::LSC_pthread_mutex_trylock;
    syscall_name_map[string("pthread_mutex_unlock")] = &thistype::LSC_pthread_mutex_unlock;
    syscall_name_map[string("pthread_spin_init")] = &thistype::LSC_pthread_spin_init;
    syscall_name_map[string("pthread_spin_destroy")] = &thistype::LSC_pthread_spin_destroy;
    syscall_name_map[string("pthread_spin_trylock")] = &thistype::LSC_pthread_spin_trylock;
    syscall_name_map[string("pthread_spin_unlock")] = &thistype::LSC_pthread_spin_unlock;
    syscall_name_map[string("pthread_cond_init")] = &thistype::LSC_pthread_cond_init;
    syscall_name_map[string("pthread_cond_destroy")] = &thistype::LSC_pthread_cond_destroy;
    syscall_name_map[string("pthread_cond_wait")] = &thistype::LSC_pthread_cond_wait;
    syscall_name_map[string("pthread_cond_signal")] = &thistype::LSC_pthread_cond_signal;
    syscall_name_map[string("pthread_key_create")] = &thistype::LSC_pthread_key_create;
    syscall_name_map[string("pthread_key_delete")] = &thistype::LSC_pthread_key_delete;
    syscall_name_map[string("pthread_getspecific")] = &thistype::LSC_pthread_getspecific;
    syscall_name_map[string("pthread_setspecific")] = &thistype::LSC_pthread_setspecific;
    syscall_name_map[string("pthread_key_getdtor")] = &thistype::LSC_pthread_key_getdtor;
#ifdef CAPSULE
    syscall_name_map[string("capsys_split")] = &thistype::LSC_cap_split;
    syscall_name_map[string("capsys_divide")] = &thistype::LSC_cap_divide;
    syscall_name_map[string("capsys_execute")] = &thistype::LSC_cap_execute;
    syscall_name_map[string("capsys_exit")] = &thistype::LSC_cap_exit;
    syscall_name_map[string("capsys_join")] = &thistype::LSC_cap_join;
    syscall_name_map[string("capsys_get_proc_id")] = &thistype::LSC_cap_get_proc_id;
    syscall_name_map[string("capsys_thread_wakeup")] = &thistype::LSC_cap_thread_wakeup;
    syscall_name_map[string("capsys_get_proc_state")] = &thistype::LSC_cap_get_proc_state;
    syscall_name_map[string("capsys_set_proc_state")] = &thistype::LSC_cap_set_proc_state;
    syscall_name_map[string("capsys_get_probing_proc_id")] = &thistype::LSC_cap_get_probing_proc_id;
    syscall_name_map[string("capsys_get_available_thread")] = &thistype::LSC_cap_get_available_thread;
#endif //CAPSULE
#ifdef NOC_SUPPORT_PARALLELIZATION
    syscall_name_map[string("npthread_create")] = &thistype::LSC_npthread_create;
    syscall_name_map[string("npthread_execute")] = &thistype::LSC_npthread_execute;
    syscall_name_map[string("pthread_join")] = &thistype::LSC_pthread_join;
#endif //NOC_SUPPORT_PARALLELIZATION

    syscall_name_map[string("syscall_print_str")] = &thistype::LSC_syscall_print_str;
    syscall_name_map[string("syscall_print_int")] = &thistype::LSC_syscall_print_int;
    syscall_name_map[string("syscall_print")] = &thistype::LSC_syscall_print;
    syscall_name_map[string("syscall_print_array")] = &thistype::LSC_syscall_print_array;

    syscall_name_map[string("timingevent")] = &thistype::LSC_syscall_timingevent;
    syscall_name_map[string("timingevent_start")] = &thistype::LSC_syscall_timingevent_start;
    syscall_name_map[string("timingevent_stop")] = &thistype::LSC_syscall_timingevent_stop;
    syscall_name_map[string("timingevent_wave")] = &thistype::LSC_syscall_timingevent_wave;
    syscall_name_map[string("output_dsp")] = &thistype::LSC_syscall_output_dsp;
    syscall_name_map[string("fast_timingevent")] = &thistype::LSC_syscall_fast_timingevent;

    syscall_name_map[string("bin_dump_init")] = &thistype::LSC_syscall_bin_dump_init;
    syscall_name_map[string("bin_dump_write")] = &thistype::LSC_syscall_bin_dump_write;
    syscall_name_map[string("bin_dump_close")] = &thistype::LSC_syscall_bin_dump_close;
    //EOSTF
#endif //if 0
    syscall_name_map[string("futex")] = &thistype::LSC_futex;
  }


}//end of namespace simsoc

