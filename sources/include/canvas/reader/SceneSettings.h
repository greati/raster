#ifndef __SCENE_SETTINGS__
#define __SCENE_SETTINGS__

#include <map>

/**
 * Scene settings to be used during the parsing.
 *
 * @author Vitor Greati
 * */
class SceneSettings {

    public:

        /** Color pallete */
        inline static std::map<std::string, RGBColor> color_pallete = {
           {"red", {255, 0 ,0}},
           {"green", {0, 255 ,0}},
           {"blue", {0, 0, 255}},
           {"white", {255, 255, 255}},
           {"black", {0, 0, 0}},
        };

        /** Pallete of fills */
        inline static std::map<std::string, Object::Fill<>> fill_pallete;

        /** Pallete of stroke */
        inline static std::map<std::string, Object::Stroke<>> stroke_pallete;

        /**
         * Get a color from the color pallete.
         *
         * @param name color name
         * */
        static RGBColor get_color(const std::string& name) {
            if (auto point_it = color_pallete.find(name); point_it != color_pallete.end())
                return point_it->second;
            else
                throw std::invalid_argument("no color with this name");
        }
};

#endif
