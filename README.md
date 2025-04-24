 # bunny_build
 

         / \
        / _ \
       | / \ |
       ||   || _______
       ||   || |\     \
       ||   || ||\     \
       ||   || || \    |
       ||   || ||  \__/
       ||   || ||   ||
        \\_/ \_/ \_//
       /   _     _   \
      /               \
      |    O     O    |
      |   \  ___  /   |
     /     \ \_/ /     \
    /  -----  |  --\    \
    |     \__/|\__/ \   |
    \       |_|_|       /
     \_____       _____/
           \     /
           |     |




*bunny_build* is an alternative psuedo-assembler for the NXP EZH (SmartDMA) IO coprocessor.

## Why bunny?

Because they are fast!  Just like EZH.

and....  It will be used on the MCX947 BunnyBrain board.

## High Level Goals

1. Retain compatibility with old keil/c macro syntax to validate functionality
2. Not require the keil tools... ever.  Works with GCC
3. EZH code can be assembled in the target/application as needed. The assembler will be a simple C file.  Assemble at run time.
4. The build process has been upgraded to be two-pass (vs C macros only in the original EZH builder) to handle labels, etc.  
5. Because of #3, we can use the C linker to get references to application variables, etc  Makes developing ezh much simpler.
6. Easy to wrap in a simple command line application. Be able to generate binary blobs in different formats (c arrays, etc) to include in MCU application code.
6. Handle GOTO/JUMP properly
7. Disassemble EZH binaries
8. Once the "C" version is complete and supports all instructions, I would like an assembler that works like the old Analog device ADSP DSP assembler.   Something that almost looks like C.

## Current state

- bunny_build can currently recreate the EZH/SmartDMA "Camera Generator".  The camera generator code was for the MCX (and LPC55).  bunny_build can input the same code and generate the same binary blob.  We need more test cases and to validate that all instructions are generated correctly.

- bunny_build is being used in some commercial projects.

- There are a few simple IO output tests cases to demonstrate simple programs

- we have some goto testcases that all appear to function well.  (this was an issue from the previous macro approach)

- 
Test cases needed:

- A program that use zero overhead loops.

## Building the Validator.

1. cd to `test/cl_build`

2. generate a build system like : `cmake ./ -B"build"`

- on Windows, that should make a Visual Studio Project in the `build` folder


- on *nix you get make files.  Although,  I like "ninja".  Makes me feel powerful

`cmake ./ -B"build" -G"Ninja`

`ninja -C "build"`

`./build/bunny_build`

Run the output binary and it should tell you that validation of the camera code worked.

## Notes

- bunny_build.c/.h was bootstrapped from the fsl_ezh_armclang.h file.  See the camera generator example, or any of the LPC55 samples. 
- I added code to support the "C" way of building the instructions.  Added print/warnings/errors to instructions that have not yet been implemented.

