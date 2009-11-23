/* $Id$ */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "libemu.h"
#include "../global.h"
#include "../airunit.h"
#include "pool.h"
#include "airunit.h"

/**
 * Emulator wrapper around AirUnit_Init().
 *
 * @name emu_AirUnit_Init
 * @implements 104B:005D:001C:39F6 ()
 * @implements 104B:0079:0026:FD93
 * @implements 104B:0082:001D:CF58
 * @implements 104B:009F:000A:A59E
 * @implements 104B:00A9:0002:2597
 */
void emu_AirUnit_Init()
{
	csip32 address;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	address = emu_get_csip32(emu_ss, emu_sp, 0x0);

	AirUnit_Init(address);

	emu_dx = 0;
	emu_ax = sizeof(AirUnit) * AIRUNIT_INDEX_MAX;
}

/**
 * Emulator wrapper around AirUnit_Recount().
 *
 * @name emu_AirUnit_Recount
 * @implements 104B:0006:0011:631B ()
 * @implements 104B:0017:0046:2F85
 * @implements 104B:0052:000B:8782
 * @implements 104B:0053:000A:478A
 */
void emu_AirUnit_Recount()
{
	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	AirUnit_Recount();
}

/**
 * Emulator wrapper around AirUnit_Allocate().
 *
 * @name emu_AirUnit_Allocate
 * @implements 104B:0171:0020:7F19 ()
 * @implements 104B:0191:0009:538F
 * @implements 104B:019A:002D:CF3C
 * @implements 104B:01C7:0008:B398
 * @implements 104B:01C8:0007:F598
 * @implements 104B:01CD:0002:D5BA
 * @implements 104B:01FA:001A:49E1
 * @implements 104B:0214:0034:E1EC
 * @implements 104B:0248:0005:8BCF
 */
void emu_AirUnit_Allocate()
{
	uint16 index;
	AirUnit *a;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	emu_dx = 0x0;
	emu_ax = 0x0;

	index = emu_get_memory16(emu_ss, emu_sp,  0x0);

	a = AirUnit_Allocate(index);

	if (a == NULL) return;
	emu_dx = g_global->airUnitStartPos.s.cs;
	emu_ax = g_global->airUnitStartPos.s.ip + a->index * sizeof(AirUnit);
}

/**
 * Get a AirUnit from the memory by index.
 *
 * @name emu_AirUnit_Get_ByIndex
 * @implements 104B:0354:0023:5A6D ()
 * @implements 104B:0377
 * @implements 104B:037D:0002:2597
 */
void emu_AirUnit_Get_ByIndex()
{
	uint16 index;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	emu_ax = 0x0;
	emu_dx = 0x0;

	index = emu_get_memory16(emu_ss, emu_sp,  0x0);

	if (index >= AIRUNIT_INDEX_MAX) return;
	emu_dx = g_global->airUnitStartPos.s.cs;
	emu_ax = g_global->airUnitStartPos.s.ip + index * sizeof(AirUnit);
}

/**
 * Emulator wrapper around AirUnit_Find(). It also initializes the
 *  PoolFindStruct, and uses a default struct in case none is given.
 *
 * @name emu_AirUnit_FindFirst
 * @implements 104B:00C2:0030:20A6 ()
 * @implements 104B:00D5:001D:2B68
 * @implements 104B:00F2:0004:5B1F
 * @implements 104B:00F6:0002:2597
 */
void emu_AirUnit_FindFirst()
{
	PoolFindStruct *find;
	AirUnit *a;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	emu_dx = 0x0;
	emu_ax = 0x0;

	find = (PoolFindStruct *)&emu_get_memory8(emu_get_memory16(emu_ss, emu_sp,  0x2), emu_get_memory16(emu_ss, emu_sp,  0x0), 0x0);
	if (emu_get_memory16(emu_ss, emu_sp,  0x2) == 0x0 && emu_get_memory16(emu_ss, emu_sp,  0x0) == 0x0) {
		emu_get_memory16(emu_ss, emu_sp,  0x2) = 0x353F;
		emu_get_memory16(emu_ss, emu_sp,  0x0) = emu_Global_GetIP(g_global->airUnitFindStruct, 0x353F);
		find = (PoolFindStruct *)g_global->airUnitFindStruct;
	}

	find->houseID = emu_get_memory16(emu_ss, emu_sp,  0x4);
	find->type    = 0xFFFF;
	find->index   = 0xFFFF;

	a = AirUnit_Find(find);

	if (a == NULL) return;
	emu_dx = g_global->airUnitStartPos.s.cs;
	emu_ax = g_global->airUnitStartPos.s.ip + a->index * sizeof(AirUnit);
}

/**
 * Emulator wrapper around AirUnit_Find(). It uses a default struct in case
 *  none is given.
 *
 * @name emu_AirUnit_FindNext
 * @implements 104B:00F8:002E:3820 ()
 * @implements 104B:0110:0016:6D19
 * @implements 104B:0124
 * @implements 104B:0126:0031:81E0
 * @implements 104B:0148:000F:4483
 * @implements 104B:0155:0002:CA3A
 * @implements 104B:0157
 * @implements 104B:0158:0013:49FB
 * @implements 104B:016B:0006:F7CE
 */
void emu_AirUnit_FindNext()
{
	PoolFindStruct *find;
	AirUnit *a;

	/* Pop the return CS:IP. */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);

	emu_dx = 0x0;
	emu_ax = 0x0;

	find = (PoolFindStruct *)&emu_get_memory8(emu_get_memory16(emu_ss, emu_sp,  0x2), emu_get_memory16(emu_ss, emu_sp,  0x0), 0x0);
	if (emu_get_memory16(emu_ss, emu_sp,  0x2) == 0x0 && emu_get_memory16(emu_ss, emu_sp,  0x0) == 0x0) {
		emu_get_memory16(emu_ss, emu_sp,  0x2) = 0x353F;
		emu_get_memory16(emu_ss, emu_sp,  0x0) = emu_Global_GetIP(g_global->airUnitFindStruct, 0x353F);
		find = (PoolFindStruct *)g_global->airUnitFindStruct;
	}

	a = AirUnit_Find(find);

	if (a == NULL) return;
	emu_dx = g_global->airUnitStartPos.s.cs;
	emu_ax = g_global->airUnitStartPos.s.ip + a->index * sizeof(AirUnit);
}
