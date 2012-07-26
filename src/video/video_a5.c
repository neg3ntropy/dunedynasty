/* video_a5.c */

#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../os/math.h"

#include "video_a5.h"

#include "../common_a5.h"
#include "../file.h"
#include "../gfx.h"
#include "../gui/gui.h"
#include "../gui/widget.h"
#include "../input/input_a5.h"
#include "../sprites.h"

#define OUTPUT_TEXTURES     false
#define ICONID_MAX          512

static ALLEGRO_DISPLAY *display;
static ALLEGRO_DISPLAY *display2;
static ALLEGRO_BITMAP *screen;
static ALLEGRO_COLOR paltoRGB[256];
static unsigned char paletteRGB[3 * 256];

static ALLEGRO_BITMAP *icon_texture;
static ALLEGRO_BITMAP *shape_texture;
static ALLEGRO_BITMAP *s_icon[ICONID_MAX][HOUSE_MAX];

bool
VideoA5_Init(void)
{
	const int w = g_widgetProperties[WINDOWID_RENDER_TEXTURE].width*8;
	const int h = g_widgetProperties[WINDOWID_RENDER_TEXTURE].height;

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	display2 = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (display == NULL || display2 == NULL)
		return false;

	screen = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	icon_texture = al_create_bitmap(w, h);
	shape_texture = al_create_bitmap(w, h);
	if (screen == NULL || icon_texture == NULL || shape_texture == NULL)
		return false;

	al_register_event_source(g_a5_input_queue, al_get_display_event_source(display));
	al_hide_mouse_cursor(display);

	al_init_image_addon();

	return true;
}

void
VideoA5_Uninit(void)
{
	for (enum HouseType houseID = HOUSE_HARKONNEN; houseID < HOUSE_MAX; houseID++) {
		for (uint16 iconID = 0; iconID < ICONID_MAX; iconID++) {
			if (s_icon[iconID][houseID] != NULL) {
				/* Don't destroy in the case of shared sub-bitmaps. */
				if ((houseID + 1 == HOUSE_MAX) || (s_icon[iconID][houseID] != s_icon[iconID][houseID + 1]))
					al_destroy_bitmap(s_icon[iconID][houseID]);

				s_icon[iconID][houseID] = NULL;
			}
		}
	}

	al_destroy_bitmap(icon_texture);
	icon_texture = NULL;

	al_destroy_bitmap(shape_texture);
	shape_texture = NULL;

	al_destroy_bitmap(screen);
	screen = NULL;
}

static void
VideoA5_CopyBitmap(const unsigned char *raw, ALLEGRO_BITMAP *dest, bool writeonly)
{
	const int w = al_get_bitmap_width(dest);
	const int h = al_get_bitmap_height(dest);

	ALLEGRO_LOCKED_REGION *reg;

	if (writeonly) {
		reg = al_lock_bitmap(dest, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_WRITEONLY);
	}
	else {
		reg = al_lock_bitmap(dest, ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE, ALLEGRO_LOCK_READWRITE);
	}

	for (int y = 0; y < h; y++) {
		unsigned char *row = &((unsigned char *)reg->data)[reg->pitch*y];

		for (int x = 0; x < w; x++) {
			const unsigned char c = raw[w*y + x];

			if (c == 0) {
				if (writeonly) {
					row[reg->pixel_size*x + 0] = 0x00;
					row[reg->pixel_size*x + 1] = 0x00;
					row[reg->pixel_size*x + 2] = 0x00;
					row[reg->pixel_size*x + 3] = 0x00;
				}
			}
			else {
				row[reg->pixel_size*x + 0] = paletteRGB[3*c + 0];
				row[reg->pixel_size*x + 1] = paletteRGB[3*c + 1];
				row[reg->pixel_size*x + 2] = paletteRGB[3*c + 2];
				row[reg->pixel_size*x + 3] = 0xFF;
			}
		}
	}

	al_unlock_bitmap(dest);
}

void
VideoA5_Tick(void)
{
	const unsigned char *raw = GFX_Screen_Get_ByIndex(0);

	al_set_target_backbuffer(display2);
	VideoA5_CopyBitmap(raw, screen, false);
	al_draw_bitmap(screen, 0, 0, 0);
	al_flip_display();

	InputA5_Tick();

	al_set_target_backbuffer(display);
	al_flip_display();
}

void
VideoA5_SetPalette(const uint8 *palette, int from, int length)
{
	const uint8 *p = palette;
	assert(from + length <= 256);

	for (int i = from; i < from + length; i++) {
		const uint8 r = ((*p++) & 0x3F) * 4;
		const uint8 g = ((*p++) & 0x3F) * 4;
		const uint8 b = ((*p++) & 0x3F) * 4;

		paltoRGB[i] = al_map_rgb(r, g, b);
		paletteRGB[3*i + 0] = r;
		paletteRGB[3*i + 1] = g;
		paletteRGB[3*i + 2] = b;
	}
}

/*--------------------------------------------------------------*/

