	.arch armv5t
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"source.c"
	.text
	.global	__aeabi_i2d
	.global	__aeabi_ui2f
	.global	__aeabi_f2d
	.global	__aeabi_dadd
	.global	__aeabi_ddiv
	.global	__aeabi_dmul
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%Lf \012\000"
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, fp, lr}
	add	fp, sp, #12          // поместить в регистр fp сумму sp и 12
	sub	sp, sp, #32          // вычесть из sp 32, сохранить в sp
	str	r0, [fp, #-40]       // Запись из регистра в память
	str	r1, [fp, #-44]       // Запись из регистра в память
	ldr	r3, [fp, #-44]       // чтение из памяти в регистр r3
	add	r3, r3, #4           // пибавить к r3 4, сохранить в r3
													 // r3 = r3 + 4
	ldr	r3, [r3]             // чтение из памяти в регистр r3 // ???
	mov	r0, r3               // r0 = r3
	bl	atoi                 // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, r0               // r3 = r0
	str	r3, [fp, #-24]       // Запись из регистра в память
	mov	r3, #0               // r3 = 0
	mov	r4, #0               // r4 = 0
	str	r3, [fp, #-20]       // Запись из регистра в память
	str	r4, [fp, #-16]       // Запись из регистра в память
	mov	r3, #0               // r3 = 0
	str	r3, [fp, #-28]       // Запись из регистра в память
	b	.L2                    // перейти к метке .L2
.L5:
	ldr	r3, [fp, #-28]       // чтение из памяти в регистр r3
	and	r3, r3, #1           // r3 = r3 & 1
	 												 // логическое И
	cmp	r3, #0               // Сравнение, вернее арифметическое вычитание без запоминания результата
													 // изменяются только флаги Rn – shifter_operand S bit always set
	bne	.L3                  // Если r3 != 0 перейти к .L3
	mov	r3, #1               // r3 = 1
	str	r3, [fp, #-32]       // Запись из регистра в память
	b	.L4                    // Безусловные переход к метке .L4
.L3:
	mvn	r3, #0               // Побитовое "НЕ"
	str	r3, [fp, #-32]       // Запись из регистра в память
.L4:
	ldr	r0, [fp, #-32]       // чтение из памяти в регистр r0
	bl	__aeabi_i2d          // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r4, r0               // r4 = r0
	mov	r5, r1               // r5 = r1
	ldr	r0, [fp, #-28]       // чтение из памяти в регистр r0
	bl	__aeabi_ui2f         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, r0               // r3 = r0
	mov	r0, r3               // r0 = r3 // ???
	bl	__aeabi_f2d          // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r2, r0               // r2 = r0
	mov	r3, r1               // r3 = r1
	bl	__aeabi_dadd         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r2, r0               // r2 = r0
	mov	r3, r1               // r3 = r1
	mov	r0, r2         	     // r0 = r2
	mov	r1, r3               // r1 = r3
	mov	r2, #0               // r2 = 0
	ldr	r3, .L7              // чтение из памяти в регистр r3
	bl	__aeabi_dadd         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r2, r0               // r2 = r0
	mov	r3, r1               // r3 = r1
 	mov	r0, r4               // r0 = r4
	mov	r1, r5               // r1 = r5
	bl	__aeabi_ddiv         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, r0               // r3 = r0
	mov	r4, r1               // r4 = r1
	mov	r2, r3               // r2 = r3
	mov	r3, r4               // r3 = r4
	sub	r1, fp, #20          // r1 = fp + 20
	ldmia	r1, {r0-r1}        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bl	__aeabi_dadd         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, r0               // r3 = r0
	mov	r4, r1               // r4 = r1
	str	r3, [fp, #-20]       // Запись из регистра в память
	str	r4, [fp, #-16]       // Запись из регистра в память
	ldr	r3, [fp, #-28]       // чтение из памяти в регистр r3
	add	r3, r3, #1           // r3 = r3 + 1
	str	r3, [fp, #-28]       // Запись из регистра в память
.L2:
	ldr	r2, [fp, #-28]       // чтение из памяти в регистр r2
 	ldr	r3, [fp, #-24]       // чтение из памяти в регистр r3
	cmp	r2, r3               // Сравнение, вернее арифметическое вычитание без запоминания результата
													 // изменяются только флаги Rn – shifter_operand S bit always set
	bls	.L5                  // если r2 <= r3 переход к метке .L5
	mov	r2, #0               // r2 = 0
	ldr	r3, .L7+4            // чтение из памяти в регистр r3
	sub	r1, fp, #20          // r1 = fp - 20
	ldmia	r1, {r0-r1}        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bl	__aeabi_dmul         // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, r0               // r3 = r0
	mov	r4, r1               // r4 = r1
	str	r3, [fp, #-20]       // Запись из регистра в память
	str	r4, [fp, #-16]       // Запись из регистра в память
	sub	r3, fp, #20          // r3 = fp - 20
	ldmia	r3, {r2-r3}        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ldr	r0, .L7+8            // чтение из памяти в регистр r3
	bl	printf               // переход с сохранением адреса возврата
													 // вызов подпрограммы
	mov	r3, #0               // r3 = 0
	mov	r0, r3               // r0 = r3
	sub	sp, fp, #12          // sp = fp - 12
	@ sp needed
	pop	{r4, r5, fp, pc}     // ??????????
.L8:
	.align	2
.L7:
	.word	1072693248
	.word	1074790400
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",%progbits
