/*
 * Copyright (C) 1995 by Pavel Antonov, Moscow, Russia.
 * Copyright (C) 1995 by Andrey A. Chernov, Moscow, Russia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Cirrus Logic CD180 -based RISCom/8 board definitions
 */

/* Oscillator frequency - 19660.08Mhz / 2 */
#define RC_OSCFREQ      9830400

#define RC_BRD(s) \
	((((RC_OSCFREQ + (s) / 2) / (s)) + CD180_CTICKS/2) / CD180_CTICKS)

#define RC_VALIDADDR(a) (   (a) == 0x220 || (a) == 0x240 || (a) == 0x250 \
			 || (a) == 0x260 || (a) == 0x2A0 || (a) == 0x2B0 \
			 || (a) == 0x300 || (a) == 0x320)

#define RC_VALIDIRQ(i)  ((i) < 16 && \
			 "\0\0\0\1\1\1\0\1\0\0\1\1\1\0\0\1"[(i) & 0xF])

/* Riscom/8 board I/O mapping */
#define RC_IOMAP(r)     ((((r) & 07) << 1) | (((r) & ~07) << 7))

/* I/O commands */
#define RC_OUT(p,i,d)           outb(RC_IOMAP(i) + (p), (d))
#define RC_IN(p,i)              inb (RC_IOMAP(i) + (p))

/* Riscom on-board registers (mapping assumed) */
#define RC_RI           0x100   /* Ring Indicator Register (read-only)  */
#define RC_DTR          0x100   /* DTR Register (write-only)            */
#define RC_BSR          0x101   /* Board Status Register (read-only)    */
#define RC_CTOUT        0x101   /* Clear Timeout (write-only)           */

/* Board Status Register */
#define RC_BSR_TOUT     0x08    /* Timeout                              */
#define RC_BSR_RXINT    0x04    /* Receiver Interrupt                   */
#define RC_BSR_TXINT    0x02    /* Transmitter Interrupt                */
#define RC_BSR_MOINT    0x01    /* Modem Control Interrupt              */

/* Interrupt groups */
#define RC_MODEMGRP     0x01    /* Modem interrupt group                */
#define RC_TXGRP        0x02    /* Transmitter interrupt group          */
#define RC_RXGRP        0x04    /* Receiver interrupt group             */

/* Priority Interrupt Level definitions */
#define RC_PILR_MODEM   (0x80 | RC_MODEMGRP)
#define RC_PILR_TX      (0x80 | RC_TXGRP   )
#define RC_PILR_RX      (0x80 | RC_RXGRP   )
