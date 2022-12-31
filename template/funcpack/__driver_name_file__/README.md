# ${driver_name} Driver

${author_name}
${author_affiliation}

## Overview

A Generic (Hardware/OS agnostic) ${driver_name} driver.

## Usage:

** TODO **

See [example.c](./example.c)

## Documentation:

Run `make doc` or `doxygen` in the repository root to generate the documentation.
Find the generated documentation at `doc/html/index.html`.

## Usage: Development

Note: Most development utils only run under linux for now. Sorry.

*(external) Development dependencies:*
  - standard posix tools + GNU make 
  - python 3.10+, including venv
  - llvm's clang-format 13+
  - (optional) llvm's clangd 13+
  - (optional) [bear](https://github.com/rizsotto/Bear), to generate a compile_commands.json for clangd.


*Reginald:*
  - All register-related boilerplate code is generated using [Reginald](https://github.com/schilkp/reginald) 
  from [${driver_name_file}_regs.yaml](${driver_name_file}_regs.yaml).
  - Instead of editing register and enum definitions in [inc/${driver_name_file}_regs.h](inc/${driver_name_file}_regs.h)
  and [inc/${driver_name_file}_reg_enums.h](inc/${driver_name_file}_reg_enums.h),
  edit [${driver_name_file}_regs.yaml](${driver_name_file}_regs.yaml).
  - The makefile automatically handles both downloading reginald with it's dependencies, and regenerating the headers.
  All generated header files are checked into git, so neither python nor reginald are required when using the driver 
  as-is.

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

  - A re-generation of all code managed by Reginad can be force using:

```bash 
$$ make clean_all
```

