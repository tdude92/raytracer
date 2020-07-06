#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "vec3f.hpp"
#include "geometry.hpp"
#include "cfgparser.hpp"

inline bool is_substr(const std::string& s, const std::string& substr) {
    return (s.find(substr) != std::string::npos);
}


inline void writeObj(Config* cfg, const ObjData& data) {
    try {
        if (data.type == OBJ::SPHERE) {
            cfg->shapes.push_back(new Sphere(
                data.pos,
                data.radius,
                data.colour,
                data.diffuse
            ));

        } else if (data.type == OBJ::LIGHTSOURCE) {
            cfg->lightSources.push_back(LightSource(
                data.pos,
                data.colour,
                data.brightness
            ));

        }
    } catch (int e) {
        std::cerr << "Error in cfg file." << std::endl;
    }
}


inline bool parseBool_cfg(const std::string& b) {
    if (b == "true")
        return true;
    else if (b == "false")
        return false;
}


Vec3f parseVec3f_cfg(std::string vec) {
    vec = vec.substr(1, vec.length() - 2);

    double x = std::stod(vec.substr(0, vec.find_first_of(",")));
    vec.erase(0, vec.find_first_of(",") + 1);

    double y = std::stod(vec.substr(0, vec.find_first_of(",")));
    vec.erase(0, vec.find_first_of(",") + 1);

    double z = std::stod(vec);

    return Vec3f(x, y, z);
}


void loadConfiguration(const std::string& fileName, Config* cfg) {
    std::ifstream file(fileName);

    ObjData* currObj = new ObjData;
    std::string line;
    while (std::getline(file, line)) {
        // Remove spaces
        std::size_t idx = line.find_first_of(" ");
        while (idx != std::string::npos) {
            line.erase(idx, 1);
            idx = line.find_first_of(" ");
        }

        if (is_substr(line, "#Sphere")) {
            writeObj(cfg, *currObj);
            delete currObj;
            currObj = new ObjData;

            currObj->type = OBJ::SPHERE;

        } else if (is_substr(line, "#LightSource")) {
            writeObj(cfg, *currObj);
            delete currObj;
            currObj = new ObjData;

            currObj->type = OBJ::LIGHTSOURCE;

        } else if (currObj->type == OBJ::SPHERE) {
            if (is_substr(line, "center"))
                currObj->pos = parseVec3f_cfg(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "radius"))
                currObj->radius = std::stod(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "colour"))
                currObj->colour = parseVec3f_cfg(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "diffuse"))
                currObj->diffuse = parseBool_cfg(line.substr(line.find_first_of("=") + 1));

        } else if (currObj->type == OBJ::LIGHTSOURCE) {
            if (is_substr(line, "colour"))
                currObj->colour = parseVec3f_cfg(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "pos"))
                currObj->pos = parseVec3f_cfg(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "brightness"))
                currObj->brightness = std::stod(line.substr(line.find_first_of("=") + 1));

        } else if (currObj->type == OBJ::FRAMEBUFFER) {
            if (is_substr(line, "width"))
                cfg->width = std::stoi(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "height"))
                cfg->height = std::stoi(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "fov"))
                cfg->fov = std::stod(line.substr(line.find_first_of("=") + 1));
            else if (is_substr(line, "aspectRatio"))
                cfg->aspectRatio = std::stod(line.substr(line.find_first_of("=") + 1));

        }
    }
    // Since currObj is only written when a new obj is being defined in the .cfg,
    // This is necessary to flush everything in currObj into cfg.
    writeObj(cfg, *currObj);
    delete currObj;
}
