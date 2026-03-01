#include <osbind.h>
#include "types.h"
#include "bitmap.h"
#include "model.h"
#include "render.h"
#include "raster.h"

int main() {
	UINT32* base;
	Room room;
	Timer timer;
	Player player;

	base = (UINT32*)Physbase();

	room = create_room_1();
	player = create_player(50, 166, player_bitmap);
	timer = create_timer();

	init_render(base);

	render_player((UINT16*)base, &player);
	render_room(base, &room);
	render_timer((UINT8*)base, &timer);
}