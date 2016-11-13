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

SongList::SongList() 
{
	size = 0;
	cap = 14;
	songs = new Song[14];
}

SongList::SongList(int reserve)
{
	size = 0;
	cap = reserve;
	songs = new Song[reserve];
}

SongList::~SongList()
{
	if (songs != NULL)
		delete[] songs;
}

bool SongList::get(int idx, Song& song) const
{
	if (idx < size)
	{
		song = songs[idx];
		return true;
	}
	else
		return false;

}

bool SongList::search(const char name[], int idx, Song& match) const
{
	int i;
	char	current[128];
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	for (i = 0; i<size; i++)
	{
		songs[i].get(idx, current);

		if (strcmp(name, current) == 0)
		{
			songs[i].get(TITLE, otitle);
			songs[i].get(ARTIST, oartist);
			songs[i].get(MINUTES, ominutes);
			songs[i].get(SECONDS, oseconds);
			songs[i].get(ALBUM, oalbum);

			match.set(TITLE, otitle);
			match.set(ARTIST, oartist);
			match.set(MINUTES, ominutes);
			match.set(SECONDS, oseconds);
			match.set(ALBUM, oalbum);
			break;
		}
	}
	if (i == size)
		return false;
	else
		return true;
}

int SongList::getSize() const
{
	return size;
}

void SongList::print() const
{
	for (int idx = 0; idx < size; idx++)
	{
		songs[idx].print();
	}
}

void SongList::remove(int idx)
{
	Song* tempSong;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	size--;
	tempSong = new Song[size];

	for (int i = 0; i < idx; i++)
	{
		songs[i].get(TITLE, otitle);
		songs[i].get(ARTIST, oartist);
		songs[i].get(MINUTES, ominutes);
		songs[i].get(SECONDS, oseconds);
		songs[i].get(ALBUM, oalbum);

		tempSong[i].set(TITLE, otitle);
		tempSong[i].set(ARTIST, oartist);
		tempSong[i].set(MINUTES, ominutes);
		tempSong[i].set(SECONDS, oseconds);
		tempSong[i].set(ALBUM, oalbum);

	}

	for (int i = size-1; i >= idx; i--)
	{
		songs[i + 1].get(TITLE, otitle);
		songs[i + 1].get(ARTIST, oartist);
		songs[i + 1].get(MINUTES, ominutes);
		songs[i + 1].get(SECONDS, oseconds);
		songs[i + 1].get(ALBUM, oalbum);

		tempSong[i].set(TITLE, otitle);
		tempSong[i].set(ARTIST, oartist);
		tempSong[i].set(MINUTES, ominutes);
		tempSong[i].set(SECONDS, oseconds);
		tempSong[i].set(ALBUM, oalbum);

	}

	delete[] songs;
	songs = tempSong;
	tempSong = NULL;
}

void SongList::loadSongs(const char fileName[])
{
	ifstream in;
	Song tempSong;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	in.open(fileName);
	if (!in)
	{
		in.clear();
		cerr << endl << "Fail to open " << fileName << " for input!" << endl << endl;
		exit(1);
	}

	in.get(otitle, 128, ';');
	while (!in.eof())
	{
		in.get();							//remove field seperator ';'	
		in.get(oartist, 128, ';');
		in.get();
		in.get(ominutes, 128, ';');
		in.get();
		in.get(oseconds, 128, ';');
		in.get();
		in.get(oalbum, 128, '\n');
		in.ignore(100, '\n');				//remove record seperator '\n'

		tempSong.set(TITLE, otitle);
		tempSong.set(ARTIST, oartist);
		tempSong.set(MINUTES, ominutes);
		tempSong.set(SECONDS, oseconds);
		tempSong.set(ALBUM, oalbum);

		addEntry(tempSong);
		in.get(otitle, 128, ';');

	}
	in.close();

}

void SongList::saveSong(const char fileName[])
{
	ofstream		out;
	int				index;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	out.open(fileName);
	if (!out)
	{
		out.clear();
		cerr << endl << "Fail to open " << fileName << " for output!" << endl << endl;
		exit(1);
	}

	for (index = 0; index<size; index++)
	{
		songs[index].get(TITLE, otitle);
		songs[index].get(ARTIST, oartist);
		songs[index].get(MINUTES, ominutes);
		songs[index].get(SECONDS, oseconds);
		songs[index].get(ALBUM, oalbum);

		out << otitle << ';' << oartist << ';' << ominutes << ';' << oseconds << ';' << oalbum << endl;
	}

	out.close();

}

void SongList::addEntry(Song& song)
{

	Song tempSong;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	if (size == cap)
		expand();

	song.get(TITLE, otitle);
	song.get(ARTIST, oartist);
	song.get(MINUTES, ominutes);
	song.get(SECONDS, oseconds);
	song.get(ALBUM, oalbum);

	songs[size].set(TITLE, otitle);
	songs[size].set(ARTIST, oartist);
	songs[size].set(MINUTES, ominutes);
	songs[size].set(SECONDS, oseconds);
	songs[size].set(ALBUM, oalbum);


	size++;
}

void SongList::expand()
{
	Song* tempSong;
	int idx;
	char otitle[128];
	char oartist[128];
	char ominutes[128];
	char oseconds[128];
	char oalbum[128];

	cap *= 2;
	tempSong = new Song[cap];

	for (idx = 0; idx < size; idx++)
	{
		songs[idx].get(TITLE, otitle);
		songs[idx].get(ARTIST, oartist);
		songs[idx].get(MINUTES, ominutes);
		songs[idx].get(SECONDS, oseconds);
		songs[idx].get(ALBUM, oalbum);

		tempSong[idx].set(TITLE, otitle);
		tempSong[idx].set(ARTIST, oartist);
		tempSong[idx].set(MINUTES, ominutes);
		tempSong[idx].set(SECONDS, oseconds);
		tempSong[idx].set(ALBUM, oalbum);
		
	}

	delete[] songs;
	songs = tempSong;
	tempSong = NULL;
}

#endif