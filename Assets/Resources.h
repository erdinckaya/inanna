
#ifndef RESOURCEMANAGER_RESOURCES_H
#define RESOURCEMANAGER_RESOURCES_H

#include "../ThirdParty/MonitorX/3rdParty/FlexibleReflection/Reflect.h"
#include "../Base/Util/Math/Rect.h"

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
    ImageAsset(const char* id, float x, float y, float w, float h, float parent_w, float parent_h, const char* parent
        , const char* format, int hitX, int hitY, int hitW, int hitH)
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
        this->hitRect = Inanna::Rectf(hitX, hitY, hitW, hitH);
        
        
        this->name = std::string(this->id);
    } 

    const char* id;
    float x;
    float y;
    float w;
    float h;
    
    float parent_w;
    float parent_h;
    Inanna::Rectf hitRect;
    
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
		IMAGE("image", 0.000000f, 0.000000f, 300.000000f, 300.000000f, 300.000000f, 300.000000f, "balls", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("balls", "/Users/always/CLionProjects/inanna/Resources/Assets/balls.png")

    {}

	ImageAsset IMAGE;


};



struct Death : public Sheet {

public:
    Death() :
		DEATH_000("Death_000", 0.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DEATH_001("Death_001", 262.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DEATH_002("Death_002", 524.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DEATH_003("Death_003", 786.000000f, 0.000000f, 263.000000f, 254.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DEATH_004("Death_004", 1049.000000f, 0.000000f, 266.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DEATH_005("Death_005", 1315.000000f, 0.000000f, 262.000000f, 255.000000f, 1577.000000f, 255.000000f, "death", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("death", "/Users/always/CLionProjects/inanna/Resources/Assets/death.png")

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
		TENNIS_FIELD("tennis_field", 0.000000f, 0.000000f, 257.000000f, 427.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		TENNIS_FIELD1("tennis_field1", 0.000000f, 512.000000f, 600.000000f, 900.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		TENNIS_FIELD2("tennis_field2", 257.000000f, 0.000000f, 336.000000f, 512.000000f, 600.000000f, 1412.000000f, "fields", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("fields", "/Users/always/CLionProjects/inanna/Resources/Assets/fields.png")

    {}

	ImageAsset TENNIS_FIELD;
	ImageAsset TENNIS_FIELD1;
	ImageAsset TENNIS_FIELD2;


};



struct Pieces : public Sheet {

public:
    Pieces() :
		BLUE("blue", 0.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		CYAN("cyan", 256.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		DARK_PURPLE("dark_purple", 512.000000f, 0.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		GHOST("ghost", 0.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		GREEN("green", 256.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		PURPLE("purple", 512.000000f, 256.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		RED("red", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		GUCHAN("guchan", 0.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		YELLOW("yellow", 256.000000f, 512.000000f, 256.000000f, 256.000000f, 768.000000f, 768.000000f, "pieces", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("pieces", "/Users/always/CLionProjects/inanna/Resources/Assets/pieces.png")

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



struct Kyo_Crouch : public Sheet {

public:
    Kyo_Crouch() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 118.000000f, 204.000000f, 118.000000f, 532.000000f, "kyo_crouch", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 204.000000f, 104.000000f, 186.000000f, 118.000000f, 532.000000f, "kyo_crouch", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 390.000000f, 118.000000f, 142.000000f, 118.000000f, 532.000000f, "kyo_crouch", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_crouch", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Crouch/kyo_crouch.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;


};



struct Kyo_Big_Kick : public Sheet {

public:
    Kyo_Big_Kick() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 116.000000f, 184.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 116.000000f, 0.000000f, 114.000000f, 216.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 230.000000f, 0.000000f, 120.000000f, 214.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 350.000000f, 0.000000f, 148.000000f, 172.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 498.000000f, 0.000000f, 204.000000f, 200.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 57.000000f, 52.000000f, 150.000000f, 90.000000f),
		FRAME5("Frame5", 702.000000f, 0.000000f, 120.000000f, 210.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 822.000000f, 0.000000f, 102.000000f, 160.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 924.000000f, 0.000000f, 130.000000f, 206.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 1054.000000f, 0.000000f, 118.000000f, 206.000000f, 1172.000000f, 216.000000f, "kyo_big_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_big_kick", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Hit/kyo_big_kick.png")

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


};



struct Kyo_Little_Fist : public Sheet {

public:
    Kyo_Little_Fist() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 130.000000f, 206.000000f, 560.000000f, 206.000000f, "kyo_little_fist", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 130.000000f, 0.000000f, 182.000000f, 204.000000f, 560.000000f, 206.000000f, "kyo_little_fist", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 312.000000f, 0.000000f, 130.000000f, 206.000000f, 560.000000f, 206.000000f, "kyo_little_fist", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 442.000000f, 0.000000f, 118.000000f, 206.000000f, 560.000000f, 206.000000f, "kyo_little_fist", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_little_fist", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Hit/kyo_little_fist.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;


};



struct Kyo_Little_Kick : public Sheet {

public:
    Kyo_Little_Kick() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 176.000000f, 218.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 176.000000f, 0.000000f, 138.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 314.000000f, 0.000000f, 134.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 448.000000f, 0.000000f, 206.000000f, 218.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 654.000000f, 0.000000f, 134.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 788.000000f, 0.000000f, 138.000000f, 212.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 926.000000f, 0.000000f, 120.000000f, 206.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 1046.000000f, 0.000000f, 118.000000f, 206.000000f, 1164.000000f, 218.000000f, "kyo_little_kick", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_little_kick", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Hit/kyo_little_kick.png")

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



struct Kyo_Idle : public Sheet {

public:
    Kyo_Idle() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 118.000000f, 206.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 206.000000f, 122.000000f, 208.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 414.000000f, 122.000000f, 208.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 622.000000f, 124.000000f, 206.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 0.000000f, 828.000000f, 124.000000f, 204.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 0.000000f, 1032.000000f, 122.000000f, 206.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 0.000000f, 1238.000000f, 122.000000f, 208.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 0.000000f, 1446.000000f, 122.000000f, 208.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 0.000000f, 1654.000000f, 120.000000f, 206.000000f, 124.000000f, 1860.000000f, "kyo_idle", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_idle", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Idle/kyo_idle.png")

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


};



struct Kyo_Jump : public Sheet {

public:
    Kyo_Jump() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 102.000000f, 160.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 110.000000f, 958.000000f, 68.000000f, 282.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 118.000000f, 736.000000f, 110.000000f, 222.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 534.000000f, 148.000000f, 202.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 0.000000f, 160.000000f, 154.000000f, 172.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 0.000000f, 332.000000f, 148.000000f, 202.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 0.000000f, 958.000000f, 110.000000f, 222.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 178.000000f, 958.000000f, 68.000000f, 282.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 102.000000f, 0.000000f, 102.000000f, 160.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME9("Frame9", 0.000000f, 736.000000f, 118.000000f, 206.000000f, 246.000000f, 1240.000000f, "kyo_jump", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_jump", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Jump/kyo_jump.png")

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


};



struct Kyo_Jump_Back : public Sheet {

public:
    Kyo_Jump_Back() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 104.000000f, 186.000000f, 120.000000f, 826.000000f, "kyo_jump_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 186.000000f, 120.000000f, 222.000000f, 120.000000f, 826.000000f, "kyo_jump_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 408.000000f, 112.000000f, 212.000000f, 120.000000f, 826.000000f, "kyo_jump_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 620.000000f, 118.000000f, 206.000000f, 120.000000f, 826.000000f, "kyo_jump_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_jump_back", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Jump/kyo_jump_back.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;


};



struct Kyo_Move_Back : public Sheet {

public:
    Kyo_Move_Back() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 112.000000f, 212.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 112.000000f, 0.000000f, 110.000000f, 216.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 222.000000f, 0.000000f, 94.000000f, 222.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 316.000000f, 0.000000f, 90.000000f, 230.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 406.000000f, 0.000000f, 88.000000f, 228.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 494.000000f, 0.000000f, 90.000000f, 220.000000f, 584.000000f, 230.000000f, "kyo_move_back", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_move_back", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Move/kyo_move_back.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;
	ImageAsset FRAME4;
	ImageAsset FRAME5;


};



struct Kyo_Move_Forward : public Sheet {

public:
    Kyo_Move_Forward() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 94.000000f, 218.000000f, 506.000000f, 232.000000f, "kyo_move_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 94.000000f, 0.000000f, 94.000000f, 226.000000f, 506.000000f, 232.000000f, "kyo_move_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 188.000000f, 0.000000f, 94.000000f, 232.000000f, 506.000000f, 232.000000f, "kyo_move_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 282.000000f, 0.000000f, 104.000000f, 224.000000f, 506.000000f, 232.000000f, "kyo_move_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 386.000000f, 0.000000f, 120.000000f, 222.000000f, 506.000000f, 232.000000f, "kyo_move_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_move_forward", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Move/kyo_move_forward.png")

    {}

	ImageAsset FRAME0;
	ImageAsset FRAME1;
	ImageAsset FRAME2;
	ImageAsset FRAME3;
	ImageAsset FRAME4;


};



struct Kyo_Oryu : public Sheet {

public:
    Kyo_Oryu() :
		FRAME0("Frame0", 206.000000f, 0.000000f, 96.000000f, 212.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 258.000000f, 474.000000f, 176.000000f, 252.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 324.000000f, 212.000000f, 92.000000f, 262.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 120.000000f, 474.000000f, 138.000000f, 248.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 0.000000f, 474.000000f, 120.000000f, 250.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 218.000000f, 212.000000f, 106.000000f, 248.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 106.000000f, 212.000000f, 112.000000f, 238.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 0.000000f, 212.000000f, 106.000000f, 234.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 0.000000f, 0.000000f, 102.000000f, 160.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME9("Frame9", 102.000000f, 0.000000f, 104.000000f, 186.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME10("Frame10", 302.000000f, 0.000000f, 118.000000f, 206.000000f, 434.000000f, 726.000000f, "kyo_oryu", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_oryu", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Oryu/kyo_oryu.png")

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


};



struct Kyo_Roll_Backward : public Sheet {

public:
    Kyo_Roll_Backward() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 140.000000f, 198.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 198.000000f, 188.000000f, 206.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 404.000000f, 204.000000f, 184.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 588.000000f, 212.000000f, 154.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 0.000000f, 742.000000f, 142.000000f, 132.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 0.000000f, 874.000000f, 188.000000f, 118.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 0.000000f, 992.000000f, 160.000000f, 140.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 0.000000f, 1132.000000f, 102.000000f, 160.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 102.000000f, 1132.000000f, 118.000000f, 206.000000f, 220.000000f, 1338.000000f, "kyo_roll_backward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_roll_backward", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Roll/kyo_roll_backward.png")

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


};



struct Kyo_Roll_Forward : public Sheet {

public:
    Kyo_Roll_Forward() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 102.000000f, 160.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 160.000000f, 160.000000f, 140.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 300.000000f, 188.000000f, 118.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 418.000000f, 142.000000f, 132.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 0.000000f, 550.000000f, 212.000000f, 154.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 0.000000f, 704.000000f, 204.000000f, 184.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 0.000000f, 888.000000f, 188.000000f, 206.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 0.000000f, 1094.000000f, 90.000000f, 220.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 90.000000f, 1094.000000f, 118.000000f, 206.000000f, 212.000000f, 1314.000000f, "kyo_roll_forward", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_roll_forward", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Roll/kyo_roll_forward.png")

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


};



struct Kyo_Run : public Sheet {

public:
    Kyo_Run() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 102.000000f, 160.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 0.000000f, 172.000000f, 126.000000f, 178.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 0.000000f, 356.000000f, 210.000000f, 184.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 102.000000f, 0.000000f, 202.000000f, 170.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 126.000000f, 172.000000f, 126.000000f, 180.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 252.000000f, 172.000000f, 218.000000f, 184.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 304.000000f, 0.000000f, 206.000000f, 172.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 328.000000f, 356.000000f, 112.000000f, 212.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 210.000000f, 356.000000f, 118.000000f, 206.000000f, 510.000000f, 568.000000f, "kyo_run", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_run", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Run/kyo_run.png")

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


};



struct Kyo_Salute : public Sheet {

public:
    Kyo_Salute() :
		FRAME0("Frame0", 0.000000f, 0.000000f, 84.000000f, 232.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME1("Frame1", 84.000000f, 0.000000f, 94.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME2("Frame2", 130.000000f, 284.000000f, 130.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME3("Frame3", 0.000000f, 284.000000f, 130.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME4("Frame4", 260.000000f, 284.000000f, 134.000000f, 228.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME5("Frame5", 394.000000f, 284.000000f, 142.000000f, 230.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME6("Frame6", 670.000000f, 0.000000f, 100.000000f, 274.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME7("Frame7", 570.000000f, 0.000000f, 100.000000f, 276.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME8("Frame8", 770.000000f, 0.000000f, 100.000000f, 276.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME9("Frame9", 276.000000f, 0.000000f, 98.000000f, 282.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME10("Frame10", 472.000000f, 0.000000f, 98.000000f, 284.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME11("Frame11", 374.000000f, 0.000000f, 98.000000f, 284.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME12("Frame12", 178.000000f, 0.000000f, 98.000000f, 280.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME13("Frame13", 536.000000f, 284.000000f, 148.000000f, 188.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME14("Frame14", 684.000000f, 284.000000f, 148.000000f, 188.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME15("Frame15", 832.000000f, 284.000000f, 148.000000f, 192.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		FRAME16("Frame16", 870.000000f, 0.000000f, 118.000000f, 206.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		IDLE("Idle", 870.000000f, 0.000000f, 118.000000f, 206.000000f, 988.000000f, 514.000000f, "kyo_salute", "RGBA8888", 0.000000f, 0.000000f, 0.000000f, 0.000000f),
		Sheet("kyo_salute", "/Users/always/CLionProjects/inanna/Resources/Assets/Kyo/Salute/kyo_salute.png")

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
	ImageAsset IDLE;


};

struct Resources {
public:
	static Balls BALLS;
	static Death DEATH;
	static Fields FIELDS;
	static Pieces PIECES;
	static Kyo_Crouch KYO_CROUCH;
	static Kyo_Big_Kick KYO_BIG_KICK;
	static Kyo_Little_Fist KYO_LITTLE_FIST;
	static Kyo_Little_Kick KYO_LITTLE_KICK;
	static Kyo_Idle KYO_IDLE;
	static Kyo_Jump KYO_JUMP;
	static Kyo_Jump_Back KYO_JUMP_BACK;
	static Kyo_Move_Back KYO_MOVE_BACK;
	static Kyo_Move_Forward KYO_MOVE_FORWARD;
	static Kyo_Oryu KYO_ORYU;
	static Kyo_Roll_Backward KYO_ROLL_BACKWARD;
	static Kyo_Roll_Forward KYO_ROLL_FORWARD;
	static Kyo_Run KYO_RUN;
	static Kyo_Salute KYO_SALUTE;


	static int SheetCount;
	static const Sheet Sheets[18];
};


#endif //RESOURCEMANAGER_RESOURCES_H
