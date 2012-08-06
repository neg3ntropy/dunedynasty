/* mentat.c */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mentat.h"

#include "../file.h"
#include "../gfx.h"
#include "../gui/gui.h"
#include "../gui/mentat.h"
#include "../ini.h"
#include "../input/input.h"
#include "../shape.h"
#include "../string.h"
#include "../table/strings.h"
#include "../timer/timer.h"
#include "../video/video.h"
#include "../wsa.h"

static const struct {
	int eyesX, eyesY;
	int mouthX, mouthY;
	int shoulderX, shoulderY;
	int accessoryX, accessoryY;
} mentat_data[HOUSE_MAX] = {
	{ 0x20,0x58, 0x20,0x68, 0x80,0x68, 0x00,0x00 },
	{ 0x28,0x50, 0x28,0x60, 0x80,0x80, 0x48,0x98 },
	{ 0x10,0x50, 0x10,0x60, 0x80,0x80, 0x58,0x90 },
	{ 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00 },
	{ 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00 },
	{ 0x40,0x50, 0x38,0x60, 0x00,0x00, 0x00,0x00 },
};

static int movingEyesSprite;
static int movingMouthSprite;
static int otherSprite;

MentatState g_mentat_state;

void
Mentat_DrawBackground(enum HouseType houseID)
{
	const char *mentat_background[HOUSE_MAX] = {
		"MENTATH.CPS", "MENTATA.CPS", "MENTATO.CPS",
		"MENTATM.CPS", "MENTATM.CPS", "MENTATM.CPS"
	};
	assert(houseID < HOUSE_MAX);

	Video_DrawCPS(mentat_background[houseID]);
}

static void
Mentat_DrawEyes(enum HouseType houseID)
{
	const enum ShapeID shapeID = SHAPE_MENTAT_EYES + houseID * 15 + movingEyesSprite;

	Shape_Draw(shapeID, mentat_data[houseID].eyesX, mentat_data[houseID].eyesY, 0, 0);
}

static void
Mentat_DrawMouth(enum HouseType houseID)
{
	const enum ShapeID shapeID = SHAPE_MENTAT_MOUTH + houseID * 15 + movingMouthSprite;

	Shape_Draw(shapeID, mentat_data[houseID].mouthX, mentat_data[houseID].mouthY, 0, 0);
}

static void
Mentat_DrawShoulder(enum HouseType houseID)
{
	if (houseID <= HOUSE_ORDOS) {
		const enum ShapeID shapeID = SHAPE_MENTAT_SHOULDER + houseID * 15;

		Shape_Draw(shapeID, mentat_data[houseID].shoulderX, mentat_data[houseID].shoulderY, 0, 0);
	}
}

static void
Mentat_DrawAccessory(enum HouseType houseID)
{
	if (houseID == HOUSE_ATREIDES || houseID == HOUSE_ORDOS) {
		const enum ShapeID shapeID = SHAPE_MENTAT_ACCESSORY + houseID * 15 + abs(otherSprite);

		Shape_Draw(shapeID, mentat_data[houseID].accessoryX, mentat_data[houseID].accessoryY, 0, 0);
	}
}

void
Mentat_Draw(enum HouseType houseID)
{
	assert(houseID < HOUSE_MAX);

	Mentat_DrawEyes(houseID);
	Mentat_DrawMouth(houseID);
	Mentat_DrawShoulder(houseID);
	Mentat_DrawAccessory(houseID);
}

/*--------------------------------------------------------------*/

static void
MentatBriefing_SplitText(MentatState *mentat)
{
	GUI_DrawText_Wrapper(NULL, 0, 0, 0, 0, 0x32);

	mentat->lines0 = GUI_Mentat_SplitText(mentat->text, 304);
	mentat->lines = mentat->lines0;
}

void
MentatBriefing_InitText(enum HouseType houseID, int campaignID, enum BriefingEntry entry,
		MentatState *mentat)
{
	const int stringID
		= STR_HOUSE_HARKONNENFROM_THE_DARK_WORLD_OF_GIEDI_PRIME_THE_SAVAGE_HOUSE_HARKONNEN_HAS_SPREAD_ACROSS_THE_UNIVERSE_A_CRUEL_PEOPLE_THE_HARKONNEN_ARE_RUTHLESS_TOWARDS_BOTH_FRIEND_AND_FOE_IN_THEIR_FANATICAL_PURSUIT_OF_POWER
		+ (houseID * 40) + ((campaignID + 1) * 4) + entry;
	assert(entry <= MENTAT_BRIEFING_ADVICE);

	strncpy(mentat->buf, String_Get_ByIndex(stringID), sizeof(mentat->buf));
	mentat->desc = NULL;
	mentat->text = mentat->buf;
	MentatBriefing_SplitText(mentat);
}

