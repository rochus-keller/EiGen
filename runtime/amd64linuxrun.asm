; AMD64 Linux runtime support
; Copyright (C) Florian Negele

; This file is part of the Eigen Compiler Suite.

; The ECS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.

; The ECS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; Under Section 7 of the GNU General Public License version 3,
; the copyright holder grants you additional permissions to use
; this file as described in the ECS Runtime Support Exception.

; You should have received a copy of the GNU General Public License
; and a copy of the ECS Runtime Support Exception along with
; the ECS.  If not, see <https://www.gnu.org/licenses/>.

; ELF file format
.header _header

	.required
	.origin	0x08048000
	.assert	.bitmode == 64

	.byte	0x7f, "ELF", 2, 1, 1, 0	; e_ident
	.pad	16
	.dbyte	2	; e_type
	.dbyte	62	; e_machine
	.qbyte	1	; e_version
	.obyte	extent (@_program_headers)	; e_entry
	.obyte	@_program_headers - .origin	; e_phoff
	.obyte	@_section_headers?_section_headers:_header - .origin	; e_shoff
	.qbyte	0	; e_flags
	.dbyte	64	; e_ehsize
	.dbyte	56	; e_phentsize
	.dbyte	count (@_program_headers)	; e_phnum
	.dbyte	64	; e_shentsize
	.dbyte	count (@_section_headers?_section_headers)	; e_shnum
	.dbyte	index (@_strtab_header?_strtab_header)	; e_shstrndx

.trailer _trailer

.const _extension

	.byte	""

; environment name
.const _environment

	.byte	"x86 Linux 64-bit", 0

; program headers
.header _program_header

	.required
base:	.equals	0x08048000
	.group	_program_headers

	.alignment	8
	.qbyte	1	; p_type
	.qbyte	7	; p_flags
	.obyte	0	; p_offset
	.obyte	base	; p_vaddr
	.obyte	base	; p_paddr
	.obyte	@_trailer - base	; p_filesz
	.obyte	@_trailer - base	; p_memsz
	.obyte	0x1000	; p_align

.header _interpreter_header

base:	.equals	0x08048000
	.group	_program_headers

	.alignment	8
	.qbyte	3	; p_type
	.qbyte	4	; p_flags
	.obyte	@_interpreter_name - base	; p_offset
	.obyte	@_interpreter_name	; p_vaddr
	.obyte	@_interpreter_name	; p_paddr
	.obyte	size (@_interpreter_name)	; p_filesz
	.obyte	size (@_interpreter_name)	; p_memsz
	.obyte	1	; p_align

.header _dynamic_header

base:	.equals	0x08048000
	.group	_program_headers
	.require	_interpreter_header

	.alignment	8
	.qbyte	2	; p_type
	.qbyte	6	; p_flags
	.obyte	@_dynamic_section - base	; p_offset
	.obyte	@_dynamic_section	; p_vaddr
	.obyte	@_dynamic_section	; p_paddr
	.obyte	size (@_dynamic_section) + 16	; p_filesz
	.obyte	size (@_dynamic_section) + 16	; p_memsz
	.obyte	8	; p_align

; section headers
.const _null_header

	.group	_section_headers
	.alignment	8
	.reserve	64

