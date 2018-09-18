/*
 * long long GetCycleCount(void)
 */
#ifdef PentiumMhz
#
# instruction RDTSC (Read Time-Stamp Counter); no op-code, so manually
# issue it with .byte 0x0f; .byte 0x31;
# This puts the low-order 32 bits in %eax, and hi in %edx
#
.global GetCycleCount
GetCycleCount:
   #ifdef __LP64__               /* If I'm using AMD64 assembly */
      xorq %rax, %rax
      .byte 0x0f; .byte 0x31
      shlq $32, %rdx
      orq %rdx, %rax
   #else                         /* otherwise, IA32 assembly */
      .byte 0x0f; .byte 0x31
   #endif
        ret

#elif defined(SparcMhz)
        .section        ".text"
        .global GetCycleCount
GetCycleCount:
        rd      %tick, %o0
        clruw   %o0, %o1         ! put the low 32 bits of o0 o1, clear high
        retl
        srlx    %o0, 32, %o0     ! put high 32 bits in low half of o0
#endif
