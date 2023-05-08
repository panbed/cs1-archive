# COP3502C Lab Assignment 10

To compile: `gcc lab_assignment_10.c && ./a.out` (Linux)


Valgrind output:
```
==374== Memcheck, a memory error detector
==374== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==374== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==374== Command: ./a.out
==374==
        notaword : 1
        ucf : 1
        no : 1
        note : 1
        corg : 1
==374==
==374== HEAP SUMMARY:
==374==     in use at exit: 0 bytes in 0 blocks
==374==   total heap usage: 18 allocs, 18 frees, 4,696 bytes allocated
==374==
==374== All heap blocks were freed -- no leaks are possible
==374==
==374== For lists of detected and suppressed errors, rerun with: -s
==374== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
