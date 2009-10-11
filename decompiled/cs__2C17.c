/* $Id$ */

#include "types.h"
#include "libemu.h"
#include "decompiled.h"

/**
 * Decompiled function f__2C17_000C_002F_3016()
 *
 * @name f__2C17_000C_002F_3016
 * @implements 2C17:000C:002F:3016 ()
 *
 * Called From: 0642:046C:0024:22E8
 * Called From: 07D4:1468:0025:2165
 * Called From: B4ED:049F:0024:9E14
 * Called From: B518:0F16:002D:1F4E
 */
void f__2C17_000C_002F_3016()
{
	emu_push(emu_bp);
	emu_movw(&emu_bp, emu_sp);
	emu_subw(&emu_sp, 0x1E8);
	emu_push(emu_si);
	emu_push(emu_di);
	emu_cmpw(&emu_get_memory16(emu_ss, emu_bp,  0x14), 0x0);
	if (!emu_flags.zf) { /* Unresolved jump */ emu_ip = 0x003E; emu_last_cs = 0x2C17; emu_last_ip = 0x0019; emu_last_length = 0x002F; emu_last_crc = 0x3016; emu_call(); return; }
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xC));
	emu_addw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x10));
	emu_push(emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xA));
	emu_addw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xE));
	emu_movb(&emu_cl, 0x3);
	emu_shlw(&emu_ax, emu_cl);
	emu_push(emu_ax);
	emu_push(emu_get_memory16(emu_ss, emu_bp,  0xC));
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xA));
	emu_shlw(&emu_ax, emu_cl);
	emu_push(emu_ax);
	emu_push(emu_cs); emu_push(0x003B); emu_cs = 0x2B6C; f__2B6C_0197_00CE_4D32();
	f__2C17_003B_000A_39F8(); return;
}

/**
 * Decompiled function f__2C17_003B_000A_39F8()
 *
 * @name f__2C17_003B_000A_39F8
 * @implements 2C17:003B:000A:39F8 ()
 *
 */
void f__2C17_003B_000A_39F8()
{
	emu_addw(&emu_sp, 0x8);
	emu_sarw(&emu_get_memory16(emu_ss, emu_bp,  0x10), 0x1);
	emu_xorw(&emu_si, emu_si);
	f__2C17_0052_000C_FA42(); return;
}

/**
 * Decompiled function f__2C17_0045_0019_D623()
 *
 * @name f__2C17_0045_0019_D623
 * @implements 2C17:0045:0019:D623 ()
 *
 * Called From: 2C17:0055:000C:FA42
 * Called From: 2C17:0055:0019:D623
 */
void f__2C17_0045_0019_D623()
{
	emu_movw(&emu_bx, emu_si);
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_si);
	emu_incw(&emu_si);
	f__2C17_0052_000C_FA42(); return;
}

/**
 * Decompiled function f__2C17_0052_000C_FA42()
 *
 * @name f__2C17_0052_000C_FA42
 * @implements 2C17:0052:000C:FA42 ()
 *
 * Called From: 2C17:0043:000A:39F8
 */
void f__2C17_0052_000C_FA42()
{
	emu_cmpw(&emu_si, emu_get_memory16(emu_ss, emu_bp,  0xE));
	if (emu_flags.cf) { f__2C17_0045_0019_D623(); return; }
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x2), 0x0);
	f__2C17_0072_000C_36DD(); return;
}

/**
 * Decompiled function f__2C17_005E_0020_A008()
 *
 * @name f__2C17_005E_0020_A008
 * @implements 2C17:005E:0020:A008 ()
 *
 * Called From: 2C17:0078:000C:36DD
 * Called From: 2C17:0078:0020:A008
 */
void f__2C17_005E_0020_A008()
{
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_ax);
	emu_incw(&emu_get_memory16(emu_ss, emu_bp, -0x2));
	f__2C17_0072_000C_36DD(); return;
}

/**
 * Decompiled function f__2C17_0072_000C_36DD()
 *
 * @name f__2C17_0072_000C_36DD
 * @implements 2C17:0072:000C:36DD ()
 *
 * Called From: 2C17:005C:0019:D623
 */
void f__2C17_0072_000C_36DD()
{
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_cmpw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x10));
	if (emu_flags.cf) { f__2C17_005E_0020_A008(); return; }
	emu_xorw(&emu_si, emu_si);
	f__2C17_00CA_000C_9B42(); return;
}

/**
 * Decompiled function f__2C17_007E_000D_EA91()
 *
 * @name f__2C17_007E_000D_EA91
 * @implements 2C17:007E:000D:EA91 ()
 *
 * Called From: 2C17:00CD:000C:9B42
 * Called From: 2C17:00CD:004B:6C03
 */
