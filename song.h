#ifndef SONG_H
#define SONG_H
#include <cstring>
#include <iostream>
#define LEN 5

enum Fields
{
	TITLE=0,
	ARTIST=1,
	MINUTES=2,
	SECONDS=3,
	ALBUM=4
};

class Song
{
public:
	Song();
	~Song();
	Song(const char title[], const char artist[], const char minutes[], const char seconds[], const char album[]);

	void get(int id, char name[]);
	void set(int id, const char name[]);
	void print();

private:
	char* artist;
	char* album;
	char* minutes;
	char* seconds;
	char* title;

};

#endif