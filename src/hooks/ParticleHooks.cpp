#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include "../Settings.hpp"

using namespace geode::prelude;

class $modify(LimitedParticles, CCParticleSystemQuad) {
    // Todos los emisores pasan por acá al crearse.
    bool initWithTotalParticles(unsigned int count, bool useTexture) {
        auto const& c = fpsboost::cfg();
        if (c.particleCap > 0) {
            count = std::min(count, static_cast<unsigned int>(c.particleCap));
        }
        if (!CCParticleSystemQuad::initWithTotalParticles(count, useTexture)) {
            return false;
        }
        if (c.hideParticles) this->setVisible(false);
        return true;
    }
};
