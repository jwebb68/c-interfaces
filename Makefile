# build main code/test/examples for modules
# modules are subfolders from root, containing a main for exes, liba for statics and libso for shared.
# all other .c,.cc files are treated as part of that module.
# <modl>/src/main.{c,cc}
# <modl>/src/liba.{c,cc}
# <modl>/src/libso.{c,cc}
# builds an exe based on module name. <modl> for exes, lib<modl>.a for statics, lib<modl>.so for shared.
# for defined configs (debug,release)
# output is in build/<config>/
# builds tests and runs them for each module.
# tests are .c,.cc files in <modl>/src/ matching pattern test_*.{c,cc}
# tests are built into build/<config>/tests/test_<modl> as an exe
# builds examples as found in the examples/ folder.
# each .c.cc file is built into an exe into the build/<config/examples folder.
#
# you will need pkg-config and catch2 installed (for c++ tests)
# TODO: pick details up from .yaml file (will mean dropping make)
# caveats:
# will only work if only one of main.c main.cc liba.c liba.cc libso.c libso.cc exist for a module
# it will die horribly if theres not only one such.
# TODO: allow specifying .c/.cc files for each module and not auto-detect.
# TODO: rewrite in C++ and not makefile.. (or rust for portability/self-containment)

.SUFFIXES:
.SUFFIXES: c cc a o

# toolchains
# GCC
# CLANG
# ARM
TOOLCHAIN ?= native

ifeq ($(TOOLCHAIN),native)
OBJDUMP=objdump
CC=cc
CXX=c++
AR=ar
AS=as
LINK=$(CC)

else ifeq ($(TOOLCHAIN),gnu)

OBJDUMP=objdump
CC=gcc
CXX=g++
AR=ar
AS=as
LINK=$(CC)

else ifeq ($(TOOLCHAIN),clang)

OBJDUMP=objdump
CC=clang
CXX=clang++
AR=ar
AS=as
LINK=$(CC)

else ifeq ($(TOOLCHAIN),arm)

CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
OBJDUMP=arm-none-eabi-objdump
LDFLAGS+=--specs=nosys.specs
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
LINK=$(CC)

else

$(error TOOLCHAIN='$(TOOLCHAIN)' not supported)

endif


TARGET_TRIP:=$(CC) -dumpmachine

# Redefine link operation as not able to assign CC to $(CXX) in build rules.
# every attempt does not reassign to CC, just uses CC which messes up C++ linking
# but reassigning into another var works..
# ie. CC= $(CXX) doesn't, LINK=$(CXX) does..
LINK.o = $(LINK) $(LDFLAGS) $(TARGET_ARCH)

allowed_configs:=
allowed_configs+=debug
allowed_configs+=release
allowed_configs+=minsize
allowed_configs+=fast
ifeq ($(origin configs), undefined)
configs:=$(allowed_configs)
endif
ifneq ($(filter-out $(allowed_configs),$(configs)),)
$(error allowed configs: $(allowed_configs))
endif

#CFLAGS already defined
CFLAGS += -Werror -Wall -Wextra -Wpedantic
CXXFLAGS += -Werror -Wall -Wextra -Wpedantic -std=c++17 -fno-exceptions

# CFLAGS additionals for debug
debug_CFLAGS := -Og -g
debug_CXXFLAGS := -Og -g
debug_CPPFLAGS := -DDEBUG
#debug_LDFLAGS:=

release_CFLAGS := -O3 -g
release_CXXFLAGS := -O3 -g
release_CPPFLAGS := -DRELEASE
#release_LDFLAGS:=
#release_LDFLAGS += --lto
#release_CFLAGS += --lto
#release_CXXFLAGS += --lto

minsize_CFLAGS := -Os -g
minsize_CXXFLAGS := -Os -g
minsize_CPPFLAGS := -DRELEASE
#minsize_LDFLAGS:=
#minsize_LDFLAGS+= --lto
#minsize_CFLAGS += --lto
#minsize_CXXFLAGS += --lto

