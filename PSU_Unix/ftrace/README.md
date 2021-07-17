# PSU_ftrace

Tracer of all functions and system call.

## Advanced informations

Below are the step I followed to catch each different type of call. This does only work on ELF x64 files.

### Prerequisite

Following a process is accessible thanks to [`ptrace`](https://man7.org/linux/man-pages/man2/ptrace.2.html). It will be used to similarly begin a tracking, get next step and read registers.

Below are the different options of ptrace I used. Refer to the man for a complete usage.
* `PTRACE_ATTACH`: Able you to track the process with pid passed as paramter.
* `PTRACE_SINGLESTEP`: Let you read and execute the following opcode.
* `PTRACE_GETREGS`: Fill the `user_regs_struct *` passed as parameters.
* `PTRACE_PEEKTEXT` or `PTRACE_PEEKDATA`: Return the long (usually 8 bytes, 64 bits) from memory at the adress passed as parameter.

To effectively track a process, I looped like so:
* Get the current registers using `PTRACE_GETREGS`.
* Get the current opcode while using `PTRACE_PEEKTEXT` at the adress of register `RIP`.
* Verify the opcode.
* Forward the program using `PTRACE_SINGLESTEP`.

### SysCall

System calls, commonly named SysCall, are present when reading opcode `0x050F`.

The called syscall is the one with the id present in register `RAX`. The list of syscall ids is present at [`<asm/unistd_64.h>`](https://code.woboq.org/linux/linux/arch/x86/include/generated/uapi/asm/unistd_64.h.html).

The argument of the syscall are respectively accessible on registers `RDI`, `RSI`, `RDX`, `RCX`, `R8` and `R9`. If more arguments are needed, you can access them while reading on the stack.

The return value of the syscall is accessible after the next step, on the register `RAX`.

### Program's function call

Track function are alone quiet easy. However retrieve this function name required a lot more steps.

#### Get function address

Program's calls are accessible with different opcode, depending on the call.

Regular calls use opcode `0xE8`. An offset is present on the following 4 bytes (int). This is the offset, relative to the address of the next opcode, at which the function is.

Other calls have `0xFF` as least significant bits. The next bytes will defined how to find the address of the function.

The rules it follow are those (`op` is the next byte of the opcode):
* Case of `op & 0x0F`:
  * `0x00`, use register `RAX`.
  * `0x01`, use register `RCX`.
  * `0x02`, use register `RBX`.
  * `0x03`, use register `RDX`.
  * `0x04`, use a particular value knowned as `SIB`, as described [here](https://www.sandpile.org/x86/opc_sib.htm).
  * `0x05`, use register `RBP`.
  * `0x06`, use register `RSI`.
  * `0x07`, use register `RDI`.
* Case of `op & 0xF0`:
  * `0x10`, the address of the function can be read from memory at the address present in the register.
  * `0x50`, the address of the function can be read from memory at the address present in the register plus the value of the byte after the opcode.
  * `0x90`, the address of the function can be read from memory at the address present in the register plus the value of the four bytes (int) after the opcode.
  * `0xD0`, the address of the function is the content of register.
* Exceptions of the rules:
  * if op is `0x15`, it does work the same way as a regular call.
  * If op is `0xD4`, the address of the function is the content of register `RSP`.

If it doesn't follow those rules, then it not a function call.

#### Get function name

First, you should know the address of the file on runtime, meaning the one you just read, is dependant of where it is load on memory. This implied you first need to know where is loaded your binaries on memory.

To get the name of a function, you first need to find in which binary it is. It can either be on the executable, or in any dependencies loaded while running. That for, you just need to compare the address of the function with the addresses of all binaries on memory.

Depending on if the function is located on the `Procedure Linkage Table` (PLT) of your binary, meaning its address is on the `.plt` section of the binary, you should act differently.

| Non-PLT case | PLT case |
| ------------ | -------- |
| You need to search on the Symbol Table of the binary, if any, as well as the Dynamic Symbol Table. Then you just need to iterate over each symbol until you find the one beginning at your function's address. | At the address of the function in the PLT is another call. It used a 2 bytes opcode, followed by a 4 bytes (int) offset relative to the next opcode.<br>This offset is located on the `Global Offset Table` (GOT) of the binary, which is the `.got` or `.got.plt` section of the binary. The functions are located at the fourth and following rows on the GOT.<br>Having the index on the GOT of a function, it is possible to access it in the Relocation section of the PLT `.rela.plt`.<br>With it, it is possible to access the name of the function, situated on the Dynamic Symbol Table. |
