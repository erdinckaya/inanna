

#include "Resources.h"

Balls Resources::BALLS;
Pieces Resources::PIECES;
Fields Resources::FIELDS;


int Resources::SheetCount = 3;

const Sheet Resources::Sheets[3] = {Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::PIECES.name, Resources::PIECES.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path)};
