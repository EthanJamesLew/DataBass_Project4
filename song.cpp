#include "song.h"

Song::Song(const char ititle[], const char iartist[], const char iminutes[], const char iseconds[], const char ialbum[])
{
	title = new char[strlen(ititle) + 1];
	artist = new char[strlen(iartist) + 1];
	minutes = new char[strlen(iminutes) + 1];
	seconds = new char[strlen(iseconds) + 1];
	album = new char[strlen(ialbum) + 1];

	strcpy(title, ititle);
	strcpy(artist, iartist);
	strcpy(minutes, iminutes);
	strcpy(seconds, iseconds);
	strcpy(album, ialbum);
}

Song::Song()
{
	title = new char[strlen("none") + 1];
	artist = new char[strlen("none") + 1];
	minutes = new char[strlen("none") + 1];
	seconds = new char[strlen("none") + 1];
	album = new char[strlen("none") + 1];

	strcpy(title, "none");
	strcpy(artist, "none");
	strcpy(minutes, "none");
	strcpy(seconds, "none");
	strcpy(album, "none");
}


Song::~Song()
{
	if (title != NULL)
	delete[] title;
	if (artist != NULL)
	delete[] artist;
	if (minutes != NULL)
	delete[] minutes;
	if (seconds != NULL)
	delete[] seconds;
	if (album != NULL)
	delete[] album;
}

void Song::get(int id, char name[])
{
	switch (id)
	{
	case TITLE: strcpy(name, title); break;
	case ARTIST: strcpy(name, artist); break;
	case MINUTES: strcpy(name, minutes); break;
	case SECONDS: strcpy(name, seconds); break;
	case ALBUM: strcpy(name, album); break;
	}
}
	

void Song::set(int id, const char name[])
{
	switch (id)
	{
	case TITLE: if (this->title != NULL) delete[] this->title; this->title = new char[strlen(name) + 1]; strcpy(this->title, name); break;
	case ARTIST: if (this->title != NULL) delete[] this->artist; this->artist = new char[strlen(name) + 1]; strcpy(this->artist, name); break;
	case MINUTES: if (this->title != NULL) delete[] this->minutes; this->minutes = new char[strlen(name) + 1]; strcpy(this->minutes, name); break;
	case SECONDS: if (this->title != NULL) delete[] this->seconds; this->seconds = new char[strlen(name) + 1]; strcpy(this->seconds, name); break;
	case ALBUM: if (this->title != NULL) delete[] this->album; this->album = new char[strlen(name) + 1]; strcpy(this->album, name); break;
	}
	
}

void Song::print()
{
	std::cout << "Title:   " << title << std::endl;
	std::cout << "Artist:  " << artist << std::endl;
	std::cout << "Duration "<< minutes << ":" << seconds << std::endl;
	std::cout << "Album:   " << album << std::endl;
}