//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "UIFactory.h"

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
