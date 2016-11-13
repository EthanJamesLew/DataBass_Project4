#ifndef SONGTUI_H
#define SONGTUI_H
#include "song.h"
#include "songlist.h"
#include <fstream>
class SongTUI
{
public:
	SongTUI();
	void save();
	void renderMenu();
	void mainloop();
private:
	void execCommand(const char command[]);
	unsigned hash(const char command[]);
	void add();
	void sartist();
	void salbum();
	void ls();
	void delidx();
	SongList slist;
};

enum keys: unsigned
{
ADD= 993596020,
SARTIST = 1902126709,
SALBUM = 3877959697,
DELIDX = 1544085933,
LS = 1446109160
};

#endif