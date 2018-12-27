//
// Created by Erdınc Kaya on 2018-12-07.
//

#include "UIFactory.h"
#include "MouseEventComponents/MouseDrag.h"
#include "Widgets/ScrollBar.h"


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
    auto entity = CreateCanvas(pos, size);
    entity.assign<Button>();
    return entity;
}

entityx::Entity Inanna::UIFactory::CreateStack(const DirectionType &direction, Vecf pos, Vecf size) {
    auto entity = CreateCanvas(pos, size);
    entity.assign<Stack>(direction);
    return entity;
}

entityx::Entity Inanna::UIFactory::CreateScrollViewer(const DirectionType &direction, Vecf pos, Vecf size) {
    auto entity = CreateCanvas(pos, size);
    entity.assign<ScrollViewer>();
    return entity;
}

entityx::Entity Inanna::UIFactory::CreateScrollViewer(Vecf pos, Vecf size) {
    auto entity = CreateCanvas(pos, size);
    entity.assign<ScrollViewer>();
    entity.assign<ScrollBar>(DirectionType::HorizontalVertical);

    return entity;
}
