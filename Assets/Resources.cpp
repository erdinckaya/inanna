

#include "Resources.h"

Balls Resources::BALLS;
Fields Resources::FIELDS;
Pieces Resources::PIECES;


int Resources::SheetCount = 3;

const Sheet Resources::Sheets[3] = {Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path), Sheet(Resources::PIECES.name, Resources::PIECES.path)};
