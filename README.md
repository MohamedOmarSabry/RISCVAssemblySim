# RISC-V Assembly C++ 32-Bit Instruction Set Simulator 

> A simple command line program made in C++ to simulate 32-bit RISCV assembly instructions.

## Description

A command line C++ program made to simulate RISC-V 32-bit instructions. You can load instructions from the `Instructions.txt` file or input them one by one using the terminal. You must use the x-register format and your instructions must end with a breaking instruction. If you decide to do it manually you have the option to delete the last instruction as well. You may also load data from a file or manually insert data. Data is in the form of an address-value pair. The addresses and values are in decimals. You may delete values if you insert their addresses. You may also change the starting instruction memory address. The simulator handles the instruction and data memory as being separate. Once you have loaded your instructions and data, you may run the simulation. The instruction count, address, and the values of your main registers will be displayed after every instruction is simulated.

## Features

- Simulates RISCV 32-bit instructions
- Can read instructions from files using x-indexed register names.
- Can read decimal memory addresses and decimal data from files.

## Getting Started

- Run the C++ file included in the GitHub. Instructions can be read from the `instructions.txt` file or inputted manually at run time.

## Authors

- **Mohammed Omar Sabry** - _GitHub Profile_: [MohamedOmarSabry](https://github.com/MohamedOmarSabry) | _Email_: momo12320@aucegypt.edu

If you encounter any issues or have suggestions for improvements, please reach out via email. Your feedback is valuable and helps us enhance the app for everyone.
