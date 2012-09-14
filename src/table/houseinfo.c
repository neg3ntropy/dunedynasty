/* $Id$ */

/** @file src/table/houseinfo.c HouseInfo file table. */

#include "sound.h"
#include "../house.h"

const HouseInfo g_table_houseInfo[] = {
	{ /* 0 */
		/* name                 */ "Harkonnen",
		/* toughness            */ 200,
		/* degradingChance      */ 85,
		/* degradingAmount      */ 3,
		/* minimapColor         */ 144,
		/* specialCountDown     */ 600,
		/* starportDeliveryTime */ 10,
		/* prefixChar           */ 'H',
		/* specialWeapon        */ HOUSE_WEAPON_MISSILE,
		/* musicWin             */ MUSIC_WIN_HARKONNEN,
		/* musicLose            */ MUSIC_LOSE_HARKONNEN,
		/* musicBriefing        */ MUSIC_BRIEFING_HARKONNEN,
		/* voiceFilename        */ "nhark.voc"
	},

	{ /* 1 */
		/* name                 */ "Atreides",
		/* toughness            */ 77,
		/* degradingChance      */ 0,
		/* degradingAmount      */ 1,
		/* minimapColor         */ 160,
		/* specialCountDown     */ 300,
		/* starportDeliveryTime */ 10,
		/* prefixChar           */ 'A',
		/* specialWeapon        */ HOUSE_WEAPON_FREMEN,
		/* musicWin             */ MUSIC_WIN_ATREIDES,
		/* musicLose            */ MUSIC_LOSE_ATREIDES,
		/* musicBriefing        */ MUSIC_BRIEFING_ATREIDES,
		/* voiceFilename        */ "nattr.voc"
	},

	{ /* 2 */
		/* name                 */ "Ordos",
		/* toughness            */ 128,
		/* degradingChance      */ 10,
		/* degradingAmount      */ 2,
		/* minimapColor         */ 176,
		/* specialCountDown     */ 300,
		/* starportDeliveryTime */ 10,
		/* prefixChar           */ 'O',
		/* specialWeapon        */ HOUSE_WEAPON_SABOTEUR,
		/* musicWin             */ MUSIC_WIN_ORDOS,
		/* musicLose            */ MUSIC_LOSE_ORDOS,
		/* musicBriefing        */ MUSIC_BRIEFING_ORDOS,
		/* voiceFilename        */ "nordo.voc"
	},

	{ /* 3 */
		/* name                 */ "Fremen",
		/* toughness            */ 10,
		/* degradingChance      */ 0,
		/* degradingAmount      */ 1,
		/* minimapColor         */ 192,
		/* specialCountDown     */ 300,
		/* starportDeliveryTime */ 0,
		/* prefixChar           */ 'O',
		/* specialWeapon        */ HOUSE_WEAPON_FREMEN,
		/* musicWin             */ MUSIC_WIN_ORDOS,
		/* musicLose            */ MUSIC_LOSE_ORDOS,
		/* musicBriefing        */ MUSIC_INVALID,
		/* voiceFilename        */ "afremen.voc"
	},

	{ /* 4 */
		/* name                 */ "Sardaukar",
		/* toughness            */ 10,
		/* degradingChance      */ 0,
		/* degradingAmount      */ 1,
		/* minimapColor         */ 208,
		/* specialCountDown     */ 600,
		/* starportDeliveryTime */ 0,
		/* prefixChar           */ 'H',
		/* specialWeapon        */ HOUSE_WEAPON_MISSILE,
		/* musicWin             */ MUSIC_WIN_HARKONNEN,
		/* musicLose            */ MUSIC_LOSE_HARKONNEN,
		/* musicBriefing        */ MUSIC_INVALID,
		/* voiceFilename        */ "asard.voc"
	},

	{ /* 5 */
		/* name                 */ "Mercenary",
		/* toughness            */ 0,
		/* degradingChance      */ 0,
		/* degradingAmount      */ 1,
		/* minimapColor         */ 224,
		/* specialCountDown     */ 300,
		/* starportDeliveryTime */ 0,
		/* prefixChar           */ 'M',
		/* specialWeapon        */ HOUSE_WEAPON_SABOTEUR,
		/* musicWin             */ MUSIC_WIN_ATREIDES,
		/* musicLose            */ MUSIC_LOSE_ATREIDES,
		/* musicBriefing        */ MUSIC_INVALID,
		/* voiceFilename        */ "amerc.voc"
	}
};