void f__2C17_007E_000D_EA91()
{
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xE));
	emu_decw(&emu_ax);
	emu_push(emu_ax);
	emu_xorw(&emu_ax, emu_ax);
	emu_push(emu_ax);
	emu_push(emu_cs); emu_push(0x008B); emu_cs = 0x2537; f__2537_000C_001C_86CB();
	f__2C17_008B_004B_6C03(); return;
}

/**
 * Decompiled function f__2C17_008B_004B_6C03()
 *
 * @name f__2C17_008B_004B_6C03
 * @implements 2C17:008B:004B:6C03 ()
 *
 */
void f__2C17_008B_004B_6C03()
{
	emu_addw(&emu_sp, 0x4);
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x4), emu_ax);
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x4));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x8), emu_ax);
	emu_movw(&emu_bx, emu_si);
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x4));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_dx, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_dx);
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_ax);
	emu_movw(&emu_bx, emu_si);
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x8));
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_ax);
	emu_incw(&emu_si);
	f__2C17_00CA_000C_9B42(); return;
}

/**
 * Decompiled function f__2C17_00CA_000C_9B42()
 *
 * @name f__2C17_00CA_000C_9B42
 * @implements 2C17:00CA:000C:9B42 ()
 *
 * Called From: 2C17:007C:0020:A008
 */
void f__2C17_00CA_000C_9B42()
{
	emu_cmpw(&emu_si, emu_get_memory16(emu_ss, emu_bp,  0xE));
	if (emu_flags.cf) { f__2C17_007E_000D_EA91(); return; }
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x2), 0x0);
	f__2C17_012A_000F_625A(); return;
}

/**
 * Decompiled function f__2C17_00D6_000D_2A92()
 *
 * @name f__2C17_00D6_000D_2A92
 * @implements 2C17:00D6:000D:2A92 ()
 *
 * Called From: 2C17:0130:000F:625A
 * Called From: 2C17:0130:0056:3346
 */
void f__2C17_00D6_000D_2A92()
{
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x10));
	emu_decw(&emu_ax);
	emu_push(emu_ax);
	emu_xorw(&emu_ax, emu_ax);
	emu_push(emu_ax);
	emu_push(emu_cs); emu_push(0x00E3); emu_cs = 0x2537; f__2537_000C_001C_86CB();
	f__2C17_00E3_0056_3346(); return;
}

/**
 * Decompiled function f__2C17_00E3_0056_3346()
 *
 * @name f__2C17_00E3_0056_3346
 * @implements 2C17:00E3:0056:3346 ()
 *
 */
void f__2C17_00E3_0056_3346()
{
	emu_addw(&emu_sp, 0x4);
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x6), emu_ax);
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x6));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x8), emu_ax);
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x6));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_dx, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_dx);
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_ax);
	emu_movw(&emu_bx, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x8));
	emu_movw(&emu_get_memory16(emu_ss, emu_bx, 0x0), emu_ax);
	emu_incw(&emu_get_memory16(emu_ss, emu_bp, -0x2));
	f__2C17_012A_000F_625A(); return;
}

/**
 * Decompiled function f__2C17_012A_000F_625A()
 *
 * @name f__2C17_012A_000F_625A
 * @implements 2C17:012A:000F:625A ()
 *
 * Called From: 2C17:00D4:004B:6C03
 */
void f__2C17_012A_000F_625A()
{
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_cmpw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x10));
	if (emu_flags.cf) { f__2C17_00D6_000D_2A92(); return; }
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x2), 0x0);
	f__2C17_01AA_0013_A00B(); return;
}

/**
 * Decompiled function f__2C17_0139_0007_211E()
 *
 * @name f__2C17_0139_0007_211E
 * @implements 2C17:0139:0007:211E ()
 *
 * Called From: 2C17:01B0:0013:A00B
 * Called From: 2C17:01B0:001F:31F4
 */
void f__2C17_0139_0007_211E()
{
	emu_movw(&emu_di, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_xorw(&emu_si, emu_si);
	f__2C17_01A2_001B_B085(); return;
}

/**
 * Decompiled function f__2C17_0140_005E_FAF1()
 *
 * @name f__2C17_0140_005E_FAF1
 * @implements 2C17:0140:005E:FAF1 ()
 *
 * Called From: 2C17:01A5:001B:B085
 * Called From: 2C17:01A5:001F:31F4
 */
void f__2C17_0140_005E_FAF1()
{
	emu_movw(&emu_bx, emu_si);
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x58);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x4), emu_ax);
	emu_movw(&emu_bx, emu_di);
	emu_shlw(&emu_bx, 0x1);
	emu_movw(&emu_ax, emu_bp - 0x1E8);
	emu_addw(&emu_bx, emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bx, 0x0));
	emu_movw(&emu_get_memory16(emu_ss, emu_bp, -0x6), emu_ax);
	emu_incw(&emu_di);
	emu_cmpw(&emu_di, emu_get_memory16(emu_ss, emu_bp,  0x10));
	if (!emu_flags.cf) {
		emu_xorw(&emu_di, emu_di);
	}
	f__2C17_0167_0037_421C(); return;
}

