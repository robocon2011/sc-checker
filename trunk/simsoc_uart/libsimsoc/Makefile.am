##
## SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
## LGPL license version 3
##

SUBDIRS =  processors/arm/ArmGen

ARMGEN_CPP_FILES = \
   armpi_dpi_int.cpp armpi_dpi_bool.cpp armpi_dpi_mov.cpp \
   armpi_mli_32.cpp armpi_mli_64_int.cpp armpi_mli_64_uint.cpp \
   armpi_loadstore_admode2_9.cpp \
   armpi_loadstore_admode2_9_zero.cpp \
   armpi_loadstore_admode2_3.cpp \
   armpi_loadstore_admode3_6.cpp \
   armpi_ldr_pc_admode2_9.cpp \
   armpi_swp.cpp \
   armpi_b_h.cpp armpi_b_l.cpp armpi_b_reg.cpp \
   armpi_clz.cpp \
   armpi_swi.cpp \
   armpi_ldmstm_pc.cpp armpi_ldmstm_nopc.cpp \
   armpi_mrs.cpp armpi_msr.cpp
ARMGEN_HPP_FILES = $(ARMGEN_CPP_FILES:%.cpp=%.hpp)

lib_LIBRARIES = libsimsoc.a

nodist_libsimsoc_a_SOURCES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES)
BUILT_SOURCES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES)
CLEANFILES = \
    arm_decode.cpp thumb_decode.cpp $(ARMGEN_CPP_FILES) $(ARMGEN_HPP_FILES) armgen_done
libsimsoc_a_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir) -I$(top_builddir) \
	               -DABS_TOP_SRCDIR="\"$(abs_top_srcdir)\"" \
                       -DABS_TOP_BUILDDIR="\"$(abs_top_builddir)\"" \
                       -DBINDIR="\"$(bindir)\""

