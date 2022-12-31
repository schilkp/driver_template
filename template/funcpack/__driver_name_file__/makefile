#
# ${driver_name} makefile
# Philipp Schilk, 2022
# Free to use with no restrictions but no guarantees.
#

# Compiler + Flags
CC=gcc
LDFLAGS=
CFLAGS=-Wall -Wextra -Wpedantic -Werror=vla -fsanitize=address -g -Isrc -Iinc -Itest/Unity -I.
DEPFLAGS=-MMD -MP -MF $$(BUILDDIR)/$$*.d

SOURCES=test/Unity/unity.c src/${driver_name_code}.c
TEST_SOURCES=$$(wildcard test/*.c)
TESTS=$$(addprefix $$(BUILDDIR)/,$$(TEST_SOURCES:.c=.out))
OBJECTS=$$(addprefix $$(BUILDDIR)/,$$(SOURCES:.c=.o))
PREPROC_EXPANDED_SRCS=$$(addprefix $$(BUILDDIR)/preproc/,$$(SOURCES))
PREPROC_EXPANDED_TEST_SRCS=$$(addprefix $$(BUILDDIR)/preproc/,$$(TEST_SOURCES))
DEPENDENCIES=$$(addprefix $$(BUILDDIR)/,$$(SOURCES:.c=.d))
DEPENDENCIES+=$$(addprefix $$(BUILDDIR)/,$$(TEST_SOURCES:.c=.d))

BUILDDIR=build

SILENT?=

# Reginald commit to use:
REGINALD_COMMIT_LOCK= 9768115

REGINALD_OUTPUT_FILES= inc/${driver_name_file}_regs.h inc/${driver_name_file}_reg_enums.h

.PHONY: all run_tests build_tests clean format doc preproc_expanded test clean_all

all: run_tests

run_tests: build_tests
	-python3 scripts/run_tests.py $$(TESTS)

build_tests: $$(TESTS)

clean:
	rm -rf $$(BUILDDIR)

clean_all: clean
	rm $$(REGINALD_OUTPUT_FILES)

format:
	python3 scripts/clang_format.py

# Link tests:
$$(BUILDDIR)/%.out: $$(BUILDDIR)/%.o $$(OBJECTS)
	$$(SILENT) $$(CC) $$(CFLAGS) $$^ -o $$@

# Compile sources and test sources
$$(BUILDDIR)/%.o: %.c makefile $$(REGINALD_OUTPUT_FILES) 
	@mkdir -p $$(dir $$@)
	$$(SILENT) $$(CC) -c $$(CFLAGS) $$(DEPFLAGS) $$*.c -o $$@

# Generate C files with all preproc expansion:
preproc_expanded: $$(PREPROC_EXPANDED_SRCS) $$(PREPROC_EXPANDED_TEST_SRCS)
$$(BUILDDIR)/preproc/%.c: %.c makefile
	@mkdir -p $$(dir $$@)
	$$(SILENT) $$(CC) -c $$(CFLAGS) -E -C $$*.c -o $$@

# Re-generate compile_commands.json using either bear or compiledb
# GEN_COMP_COMMANDS_CMD=compiledb make
GEN_COMP_COMMANDS_CMD=bear -- make
compile_commands.json: clean
	$$(GEN_COMP_COMMANDS_CMD)

# Generate documentation using doxygen:
doc:
	doxygen
	firefox doc/html/index.html

# Generate register header files using reginald:
REGINALD_PYTHON=scripts/reginald/env/bin/python
REGINALD=scripts/reginald/run.py

inc/${driver_name_code}_regs.h: ${driver_name_file}_regs.yaml $$(REGINALD)
	$$(REGINALD_PYTHON) $$(REGINALD) ${driver_name_file}_regs.yaml c_funcpack.regs > inc/${driver_name_file}_regs.h
	clang-format -i -style=file inc/${driver_name_code}_regs.h

inc/${driver_name_code}_reg_enums.h: ${driver_name_file}_regs.yaml $$(REGINALD)
	$$(REGINALD_PYTHON) $$(REGINALD) ${driver_name_file}_regs.yaml c_funcpack.enums > inc/${driver_name_file}_reg_enums.h
	clang-format -i -style=file inc/${driver_name_code}_reg_enums.h

test: scripts/reginald/run.py
# Download and setup the correct version of reginald:
$$(REGINALD): makefile
	@echo ""
	@echo "==== Installing Reginald: Cloning Reginald repo... ======================================"
	@echo ""
	rm -rf scripts/reginald
	git clone git@github.com:schilkp/reginald.git scripts/reginald
	git -C scripts/reginald checkout $$(REGINALD_COMMIT_LOCK)
	@echo ""
	@echo "==== Setting up python venv... =========================================================="
	@echo ""
	python -m venv scripts/reginald/env
	@echo ""
	@echo "==== Installing reginald dependencies into venv... ======================================"
	@echo ""
	scripts/reginald/env/bin/python -m pip install -r scripts/reginald/requirements.txt
	@echo ""
	@echo "==== Reginald Ready! ===================================================================="
	@echo ""

# Keep dependencies around, make them an explicit target:
$$(DEPENDENCIES):

# Keep object files and output files:
.PRECIOUS: $$(BUILDDIR)/%.out
.PRECIOUS: $$(BUILDDIR)/%.o

ifneq ($$(MAKECMDGOALS),clean)
ifneq ($$(MAKECMDGOALS),format)
ifneq ($$(MAKECMDGOALS),compile_commands)
ifneq ($$(MAKECMDGOALS),doc)
include $$(DEPENDENCIES)
endif
endif
endif
endif
