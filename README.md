# Project 0 - Protect your binary

This document aims to explain the protection mechanism used to protect the check_flag program logic.
How to run the program
If you have the protected/unprotected binary, run ./check_flag directly. If you have source code, run ‘make release-protected’ for protected binary or ‘make release-unprotected’ for unprotected binary and then run ./check_flag

## Constraints
The constraints in this project are limited to what characters are acceptable as valid flag characters and are as follows -
* Any character between lower case ‘a’ and lower case ‘z’
* Underscores

## Base flag checker logic (unprotected)
The base logic that is used to validate the flag provided by the user is simple and just has 2 mathematical operations -

* For every input flag character, repeat steps 2 to 4
* Subtract 95 from the ASCII value of the flag character
* Multiply the above difference by 10
* If this value does not match with the stored, accepted value at the current index, indicate that the flag is invalid and break out of the loop
* If all characters have matched, indicate that the flag is valid

## Protecting the above logic using a Custom VM
As the above logic is overly simple to reverse engineer, I had to implement a protection mechanism so that this logic is not revealed easily. So, I implemented a custom virtual machine.

This Virtual Machine is just a C++ based class and has the following properties:

* Six General Purpose Registers from ‘reg1’ to ‘reg6’
* A special DataPointer register (usage explained later)
* A special register rip that maintains the instruction pointer
* A boolean zFlag
* A RAM that is allocated 1000 bytes
* A set of instructions (listed later)

Using this Virtual machine, the base logic is protected using the below steps, which keep on adding to the overall complexity of the protection logic.

### Step 1: Initializing instructions, registers and their mapping:
Every instruction and every register has a specific custom code as follows - 

mov (register into register)
100
reg1
202
mov (value into register)
101
reg2
203
add
102
reg3
204
sub
103
reg4
205
mul
104
reg5
206
div
105
reg6
207
cmp
106
dp
208
je
107




lea
108




lfr
109






* mov (register into register): This would move the rightmost register’s value into the leftmost register. E.g. mov reg1, reg2
* mov (value into register): This would move the specified value into the register
* add: This would add two registers’ values and store the result in the leftmost register. E.g. add reg1, reg2
* sub: This would subtract two registers’ values and store the result in the leftmost register. E.g. sub reg1, reg2
* mul: This would multiply two registers’ values and store the result in the leftmost register. E.g. mul reg1, reg2
* div: This would divide two registers’ values and store the result in the leftmost register. E.g. div reg1, reg2
* cmp: This would compare two registers’ values and set zFlag to true if they are equal. E.g. cmp reg1, reg2
* je: This would accept two registers and jump to the instruction which is pointed by the leftmost register if zFlag is true, else it would jump to the instruction pointed by the rightmost register. E.g. je reg1, reg2
* lea: This would load data from the index pointed by the data pointer, i.e. dp register in the specified register. E.g. lea reg1, dp
* lfr: This would load data from the RAM at the index pointed by the rightmost register into the leftmost register. E.g. lea reg1, reg2

This mapping is stored in an unordered_map. The key of this unorder map is the opcode of the custom instructions above and the value is a lambda function that accepts two integers. These two integers are the codes to two registers provided to the instruction.

Once this mapping is initialized, the RAM is allocated 1000 bytes of memory.

### Step 2: Finding the exact point of execution

This VM has a execute method that accepts a list of integers. This is a list of step-wise instructions that the VM is supposed to perform as per the instructions and registers mapping.

For instance, the list [102, 204, 205] translates to “add reg3, reg4” as per the above mapping and so the values present in reg3 and reg4 would be added and the result would be stored in register reg3. Here, the VM would try to find 102 in the unordered_map, it would get a lambda function that adds two values and thus it would add values in 204 and 205.

However, since the base logic is overly simplified, the number of custom assembly instructions would be very small and thus would still be moderately easy to reverse engineer. To make it more complex, I have followed the below steps - 

* Before all the instructions start, set the first number in the list to be ‘101’
* Add about 1000-2000 completely random integers in the vector that make no sense to the mapping, such that they don’t have the number ‘101’
* Append the actual assembly opcode to the list of integers after this gibberish. Note that this assembly code also starts from ‘101’
* So, the list would look like [101,x,x,x,x,x,x,x,101, 102, …<actual assembly code>....]
* When these integers are passed to the execute method, a ‘start’ variable stores the first 101 value
* The ‘rip’ register points to index 1, meaning that the VM would ignore the first 101
* No instructions are executed till the 2nd ‘101’ is encountered
* Once it is found, all the data post this is considered for execution by the VM

### Step 3: Execution of custom assembly data

Once the starting point is found, the VM starts executing the assembly instructions one by one as follows - 

* VM ensures that the ‘rip’ value has not exceeded the instructions’ list size and loops
* Since every instruction comes as a triplet of integers, e.g. “add reg3, reg4” or “mov reg5, 100”, the VM will try to look for the integer pointed by rip, rip + 1 and rip + 2
* Value at rip will be looked up in the unordered_map and a lambda would be returned
* To this lambda, the VM will pass ‘rip + 1’ and ‘rip + 2’ values and thus execute the specified instruction
* After every instruction execution, the rip value will be incremented by 3

### Step 4: Matching the input flag values with stored flag values

To make this VM even more complicated, I have mixed the ‘data section’ with the code section’. I have not maintained a separate array that stores valid flag characters. In my list of integers that represent custom assembly instructions, I have added the data at a specific position. This position is maintained by the data pointer register dp. E.g. - 

mov reg1 22
mov reg2 0
mov dp 1086
add dp reg2
lea reg3 dp
lfr reg4 reg2
mov reg5 95
sub reg4 reg5
mov reg5 10
mul reg4 reg5
cmp reg3 reg4
mov reg4 1068
mov reg5 1108
je reg4 reg5
mov reg4 1
add reg2 reg4
cmp reg1 reg2
mov reg4 1032
mov reg5 1108
je reg5 reg4
100 50 0
190 20 210
90 60 190
0 30 60
0 210 190
20 230 60
130 100 150 80
mov reg4 22
cmp reg2 reg4




As highlighted in the above assembly, we can see that the flag data is present at a very specific position, only known by the ‘dp’ register

As per the above algorithm, ‘lea’ would load data from the data section which represents the stored, valid flag and ‘lfr’ would ‘load from RAM’, the provided input flag. As per the algorithm explained in the base flag checker section, the operations would be performed on the input data and the result would be compared with the stored flag characters one by one. If all characters match, the value of zFlag would be set to true which will be used later to display “Good flag” or “Bad flag”.

### Step 5: Flag size check

At the end of the list of integer instructions, I am adding the expected ‘size’ of the flag. This is to make sure that, if the valid flag is “xyz”, then an input “xyzxyz” would not be accepted as a valid flag just because the first three characters of the input flag match with the stored flag.


### Step 6: Final touch-ups

Finally, I strip the binary to get rid of all the possible symbols such as class or method names as they should not provide any hints towards the protection mechanism. I also compile the binary with -O3 optimization to make it more difficult for reverse engineering tools to interpret the algorithm.

### Conclusion:
I believe that all the 6 steps above would secure the algorithm as much as possible. We can keep adding as many layers of complexity to this project as humanly possible and make it almost impossible to reverse engineer.
