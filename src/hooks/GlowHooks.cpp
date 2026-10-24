#include <Geode/Geode.hpp>
#include <Geode/modify/GameObject.hpp>
#include "../Settings.hpp"

using namespace geode::prelude;

class $modify(GlowGameObject, GameObject) {
    void setVisible(bool visible) {
        GameObject::setVisible(visible);
        if (fpsboost::cfg().disableGlow && m_glowSprite) {
            m_glowSprite->setVisible(false);
        }
    }
};
