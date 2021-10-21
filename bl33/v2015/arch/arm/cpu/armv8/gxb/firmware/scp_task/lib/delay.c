/*
* Copyright (C) 2017 Amlogic, Inc. All rights reserved.
* *
This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* *
This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
* *
You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* *
Description:
*/

#define P_EE_TIMER_E		(*((volatile unsigned *)(0xc1100000 + (0x2662 << 2))))

unsigned int get_time(void)
{
	return P_EE_TIMER_E;
}

void _udelay(unsigned int us)
{
	unsigned int t0 = get_time();

	while (get_time() - t0 <= us)
		;
}

