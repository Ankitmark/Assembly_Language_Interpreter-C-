# Assembly_Language_Interpreter-C-
Build an Assembly Language Interpreter (ALI) for a Simple Assembly Language (SAL) in C++

This project is about building an Assembly Language Interpreter (ALI) for a Simple Assembly Language (SAL).
Fortunately for you SAL has a limited set of instructions, described below, which makes it easier to write the ALI.
SAL programs are executed on a virtual (emulated) machine consisting of a memory, which stores program code
and program data, an accumulator register, an additional register and a Program Counter (PC), which keeps track
of the instruction being currently executed. Your ALI can execute SAL programs one line at a time (in a sort of
debug mode) or at once until a halt instruction is encountered.

The execution of a ALI consists of the following three steps:
1. Prompt the user for a file name in the current directory.
2. Read a SAL from the file. The program is stored in the memory starting at address 0.
3. Execute a command loop consisting of three commands:

l – Executes a line of code, starting from line 0, updates the PC, the registers and memory according to
the instruction and prints the values of the registers, the zero and overflow bits, and memory after the
line is executed.
a – Executes all the instructions until a halt instruction is encountered or there are no more instructions
to be executed.
q – Quits the command loop.

The computer hardware uses 32-bit words and consists of the following components:

1. Memory. A 32-bit, word-addressable memory (RAM) for data, holding 256 words. Words are addressed by
their location, starting from location 0 all the way up to location 255. Each location may either hold a signed
integer in 2’s complement notation or a SAL instruction.
2. Accumulator. A 32-bit register. It is also known as Register A or A for short.
3. Additional register. A 32-bit register also known as Register B or B for short.
4. Program counter (PC). An 8-bit program counter (PC). The PC holds the address (number in program
memory) of the next instruction to be executed. Before the program starts execution, the PC holds the value 0. It is subsequently updated as each instruction is executed.
5. A zero-result bit. This bit is set if the last ADD instruction produced a zero result. This bit is cleared if the
last ADD instruction produced a result different from zero. The initial value is zero. The bit is changed only
after ADD instructions are executed.
6. An overflow bit. This bit is set whenever an ADD instruction produces an overflow (i.e., a result that cannot
be stored in 2’s complement notation with 32 bits). It is cleared if the ADD instruction did not produce an
overflow. The initial value is zero.


1.DEC symbol - Declares a symbolic variable consisting of a single letter (e.g., X). The
variable is stored at the memory location of this instruction.
2.LDA symbol - Loads byte at data memory address of symbol into the accumulator.
3.LDB symbol - Loads byte at data memory address symbol into B.
4.LDI value - Loads the integer value into the accumulator register. The value could be negative.
5.STR symbol - Stores content of accumulator into data memory at address of symbol.
6.XCH Exchanges - the content registers A and B.
7.JMP number - Transfers control to instruction at address number in program memory.
8.JZS number - Transfers control to instruction at address number if the zero-result bit is set.
9.JVS number - Transfers control to instruction at address number if the overflow bit is set.
10.ADD Adds - the content of registers A and B. The sum is stored in A. The overflow and zero-result bits are set or cleared as needed.
11.HLT Terminates program execution.

Table 1: Instruction set of SAL.

The registers are used to hold data for arithmetic operations (i.e., additions). The program counter holds the
index value (starting at 0) of the next instruction to be executed. SAL has the instruction set shown in Table 1.