fast_CFLAGS := -Ofast -g
fast_CXXFLAGS := -Ofast -g
fast_CPPFLAGS := -DRELEASE
#minsize_LDFLAGS:=
#minsize_LDFLAGS+= --lto
#minsize_CFLAGS += --lto
#minsize_CXXFLAGS += --lto

# 'global' additionals for compoent
proj=c-interfaces
c-interfaces_CXXFLAGS :=

# additionals for component per config
c-interfaces_debug_CFLAGS :=
c-interfaces_debug_CPPFLAGS :=
c-interfaces_debug_CXXFLAGS :=

c-interfaces_release_CFLAGS :=
c-interfaces_release_CPPFLAGS :=
c-interfaces_release_CXXFLAGS :=

c-interfaces_minsize_CFLAGS :=
c-interfaces_minsize_CPPFLAGS :=
c-interfaces_minsize_CXXFLAGS :=

c-interfaces_fast_CFLAGS :=
c-interfaces_fast_CPPFLAGS :=
c-interfaces_fast_CXXFLAGS :=

c-interfaces_DEPS:=

modls:=
modls+=c-interfaces-r2
modls+=c-interfaces-m2
modls+=c-interfaces-m3
modls+=c-interfaces-m4

# build makefile to build/clean buildtree from src
# in makefile:
# $<modl>_DEPS:= lists deps of modl, relative to root of project.
# must be in same project..TODO: cross project building so can pull in projs from other repos.
# $modls:= <list of modules to build.

# folder tree laid out thus:
# examples/<nmame>.c
# examples/<nmame>.cc
# <modl>/src/
# <modl>/src/main.{c,cc} # for exe builds
# <modl>/<src>/liba.{c,cc} # for static lib builds
# <modl>/<src>/libso.{c,cc} # for shared lib builds
# <modl>/src/<other>.{c,cc}

# will compile examples/<file>.c into build/<config>/obj/examples/<file>.o
# will link build/<config>/obj/examples/<file>/<file>.o into build/<config>/examples/<file>
# i.e. every single .c and .cc file compiles to a single product.
# dependencies are from main project (is no deps between examples)

# will compile modl/src/<file>.{c,cc} into build/<config>/obj/<modl>/<file>.o
# will preprocess modl/src/<file>.{c,cc} into build/<config>/dep/<modl>/<file>.d for deps tracking of included files.

# for c,cc exes:
# will link build/<config>/obj/<modl>/<file>.o into build/<config>/obj/<modl>
# for c,cc statics:
# will link build/<config>/obj/<modl>/<file>.o into build/<config>/obj/lib<modl>.a
# for c,cc shared libs
# will link build/<config>/obj/<modl>/<file>.o into build/<config>/obj/lib<modl>.so

# TODO: error out if main.c/main.cc exist together
# TODO: error out if liba.c/liba.cc exist together
# TODO: error out if libso.c/libso.cc exist together
# TODO: error out if main.{c,cc} or liba.{c,cc} or libso.{c,cc} exist together

all: build

