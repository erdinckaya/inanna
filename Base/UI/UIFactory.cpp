//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "UIFactory.h"
#include "Components/RenderFrame.h"


entityx::Entity Inanna::UIFactory::CreateCanvas(Vecf pos, Vecf size) {
    auto entity = entities.create();
    entity.assign<Canvas>();
    entity.assign<Widget>();
    entity.assign<Renderable>();
    entity.assign<Interaction>();
    entity.assign<Position>(pos);
    entity.assign<Sizable>(size);
    entity.assign<Scalable>();

    return entity;
}

entityx::Entity Inanna::UIFactory::CreateButton(Vecf pos, Vecf size) {
    auto entity = entities.create();
    entity.assign<Button>();
    entity.assign<Widget>();
    entity.assign<Renderable>();
    entity.assign<Interaction>();
    entity.assign<Position>(pos);
    entity.assign<Sizable>(size);
    entity.assign<Scalable>();

    return entity;
}
