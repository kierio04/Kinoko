#include "RaceManager.hh"

#include "game/system/CourseMap.hh"
#include "game/system/KPadDirector.hh"
#include "game/system/map/MapdataStartPoint.hh"

namespace System {

void RaceManager::findKartStartPoint(EGG::Vector3f &pos, EGG::Vector3f &angles) {
    // For time trials and ghost race
    // When expanding to other gamemodes, we will need the player index
    u32 placement = 1;
    u32 playerCount = 1;
    u32 startPointIdx = 0;

    MapdataStartPoint *kartpoint = CourseMap::Instance()->getStartPoint(startPointIdx);

    if (kartpoint) {
        kartpoint->findKartStartPoint(pos, angles, placement - 1, playerCount);
    } else {
        pos.setZero();
        angles = EGG::Vector3f::ex;
    }
}

void RaceManager::calc() {
    constexpr u16 STAGE_INTRO_DURATION = 172;

    switch (m_stage) {
    case Stage::Intro:
        if (++m_introTimer >= STAGE_INTRO_DURATION) {
            m_stage = Stage::Countdown;
            KPadDirector::Instance()->startGhostProxies();
        }
        break;
    case Stage::Countdown:
        if (++m_timer >= STAGE_COUNTDOWN_DURATION) {
            m_stage = Stage::Race;
        }
        break;
    case Stage::Race:
        ++m_timer;
        break;
    default:
        break;
    }
}

bool RaceManager::isStageReached(Stage stage) const {
    return static_cast<std::underlying_type_t<Stage>>(m_stage) >=
            static_cast<std::underlying_type_t<Stage>>(stage);
}

int RaceManager::getCountdownTimer() const {
    return STAGE_COUNTDOWN_DURATION - m_timer;
}

const RaceManagerPlayer &RaceManager::player() const {
    return m_player;
}

RaceManager::Stage RaceManager::stage() const {
    return m_stage;
}

RaceManager *RaceManager::CreateInstance() {
    assert(!s_instance);
    s_instance = new RaceManager;
    return s_instance;
}

RaceManager *RaceManager::Instance() {
    return s_instance;
}

void RaceManager::DestroyInstance() {
    assert(s_instance);
    delete s_instance;
    s_instance = nullptr;
}

RaceManager::RaceManager() : m_stage(Stage::Intro), m_introTimer(0), m_timer(0) {}

RaceManager::~RaceManager() = default;

RaceManagerPlayer::RaceManagerPlayer() {
    m_inputs = &KPadDirector::Instance()->playerInput();
}

const KPad *RaceManagerPlayer::inputs() const {
    return m_inputs;
}

RaceManager *RaceManager::s_instance = nullptr;

} // namespace System
