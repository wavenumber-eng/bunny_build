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




*bunny_build* is an alternative psuedo-assembler for the NXP / EZH IO coprocessor.

## Why bunny?

Because they are fast!  Just like EZH.

and....  It will be used on the Wavenumber MCX947 bunny brain board.

## High Level Goals

1. Retain compatibility with old keil/c macro syntax to validate functionality
2. Not require the keil tools... ever.  Works with GCC
3. EZH code can be assembled in the target/application as needed. The assembler will be a simple C file.  Assemble at run time!
4. The build process has been upgraded to be two-pass (vs C macros only in the original EZH builder) to handle labels, etc.  
5. Because of #3, we can use the C linker to get references to application variables, etc  Makes developing ezh much simpler.
6. Easy to wrap in a simple command line application. Be able to generate binary blobs in different formats (c arrays, etc) to include in MCU application code.
6. Handle GOTO/JUMP properly
7. Disassemble EZH binaries

## Current state

- bunny_build can currently recreate the EZH/Smart "Camera Generator".  The camera generator code was for the MCX (and LPC55).  bunny_build can input the same code and generator the samy binary blob.

- Need more test cases to validate the assembler.   Next will be the lpc55 "hello_pdm"

- Need some simple IO toggle type test programs to validate.

## building the validator.

1. cd to `test/`
2. generate a build system like : `cmake ./ -B"build"`

- on Windows, that should make a visual studio project in the `build` folder
- on *nix you get make files.  Although,  I like "ninja".  Makes me feel powerful

`cmake ./ -B"build" -G"Ninja`

`cd build`

`ninja`

run the output binary and it should tell you that validation of the camera code worked.
