#!/usr/bin/make -f

.DEFAULT_GOAL:=help
.PHONY: help Array clean
.SILENT: help Array clean

help:
	$(call msg_info,"Build targets:")
	echo "Array       - Build target array"

Array:
	${MAKE} -C Array

clean:
	${MAKE} -C Array clean