allsrc:=$(foreach f,$(modls),$(wildcard $(f)/src/*.c $(f)/src/*.cc))
allhdr:=$(foreach f,$(modls),$(wildcard $(f)/src/*.h $(f)/src/*.hh))
testsrc:= $(foreach f,$(modls),$(wildcard $(f)/src/test_*.c $(f)/src/test_*.cc))
src:=$(filter-out $(testsrc),$(foreach f,$(modls),$(wildcard $(f)/src/*.c $(f)/src/*.cc)))

obj:=
clean:=
dep:=
rtests:=

# $1 = modl, $2 = config
define mk_modl
clean+=$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src)))
clean+=$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src)))
clean+=$(patsubst $(1)/src/%.s,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.s,$(src)))

build/$(2)/obj/$(1): ; mkdir -p $$@
build/$(2)/dep/$(1): ; mkdir -p $$@

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))): | build/$(2)/obj/$(1))
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))): | build/$(2)/obj/$(1))
$(if $(filter $(1)/src/%.s,$(src)),$(patsubst $(1)/src/%.s,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.s,$(src))): | build/$(2)/obj/$(1))

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.c,$(src))): | build/$(2)/dep/$(1))
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.cc,$(src))): | build/$(2)/dep/$(1))
$(if $(filter $(1)/src/%.s,$(src)),$(patsubst $(1)/src/%.s,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.s,$(src))): | build/$(2)/dep/$(1))

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.c,$(src))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.cc,$(src))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(foreach m,$($(1)_DEPS),-I$(m)/src))

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))): CFLAGS:=$$(CFLAGS) $$($(1)_CFLAGS) $$($(2)_CFLAGS) $$($(1)_$(2)_CFLAGS))

$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS)  $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))): CXXFLAGS:=$$(CXXFLAGS) $$($(1)_CXXFLAGS) $$($(2)_CXXFLAGS) $$($(1)_$(2)_CXXFLAGS))

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))): build/$(2)/obj/$(1)/%.o: $(1)/src/%.c ;$$(COMPILE.c) -o $$@  $$<)
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))): build/$(2)/obj/$(1)/%.o: $(1)/src/%.cc ;$$(COMPILE.cc) -o $$@  $$<)
$(if $(filter $(1)/src/%.s,$(src)),$(patsubst $(1)/src/%.s,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.s,$(src))): build/$(2)/obj/$(1)/%.o: $(1)/src/%.s ;$$(COMPILE.s) -o $$@  $$<)

$(if $(filter $(1)/src/%.c,$(src)),$(patsubst $(1)/src/%.c,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.c,$(src))): build/$(2)/dep/$(1)/%.d: $(1)/src/%.c ;$$(COMPILE.c) -MM -MT $$(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$$<) -o $$@ $$<)
$(if $(filter $(1)/src/%.cc,$(src)),$(patsubst $(1)/src/%.cc,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.cc,$(src))): build/$(2)/dep/$(1)/%.d: $(1)/src/%.cc ;$$(COMPILE.cc) -MM -MT $$(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$$<) -o $$@  $$<)
$(if $(filter $(1)/src/%.s,$(src)),$(patsubst $(1)/src/%.s,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.s,$(src))): build/$(2)/dep/$(1)/%.d: $(1)/src/%.s ;$$(COMPILE.s) -MM -MT $$(patsubst $(1)/src/%.s,build/$(2)/obj/$(1)/%.o,$$<) -o $$@  $$<)

$(if $(filter $(1)/src/%.c,$(src)),dep += $(patsubst $(1)/src/%.c,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.c,$(src))))
$(if $(filter $(1)/src/%.cc,$(src)),dep += $(patsubst $(1)/src/%.cc,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.cc,$(src))))
$(if $(filter $(1)/src/%.s,$(src)),dep +=$(patsubst $(1)/src/%.s,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.s,$(src))))

$(if $(filter $(1)/src/liba.c,$(src)),build/$(2)/lib$(1).a: | build/$(2))
$(if $(filter $(1)/src/liba.c,$(src)),build/$(2)/lib$(1).a: $(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))); $$(AR) rcs $$@ $$^)
$(if $(filter $(1)/src/liba.c,$(src)),build/$(2)/$(1): $(foreach m,$($(1)_DEP),$$($(m)_targ)))
$(if $(filter $(1)/src/liba.c,$(src)),build: build/$(2)/lib$(1).a)
$(if $(filter $(1)/src/liba.c,$(src)),clean += build/$(2)/lib$(1).a)
$(if $(filter $(1)/src/liba.c,$(src)),$(1)_targ := build/$(2)/lib$(1).a)

$(if $(filter $(1)/src/liba.cc,$(src)),build/$(2)/lib$(1).a: | build/$(2))
$(if $(filter $(1)/src/liba.cc,$(src)),build/$(2)/lib$(1).a: $(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))); $$(AR) rcs $$@ $$^)
$(if $(filter $(1)/src/liba.cc,$(src)),build/$(2)/$(1): $(foreach m,$($(1)_DEP),$$($(m)_targ)))
$(if $(filter $(1)/src/liba.cc,$(src)),build: build/$(2)/lib$(1).a)
$(if $(filter $(1)/src/liba.cc,$(src)),clean += build/$(2)/lib$(1).a)
$(if $(filter $(1)/src/liba.cc,$(src)),$(1)_targ := build/$(2)/lib$(1).a)

$(if $(filter $(1)/src/main.c,$(src)),build/$(2)/$(1): | build/$(2))
$(if $(filter $(1)/src/main.c,$(src)),build/$(2)/$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter $(1)/src/main.c,$(src)),build/$(2)/$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter $(1)/src/main.c,$(src)),build/$(2)/$(1): $(patsubst $(1)/src/%.c,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.c,$(src))); $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter $(1)/src/main.c,$(src)),build/$(2)/$(1): $(foreach m,$($(1)_DEP),$$($(m)_targ)))
$(if $(filter $(1)/src/main.c,$(src)),build: build/$(2)/$(1))
$(if $(filter $(1)/src/main.c,$(src)),clean += build/$(2)/$(1))
$(if $(filter $(1)/src/main.c,$(src)),$(1)_targ := build/$(2)/$(1))

$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): | build/$(2))
$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): LINK = $(CXX))
$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): $(patsubst $(1)/src/%.cc,build/$(2)/obj/$(1)/%.o,$(filter $(1)/src/%.cc,$(src))); $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter $(1)/src/main.cc,$(src)),build/$(2)/$(1): $(foreach m,$($(1)_DEP),$$($(m)_targ)))
$(if $(filter $(1)/src/main.cc,$(src)),build: build/$(2)/$(1))
$(if $(filter $(1)/src/main.cc,$(src)),clean += build/$(2)/$(1))
$(if $(filter $(1)/src/main.cc,$(src)),$(1)_targ := build/$(2)/$(1))

endef


$(foreach c,$(configs),build/$(c) build/$(c)/obj):
	mkdir -p $@

$(foreach m,$(modls),$(foreach c,$(configs),$(eval $(call mk_modl,$(m),$(c)))))

examples:=
examples+=$(patsubst examples/%.c,%,$(wildcard examples/*.c))
examples+=$(patsubst examples/%.cc,%,$(wildcard examples/*.cc))

examples_src:=$(wildcard examples/*.c examples/*.cc)

examples_deps:=
examples_deps+=c-interfaces-m2
examples_deps+=c-interfaces-m3
examples_deps+=c-interfaces-m4

# $1 = example name $2 = config
define mk_example
clean += $(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src)))
clean += $(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src)))

$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src))): CPPFLAGS += $($(2)_CPPFLAGS) $(foreach m,$(modls),-I$(m)/src))
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src))): CPPFLAGS +=  $($(2)_CPPFLAGS)  $(foreach m,$(modls),-I$(m)/src))
$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src))): CFLAGS += $($(2)_CFLAGS))
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src))): CFLAGS +=  $($(2)_CFLAGS))
$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src))): CXXFLAGS += $($(2)_CXXFLAGS))
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src))): CXXFLAGS +=  $($(2)_CXXFLAGS))

$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).c,$(examples_src))): CPPFLAGS +=  $($(2)_CPPFLAGS) $(foreach m,$(modls),-I$(m)/src))
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).cc,$(examples_src))): CPPFLAGS +=  $($(2)_CPPFLAGS) $(foreach m,$(modls),-I$(m)/src))

$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).c,$(examples_src))): build/$(2)/dep/examples/%.d: examples/%.c | build/$(2)/dep/examples; $$(COMPILE.c)  -MM -MT $$(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$$<) -o $$@ $$<)
$(if $(filter examples/$(1).c,$(examples_src)), clean += $(patsubst examples/$(1).c,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).c,$(examples_src))))
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).cc,$(examples_src))): build/$(2)/dep/examples/%.d: examples/%.cc | build/$(2)/dep/examples; $$(COMPILE.cc) -MM -MT $$(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$$<) -o $$@ $$<)
$(if $(filter examples/$(1).cc,$(examples_src)), clean += $(patsubst examples/$(1).cc,build/$(2)/dep/examples/$(1).d,$(filter examples/$(1).cc,$(examples_src))))

$(if $(filter $(1)/src/%.c,$(src)),dep += $(patsubst $(1)/src/%.c,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.c,$(src))))
$(if $(filter $(1)/src/%.cc,$(src)),dep += $(patsubst $(1)/src/%.cc,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.cc,$(src))))
$(if $(filter $(1)/src/%.s,$(src)),dep +=$(patsubst $(1)/src/%.s,build/$(2)/dep/$(1)/%.d,$(filter $(1)/src/%.s,$(src))))

$(if $(filter examples/$(1).c,$(examples_src)),dep += build/$(2)/dep/examples/$(1).d)
$(if $(filter examples/$(1).cc,$(examples_src)),dep += build/$(2)/dep/examples/$(1).d)

$(if $(filter examples/$(1).c,$(examples_src)),$(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src))): build/$(2)/obj/examples/%.o: examples/%.c | build/$(2)/obj/examples; $$(COMPILE.c) -o $$@ $$<)
$(if $(filter examples/$(1).cc,$(examples_src)),$(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src))): build/$(2)/obj/examples/%.o: examples/%.cc | build/$(2)/obj/examples; $$(COMPILE.cc) -o $$@ $$<)

$(if $(filter examples/$(1).c,$(examples_src)), build/$(2)/examples/$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter examples/$(1).c,$(examples_src)), build/$(2)/examples/$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter examples/$(1).c,$(examples_src)), build/$(2)/examples/$(1): $(patsubst examples/$(1).c,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).c,$(examples_src))) | build/$(2)/examples; $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter examples/$(1).c,$(examples_src)),build/$(2)/examples/$(1): $(foreach m,$(modls),$(filter %.a %.so,$($(m)_targ))))
$(if $(filter examples/$(1).c,$(examples_src)),examples: build/$(2)/examples/$(1))
$(if $(filter examples/$(1).c,$(examples_src)),clean += build/$(2)/examples/$(1))

$(if $(filter examples/$(1).cc,$(examples_src)), build/$(2)/examples/$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter examples/$(1).cc,$(examples_src)), build/$(2)/examples/$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter examples/$(1).cc,$(examples_src)), build/$(2)/examples/$(1): LINK = $(CXX))
$(if $(filter examples/$(1).cc,$(examples_src)), build/$(2)/examples/$(1): $(patsubst examples/$(1).cc,build/$(2)/obj/examples/$(1).o,$(filter examples/$(1).cc,$(examples_src))) | build/$(2)/examples; $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter examples/$(1).cc,$(examples_src)),build/$(2)/examples/$(1):  $(foreach m,$(modls),$(filter %.a %.so,$($(m)_targ))))
$(if $(filter examples/$(1).cc,$(examples_src)),examples: build/$(2)/examples/$(1))
$(if $(filter examples/$(1).cc,$(examples_src)),clean += build/$(2)/examples/$(1))

$(if $(filter examples/$(1).c,$(examples_src)),build/$(2)/examples/$(1).s: build/$(2)/examples/$(1); $(OBJDUMP) -Sr $$< > $$@)
$(if $(filter examples/$(1).c,$(examples_src)),examples: build/$(2)/examples/$(1).s)
$(if $(filter examples/$(1).c,$(examples_src)),clean += build/$(2)/examples/$(1).s)

$(if $(filter examples/$(1).cc,$(examples_src)),build/$(2)/examples/$(1).s: build/$(2)/examples/$(1); $(OBJDUMP) -Sr $$< > $$@)
$(if $(filter examples/$(1).cc,$(examples_src)),examples: build/$(2)/examples/$(1).s)
$(if $(filter examples/$(1).cc,$(examples_src)),clean += build/$(2)/examples/$(1).s)

endef


$(foreach c,$(configs),build/$(c)/obj/examples build/$(c)/dep/examples build/$(c)/examples):
	mkdir -p $@

$(foreach e,$(examples),$(foreach c,$(configs),$(eval $(call mk_example,$(e),$(c)))))

define mk_modl_tests
clean+=$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc)))
clean+=$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc)))
clean+=$(patsubst $(1)/src/test_%.s,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.s,$(testsrc)))

build/$(2)/obj/tests/$(1): ; mkdir -p $$@
build/$(2)/dep/tests/$(1): ; mkdir -p $$@

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc))): | build/$(2)/obj/tests/$(1))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc))): | build/$(2)/obj/tests/$(1))
$(if $(filter $(1)/src/test_%.s,$(testsrc)),$(patsubst $(1)/src/test_%.s,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.s,$(testsrc))): | build/$(2)/obj/tests/$(1))

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.c,$(testsrc))): | build/$(2)/dep/tests/$(1))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.cc,$(testsrc))): | build/$(2)/dep/tests/$(1))
$(if $(filter $(1)/src/test_%.s,$(testsrc)),$(patsubst $(1)/src/test_%.s,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.s,$(testsrc))): | build/$(2)/dep/tests/$(1))

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.c,$(testsrc))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.cc,$(testsrc))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(shell pkg-config --cflags catch2) $(foreach m,$($(1)_DEPS),-I$(m)/src))

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc))): CFLAGS:=$$(CFLAGS) $$($(1)_CFLAGS) $$($(2)_CFLAGS) $$($(1)_$(2)_CFLAGS))

$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc))): CPPFLAGS:=$$(CPPFLAGS) $$($(1)_CPPFLAGS) $$($(2)_CPPFLAGS) $$($(1)_$(2)_CPPFLAGS) $(shell pkg-config --cflags catch2) $(foreach m,$($(1)_DEPS),-I$(m)/src))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc))): CXXFLAGS:=$$(CXXFLAGS) $$($(1)_CXXFLAGS) $$($(2)_CXXFLAGS) $$($(1)_$(2)_CXXFLAGS))

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc))): build/$(2)/obj/tests/$(1)/test_%.o: $(1)/src/test_%.c ;$$(COMPILE.c) -o $$@  $$<)
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc))): build/$(2)/obj/tests/$(1)/test_%.o: $(1)/src/test_%.cc ;$$(COMPILE.cc) -o $$@  $$<)
$(if $(filter $(1)/src/test_%.s,$(testsrc)),$(patsubst $(1)/src/test_%.s,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.s,$(testsrc))): build/$(2)/obj/tests/$(1)/test_%.o: $(1)/src/test_%.s ;$$(COMPILE.s) -o $$@  $$<)

$(if $(filter $(1)/src/test_%.c,$(testsrc)),$(patsubst $(1)/src/test_%.c,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.c,$(testsrc))): build/$(2)/dep/tests/$(1)/test_%.d: $(1)/src/test_%.c ;$$(COMPILE.c) -MM -MT $$(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$$<) -o $$@ $$<)
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),$(patsubst $(1)/src/test_%.cc,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.cc,$(testsrc))): build/$(2)/dep/tests/$(1)/test_%.d: $(1)/src/test_%.cc ;$$(COMPILE.cc) -MM -MT $$(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$$<) -o $$@  $$<)
$(if $(filter $(1)/src/test_%.s,$(testsrc)),$(patsubst $(1)/src/test_%.s,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.s,$(testsrc))): build/$(2)/dep/$(1)/test/%.d: $(1)/src/test_%.s ;$$(COMPILE.s) -MM -MT $$(patsubst $(1)/src/test_%.s,build/$(2)/obj/tests/$(1)/test_%.o,$$<) -o $$@  $$<)

$(if $(filter $(1)/src/test_%.c,$(testsrc)),dep += $(patsubst $(1)/src/test_%.c,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.c,$(testsrc))))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),dep += $(patsubst $(1)/src/test_%.cc,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.cc,$(testsrc))))
$(if $(filter $(1)/src/test_%.s,$(testsrc)),dep +=$(patsubst $(1)/src/test_%.s,build/$(2)/dep/tests/$(1)/test_%.d,$(filter $(1)/src/test_%.s,$(testsrc))))

$(if $(filter $(1)/src/test_%.s,$(testsrc)),build/$(2)/tests/test_$(1): $(foreach m,$(modls),$(filter %.a %.so,$($(m)_targ))))
$(if $(filter $(1)/src/test_%.c,$(testsrc)),build/$(2)/tests/test_$(1): $(foreach m,$(modls),$(filter %.a %.so,$($(m)_targ))))
$(if $(filter $(1)/src/test_%.cc,$(testsrc)),build/$(2)/tests/test_$(1): $(foreach m,$(modls),$(filter %.a %.so,$($(m)_targ))))

$(if $(filter $(1)/src/test_main.c,$(testsrc)),build/$(2)/tests/test_$(1): | build/$(2)/tests)
$(if $(filter $(1)/src/test_main.c,$(testsrc)),build/$(2)/tests/test_$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter $(1)/src/test_main.c,$(testsrc)),build/$(2)/tests/test_$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter $(1)/src/test_main.c,$(testsrc)),build/$(2)/tests/test_$(1): $(patsubst $(1)/src/test_%.c,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.c,$(testsrc))); $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter $(1)/src/test_main.c,$(testsrc)),rtests+= build/$(2)/tests/test_$(1))
$(if $(filter $(1)/src/test_main.c,$(testsrc)),clean += build/$(2)/tests/test_$(1))

$(if $(filter $(1)/src/test_main.cc,$(testsrc)),build/$(2)/tests/test_$(1): | build/$(2)/tests)
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),build/$(2)/tests/test_$(1): LDFLAGS += $($(2)_LDFLAGS))
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),build/$(2)/tests/test_$(1): LDLIBS += $($(2)_LDLIBS))
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),build/$(2)/tests/test_$(1): LINK = $(CXX))
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),build/$(2)/tests/test_$(1): $(patsubst $(1)/src/test_%.cc,build/$(2)/obj/tests/$(1)/test_%.o,$(filter $(1)/src/test_%.cc,$(testsrc))); $$(LINK.o) $$^ $$(LOADLIBES) $$(LDLIBS) -o $$@)
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),rtests+= build/$(2)/tests/test_$(1) )
$(if $(filter $(1)/src/test_main.cc,$(testsrc)),clean += build/$(2)/tests/test_$(1))

endef



$(foreach c,$(configs),build/$(c)/obj/tests build/$(c)/dep/tests build/$(c)/tests):
	mkdir -p $@

$(foreach m,$(modls),$(foreach c,$(configs),$(eval $(call mk_modl_tests,$(m),$(c)))))



.PHONY: build
build:

.PHONY: examples
examples:

.PHONY: clean
clean:
	$(RM) $(clean)
	find . -name '*.orig' -delete


.PNONY: $(addprefix run_,$(rtests))
$(foreach d,$(rtests),$(eval run_$(d): $(d)))

$(addprefix run_,$(rtests)):
	$(patsubst run_%,%,$@) -b



.PHONY: test tests
tests: $(addprefix run_,$(rtests))
test: tests

distclean:
	$(RM) -r build

# clang-format does not format class/struct defs how I like them
# with access spec 1 indent, and members 1 more indent after that
# currently puts access spec on same level as members..
# but then I want a full reformatter (space between functions, members etc.. managed as well).
.PHONY: format reformat
reformat: format

format:
	astyle --project=.astylerc --ascii --suffix=none  $(allsrc) $(allhdr)

#foo:
	#env -u NIX_CFLAGS_COMPILE clang-format -style=file -i $(allsrc) $(allhdr)

ifneq ($(MAKECMDGOALS),distclean)
-include $(dep)
endif
