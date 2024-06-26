#include "KartSuspension.hh"

namespace Kart {

KartSuspension::KartSuspension() = default;

KartSuspension::~KartSuspension() {
    delete m_physics;
}

void KartSuspension::init(u16 wheelIdx, u16 bspWheelIdx) {
    m_physics = new KartSuspensionPhysics(wheelIdx, bspWheelIdx);
}

void KartSuspension::initPhysics() {
    m_physics->init();
}

void KartSuspension::setInitialState() {
    m_physics->setInitialState();
}

KartSuspensionPhysics *KartSuspension::suspPhysics() {
    return m_physics;
}

KartSuspensionFrontBike::KartSuspensionFrontBike() = default;

KartSuspensionFrontBike::~KartSuspensionFrontBike() = default;

KartSuspensionRearBike::KartSuspensionRearBike() = default;

KartSuspensionRearBike::~KartSuspensionRearBike() = default;

} // namespace Kart
