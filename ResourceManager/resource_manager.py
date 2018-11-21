import os
import json

resource_path = "Resources"
output_path = os.path.join("..", "Assets", "Resources.h")
output_path_cpp = os.path.join("..", "Assets", "Resources.cpp")
atlas_path = os.path.join("..", "Resources")


class Resource:
    def __init__(self, name, path, data):
        self.name = name
        self.path = path
        self.data = data


resources = []

for root, dirs, files in os.walk(atlas_path):
    for file in files:
        if file.endswith(".png"):
            name = file.split(".")[0]
            path = os.path.join(root, file)
            data = os.path.join(root, file.split(".")[0] + ".json")
            resources.append(Resource(name, path, data))


result_str = ""

image_class_str = \
    """
#ifndef RESOURCEMANAGER_RESOURCES_H
#define RESOURCEMANAGER_RESOURCES_H
    
    
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



"""

result_str += image_class_str

assets_assets_class_str = """

struct %s {

public:
    %s() :
%s
    {}

%s
};

"""



cpp_file_value_str = ""

atlas_class_str = ""
for resource in resources:
    sheet_data = None
    with open(resource.data, 'r') as f:
        sheet_data = json.load(f)
    frames = sheet_data["frames"]
    name = sheet_data["meta"]["image"].split(".")[0]
    sheet_format = sheet_data["meta"]["format"]
    sheet_width = sheet_data["meta"]["size"]["w"]
    sheet_height = sheet_data["meta"]["size"]["h"]

    asset_definition_class_str = ""
    assets_values_class_str = ""
    frame_count = 0
    for frame in frames:
        frame_count += 1
        id = frame["filename"].split(".")[0]
        x = frame["frame"]["x"]
        y = frame["frame"]["y"]
        w = frame["frame"]["w"]
        h = frame["frame"]["h"]
        asset_definition_class_str += "\tImageAsset %s;\n" % (id.upper())

        comma = "," if len(frames) != frame_count else ""
        assets_values_class_str += "\t\t%s(\"%s\", %ff, %ff, %ff, %ff, %ff, %ff, \"%s\", \"%s\")%s\n" % (id.upper(), id, x, y, w, h, sheet_width, sheet_height, name, sheet_format, comma)

    result_str += assets_assets_class_str % (name.title(), name.title(), assets_values_class_str, asset_definition_class_str)
    atlas_class_str += "\t static %s %s;\n" % (name.title(), name.upper())

    cpp_file_value_str += "%s Resources::%s;\n" % (name.title(), name.upper())



resources_class_str = \
    """struct Resources {
public:
%s
};


#endif //RESOURCEMANAGER_RESOURCES_H
""" % atlas_class_str

result_str += resources_class_str

print(result_str)


cpp_file_str = """

#include \"Resources.h\"

%s

""" % cpp_file_value_str


with open(output_path, 'w') as the_file:
    the_file.write(result_str)


with open(output_path_cpp, 'w') as the_file:
    the_file.write(cpp_file_str)