EXTRA_DIST = $(srcdir)/processors/arm_v6/simlight/slv6_iss_arm_decode_store.c\
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_thumb_decode_store.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.cold.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.hot.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_grouped.cold.c \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss_grouped.hot.c \
			$(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
			$(srcdir)/processors/ppc/ppc_llvm_lib.cpp \
			 $(srcdir)/processors/arm_v6/simlight/slv6_iss.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_condition.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_math.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_mode.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_processor.c \
			$(srcdir)/processors/arm_v6/simlight/slv6_status_register.c

#=====================================================================
# Tools
#=====================================================================

libsimsoc_a_SOURCES = \
    module.cpp \
    context.cpp \
    command_line.cpp \
    display.cpp \
    io.cpp \
    random.cpp \
    \
    components/dce_xterm.cpp \
    components/bus.cpp \
    components/irqc.cpp \
    components/stop_box.cpp \
    components/nand_flash.cpp \
    components/serial_flash.cpp \
    components/elf_loader.cpp \
    components/dce_stub.cpp \
    components/dce_factory.cpp \
    components/dce_driver.cpp \
    components/st_smi.cpp\
    components/dce_host_uart.cpp \
    components/memory.cpp \
    components/primecell_uart.cpp \
    components/primecell_dmac_pl080.cpp \
    components/dce_host_uart_pthread.cpp \
    components/debug_console.cpp \
    components/rw_stub.cpp \
    components/primecell_vic_pl190.cpp \
    components/rtc.cpp \
    components/primexsys_ctrl.cpp \
    components/uart_16550.cpp \
    components/watchdog.cpp \
    components/dce_null_modem.cpp \
    components/debug_mem_loader.cpp \
    components/gmac_univ.cpp \
    components/it_stub.cpp \
    components/dce_xterm_pthread.cpp \
    components/ti_am1x_aintc.cpp \
    components/ti_am1x_timer64.cpp \
    components/ti_am1x_rtc.cpp \
    components/ti_am1x_uart.cpp \
    components/ti_am1x_emac.cpp \
    components/ti_am1x_emac_module.cpp \
    components/ti_am1x_emac_control.cpp \
    components/ti_am1x_mdio.cpp \
    \
    processors/common.cpp \
    processors/iss.cpp \
    processors/iss.tpp \
    processors/mmu.cpp \
    processors/mmu.tpp \
    processors/tlb.cpp \
    processors/tlb.tpp \
    processors/processor.cpp \
    processors/processor_base.cpp \
    processors/processor_base.hpp \
    processors/llvm_gen_parameters.hpp \
    processors/llvm_gen_parameters.cpp \
    \
    processors/mips/mips_registers.cpp \
    processors/mips/mips_base.cpp \
    processors/mips/mips_coprocessor.cpp \
    processors/mips/mips_coprocessor.tpp \
    processors/mips/mips_debugger.hpp \
    processors/mips/mips_debugger.cpp \
    processors/mips/mips_debugger.tpp \
    processors/mips/mips_decode_macros.hpp \
    processors/mips/mips_processor.cpp \
    processors/mips/mips_processor.tpp \
    processors/mips/mips_mmu.cpp \
    processors/mips/mips_mmu.tpp \
    processors/mips/mips_tlb.cpp \
    processors/mips/mips_tlb.tpp \
    processors/mips/mips_translation_page.cpp \
    processors/mips/mips_translation_page.tpp \
    processors/mips/mipsis.hpp \
    processors/mips/mipsis.tpp \
    processors/mips/mipsis_visitor.hpp \
    processors/mips/mipsis_visitor.tpp \
    processors/mips/mipsis_visitor.cpp \
    processors/mips/mipsis_dyntrans.hpp \
    processors/mips/mipsis_dyntrans.tpp \
    processors/mips/mipsis_dyntrans.cpp \
    processors/mips/mipsis_arithmetic.hpp \
    processors/mips/mipsis_arithmetic.tpp \
    processors/mips/mipsis_arithmetic.cpp \
    processors/mips/mipsis_branch.hpp \
    processors/mips/mipsis_branch.tpp \
    processors/mips/mipsis_branch.cpp \
    processors/mips/mipsis_coprocessor.hpp \
    processors/mips/mipsis_coprocessor.tpp \
    processors/mips/mipsis_loadstore.hpp \
    processors/mips/mipsis_loadstore.tpp \
    processors/mips/mips_decode.tpp \
    processors/mips/mips_decode.cpp \
    processors/mips/mips_translator.hpp \
    processors/mips/mips_translator.tpp \
    processors/mips/mips_translator.cpp \
    processors/mips/mipspi.hpp \
    processors/mips/mipspi.tpp \
    \
    processors/arm/arm_condition.cpp \
    processors/arm/arm_coproc.cpp \
    processors/arm/arm_cpu.cpp \
    processors/arm/arm_debugger.hpp \
    processors/arm/arm_debugger.cpp \
    processors/arm/arm_decode.isc \
    processors/arm/arm_dpi.cpp \
    processors/arm/arm_loadstore.cpp \
    processors/arm/arm_mmu.cpp \
    processors/arm/arm_processor.cpp \
    processors/arm/arm_shift.cpp \
    processors/arm/arm_status_register.cpp \
    processors/arm/arm_systemcontrol_coproc.cpp \
    processors/arm/arm_thumb_pi.hpp \
    processors/arm/arm_thumb_pi.cpp \
    processors/arm/arm_tlb.cpp \
    processors/arm/arm_translation_page.cpp \
    processors/arm/armis.cpp \
    processors/arm/armis_visitor.hpp \
    processors/arm/armis_visitor.cpp \
    processors/arm/armis_dyntrans.hpp \
    processors/arm/armis_dyntrans.cpp \
    processors/arm/armis_arithmetic.hpp \
    processors/arm/armis_arithmetic.cpp \
    processors/arm/armis_arithmetic.tpp \
    processors/arm/armis_control.hpp \
    processors/arm/armis_control.cpp \
    processors/arm/armis_coproc.hpp \
    processors/arm/armis_coproc.cpp \
    processors/arm/armis_loadstore.hpp \
    processors/arm/armis_loadstore.cpp \
    processors/arm/armis_loadstore.tpp \
    processors/arm/armis_edsp.hpp \
    processors/arm/armis_edsp.cpp \
    processors/arm/armpi.cpp \
    processors/arm/arm_translate.hpp \
    processors/arm/arm_translate.cpp \
    processors/arm/thumb_decode.isc \
    processors/arm/thumbis_arithmetic.hpp \
    processors/arm/thumbis_arithmetic.cpp \
    processors/arm/thumbis_control.hpp \
    processors/arm/thumbis_control.cpp \
    processors/arm/thumbis_loadstore.hpp \
    processors/arm/thumbis_loadstore.cpp \
    processors/arm/thumb_translate.hpp \
    processors/arm/thumb_translate.cpp \
    \
    processors/arm_v6/arm_v6_processor.cpp \
    processors/arm_v6/arm_v6_debugger.hpp \
    processors/arm_v6/arm_v6_debugger.cpp \
    processors/arm_v6/arm_v6_coproc.cpp \
    processors/arm_v6/arm_v5_systemcontrol_coproc.cpp \
    processors/arm_v6/arm_v5_mmu.cpp \
    processors/arm_v6/arm_v5_tlb.cpp \
    processors/arm_v6/arm_v6_translation_page.cpp \
    processors/arm_v6/arm_v6_dyntrans.hpp \
    processors/arm_v6/arm_v6_dyntrans.cpp \
    processors/arm_v6/simlight/slv6_condition.cpp \
    processors/arm_v6/simlight/slv6_iss.cpp \
    processors/arm_v6/simlight/slv6_iss_expanded.h \
    processors/arm_v6/simlight/slv6_iss_grouped.h \
    processors/arm_v6/simlight/slv6_iss_grouped.hot.cpp \
    processors/arm_v6/simlight/slv6_iss_grouped.cold.cpp \
    processors/arm_v6/simlight/slv6_iss_arm_decode_store.cpp \
    processors/arm_v6/simlight/slv6_iss_thumb_decode_store.cpp \
    processors/arm_v6/simlight/slv6_iss_c_prelude.h \
    processors/arm_v6/simlight/slv6_iss_h_prelude.h \
    processors/arm_v6/simlight/slv6_math.h \
    processors/arm_v6/simlight/slv6_math.cpp \
    processors/arm_v6/simlight/slv6_mode.cpp \
    processors/arm_v6/simlight/slv6_processor.cpp \
    processors/arm_v6/simlight/slv6_status_register.cpp \
    processors/arm_v6/simlight/slv6_iss_printers.cpp \
    processors/arm_v6/arm_v6_printers.cpp \
    \
    processors/ppc/ppc_debugger.hpp \
    processors/ppc/ppc_decode.cpp \
    processors/ppc/ppcis_dyntrans.hpp \
    processors/ppc/ppcis_dyntrans.cpp \
    processors/ppc/ppc_translate.hpp \
    processors/ppc/ppc_translate.cpp \
    processors/ppc/ppcis.cpp \
    processors/ppc/ppc_pi.cpp \
    processors/ppc/ppc_utils.hpp \
    processors/ppc/ppcis_visitor.hpp \
    processors/ppc/ppcis_visitor.cpp \
    processors/ppc/ppcis_alu.cpp \
    processors/ppc/ppcis_alu.hpp \
    processors/ppc/ppcis_loadstore.cpp \
    processors/ppc/ppcis_loadstore.hpp \
    processors/ppc/ppc_processor.cpp \
    processors/ppc/ppc_fpsc_register.cpp \
    processors/ppc/ppcis_misc.cpp \
    processors/ppc/ppcis_misc.hpp \
    processors/ppc/ppc_cpu.cpp \
    processors/ppc/ppcis_fpu.hpp \
    processors/ppc/ppcis_fpu.cpp \
    processors/ppc/ppcis_fpu.tpp \
    processors/ppc/ppc_mmu.cpp \
    processors/ppc/ppc_tlb.cpp \
    processors/ppc/ppc_translation_page.cpp \
    processors/ppc/ppc_fp_unit.cpp \
    processors/ppc/ppc_debugger.cpp \
    processors/ppc/ppc_syscall.cpp \
    processors/ppc/ppc_linux_os.cpp \
    processors/ppc/ppc_statistics.hpp \
    processors/ppc/ppc_statistics_simple.hpp \
    processors/ppc/ppc_statistics_simple.cpp \
    processors/ppc/ppc_statistics_verysimple.hpp \
    processors/ppc/ppc_statistics_verysimple.cpp \
    processors/ppc/ppc_statistics_arithmetic.hpp \
    processors/ppc/ppc_statistics_arithmetic.cpp \
    \
    SoCs/spear/spear_soc_conf.cpp \
    SoCs/spear/spear_gpts.cpp \
    SoCs/spear/spear_sdram.cpp \
    SoCs/spear/spearplus600.cpp \
    \
    SoCs/TI_AM1707/syscfg.cpp \
    SoCs/TI_AM1707/psc.cpp \
    SoCs/TI_AM1707/TI_AM1707.cpp \
    \
    SoCs/TMPR3927/tmpr3927.cpp \
    SoCs/TMPR3927/tmpr3927_irc.cpp \
    \
    tools/debugger/debugger.cpp \
    \
    translation_table.cpp \
    interfaces/RS232.cpp \
    interfaces/tlm.cpp \
    interfaces/float_point_unit.cpp \
    interfaces/endian.cc \
    \
    network/pcaplog.cpp \
    network/poll.cpp \
    network/ethernet/ether-address.cpp \
    network/ethernet/ether-buffer.cpp \
    network/ethernet/ether-transport.cpp \
    network/ethernet/arch/ethtr-mcast.cpp \
    network/ethernet/arch/ethtr-null.cpp

if LINUXTAP
libsimsoc_a_SOURCES += network/ethernet/arch/ethtr-linuxtap.cpp
endif

if PCAP
libsimsoc_a_SOURCES += network/ethernet/arch/ethtr-pcap.cpp
endif

arm_decode.cpp: processors/arm/arm_decode.isc Makefile ../utils/ISC/isc
	../utils/ISC/isc $(srcdir)/processors/arm/arm_decode.isc -o $@

thumb_decode.cpp: processors/arm/thumb_decode.isc Makefile ../utils/ISC/isc
	../utils/ISC/isc $(srcdir)/processors/arm/thumb_decode.isc -o $@

$(ARMGEN_CPP_FILES): Makefile armgen_done

armgen_done: Makefile processors/arm/ArmGen/armgen
	processors/arm/ArmGen/armgen -o armgen_done

processors/arm/ArmGen/armgen: Makefile
	cd processors/arm/ArmGen && $(MAKE)

components/elf_loader.hpp: config.h

################################################################################
if LLVM_COND
libsimsoc_adir=$(datadir)
libsimsoc_a_DATA=ppc_llvm_lib.bc arm_v6_llvm_lib.bc

ppc_llvm_lib.bc: $(srcdir)/processors/ppc/ppc_llvm_lib.cpp libsimsoc_a-ppc_pi.o Makefile
	$(LLVMGXX) -c -emit-llvm $< $(libsimsoc_a_CPPFLAGS) -I $(top_builddir)/libsimsoc -DNDEBUG -O3 -o $@

arm_v6_llvm_lib.hot.bc: $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.hot.c \
 $(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.h \
 libsimsoc_a-slv6_iss_grouped.hot.o Makefile
	$(LLVMGXX) -c -emit-llvm -I $(top_builddir)/libsimsoc -DNDEBUG \
                   $(libsimsoc_a_CPPFLAGS) -DSLV6_ISS_grouped_H \
                   --include $< $(srcdir)/processors/arm_v6/arm_v6_llvm_lib.cpp \
                   -O3 -o $@

arm_v6_llvm_lib.cold.bc: $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.cold.c \
 $(srcdir)/processors/arm_v6/simlight/slv6_iss_expanded.h \
 libsimsoc_a-slv6_iss_grouped.cold.o Makefile
	$(LLVMGXX) -c -emit-llvm $< $(libsimsoc_a_CPPFLAGS) -DSLV6_ISS_grouped_H \
                   -I $(top_builddir)/libsimsoc -DNDEBUG -O1 -o $@

arm_v6_llvm_lib.bc: arm_v6_llvm_lib.hot.bc arm_v6_llvm_lib.cold.bc
	$(LLVMLINK) $^ -o=$@

CLEANFILES += ppc_llvm_lib.bc arm_v6_llvm_lib.bc \
	arm_v6_llvm_lib.hot.bc arm_v6_llvm_lib.cold.bc

libsimsoc_a_SOURCES+= \
    processors/compil_server.hpp \
    processors/compil_server.tpp \
    processors/ppc/ppc_llvm_generator.hpp \
    processors/ppc/ppc_llvm_generator.cpp \
    processors/arm_v6/arm_v6_llvm_generator.hpp \
    processors/arm_v6/arm_v6_llvm_generator.cpp \
    processors/arm_v6/arm_v6_llvm_server.hpp \
    processors/arm_v6/arm_v6_llvm_server.cpp \
    processors/arm_v6/simlight/slv6_iss-llvm_generator.hpp

endif
