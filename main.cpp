#include "song.h"
#include "songtui.h"

int main(int argc, char* argv[])
{
	SongTUI tui = SongTUI();
	tui.renderMenu();
	tui.mainloop();
	tui.save();
	return 0;
}