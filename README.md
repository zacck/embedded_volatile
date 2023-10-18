Example code to demostrate use and need of `volatile`
LEVEL 0 Optimization
```assembly
10                    	uint32_t value = 0;
080001ee: 00 23         movs    r3, #0
080001f0: 7b 60         str     r3, [r7, #4]
11                    	uint32_t *p = (uint32_t *)SRAM_ADDRESS1;
080001f2: 04 4b         ldr     r3, [pc, #16]   ; (0x8000204 <main+28>)
080001f4: 3b 60         str     r3, [r7, #0]
15                    		value = *p;
080001f6: 3b 68         ldr     r3, [r7, #0]
080001f8: 1b 68         ldr     r3, [r3, #0]
080001fa: 7b 60         str     r3, [r7, #4]
16                    		if(value) break;
080001fc: 7b 68         ldr     r3, [r7, #4]
080001fe: 00 2b         cmp     r3, #0
08000200: f9 d0         beq.n   0x80001f6 <main+14>
20                    	while(1);
```
================================================================================================
LEVEL 02 Optimization without volatile keyword
```assembly
080001e6: 00 08         lsrs    r0, r0, #32
15                    		value = *p;
                      main:
080001e8: 4f f0 00 53   mov.w   r3, #536870912  ; 0x20000000
080001ec: 5b 68         ldr     r3, [r3, #4]
16                    		if(value) break;
; compiler optimizes away reads 
080001ee: 03 b9         cbnz    r3, 0x80001f2 <main+10>
080001f0: fe e7         b.n     0x80001f0 <main+8>
20                    	while(1);
```
================================================================================
Level 02 Optimization with volatile keyword
Note the generated assembly code now branches on comparison
With volatile keyword

```assembly
080001e6: 00 08         lsrs    r0, r0, #32
16                    		value = *p;
                      main:
080001e8: 4f f0 00 52   mov.w   r2, #536870912  ; 0x20000000
080001ec: 53 68         ldr     r3, [r2, #4]
17                    		if(value) break;
; compiler jumps back to read every loop
080001ee: 00 2b         cmp     r3, #0
080001f0: fc d0         beq.n   0x80001ec <main+4>
21                    	while(1);
080001f2: fe e7         b.n     0x80001f2 <main+10>
```
