#ifndef ENUMERATION_H
#define ENUMERATION_H

#include "enum_house.h"
#include "enum_structure.h"
#include "enum_unit.h"

enum Brain {
	BRAIN_NONE,
	BRAIN_HUMAN,
	BRAIN_CPU_ENEMY,
	BRAIN_CPU_ALLY,
};

enum TileUnveilCause {
	UNVEILCAUSE_UNCHANGED,

	/* Short reveal. */
	UNVEILCAUSE_EXPLOSION,

	/* Long reveals. */
	UNVEILCAUSE_STRUCTURE_PLACED,
	UNVEILCAUSE_STRUCTURE_SCRIPT,
	UNVEILCAUSE_UNIT_UPDATE,
	UNVEILCAUSE_UNIT_SCRIPT,
	UNVEILCAUSE_BULLET_FIRED,

	/* Client side. */
	UNVEILCAUSE_STRUCTURE_VISION,
	UNVEILCAUSE_UNIT_VISION,
	UNVEILCAUSE_INITIALISATION,
	UNVEILCAUSE_SHORT,
	UNVEILCAUSE_LONG,
};

enum MentatID {
	MENTAT_RADNOR,
	MENTAT_CYRIL,
	MENTAT_AMMON,
	MENTAT_BENE_GESSERIT,
	MENTAT_CUSTOM,
	MENTAT_MAX
};

#endif
