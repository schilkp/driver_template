# ${driver_name} Driver

${author_name}
${author_affiliation}

## Overview

- Generic (Hardware/OS agnostic) driver.
- Zephyr wrapper.

## Usage: Generic

** TODO **

See [example_generic.c](./example_generic.c)

## Usage: Zephyr

** TODO **

## Documentation:

Run `make doc` or `doxygen` in the repository root to generate the documentation.
Find the generated documentation at `doc/html/index.html`.

## Usage: Development

Note: Most development utils only run under linux for now. Sorry.

*(external) Development dependencies:*
  - standard posix tools + GNU make 
  - python 3.10+
  - llvm's clang-format 13+
  - doxygen 1.9.5+
  - (optional) llvm's clangd 13+
  - (optional) [bear](https://github.com/rizsotto/Bear), to generate a compile_commands.json for clangd.

*Quickstart:*
 - The driver and unit tests can be compiled and run via make:

```bash
# Compile + Run unit tests:
$$ make all

# Clean:
$$ make clean
```
 - All unit tests are found in `test/`. Additional test sources need to be added to the makefile.
 - All code should be formatted according to the `.clang-format` file provided:

```bash
$$ make format
```

 - For LSP support using `clangd`, a `compile_commands.json` can be generated using [bear](https://github.com/rizsotto/Bear):

```bash 
$$ make clean
$$ bear -- make
```

 - Use the 'test_watch' script to repeadetly run tests on a second monitor:

```bash 
$$ ./scripts/test_watch.sh
```
