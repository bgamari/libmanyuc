/* Adapted for CortexM3 STM32F4xx, originally based on LPC17xx.ld */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)

MEMORY
{
	rom (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
	ram (rwx) : ORIGIN = 0x10000000, LENGTH =  32K

	iram1 (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
	iram2 (rwx) : ORIGIN = 0x2001c000, LENGTH =  16K

}

EXTERN (__interrupt_vector_table)

SECTIONS
{
	.text :
        {
		/* Insert the interrupt vector table first */
		__interrupt_vector_table = .;
		*(.interrupt_vector_table)
		/* Startup assembly */
		*(.startup)

		/* Rest of the code (C) */
		*(.text)
		*(.text.*)
		*(.gnu.linkonce.t.*)
		*(.glue_7)
		*(.glue_7t)
		*(.vfp11_veneer)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.gcc_except_table)
		*(.rodata)
		*(.rodata*)
		*(.gnu.linkonce.r.*)

		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP (*(.preinit_array))
		__preinit_array_end = .;

		. = ALIGN(4);
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;

		. = ALIGN(0x4);
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*crtend.o(.ctors))

		. = ALIGN(4);
		KEEP(*(.fini))

		. = ALIGN(4);
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;

		. = ALIGN(0x4);
		KEEP (*crtbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*crtend.o(.dtors))
		. = ALIGN(8);
		_end_text = .;
		_start_datai = .;
	} >rom

	.data : {
		_start_data = .;
		*(vtable vtable.*)
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		. = ALIGN (8);
		_end_data = .;
	} >ram AT >rom

	.data_init : 
	{
		_end_datai = .;
	} >rom

	__exidx_start = .;
	.ARM.exidx : 
	{ 
		*(.ARM.exidx* .gnu.linkonce.armexidx.*) 
	} > rom
	__exidx_end = .;

	.bss :
	{
		_start_bss = .;

		*(.bss .bss.*)
		*(.gnu.linkonce.b*)
		*(COMMON)

	} >ram 

	. = ALIGN(4);
	_end_bss = .;

	. = ALIGN(256);

	/* Stack can grow down to here, right after data and bss sections in 
	 * SRAM */
	_start_heap = .;

	PROVIDE( __cs3_heap_start = _start_heap);

	/* Linker wants .eh_frame section defined because of gcc 4.4.X bug,
	 * just discard it here. */
	/DISCARD/ :
	{
		*(.eh_*)
	}
}

_end = .;
PROVIDE(end = .);
