#pragma once

#include "game/system/MultiDvdArchive.hh"

#include <abstract/List.hh>
#include <egg/core/Scene.hh>

namespace Scene {

class GameScene : public EGG::Scene {
public:
    GameScene();
    ~GameScene() override;

    void calc() final;
    void enter() final;
    void exit() final;
    void reinit() final;

    virtual void createEngines() = 0;
    virtual void initEngines() = 0;
    virtual void calcEngines() = 0;
    virtual void destroyEngines() = 0;
    virtual void configure() = 0;
    virtual void onReinit() {}

protected:
    void appendResource(System::MultiDvdArchive *archive, s32 id);

private:
    struct Resource {
        System::MultiDvdArchive *archive;
        s32 id;
    };

    void initScene();
    void deinitScene();
    void unmountResources();

    Abstract::List m_resources;
    int m_nextSceneId;
};

} // namespace Scene
