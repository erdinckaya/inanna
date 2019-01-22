
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





struct Kyo_Salute : public Sheet {

public:
    Kyo_Salute() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 84.000000f, 232.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME1("Frame1", 84.000000f, 0.000000f, 94.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME2("Frame2", 130.000000f, 284.000000f, 130.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME3("Frame3", 0.000000f, 284.000000f, 130.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME4("Frame4", 260.000000f, 284.000000f, 134.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME5("Frame5", 394.000000f, 284.000000f, 142.000000f, 230.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME6("Frame6", 670.000000f, 0.000000f, 100.000000f, 274.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME7("Frame7", 570.000000f, 0.000000f, 100.000000f, 276.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME8("Frame8", 770.000000f, 0.000000f, 100.000000f, 276.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME9("Frame9", 276.000000f, 0.000000f, 98.000000f, 282.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME10("Frame10", 472.000000f, 0.000000f, 98.000000f, 284.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME11("Frame11", 374.000000f, 0.000000f, 98.000000f, 284.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME12("Frame12", 178.000000f, 0.000000f, 98.000000f, 280.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME13("Frame13", 536.000000f, 284.000000f, 148.000000f, 188.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME14("Frame14", 684.000000f, 284.000000f, 148.000000f, 188.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME15("Frame15", 832.000000f, 284.000000f, 148.000000f, 192.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		FRAME16("Frame16", 870.000000f, 0.000000f, 118.000000f, 206.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888"),
		Sheet("kyo_salute", "/home/misterdortnal/CLionProjects/Inanna/Resources/kyo_salute.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;
	ImageAsset FRAME4;
	ImageAsset FRAME5;
	ImageAsset FRAME6;
	ImageAsset FRAME7;
	ImageAsset FRAME8;
	ImageAsset FRAME9;
	ImageAsset FRAME10;
	ImageAsset FRAME11;
	ImageAsset FRAME12;
	ImageAsset FRAME13;
	ImageAsset FRAME14;
	ImageAsset FRAME15;
	ImageAsset FRAME16;


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
		Sheet("pieces", "/home/misterdortnal/CLionProjects/Inanna/Resources/pieces.png")

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



struct Balls : public Sheet {

public:
    Balls() :
		IMAGE("image", 0.000000f, 0.000000f, 300.000000f, 300.000000f, 300.000000f, 300.000000f, "balls", "RGBA8888"),
		Sheet("balls", "/home/misterdortnal/CLionProjects/Inanna/Resources/balls.png")

    {}

	ImageAsset IMAGE;


};



struct Death : public Sheet {

public:
    Death() :
		DEATH_000("Death_000", 0.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		DEATH_001("Death_001", 262.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		DEATH_002("Death_002", 524.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		DEATH_003("Death_003", 786.000000f, 0.000000f, 263.000000f, 254.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		DEATH_004("Death_004", 1049.000000f, 0.000000f, 266.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		DEATH_005("Death_005", 1315.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888"),
		Sheet("death", "/home/misterdortnal/CLionProjects/Inanna/Resources/death.png")

    {}

	ImageAsset DEATH_000;
	ImageAsset DEATH_001;
	ImageAsset DEATH_002;
	ImageAsset DEATH_003;
	ImageAsset DEATH_004;
	ImageAsset DEATH_005;


};



struct Fields : public Sheet {

public:
    Fields() :
		TENNIS_FIELD("tennis_field", 0.000000f, 0.000000f, 257.000000f, 427.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		TENNIS_FIELD1("tennis_field1", 0.000000f, 512.000000f, 600.000000f, 900.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		TENNIS_FIELD2("tennis_field2", 257.000000f, 0.000000f, 336.000000f, 512.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888"),
		Sheet("fields", "/home/misterdortnal/CLionProjects/Inanna/Resources/fields.png")

    {}

	ImageAsset TENNIS_FIELD;
	ImageAsset TENNIS_FIELD1;
	ImageAsset TENNIS_FIELD2;


};



struct Kyo_Little_Kick : public Sheet {

public:
    Kyo_Little_Kick() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 176.000000f, 218.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME1("Frame1", 176.000000f, 0.000000f, 138.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME2("Frame2", 314.000000f, 0.000000f, 134.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME3("Frame3", 448.000000f, 0.000000f, 206.000000f, 218.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME4("Frame4", 654.000000f, 0.000000f, 134.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME5("Frame5", 788.000000f, 0.000000f, 138.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME6("Frame6", 926.000000f, 0.000000f, 120.000000f, 206.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		FRAME7("Frame7", 1046.000000f, 0.000000f, 118.000000f, 206.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888"),
		Sheet("kyo_little_kick", "/home/misterdortnal/CLionProjects/Inanna/Resources/kyo_little_kick.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;
	ImageAsset FRAME4;
	ImageAsset FRAME5;
	ImageAsset FRAME6;
	ImageAsset FRAME7;


};

struct Resources {
public:
	static Kyo_Salute KYO_SALUTE;
	static Pieces PIECES;
	static Balls BALLS;
	static Death DEATH;
	static Fields FIELDS;
	static Kyo_Little_Kick KYO_LITTLE_KICK;


	static int SheetCount;
	static const Sheet Sheets[6];
};


#endif //RESOURCEMANAGER_RESOURCES_H
