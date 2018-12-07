//
// Created by Erdınc Kaya on 2018-12-07.
//

#ifndef INANNA_UIFACTORY_H
#define INANNA_UIFACTORY_H


#include <entityx/Entity.h>
#include <entityx/quick.h>

#include "Widgets/Canvas.h"
#include "../../Assets/Resources.h"
#include "Components/Renderable.h"
#include "Components/Interaction.h"
#include "Components/Scalable.h"
#include "Components/Position.h"
#include "Components/Sizable.h"
#include "Components/Widget.h"


namespace Inanna {
    class UIFactory : public entityx::EntityX {
    public:
        UIFactory() = default;

        entityx::Entity CreateCanvas(Vecf pos = Vecf(0, 0), Vecf size = Vecf(100, 100));
    };
}


#endif //INANNA_UIFACTORY_H
