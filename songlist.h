#ifndef SONGLIST_H
#define SONGLIST_H

#include <fstream>
using namespace std;
#include "song.h"

const int INIT_CAP = 128;

class SongList
{
public:
	SongList();
	SongList(int reserve);

	~SongList();

	bool get(int idx, Song& song) const;
	bool search(const char name[], int idx, Song& match) const;
	void searchp(const char name[], int idx) const;
	int getSize() const;
	void print() const;
	void remove(int idx);
	void loadSongs(const char fileName[]);
	void saveSong(const char fileName[]);
	void addEntry(Song& song);

private:
	void expand();
	Song* songs;
	int size;
	int cap;
};
#endif