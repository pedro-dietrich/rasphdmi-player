SECTIONS {
	. = 0x8000;
	.text : {
		boot.o(.text)
		*(.text)
	}

	. = ALIGN(4);
	data_begin = .;
	.data : {
		*(.data)
	}

	. = ALIGN(4);
	bss_begin = .;
	.bss : {
		*(.bss*)
	}
	bss_end = .;

	. = ALIGN(8);
	heap_addr = .;
	. = . + 32K;
	stack_addr = .;
}
