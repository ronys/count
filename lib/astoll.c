/* @(#)astoll.c	1.1 00/12/03 Copyright 1985,2000 J. Schilling */
/*
 *	astoll() converts a string to long long
 *
 *	Leading tabs and spaces are ignored.
 *	Both return pointer to the first char that has not been used.
 *	Caller must check if this means a bad conversion.
 *
 *	leading "+" is ignored
 *	leading "0"  makes conversion octal (base 8)
 *	leading "0x" makes conversion hex   (base 16)
 *
 *	Llong is silently reverted to long if the compiler does not
 *	support long long.
 *
 *	Copyright (c) 1985,2000 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <mconfig.h>
#include <standard.h>
#include <utypes.h>
#include <schily.h>

#define is_space(c)	 ((c) == ' ' || (c) == '\t')
#define is_digit(c)	 ((c) >= '0' && (c) <= '9')
#define is_hex(c)	(((c) >= 'a' && (c) <= 'f') || \
			 ((c) >= 'A' && (c) <= 'F'))

#define to_lower(c)	(((c) >= 'A' && (c) <= 'Z') ? (c) - 'A'+'a' : (c))

char *astoll(s, l)
	register const char *s;
	Llong *l;
{
	int neg = 0;
	register Llong ret = (Llong)0;
	register int base = 10;
	register int digit;
	register char c;
	
	while (is_space(*s))
		s++;

	if (*s == '+') {
		s++;
	} else if (*s == '-') {
		s++;
		neg++;
	}

	if (*s == '0') {
		base = 8;
		s++;
		if (*s == 'x' || *s == 'X') {
			s++;
			base = 16;
		}
	}
	for (;(c = *s) != 0; s++) {

		if (is_digit(c)) {
			digit = c - '0';
		} else if (is_hex(c)) {
			digit = to_lower(c) - 'a' + 10;
		} else {
			break;
		}

		if (digit < base) {
			ret *= base;
			ret += digit;
		} else {
			break;
		}
	}
	if (neg)
		ret = -ret;
	*l = ret;
	return ((char *)s);
}
