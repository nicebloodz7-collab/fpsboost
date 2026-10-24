#include <Geode/Geode.hpp>
#include <Geode/modify/ShaderLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../Settings.hpp"

using namespace geode::prelude;

class $modify(LeanShaderLayer, ShaderLayer) {
    // EXPERIMENTAL: los niveles con shader triggers pueden verse distintos.
    void performCalculations() {
        if (fpsboost::cfg().skipShaderCalc) return;
        ShaderLayer::performCalculations();
    }
};

// Aplica el intervalo de FPS una vez al arrancar el juego
class $modify(FpsMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        static bool done = false;
        if (!done) { fpsboost::applyFps(); done = true; }
        return true;
    }
};
