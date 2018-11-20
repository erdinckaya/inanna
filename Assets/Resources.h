
#ifndef RESOURCEMANAGER_RESOURCES_H
#define RESOURCEMANAGER_RESOURCES_H
    
    
struct Image {
public:

    Image(const char* id, float x, float y, float w, float h, float parent_w, float parent_h, const char* parent, const char* format)
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





struct Pieces {

public:
    Pieces() :
		BLUE("blue", 0.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		CYAN("cyan", 256.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		DARK_PURPLE("dark_purple", 512.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		GHOST("ghost", 0.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		GREEN("green", 256.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PURPLE("purple", 512.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		RED("red", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		YELLOW("yellow", 256.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888")

    {}

	Image BLUE;
	Image CYAN;
	Image DARK_PURPLE;
	Image GHOST;
	Image GREEN;
	Image PURPLE;
	Image RED;
	Image YELLOW;

};

struct Resources {
public:
	 static Pieces PIECES;

};


#endif //RESOURCEMANAGER_RESOURCES_H