static int
VideoA5_NumIconsInGroup(enum IconMapEntries group)
{
	if (!(0 < group && group < ICM_ICONGROUP_EOF))
		return 0;

	/* group == ICM_ICONGROUP_RADAR_OUTPOST. */
	if (group + 1 == ICM_ICONGROUP_EOF) {
		return 24;
	}
	else {
		return g_iconMap[group + 1] - g_iconMap[group];
	}
}

static void
VideoA5_ExportIconGroup(enum IconMapEntries group, int num_common,
		int x, int y, int *retx, int *rety)
{
	const int WINDOW_W = g_widgetProperties[WINDOWID_RENDER_TEXTURE].width*8;
	const int WINDOW_H = g_widgetProperties[WINDOWID_RENDER_TEXTURE].height;
	const int num = VideoA5_NumIconsInGroup(group);

	if (num_common < 0)
		num_common = num;

	for (enum HouseType houseID = HOUSE_HARKONNEN; houseID < HOUSE_MAX; houseID++) {
		GUI_Palette_CreateRemap(houseID);

		for (int idx = 0; idx < num; idx++) {
			const uint16 iconID = g_iconMap[g_iconMap[group] + idx];
			assert(iconID < ICONID_MAX);

			if (s_icon[iconID][houseID] != NULL)
				continue;

			if ((idx >= num_common) || (houseID == HOUSE_HARKONNEN)) {
				if (x + TILE_SIZE - 1 >= WINDOW_W) {
					x = 0;
					y += TILE_SIZE + 1;

					if (y + TILE_SIZE - 1 >= WINDOW_H)
						exit(1);
				}

				GFX_DrawSprite_(iconID, x, y, houseID);

				s_icon[iconID][houseID] = al_create_sub_bitmap(icon_texture, x, y, TILE_SIZE, TILE_SIZE);
				assert(s_icon[iconID][houseID] != NULL);

				x += TILE_SIZE + 1;
			}
			else {
				s_icon[iconID][houseID] = s_icon[iconID][HOUSE_HARKONNEN];
			}
		}
	}

	*retx = x;
	*rety = y;
}

static void
VideoA5_InitIcons(unsigned char *buf)
{
	const struct {
		int num_common;
		enum IconMapEntries group;
	} icon_data[] = {
		{ -1, ICM_ICONGROUP_ROCK_CRATERS },
		{ -1, ICM_ICONGROUP_SAND_CRATERS },
		{ -1, ICM_ICONGROUP_FLY_MACHINES_CRASH },
		{ -1, ICM_ICONGROUP_SAND_TRACKS },
		{ -1, ICM_ICONGROUP_WALLS },
		{ -1, ICM_ICONGROUP_FOG_OF_WAR },
		{ -1, ICM_ICONGROUP_CONCRETE_SLAB },
		{ -1, ICM_ICONGROUP_LANDSCAPE },
		{ -1, ICM_ICONGROUP_SPICE_BLOOM },
		{ -1, ICM_ICONGROUP_BASE_DEFENSE_TURRET },
		{ -1, ICM_ICONGROUP_BASE_ROCKET_TURRET },

		{  0, ICM_ICONGROUP_SAND_DEAD_BODIES },
		{ 18, ICM_ICONGROUP_HOUSE_PALACE },
		{  8, ICM_ICONGROUP_LIGHT_VEHICLE_FACTORY },
		{ 12, ICM_ICONGROUP_HEAVY_VEHICLE_FACTORY },
		{ 12, ICM_ICONGROUP_HI_TECH_FACTORY },
		{  8, ICM_ICONGROUP_IX_RESEARCH },
		{  8, ICM_ICONGROUP_WOR_TROOPER_FACILITY },
		{  8, ICM_ICONGROUP_CONSTRUCTION_YARD },
		{  8, ICM_ICONGROUP_INFANTRY_BARRACKS },
		{  8, ICM_ICONGROUP_WINDTRAP_POWER },
		{ 18, ICM_ICONGROUP_STARPORT_FACILITY },
		{ 12, ICM_ICONGROUP_SPICE_REFINERY },
		{ 12, ICM_ICONGROUP_VEHICLE_REPAIR_CENTRE },
		{  8, ICM_ICONGROUP_SPICE_STORAGE_SILO },
		{  8, ICM_ICONGROUP_RADAR_OUTPOST },

		{  0, ICM_ICONGROUP_EOF }
	};

	int x = 0, y = 0;

	al_set_target_bitmap(icon_texture);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));

	for (int i = 0; icon_data[i].group < ICM_ICONGROUP_EOF; i++) {
		VideoA5_ExportIconGroup(icon_data[i].group, icon_data[i].num_common,
				x, y, &x, &y);
	}

	VideoA5_CopyBitmap(buf, icon_texture, true);

#if OUTPUT_TEXTURES
	al_save_bitmap("icons.png", icon_texture);
#endif
}

void
VideoA5_DrawIcon(uint16 iconID, enum HouseType houseID, int x, int y)
{
	assert(iconID < ICONID_MAX);
	assert(houseID < HOUSE_MAX);
	assert(s_icon[iconID][houseID] != NULL);

	al_draw_bitmap(s_icon[iconID][houseID], x, y, 0);
}