/**
 * Decompiled function f__2C17_0167_0037_421C()
 *
 * @name f__2C17_0167_0037_421C
 * @implements 2C17:0167:0037:421C ()
 *
 * Called From: 2C17:0163:005E:FAF1
 */
void f__2C17_0167_0037_421C()
{
	emu_push(emu_get_memory16(emu_ss, emu_bp,  0x14));
	emu_push(emu_get_memory16(emu_ss, emu_bp,  0x12));
	emu_movw(&emu_ax, 0x2);
	emu_push(emu_ax);
	emu_movw(&emu_ax, 0x1);
	emu_push(emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x6));
	emu_shlw(&emu_ax, 0x1);
	emu_movw(&emu_dx, emu_get_memory16(emu_ss, emu_bp,  0xC));
	emu_addw(&emu_dx, emu_ax);
	emu_push(emu_dx);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0xA));
	emu_addw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x4));
	emu_push(emu_ax);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x6));
	emu_shlw(&emu_ax, 0x1);
	emu_movw(&emu_dx, emu_get_memory16(emu_ss, emu_bp,  0x8));
	emu_addw(&emu_dx, emu_ax);
	emu_push(emu_dx);
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x6));
	emu_addw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x4));
	emu_push(emu_ax);
	emu_push(emu_cs); emu_push(0x019E); emu_cs = 0x24D0; f__24D0_000D_0039_C17D();
	f__2C17_019E_001F_31F4(); return;
}

/**
 * Decompiled function f__2C17_019E_001F_31F4()
 *
 * @name f__2C17_019E_001F_31F4
 * @implements 2C17:019E:001F:31F4 ()
 *
 */
void f__2C17_019E_001F_31F4()
{
	emu_addw(&emu_sp, 0x10);
	emu_incw(&emu_si);
	f__2C17_01A2_001B_B085(); return;
}

/**
 * Decompiled function f__2C17_01A2_001B_B085()
 *
 * @name f__2C17_01A2_001B_B085
 * @implements 2C17:01A2:001B:B085 ()
 *
 * Called From: 2C17:013E:0007:211E
 */
void f__2C17_01A2_001B_B085()
{
	emu_cmpw(&emu_si, emu_get_memory16(emu_ss, emu_bp,  0xE));
	if (emu_flags.cf) { f__2C17_0140_005E_FAF1(); return; }
	emu_incw(&emu_get_memory16(emu_ss, emu_bp, -0x2));
	f__2C17_01AA_0013_A00B(); return;
}

/**
 * Decompiled function f__2C17_01AA_0013_A00B()
 *
 * @name f__2C17_01AA_0013_A00B
 * @implements 2C17:01AA:0013:A00B ()
 *
 * Called From: 2C17:0137:0056:3346
 */
void f__2C17_01AA_0013_A00B()
{
	emu_movw(&emu_ax, emu_get_memory16(emu_ss, emu_bp, -0x2));
	emu_cmpw(&emu_ax, emu_get_memory16(emu_ss, emu_bp,  0x10));
	if (emu_flags.cf) { f__2C17_0139_0007_211E(); return; }
	emu_cmpw(&emu_get_memory16(emu_ss, emu_bp,  0x14), 0x0);
	if (emu_flags.zf) {
		emu_push(emu_cs); emu_push(0x01BD); emu_cs = 0x2B6C; f__2B6C_0292_0028_3AD7();
	}
	f__2C17_01BD_0006_F7CE(); return;
}

/**
 * Decompiled function f__2C17_01BD_0006_F7CE()
 *
 * @name f__2C17_01BD_0006_F7CE
 * @implements 2C17:01BD:0006:F7CE ()
 *
 */
void f__2C17_01BD_0006_F7CE()
{
	emu_pop(&emu_di);
	emu_pop(&emu_si);
	emu_movw(&emu_sp, emu_bp);
	emu_pop(&emu_bp);

	/* Return from this function */
	emu_pop(&emu_ip);
	emu_pop(&emu_cs);
	return;
}
