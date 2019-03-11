#ifndef __SCENE_SETTINGS__
#define __SCENE_SETTINGS__

#include <map>

class SceneSettings {

    public:
        inline static std::map<std::string, RGBColor> color_pallete = {
           {"red", {255, 0 ,0}},
           {"green", {0, 255 ,0}},
           {"blue", {0, 0, 255}},
           {"white", {255, 255, 255}},
           {"black", {0, 0, 0}},
        };

        inline static std::map<std::string, Object::Fill<>> fill_pallete;
        inline static std::map<std::string, Object::Stroke<>> stroke_pallete;

        static RGBColor get_color(const std::string& str) {
            if (auto point_it = color_pallete.find(str); point_it != color_pallete.end())
                return point_it->second;
            else
                throw std::invalid_argument("no color with this name");
        }
};

#endif