/*--------------------------------------------------------------*/

static void
VideoA5_ExportShape(uint16 shapeID, int x, int y, int row_h,
		int *retx, int *rety, int *ret_row_h)
{
	const int WINDOW_W = g_widgetProperties[WINDOWID_RENDER_TEXTURE].width*8;
	const int WINDOW_H = g_widgetProperties[WINDOWID_RENDER_TEXTURE].height;
	uint8 *const shape = g_sprites[shapeID];
	const int w = Sprite_GetWidth(shape);
	const int h = Sprite_GetHeight(shape);

	if (x + w - 1 >= WINDOW_W) {
		x = 0;
		y += row_h + 1;
		row_h = 0;

		if (y + h - 1 >= WINDOW_H)
			exit(1);
	}

	GUI_DrawSprite(0, shape, x, y, WINDOWID_RENDER_TEXTURE, 0x100, g_remap, 1);

	*retx = x + w + 1;
	*rety = y;
	*ret_row_h = max(row_h, h);
}

static void
VideoA5_InitShapes(unsigned char *buf)
{
	/* Check Sprites_Init. */
	const struct {
		int start, end;
		bool remap;
	} shape_data[] = {
		{   0,   6, false }, /* MOUSE.SHP */
		{  12, 110, false }, /* SHAPES.SHP */
		{   7,  11,  true }, /* BTTN */
		{ 355, 372,  true }, /* CHOAM */
		{ 111, 150,  true }, /* UNITS2.SHP */
		{ 151, 161, false }, /* UNITS1.SHP */
		{ 162, 167,  true }, /* UNITS1.SHP: tanks */
		{ 168, 237, false }, /* UNITS1.SHP */
		{ 238, 354,  true }, /* UNITS.SHP */
		{ 373, 386, false }, /* MENTAT */
		{ 387, 401, false }, /* MENSHPH.SHP */
		{ 402, 416, false }, /* MENSHPA.SHP */
		{ 417, 431, false }, /* MENSHPO.SHP */
		/*477, 504,  true */ /* PIECES.SHP */
		/*505, 513, false */ /* ARROWS.SHP */
		/*514, 524, false */ /* CREDIT1.SHP .. CREDIT11.SHP */

		/* BENE.PAL shapes. */
		{  -2,   0, false },
		/*432, 461, false */ /* MENSHPM.SHP: Fremen, Sardaukar */
		{ 462, 476, false }, /* MENSHPM.SHP */

		{  -1,   0, false }
	};

	const int WINDOW_W = g_widgetProperties[WINDOWID_RENDER_TEXTURE].width*8;
	const int WINDOW_H = g_widgetProperties[WINDOWID_RENDER_TEXTURE].height;

	int x = 0, y = 0, row_h = 0;

	al_set_target_bitmap(shape_texture);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));

	for (int group = 0; shape_data[group].start != -1; group++) {
		if (shape_data[group].start == -2) {
			VideoA5_CopyBitmap(buf, shape_texture, true);
			memset(buf, 0, WINDOW_W * WINDOW_H);

			File_ReadBlockFile("BENE.PAL", paletteRGB, 3 * 256);
			VideoA5_SetPalette(paletteRGB, 0, 256);
			continue;
		}

		for (enum HouseType house = HOUSE_HARKONNEN; house < HOUSE_MAX; house++) {
			GUI_Palette_CreateRemap(house);

			for (int shapeID = shape_data[group].start; shapeID <= shape_data[group].end; shapeID++) {
				if ((shape_data[group].remap) || (house == HOUSE_HARKONNEN)) {
					VideoA5_ExportShape(shapeID, x, y, row_h, &x, &y, &row_h);
				}
			}
		}
	}

	VideoA5_CopyBitmap(buf, shape_texture, false);

#if OUTPUT_TEXTURES
	al_save_bitmap("shapes.png", shape_texture);
#endif

	File_ReadBlockFile("IBM.PAL", paletteRGB, 3 * 256);
	VideoA5_SetPalette(paletteRGB, 0, 256);
}

/*--------------------------------------------------------------*/

void
VideoA5_InitSprites(void)
{
	const int WINDOW_W = g_widgetProperties[WINDOWID_RENDER_TEXTURE].width*8;
	const int WINDOW_H = g_widgetProperties[WINDOWID_RENDER_TEXTURE].height;
	const uint16 old_screen = GFX_Screen_SetActive(0);
	const enum WindowID old_widget = Widget_SetCurrentWidget(WINDOWID_RENDER_TEXTURE);

	unsigned char *buf = GFX_Screen_GetActive();

	File_ReadBlockFile("IBM.PAL", paletteRGB, 3 * 256);
	VideoA5_SetPalette(paletteRGB, 0, 256);

	memset(buf, 0, WINDOW_W * WINDOW_H);
	VideoA5_InitIcons(buf);

	memset(buf, 0, WINDOW_W * WINDOW_H);
	VideoA5_InitShapes(buf);

	al_set_target_backbuffer(display);

	GFX_Screen_SetActive(old_screen);
	Widget_SetCurrentWidget(old_widget);
}
