
#*********************************
ifdef DEFINE_VRE
    VRE = "Hello World!"
endif

ifeq ($(OPT),)
    VRE ?= "Hello World! First!"
endif
#*********************************

#shell
GCC_MAJOR_VER := $(shell gcc --version | grep ^gcc | sed 's/^.* //g' | cut -f1 -d.)
GCC_MINOR_VER := $(shell gcc --version | grep ^gcc | sed 's/^.* //g' | cut -f2 -d.)

#compare
GCC_MAJOR_EQ4 := $(shell expr $(GCC_MAJOR_VER) = 4)
GCC_MAJOR_GT4 := $(shell expr $(GCC_MAJOR_VER) \> 4)

#target
all:
	@for i in $(VRE); \
	do \
		echo $$i; \
	done
