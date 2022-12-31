# Driver Project Generator
Philipp Schilk, 2022

Automatically generate a driver skeleten.

## Usage:
 - Edit new_driver.py: Adapt all names as desired
 - `python new_driver.py`

## Available templates:
 - macromap
   - Generic driver .
   - Macro system for register packing/unpacking.
   - Unit testing based on ThrowTheSwitch's [Unity](https://github.com/ThrowTheSwitch/Unity).
   - Doxygen documentation generation.
   - A makefile and python test-runner script to handle unit testing.
   - A clang-format file, with definetly un-controversial settings.
   - A python script to format all code, and precommit hook to validate formatting.

 - macromap_zephyr
   - Includes a wrapper to provide the zephyr device interface, and dts and kconfig integration.
   - Includes build system/files to include driver into zephyr as an 'out-of-tree' driver.
   - Otherwise the sames as 'macromap'.

 - funcpack
   - Generic driver 
   - Functions for register packing/unpacking generated with [Reginald](git@github.com:schilkp/reginald.git).
   - Unit testing based on ThrowTheSwitch's [Unity](https://github.com/ThrowTheSwitch/Unity).
   - Doxygen documentation generation.
   - A makefile to handle code generation and unit testing using a python test-runner script.
   - A clang-format file, with definetly un-controversial settings.
   - A python script to format all code, and precommit hook to validate formatting.

