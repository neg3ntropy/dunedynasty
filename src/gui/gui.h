/** @file src/gui/gui.h Generic GUI definitions. */

#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "enumeration.h"
#include "types.h"
#include "../gfx.h"

/**
 * The possible selection types.
 */
enum SelectionType {
	SELECTIONTYPE_MENTAT    = 0,                            /*!< Used in most mentat screens. */
	SELECTIONTYPE_TARGET    = 1,                            /*!< Used when attacking or moving a unit, the target screen. */
	SELECTIONTYPE_PLACE     = 2,                            /*!< Used when placing a structure. */
	SELECTIONTYPE_UNIT      = 3,                            /*!< Used when selecting a Unit. */
	SELECTIONTYPE_STRUCTURE = 4,                            /*!< Used when selecting a Structure or nothing. */
	SELECTIONTYPE_DEBUG     = 5,                            /*!< Used when debugging scenario. */
	SELECTIONTYPE_UNKNOWN6  = 6,                            /*!< ?? */
	SELECTIONTYPE_INTRO     = 7,                            /*!< Used in intro of the game. */

	SELECTIONTYPE_MAX       = 8
};

/**
 * Hall Of Fame data struct.
 */
typedef struct HallOfFameStruct {
	char name[6];                                           /*!< Name of the entry. */
	uint16 score;                                           /*!< Score of the entry. */
	uint16 rank;                                            /*!< Rank of the entry. */
	uint16 campaignID;                                      /*!< Which campaign was reached. */
	uint8  houseID;                                         /*!< Which house was playing. */

#if 0
	uint8  padding1;                                        /*!< Padding bytes. */
	uint16 padding2;                                        /*!< Padding bytes. */
#else
	/* Dune Dynasty: extra padding bytes used to extend name. */
	char name_extended[3];
#endif
} HallOfFameStruct;
assert_compile(sizeof(HallOfFameStruct) == 16);

/**
 * Information for the selection type.
 */
typedef struct SelectionTypeStruct {
	 int8  visibleWidgets[20];                              /*!< List of index of visible widgets, -1 terminated. */
#if 0
	bool   variable_04;                                     /*!< ?? */
	bool   variable_06;                                     /*!< ?? */
#endif
	uint16 defaultWidget;                                   /*!< Index of the default Widget. */
} SelectionTypeStruct;

struct Widget;

extern const SelectionTypeStruct g_table_selectionType[SELECTIONTYPE_MAX];

extern uint8 g_palette_998A[3 * 256];
extern uint8 g_remap[256];
extern uint16 g_productionStringID;

extern uint16 g_viewportMessageCounter;
extern const char *g_viewportMessageText;
extern uint16 g_viewportPosition;
extern int g_viewport_scrollOffsetX;
extern int g_viewport_scrollOffsetY;
extern float g_viewport_desiredDX;
extern float g_viewport_desiredDY;

extern uint16 g_selectionRectanglePosition;
extern uint16 g_selectionPosition;
extern uint16 g_selectionWidth;
extern uint16 g_selectionHeight;
extern int16  g_selectionState;

extern uint16 g_cursorSpriteID;

extern bool g_structureHighHealth;

extern void GUI_ClearScreen(Screen screenID);
extern void GUI_DrawScreen(Screen screenID);
extern void GUI_DrawSprite_(Screen memory, uint8 *sprite, int16 posX, int16 posY, uint16 windowID, uint16 flags, ...);
extern void GUI_DrawInterfaceAndRadar(void);
extern void GUI_Palette_RemapScreen(uint16 left, uint16 top, uint16 width, uint16 height, Screen screenID, uint8 *remap);
extern void GUI_Screen_Copy(int16 xSrc, int16 ySrc, int16 xDst, int16 yDst, int16 width, int16 height, Screen screenSrc, Screen screenDst);

extern void GUI_DrawCredits(int credits, uint16 mode, int x);

extern void GUI_Palette_CreateMapping(uint8 *palette, uint8 *colors, uint8 reference, uint8 intensity);
extern void GUI_Palette_CreateRemap(uint8 houseID);
extern void GUI_Palette_CreateRemapDeviatorGas(uint8 houseID);
extern void GUI_PaletteAnimate(void);

extern void GUI_DrawChar_(unsigned char c, int x, int y);
extern void GUI_DisplayText(const char *str, int16 importance, ...);
extern void GUI_DrawStatusBarText(int x, int y);
extern void GUI_DrawStatusBarTextWrapper(uint8 priority, uint16 str1, uint16 str2, uint16 str3);
extern void GUI_DrawText(const char *string, int16 left, int16 top, uint8 fgColour, uint8 bgColour);
extern void GUI_DrawTextAlpha(const char *string, int x, int y, unsigned char alpha);
extern void GUI_DrawText_Wrapper(const char *string, int16 left, int16 top, uint8 fgColour, uint8 bgColour, uint16 flags, ...);
extern void GUI_DrawTextOnFilledRectangle(const char *string, uint16 top);

extern void GUI_UpdateProductionStringID(void);
extern uint16 GUI_SplitText(char *str, uint16 maxwidth, char delimiter);
extern void GUI_ChangeSelectionType(uint16 selectionType);
extern void GUI_InitColors(const uint8 *colors, uint8 first, uint8 last);
extern const char *GUI_String_Get_ByIndex(int16 stringID);
extern uint16 Update_Score(int16 score, uint16 *harvestedAllied, uint16 *harvestedEnemy, uint8 houseID);
extern void GUI_HallOfFame_SetColourScheme(bool enter);
extern void GUI_HallOfFame_Show(enum HouseType houseID, uint16 score);
extern uint16 GUI_HallOfFame_DrawData(HallOfFameStruct *data, bool show);

#endif /* GUI_GUI_H */
