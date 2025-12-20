/**
 * @file dev_zone.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
// git update-index --skip-worktree example/dev_zone.cpp
#include "../utils/raylib_wrapper.hpp"
#include <uitk/short_namespace.hpp>
#include <games/dvd_screensaver/dvd_screensaver.hpp>
#include <mooncake_log.h>
#include <vector>

using namespace uitk;
using namespace uitk::games;
using namespace uitk::games::dvd_screensaver;

namespace smooth_ui_toolkit::games::dvd_screensaver {

class DvdScreensaverRaylib : public DvdScreensaver {
protected:
    Vector2 screen_size = {800, 450};
    Vector2 logo_size = {50, 30};
    size_t logo_count = 12;
    std::vector<Color> logo_colors;

    void onBuildLevel() override
    {
        addScreenFrameAsWall(screen_size);

        for (int i = 0; i < logo_count; i++) {
            addRandomLogo(i, screen_size, logo_size);
            logo_colors.push_back(GetRandomColor());
        }
    }

    void onRender() override
    {
        ClearBackground(WHITE);

        getWorld().forEachObject([&](GameObject* obj) {
            auto group = static_cast<Group>(obj->groupId);

            if (group == Group::Wall) {
                auto p = obj->get<Transform>()->position;
                auto s = obj->get<RectShape>()->size;
                DrawRectangle(p.x - s.x / 2, p.y - s.y / 2, s.x, s.y, GRAY);
            }

            else {
                auto p = obj->get<Transform>()->position;
                auto s = obj->get<RectShape>()->size;
                DrawRectangle(p.x - s.x / 2, p.y - s.y / 2, s.x, s.y, logo_colors[obj->groupId]);
            }
        });
    }
};

} // namespace smooth_ui_toolkit::games::dvd_screensaver

int main()
{
    DvdScreensaverRaylib game;
    game.init();

    raylib::create_window(800, 450, "你好", [&]() {
        game.update();
        // SDL_Delay(1.0f / 30.0f * 1000);
    });
    return 0;
}
