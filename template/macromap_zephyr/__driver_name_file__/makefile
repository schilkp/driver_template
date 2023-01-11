#
# ${driver_name} makefile
# Philipp Schilk, 2022
# Free to use with no restrictions but no guarantees.
#


################################################################################
#               ____  _____ _____ _____ ___ _   _  ____ ____
#              / ___|| ____|_   _|_   _|_ _| \ | |/ ___/ ___|
#              \___ \|  _|   | |   | |  | ||  \| | |  _\___ \
#               ___) | |___  | |   | |  | || |\  | |_| |___) |
#              |____/|_____| |_|   |_| |___|_| \_|\____|____/
#
#################################################################################

# Compiler + Flags
CC=gcc
LDFLAGS=
CFLAGS=-Wall -Wextra -Wpedantic -Werror=vla -fsanitize=address -g -Isrc -Iinc -Itest/Unity -I.
DEPFLAGS=-MMD -MP -MF $$(BUILDDIR)/$$*.d

# Sources: 
SOURCES=test/Unity/unity.c src/${driver_name_file}.c

# Automatically genereated sources lists, ususally do not have to be changed:
TEST_SOURCES=$$(wildcard test/*.c)
TESTS=$$(addprefix $$(BUILDDIR)/,$$(TEST_SOURCES:.c=.out))
OBJECTS=$$(addprefix $$(BUILDDIR)/,$$(SOURCES:.c=.o))
DEPENDENCIES=$$(addprefix $$(BUILDDIR)/,$$(SOURCES:.c=.d))
DEPENDENCIES+=$$(addprefix $$(BUILDDIR)/,$$(TEST_SOURCES:.c=.d))

BUILDDIR=build

# Set to '@' to supress commands being echoed
SILENT?=

################################################################################
#         ____ ___  __  __ ____ ___ _        _  _____ ___ ___  _   _
#        / ___/ _ \|  \/  |  _ \_ _| |      / \|_   _|_ _/ _ \| \ | |
#       | |  | | | | |\/| | |_) | || |     / _ \ | |  | | | | |  \| |
#       | |__| |_| | |  | |  __/| || |___ / ___ \| |  | | |_| | |\  |
#        \____\___/|_|  |_|_|  |___|_____/_/   \_\_| |___\___/|_| \_|
#
################################################################################

.PHONY: all
all: run_tests

.PHONY: run_tests
run_tests: build_tests
	-python3 scripts/run_tests.py $$(TESTS)

.PHONY: build_tests
build_tests: $$(TESTS)

.PHONY: clean
clean:
	rm -rf $$(BUILDDIR)

# Link tests:
$$(BUILDDIR)/%.out: $$(BUILDDIR)/%.o $$(OBJECTS)
	$$(SILENT) $$(CC) $$(CFLAGS) $$^ -o $$@

# Compile sources and test sources
$$(BUILDDIR)/%.o: %.c makefile
	@mkdir -p $$(dir $$@)
	$$(SILENT) $$(CC) -c $$(CFLAGS) $$(DEPFLAGS) $$*.c -o $$@


################################################################################
#                   _   _ _____ ___ _     ___ _______   __
#                  | | | |_   _|_ _| |   |_ _|_   _\ \ / /
#                  | | | | | |  | || |    | |  | |  \ V /
#                  | |_| | | |  | || |___ | |  | |   | |
#                   \___/  |_| |___|_____|___| |_|   |_|
#
################################################################################

.PHONY: format
format:
	python3 scripts/clang_format.py

# Generate documentation using doxygen:
doc:
	doxygen
	firefox doc/html/index.html

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
