/* $Id$ */

#include "types.h"
#include "libemu.h"
#include "decompiled.h"

/**
 * Overlay Handler for 0x3536
 *
 * @param entry The entry point of the overlay table.
 *
 * @name ovl__3536
 * @implements 3536:002F (3)
 * @implements 3536:0039 (5)
 *
 * Called From: 261F:01B9:001B:EDBF
 * Called From: 261F:01B9:001B:EDBF
 * Called From: B4B8:175F:0042:5923
 * Called From: B53B:0191:0016:AA3C
 * Called From: B53B:01C4:0024:3A58
 */
void ovl__3536(uint8 entry)
{
	if (emu_get_memory8(0x3536, 0, 0x20) == 0xCD || entry == 0xFF) {
		/* The overlay is not yet loaded. Do so by calling int 3F */
		uint16 ent_ip = (entry == 0xFF) ? 0x02 : (entry * 5) + 0x22;
		emu_pushf(); emu_flags.inf = 0; emu_push(emu_cs); emu_cs = 0x261F; emu_push(ent_ip); f__261F_0008_0033_66ED();
	}
	if (entry == 0xFF) return;

	/* Call the overlay function with the current cs it is loaded at */
	emu_cs = emu_get_memory16(0x3536, 0, (entry * 5) + 0x23);
	switch (entry) {
		case 3: f__B536_0129_000A_8178(); return;
		case 5: f__B536_0148_0060_01F3(); return;
	}
}
