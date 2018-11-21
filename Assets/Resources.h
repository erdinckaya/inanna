
#ifndef RESOURCEMANAGER_RESOURCES_H
#define RESOURCEMANAGER_RESOURCES_H

#include<string>

struct Sheet {
public:
    Sheet(const char* name, const char* path) : name(name), path(path) {}
    
    const char* name;
    const char* path;
};

    
struct ImageAsset {
public:

    ImageAsset(const char* id, float x, float y, float w, float h, float parent_w, float parent_h, const char* parent, const char* format)
    {
        this->id = id;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->parent_w = parent_w;
        this->parent_h = parent_h;
        this->parent = parent;
        this->format = format;
    } 

    const char* id;
    float x;
    float y;
    float w;
    float h;
    
    float parent_w;
    float parent_h;
    
    const char* parent;
    const char* format;
};





struct Pieces : public Sheet {

public:
    Pieces() :
		PIECES_BLUE("pieces_blue", 0.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_CYAN("pieces_cyan", 256.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_DARK_PURPLE("pieces_dark_purple", 512.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_GHOST("pieces_ghost", 0.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_GREEN("pieces_green", 256.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_PURPLE("pieces_purple", 512.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_RED("pieces_red", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PIECES_YELLOW("pieces_yellow", 256.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		Sheet("pieces", "/home/misterdortnal/CLionProjects/Inanna/Resources/pieces.png")

    {}

	ImageAsset PIECES_BLUE;
	ImageAsset PIECES_CYAN;
	ImageAsset PIECES_DARK_PURPLE;
	ImageAsset PIECES_GHOST;
	ImageAsset PIECES_GREEN;
	ImageAsset PIECES_PURPLE;
	ImageAsset PIECES_RED;
	ImageAsset PIECES_YELLOW;


};

struct Resources {
public:
	static Pieces PIECES;


	static int SheetCount;
	static const Sheet Sheets[1];
};


#endif //RESOURCEMANAGER_RESOURCES_H
