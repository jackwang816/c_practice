#!/usr/bin/make -f

.DEFAULT_GOAL:=help
.PHONY: help array clean pcreTest
.SILENT: help array clean pcreTest

help:
	$(call msg_info,"Build targets:")
	echo "Array       - Build target array"

array:
	${MAKE} -C array

pcreTest:
	${MAKE} -C pcreTest

clean:
	${MAKE} -C array clean

