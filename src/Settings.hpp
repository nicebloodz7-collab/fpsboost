#pragma once
#include <Geode/Geode.hpp>

namespace fpsboost {
    struct Config {
        int   fpsTarget       = 240;
        bool  cullingEnabled  = true;
        float cullingMargin   = 60.f;
        bool  cullingVertical = true;
        bool  disableGlow     = false;
        int   particleCap     = 60;
        bool  hideParticles   = false;
        bool  skipShaderCalc  = false;
    };

    inline Config& cfg() {
        static Config c;
        return c;
    }

    // Lee el valor inicial y se suscribe a cambios.
    // T = tipo del setting en Geode, U = tipo del campo destino.
    template <class T, class U>
    void bind(char const* key, U& target) {
        target = static_cast<U>(geode::Mod::get()->getSettingValue<T>(key));
        geode::listenForSettingChanges<T>(key, [&target](T v) {
            target = static_cast<U>(v);
        });
    }

    inline void applyFps() {
        int fps = std::max(1, cfg().fpsTarget);
        cocos2d::CCApplication::sharedApplication()->setAnimationInterval(1.0 / fps);
    }
}
