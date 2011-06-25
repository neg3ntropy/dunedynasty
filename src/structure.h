/* $Id$ */

/** @file src/structure.h %Structure handling definitions. */

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "object.h"

/**
 * Types of Structures available in the game.
 */
typedef enum StructureType {
	STRUCTURE_SLAB_1x1          = 0,
	STRUCTURE_SLAB_2x2          = 1,
	STRUCTURE_PALACE            = 2,
	STRUCTURE_LIGHT_VEHICLE     = 3,
	STRUCTURE_HEAVY_VEHICLE     = 4,
	STRUCTURE_HIGH_TECH         = 5,
	STRUCTURE_HOUSE_OF_IX       = 6,
	STRUCTURE_WOR_TROOPER       = 7,
	STRUCTURE_CONSTRUCTION_YARD = 8,
	STRUCTURE_WINDTRAP          = 9,
	STRUCTURE_BARRACKS          = 10,
	STRUCTURE_STARPORT          = 11,
	STRUCTURE_REFINERY          = 12,
	STRUCTURE_REPAIR            = 13,
	STRUCTURE_WALL              = 14,
	STRUCTURE_TURRET            = 15,
	STRUCTURE_ROCKET_TURRET     = 16,
	STRUCTURE_SILO              = 17,
	STRUCTURE_OUTPOST           = 18,

	STRUCTURE_MAX               = 19,
	STRUCTURE_INVALID           = 0xFF
} StructureType;

/**
 * A Structure as stored in the memory.
 */
typedef struct Structure {
	Object o;                                               /*!< Common to Unit and Structures. */
	uint16 variable_47;                                     /*!< ?? The 16bit version of HouseID? */
	uint16 variable_49;                                     /*!< ?? */
	uint8  variable_4B;                                     /*!< ?? */
	uint16 objectType;                                      /*!< Type of Unit/Structure we are building. */
	uint8  upgradeLevel;                                    /*!< The current level of upgrade of the Structure. */
	uint8  upgradeTimeLeft;                                 /*!< Time left before upgrade is complete, or 0 if no upgrade available. */
	uint16 countDown;                                       /*!< General countdown for various of functions. */
	uint16 variable_52;                                     /*!< ?? Used as 'overflow' value for building stuff. */
	 int16 animation;                                       /*!< The animation frame. -1 is the 'just built', 0 is 'normal', .. */
	uint16 hitpointsMax;                                    /*!< Max amount of hitpoints. */
}  Structure;

/**
 * Static information per Structure type.
 */
typedef struct StructureInfo {
	ObjectInfo o;                                           /*!< Common to UnitInfo and StructureInfo. */
	uint32 enterFilter;                                     /*!< Bitfield determining which unit is allowed to enter the structure. If bit n is set, then units of type n may enter */
	uint16 creditsStorage;                                  /*!< How many credits this Structure can store. */
	 int16 powerUsage;                                      /*!< How much power this Structure uses (positive value) or produces (negative value). */
	uint16 layout;                                          /*!< Layout type of Structure. */
	uint16 iconGroup;                                       /*!< In which IconGroup the sprites of the Structure belongs. */
	csip32 animationProc[3];                                /*!< The procs to the Animation of the Structure. */
	uint16 buildableUnits[8];                               /*!< Which units this structure can produce. */
	uint16 upgradeCampaign[3];                              /*!< Minimum campaign for upgrades. */
} StructureInfo;

struct House;
struct Widget;

extern StructureInfo g_table_structureInfo[];

extern Structure *g_structureActive;

extern void GameLoop_Structure();
extern uint8 Structure_StringToType(const char *name);
extern Structure *Structure_Create(uint16 index, uint8 typeID, uint8 houseID, uint16 position);
extern bool Structure_Place(Structure *s, uint16 position);
extern void Structure_CalculateHitpointsMax(struct House *h);
extern void Structure_SetAnimation(Structure *s, int16 animation);
extern Structure *Structure_Get_ByPackedTile(uint16 packed);
extern uint32 Structure_GetStructuresBuilt(struct House *h);
extern int16 Structure_IsValidBuildLocation(uint16 position, StructureType type);
extern bool Structure_Save(FILE *fp);
extern bool Structure_Load(FILE *fp, uint32 length);
extern void Structure_ActivateSpecial(Structure *s);
extern void Structure_RemoveFog(Structure *s);
extern bool Structure_Damage(Structure *s, uint16 damage, uint16 range);
extern bool Structure_IsUpgradable(Structure *s);
extern bool Structure_ConnectWall(uint16 position, bool recurse);
extern struct Unit *Structure_GetLinkedUnit(Structure *s);
extern void Structure_UntargetMe(Structure *s);
extern uint16 Structure_FindFreePosition(Structure *s, bool checkForSpice);
extern void Structure_0C3A_1002(Structure *s);
extern bool Structure_BuildObject(Structure *s, uint16 objectType);
extern bool Structure_SetUpgradingState(Structure *s, int8 value, struct Widget *w);
extern bool Structure_SetRepairingState(Structure *s, int8 value, struct Widget *w);
extern void Structure_UpdateMap(Structure *s);
extern uint32 Structure_GetBuildable(Structure *s);
extern void Structure_HouseUnderAttack(uint8 houseID);
extern uint16 Structure_AI_PickNextToBuild(Structure *s);

#endif /* STRUCTURE_H */
