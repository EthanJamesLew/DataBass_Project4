#include "song.h"
#include "songlist.h"

int main(int argc, char* argv[])
{
	Song temp = Song();
	SongList list = SongList(1);
	list.loadSongs("songs.txt");
	bool search = list.search("Drive North", ALBUM, temp);
	if (search)
		temp.print();
	list.remove(0);
	list.print();
	list.saveSong("so.txt");
	return 0;
}