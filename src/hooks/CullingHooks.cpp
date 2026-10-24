#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../Settings.hpp"

using namespace geode::prelude;

class $modify(CullPlayLayer, PlayLayer) {
    // GD ya hace su culling; lo ejecutamos primero y luego recortamos más.
    void updateVisibility(float dt) {
        PlayLayer::updateVisibility(dt);

        auto const& c = fpsboost::cfg();
        if (!c.cullingEnabled || !m_objectLayer) return;

        float scale = m_objectLayer->getScale();
        if (scale <= 0.f) return;

        auto win = CCDirector::sharedDirector()->getWinSize();
        auto pos = m_objectLayer->getPosition();

        float left   = -pos.x / scale - c.cullingMargin;
        float right  = (-pos.x + win.width)  / scale + c.cullingMargin;
        float bottom = -pos.y / scale - c.cullingMargin;
        float top    = (-pos.y + win.height) / scale + c.cullingMargin;

        constexpr float kSection = 100.f;
        int first = std::max(0, static_cast<int>(left / kSection) - 1);
        int last  = std::min(static_cast<int>(m_sections.size()) - 1,
                             static_cast<int>(right / kSection) + 1);

        for (int i = first; i <= last; ++i) {
            auto* section = m_sections[i];
            if (!section) continue;

            for (GameObject* obj : *section) {
                if (!obj || !obj->isVisible()) continue;
                // No tocar triggers ni objetos con grupos (pueden moverse/alternarse)
                if (obj->m_isTrigger || obj->m_groupCount > 0) continue;

                auto  p  = obj->getPosition();
                auto  s  = obj->getContentSize();
                float hw = s.width  * 0.5f * std::abs(obj->getScaleX());
                float hh = s.height * 0.5f * std::abs(obj->getScaleY());

                bool outX = (p.x + hw) < left || (p.x - hw) > right;
                bool outY = c.cullingVertical &&
                            ((p.y + hh) < bottom || (p.y - hh) > top);

                if (outX || outY) obj->setVisible(false);
            }
        }
    }
};
