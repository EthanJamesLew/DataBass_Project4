#include "songtui.h"

SongTUI::SongTUI()
{

	slist.loadSongs("songs.txt");
}

void SongTUI::save()
{
	slist.saveSong("songs.txt");
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
	case SALBUM: salbum(); break;
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
	Song song;
	char com[128];

	std::cout << "\tEnter a title: ";
	std::cin.getline(com, 256);
	song.set(TITLE, com);

	std::cout << "\tEnter a artist: ";
	std::cin.getline(com, 256);
	song.set(ARTIST, com);

	bool quit = false;

	while (!quit)
	{
		std::cout << "\tEnter a duration(mm:ss): ";
		std::cin.getline(com, 256);
		if (strlen(com) < 4)
		{
			std::cout << "\t\tCould not understand time" << std::endl;
			continue;
		}
		if (!(com[strlen(com) - 3] && isdigit(com[strlen(com) - 2]) && isdigit(com[strlen(com) - 1])))
		{
			std::cout << "\t\tCould not read digits" << std::endl;
			continue;
		}

		int seconds = 10 * (com[3] - '0') + (com[4] - '0');
		if (seconds > 59)
		{
			std::cout << "\t\tInvalid Seconds" << std::endl;
			continue;
		}

		char sec[3];
		char min[128];
		int i = 0;

		for (i = 0; com[i] != ':'; i++)
		{
			min[i] = com[i];
		}

		min[i] = '\0';
		sec[0] = com[strlen(com) - 2];
		sec[1] = com[strlen(com) - 1];
		sec[2] = '\0';

		song.set(MINUTES, min);
		song.set(SECONDS, sec);

		quit = true;

	}

	std::cout << "\tEnter an album: ";
	std::cin.getline(com, 256);
	song.set(ALBUM, com);

	slist.addEntry(song);
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
	} while (cin.fail() || idx > slist.getSize() || idx < 1);

	slist.remove(idx - 1);
}
