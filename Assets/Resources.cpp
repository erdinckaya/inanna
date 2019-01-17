

#include "Resources.h"

Balls Resources::BALLS;
Death Resources::DEATH;
Fields Resources::FIELDS;
Pieces Resources::PIECES;


int Resources::SheetCount = 4;

const Sheet Resources::Sheets[4] = {Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::DEATH.name, Resources::DEATH.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path), Sheet(Resources::PIECES.name, Resources::PIECES.path)};
