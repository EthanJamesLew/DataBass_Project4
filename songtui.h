#ifndef SONGTUI_H
#define SONGTUI_H
#include "song.h"
#include "songlist.h"
#include <fstream>
class SongTUI
{
public:
	SongTUI();
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

SongTUI::SongTUI()
{
	
	slist.loadSongs("songs.txt");
}

void SongTUI::renderMenu()
{
	std::ifstream infile1;
	infile1.open("menu.txt");

	if (infile1.fail())
	{
		std::cout << "File failed to open.\n";
		exit(1);
	}

	do
	{
		if (infile1.peek() != EOF) std::cout << (char)infile1.get();
	} while ((infile1.good()));
}

void SongTUI::mainloop()
{
	char command[128];
	while (true)
	{
		std::cout << "data-bass>";
		std::cin.getline(command, 1000);
		if (!strcmp(command, "exit") | !strcmp(command, "quit") | !strcmp(command, "q") | !strcmp(command, "break"))
		{
			break;
		}
		execCommand(command);
	}
}


void SongTUI::execCommand(const char command[])
{
	unsigned key = hash(command);
	switch (key)
	{
	case ADD: add(); break;
	case SARTIST: sartist(); break;
	case SALBUM: std::cout << "salbum" << std::endl; break;
	case DELIDX: delidx(); break;
	case LS: ls(); break;
	default: std::cout << "Invalid command" << std::endl;
	}
}

unsigned SongTUI::hash(const char command[])
{
	int max = strlen(command);
	unsigned h = 0x811c9dc5;

	for (int i = 0; i<max; i++)
		h = (h ^ command[i]) * 0x01000193;

	return h;
}

void SongTUI::add()
{

}

void SongTUI::sartist()
{
	char com[128];
	std::cout << "Enter an artist:";
	cin.getline(com, '\n');

	slist.searchp(com, ARTIST);

}

void SongTUI::salbum()
{
	char com[128];
	std::cout << "Enter an album:";
	cin.getline(com, '\n');

	slist.searchp(com, ALBUM);
}

void SongTUI::ls()
{
	slist.print();
}

void SongTUI::delidx()
{
	int idx;
	
	do
	{
		std::cout << "Enter an index:";
		std::cin >> idx;
		cin.clear();
		cin.ignore(128, '\n');
	} while (cin.fail() || idx > slist.getSize()-1 || idx < 1);

	slist.remove(idx-1);
}

#endif