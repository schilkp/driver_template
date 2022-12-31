# Driver Project Generator
Philipp Schilk, 2022

Automatically generate a driver skeleten.

## Usage:
 - Edit new_driver.py: Adapt all names as desired
 - `python new_driver.py`

## Available templates:
 - macromap
   - Generic driver using a macro system for register packing.
   - Unit testing based on ThrowTheSwitch's [Unity](https://github.com/ThrowTheSwitch/Unity).
   - Doxygen documentation generation.
   - A makefile and python test-runner script to handle unit testing.
   - A clang-format file, with definetly un-controversial settings.
   - A python script to format all code, and precommit hook to validate formatting.

 - macromap_zephyr
   - Includes a wrapper to provide the zephyr device interface, and dts and kconfig integration.
   - Includes build system/files to include driver into zephyr as an 'out-of-tree' driver.
   - Otherwise the sames as 'macromap'.
