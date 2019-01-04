
#ifndef RESOURCEMANAGER_RESOURCES_H
#define RESOURCEMANAGER_RESOURCES_H

#include "../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"

#include<string>
#include<string.h>

struct Sheet {
public:
    Sheet(const char* name, const char* path) : name(name), path(path) {}
    
    const char* name;
    const char* path;
};

    
struct ImageAsset {
public:
    explicit ImageAsset() : id("") {}
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
        
        this->name = std::string(this->id);
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
    
    std::string name;
    
    bool valid() const {
        return strcmp(id, "") != 0;
    }
    
    REFLECT()
};





struct Balls : public Sheet {

public:
    Balls() :
		IMAGE("image", 0.000000f, 0.000000f, 300.000000f, 300.000000f, 300.000000f, 300.000000f, "balls", "RGBA8888"),
		Sheet("balls", "/Users/always/CLionProjects/inanna/Resources/balls.png")

    {}

	ImageAsset IMAGE;


};



struct Fields : public Sheet {

public:
    Fields() :
		TENNIS_FIELD("tennis_field", 0.000000f, 0.000000f, 257.000000f, 427.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		TENNIS_FIELD1("tennis_field1", 0.000000f, 512.000000f, 600.000000f, 900.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		TENNIS_FIELD2("tennis_field2", 257.000000f, 0.000000f, 336.000000f, 512.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		Sheet("fields", "/Users/always/CLionProjects/inanna/Resources/fields.png")

    {}

	ImageAsset TENNIS_FIELD;
	ImageAsset TENNIS_FIELD1;
	ImageAsset TENNIS_FIELD2;


};



struct Pieces : public Sheet {

public:
    Pieces() :
		BLUE("blue", 0.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		CYAN("cyan", 256.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		DARK_PURPLE("dark_purple", 512.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		GHOST("ghost", 0.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		GREEN("green", 256.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		PURPLE("purple", 512.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		RED("red", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		GUCHAN("guchan", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		YELLOW("yellow", 256.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888"),
		Sheet("pieces", "/Users/always/CLionProjects/inanna/Resources/pieces.png")

    {}

	ImageAsset BLUE;
	ImageAsset CYAN;
	ImageAsset DARK_PURPLE;
	ImageAsset GHOST;
	ImageAsset GREEN;
	ImageAsset PURPLE;
	ImageAsset RED;
	ImageAsset GUCHAN;
	ImageAsset YELLOW;


};

struct Resources {
public:
	static Balls BALLS;
	static Fields FIELDS;
	static Pieces PIECES;


	static int SheetCount;
	static const Sheet Sheets[3];
};


#endif //RESOURCEMANAGER_RESOURCES_H