#define section

	; section header
	.const _#0_header

	base:	.equals	0x08048000
		.group	_section_headers
		.require	_#1_header

		.alignment	8
		.qbyte	position (@_.#0_string) + 1	; sh_name
		.qbyte	#2	; sh_type
		.obyte	#3	; sh_flags
		.obyte	#4	; sh_addr
		.obyte	#5	; sh_offset
		.obyte	#6	; sh_size
		.qbyte	0	; sh_link
		.qbyte	0	; sh_info
		.obyte	1	; sh_addralign
		.obyte	0	; sh_entsize

	; string table entry
	.const _.#0_string

		.duplicable
		.group	_string_table

		.byte	".#0", 0

#enddef

	section	debug_abbrev, text, 1, 0, 0, @_debug_abbrev_section - base, size (@_debug_abbrev_section) + 1
	section	debug_info, text, 1, 0, 0, @_debug_info_section - base, size (@_debug_info_section)
	section	debug_line, text, 1, 0, 0, @_debug_line_section - base, size (@_debug_line_section)
	section	strtab, null, 3, 0, 0, @_string_table_begin - base, size (@_string_table) + 1
	section text, strtab, 1, 7, base, 0, @_trailer - base

#undef section

; system call wrappers
#repeat 7

	.code _system_call_wrapper##

		#if ## > 0
			mov	rdi, [rsp + 8]
		#endif
		#if ## > 1
			mov	rsi, [rsp + 16]
		#endif
		#if ## > 2
			mov	rdx, [rsp + 24]
		#endif
		#if ## > 3
			mov	r10, [rsp + 32]
		#endif
		#if ## > 4
			mov	r8, [rsp + 40]
		#endif
		#if ## > 5
			mov	r9, [rsp + 48]
		#endif
		syscall
		ret

#endrep

; wrappers for system calls
#define system_call

	.code #0
		mov	eax, #1
		jmp	dword @_system_call_wrapper#2

#enddef

	system_call	sys_brk, 12, 1
	system_call	sys_clock_getres, 229, 2
	system_call	sys_clock_gettime, 228, 2
	system_call	sys_clone, 56, 5
	system_call	sys_close, 3, 1
	system_call	sys_exit, 60, 1
	system_call	sys_exit_group, 231, 1
	system_call	sys_futex, 202, 6
	system_call	sys_getpid, 39, 0
	system_call	sys_gettid, 186, 0
	system_call	sys_lseek, 8, 3
	system_call	sys_nanosleep, 35, 2
	system_call	sys_open, 2, 3
	system_call	sys_read, 0, 3
	system_call	sys_rename, 82, 2
	system_call	sys_sched_getaffinity, 204, 3
	system_call	sys_sched_setaffinity, 203, 3
	system_call	sys_time, 201, 1
	system_call	sys_times, 100, 1
	system_call	sys_unlink, 87, 1
	system_call	sys_waitid, 247, 5
	system_call	sys_write, 1, 3

#undef system_call

; interpreter for dynamic linking
.const _interpreter_name

	.byte	"/lib64/ld-linux-x86-64.so.2", 0

; string table for dynamic linking
.const _string_table_begin

	.group	_string_tab

	.alignment	8
	.byte	0

; section for dynamic linking
.const _dynamic_section_begin

	.group	_dynamic_section
	.require	_dynamic_header

	.alignment	8
	.obyte	5, @_string_table_begin	; DT_STRTAB
	.obyte	6, @_symbol_table_begin	; DT_SYMTAB
	.obyte	7, @_relocation_table	; DT_RELA
	.obyte	8, size (@_relocation_table)	; DT_RELASZ
	.obyte	9, 0x18	; DT_RELAENT
	.obyte	10, size (@_string_table) + 1	; DT_STRSZ
	.obyte	11, 0x18	; DT_SYMENT

.const _dynamic_section_sentinel

	.group	_dynamic_section_end
	.require	_dynamic_section_begin

	.alignment	8
	.obyte	0, 0	; DT_NULL

; symbol table for dynamic linking
.const _symbol_table_begin

	.group	_symbol_tab

	.alignment	8
	.qbyte	0	; st_name
	.byte	0	; st_info
	.byte	0	; st_other
	.dbyte	0	; st_shndx
	.obyte	0	; st_value
	.obyte	0	; st_size

; imported libraries
#define library

	; dynamic section entry
	.const _dynamic_section_#0

		.duplicable
		.group	_dynamic_section
		.require	_dynamic_section_sentinel

		.alignment	8
		.obyte	1, position (@_#0_string) + 1	; DT_NEEDED

	; string table entry
	.const _#0_string

		.duplicable
		.group	_string_table

		.byte	#1, 0

#enddef

; function call wrappers
#repeat 7

	.code _function_call_wrapper##

		pop	rbx
		#if ## > 0
			mov	rdi, [rsp]
		#endif
		#if ## > 1
			mov	rsi, [rsp + 8]
		#endif
		#if ## > 2
			mov	rdx, [rsp + 16]
		#endif
		#if ## > 3
			mov	rcx, [rsp + 24]
		#endif
		#if ## > 4
			mov	r8, [rsp + 32]
		#endif
		#if ## > 5
			mov	r9, [rsp + 40]
		#endif
		mov	r12, rsp
		and	rsp, ~1111b
		call	rax
		mov	rsp, r12
		jmp	rbx

#endrep

; imported library functions
#define function

	; symbol table entry
	.const _#1_symbol

		.duplicable
		.group	_symbol_table
		.require	_dynamic_section_#0

		.alignment	8
		.qbyte	position (@_#1_string) + 1	; st_name
		.byte	0x12	; st_info
		.byte	0x0	; st_other
		.dbyte	0	; st_shndx
		.obyte	0	; st_value
		.obyte	0	; st_size

	; string table entry
	.const _#1_string

		.duplicable
		.group	_string_table

		.byte	"#1", 0

	; relocation table entry
	.const _#1_relocation

		.duplicable
		.group	_relocation_table

		.alignment	8
		.obyte	@_#1	; r_offset
		.qbyte	1	; r_info
		.qbyte	index (@_#1_symbol) + 1
		.obyte	0	; r_addend

	; function address
	.const _#1

		.duplicable
		.require	_#1_relocation

		.alignment	8
		.reserve	8

	; function wrapper
	.code #1

		.duplicable
		mov	rax, [rip + @_#1]
		jmp	dword @_function_call_wrapper#2

#enddef


#undef library
#undef function

; standard argc variable
.data _argc

	.alignment	4
	.reserve	4
	.require	_init_argc

; initialize argc variable
.initdata _init_argc

	mov	rax, [rsp]
	mov	[rip + @_argc], eax

; standard argv variable
.data _argv

	.alignment	8
	.reserve	8
	.require	_init_argv

; initialize argv variable
.initdata _init_argv

	lea	rax, [rsp + 8]
	mov	[rip + @_argv], rax


