Describe the procedure that how you get the flag
===
## 1. open gdb
```
gdb -q traceme2
```
## 2. run
```
(gdb) r
Starting program: /home/rslai/Course/Unix/nctu_unix_hw4/problemset/traceme/traceme2 

Program received signal SIGTRAP, Trace/breakpoint trap.
0x00007ffff7a42428 in __GI_raise (sig=5) at ../sysdeps/unix/sysv/linux/raise.c:54
54      ../sysdeps/unix/sysv/linux/raise.c: No such file or directory.
```
## 3. 執行下一行指令，function call會被當作一行指令，不會進去function裡面一行一行執行
```
(gdb) n
55      in ../sysdeps/unix/sysv/linux/raise.c
(gdb) n
main (argc=1, argv=0x7fffffffdc28) at traceme.c:43
43      traceme.c: No such file or directory.
(gdb) n
traced
44      in traceme.c
(gdb) p output
$1 = '\000' <repeats 63 times>
```
### 假設當前已經獲得 output 的 n 個字元，因為目標是要獲得共 38 個字元，因此每次至少要 `next (38-n)`
```
(gdb) n 38
44      in traceme.c
(gdb) p output
$2 = "ASM{a_Pr0ce55_can_b", '\000' <repeats 44 times>
(gdb) n 19
45      in traceme.c
(gdb) p output
$3 = "ASM{a_Pr0ce55_can_b_trac3d_0", '\000' <repeats 35 times>
(gdb) n 10
45      in traceme.c
(gdb) p output
$4 = "ASM{a_Pr0ce55_can_b_trac3d_0n1Y_0", '\000' <repeats 30 times>
(gdb) n 5
44      in traceme.c
(gdb) p output
$5 = "ASM{a_Pr0ce55_can_b_trac3d_0n1Y_0nc3", '\000' <repeats 27 times>
(gdb) n 2
44      in traceme.c
(gdb) p output
$6 = "ASM{a_Pr0ce55_can_b_trac3d_0n1Y_0nc3}", '\000' <repeats 26 times>
```
## 4. close gdb
```
(gdb) q
A debugging session is active.

        Inferior 1 [process 31954] will be killed.

Quit anyway? (y or n) y
```
