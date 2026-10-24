#include <Geode/Geode.hpp>
#include "Settings.hpp"

using namespace geode::prelude;

$execute {
    auto& c = fpsboost::cfg();
    fpsboost::bind<int64_t, int>("fps-target", c.fpsTarget);
    fpsboost::bind<bool, bool>("culling-enabled", c.cullingEnabled);
    fpsboost::bind<double, float>("culling-margin", c.cullingMargin);
    fpsboost::bind<bool, bool>("culling-vertical", c.cullingVertical);
    fpsboost::bind<bool, bool>("disable-glow", c.disableGlow);
    fpsboost::bind<int64_t, int>("particle-cap", c.particleCap);
    fpsboost::bind<bool, bool>("hide-particles", c.hideParticles);
    fpsboost::bind<bool, bool>("skip-shader-calc", c.skipShaderCalc);

    listenForSettingChanges<int64_t>("fps-target", [](int64_t) {
        fpsboost::applyFps();
    });
}