void
MentatBriefing_DrawText(MentatState *mentat)
{
	if (mentat->desc) {
		const WidgetProperties *wi = &g_widgetProperties[WINDOWID_MENTAT_PICTURE];

		GUI_DrawText_Wrapper(mentat->desc, wi->xBase*8 + 5, wi->yBase + 3, g_curWidgetFGColourBlink, 0, 0x31);
	}

	if (mentat->lines > 0)
		GUI_DrawText_Wrapper(mentat->text, 4, 1, g_curWidgetFGColourBlink, 0, 0x32);
}

void
MentatBriefing_AdvanceText(MentatState *mentat)
{
	while (mentat->text[0] != '\0') {
		mentat->text++;
	}

	mentat->text++;
	mentat->lines--;

	if (mentat->lines <= 0) {
		mentat->state = MENTAT_IDLE;
	}
}

/*--------------------------------------------------------------*/

void
MentatBriefing_InitWSA(enum HouseType houseID, int scenarioID, enum BriefingEntry entry, MentatState *mentat)
{
	const char *key[3] = { "BriefPicture", "WinPicture", "LosePicture" };
	const char *def[3] = { "HARVEST.WSA", "WIN1.WSA", "LOSTBILD.WSA" };
	assert(entry <= MENTAT_BRIEFING_ADVICE);

	if (scenarioID <= 0) {
		const char *wsaFilename = House_GetWSAHouseFilename(houseID);

		mentat->wsa = WSA_LoadFile(wsaFilename, GFX_Screen_Get_ByIndex(5), GFX_Screen_GetSize_ByIndex(5), false);
	}
	else {
		char filename[16];
		snprintf(filename, sizeof(filename), "SCEN%c%03d.INI", g_table_houseInfo[houseID].name[0], scenarioID);

		char *buf = File_ReadWholeFile(filename);
		if (buf == NULL) {
			mentat->wsa = NULL;
			return;
		}

		char wsaFilename[16];
		Ini_GetString("BASIC", key[entry], def[entry], wsaFilename, sizeof(wsaFilename), buf);
		free(buf);

		mentat->wsa = WSA_LoadFile(wsaFilename, GFX_Screen_Get_ByIndex(5), GFX_Screen_GetSize_ByIndex(5), false);
	}

	mentat->wsa_timer = Timer_GetTicks();
	mentat->wsa_frame = 0;
}

void
MentatBriefing_DrawWSA(MentatState *mentat)
{
	if (mentat->wsa == NULL)
		return;

	const int64_t curr_ticks = Timer_GetTicks();
	const int frame = mentat->wsa_frame + (curr_ticks - mentat->wsa_timer) / 7;

	if (!Video_DrawWSA(mentat->wsa, frame, 0, 0, 128, 48, 184, 112)) {
		Video_DrawWSA(mentat->wsa, 0, 0, 0, 128, 48, 184, 112);
		mentat->wsa_timer = curr_ticks;
		mentat->wsa_frame = 0;
	}
}

/*--------------------------------------------------------------*/

static void
MentatHelp_Draw(enum HouseType houseID, MentatState *mentat)
{
	Mentat_DrawBackground(houseID);

	if (mentat->state == MENTAT_SHOW_CONTENTS) {
		GUI_Mentat_Draw(true);
	}
	else {
		MentatBriefing_DrawText(mentat);
	}

	if (mentat->state != MENTAT_SHOW_TEXT) {
		GUI_Widget_Draw(g_widgetMentatFirst);
	}

	Mentat_Draw(houseID);
}

bool
MentatHelp_Tick(enum HouseType houseID, MentatState *mentat)
{
	MentatHelp_Draw(houseID, mentat);

	if (mentat->state == MENTAT_SHOW_CONTENTS) {
		const int widgetID = GUI_Widget_HandleEvents(g_widgetMentatTail);

		if (widgetID == 0x8001) {
			return true;
		}
		else {
			GUI_Mentat_HelpListLoop(widgetID);

			if (mentat->state == MENTAT_SHOW_TEXT)
				MentatBriefing_SplitText(mentat);
		}
	}
	else if (mentat->state == MENTAT_SHOW_TEXT) {
		if (Input_IsInputAvailable()) {
			const int key = Input_GetNextKey();

			if (key == SCANCODE_ESCAPE || key == SCANCODE_SPACE || key == MOUSE_LMB || key == MOUSE_RMB)
				MentatBriefing_AdvanceText(mentat);
		}
	}
	else {
		const int widgetID = GUI_Widget_HandleEvents(g_widgetMentatFirst);

		if (widgetID == 0x8001) {
			mentat->state = MENTAT_SHOW_CONTENTS;
			GUI_Mentat_LoadHelpSubjects(false);
		}
	}

	return false;
}
