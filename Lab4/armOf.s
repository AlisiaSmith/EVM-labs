	.arch armv5t
	.eabi_attribute 23, 1
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"source.c"
	.text
	.global	__aeabi_ui2f
	.global	__aeabi_f2d
	.global	__aeabi_dadd
	.global	__aeabi_ddiv
	.global	__aeabi_dmul
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r9, r10, fp, lr}    // ???????
	ldr	r0, [r1, #4]       // чтение из памяти в регистр r0
	mov	r2, #10            // r2 = 10
	mov	r1, #0             // r1 = 0
	bl	strtol             // переход с сохранением адреса возврата
										  	 // вызов подпрограммы
	mov	r10, #0            // r10 = 0
	mov	fp, r0             // fp = r0
	mov	r4, #0             // r4 = 0
	mov	r5, #0             // r5 = 0
	mov	r6, #0             // r6 = 0
	mov	r8, #0             // r8 = 0
	ldr	r7, .L8            // чтение из памяти в регистр r7
	ldr	r9, .L8+4          // чтение из памяти в регистр r9
.L2:
	tst	r10, #1            // логическое И, но без запоминания результата,
												 // изменяются только флаги Rn AND shifter_operand S bit always set
	mov	r0, r10            // r0 = r10
	bne	.L3                // Если r0 != r10 перейти к .L3
	bl	__aeabi_ui2f       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	bl	__aeabi_f2d        // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	bl	__aeabi_dadd       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r6             // r2 = r6
	mov	r3, r7             // r3 = r7
	bl	__aeabi_dadd       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	mov	r0, r6             // r0 = r6
	mov	r1, r7             // r1 = r7
	bl	__aeabi_ddiv       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	mov	r0, r4             // r0 = r4
	mov	r1, r5             // r1 = r5
	bl	__aeabi_dadd       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	add	r10, r10, #1       // r10 = r10 + 1
	cmp	r10, fp            // Сравнение, вернее арифметическое вычитание без запоминания результата
												 // изменяются только флаги Rn – shifter_operand S bit always set
	mov	r4, r0             // r4 = r0
	mov	r5, r1             // r5 = r1
	bls	.L2                // если r10 <= fp переход к метке .L2
.L5:
	mov	r0, r4             // r0 = r4
	mov	r1, r5             // r1 = r5
	mov	r2, #0             // r2 = 0
	ldr	r3, .L8+8          // чтение из памяти в регистр r3
	bl	__aeabi_dmul       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	mov	r0, #1             // r0 = 1
	ldr	r1, .L8+12         // чтение из памяти в регистр r1
	bl	__printf_chk       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r0, #0             // r0 = 0
	pop	{r3, r4, r5, r6, r7, r8, r9, r10, fp, pc}    // ??????????
.L3:
	bl	__aeabi_ui2f       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	bl	__aeabi_f2d        // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	bl	__aeabi_dadd       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r6             // r2 = r6
	mov	r3, r7             // r3 = r7
	bl	__aeabi_dadd       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	mov	r0, r8             // r0 = r8
	mov	r1, r9             // r1 = r9
	bl	__aeabi_ddiv       // переход с сохранением адреса возврата
												 // вызов подпрограммы
	mov	r2, r0             // r2 = r0
	mov	r3, r1             // r3 = r1
	mov	r0, r4             // r0 = r4
	mov	r1, r5             // r1 = r5
	bl	__aeabi_dadd			 // переход с сохранением адреса возврата
												 // вызов подпрограммы
	add	r10, r10, #1       // r10 = r10 + 1
	cmp	fp, r10            // Сравнение, вернее арифметическое вычитание без запоминания результата
												 // изменяются только флаги Rn – shifter_operand S bit always set
	mov	r4, r0             // r4 = r0
	mov	r5, r1             // r5 = r1
	bcs	.L2                // Если fp >=  r10  перейти к .L2
	b	.L5                  // переход к .L5
.L9:
	.align	2
.L8:
	.word	1072693248
	.word	-1074790400
	.word	1074790400
	.word	.LC0
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%Lf \012\000"
	.ident	"GCC: (Ubuntu/Linaro 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",%progbits
