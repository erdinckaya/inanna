

#include "Resources.h"

Pieces Resources::PIECES;


int Resources::SheetCount = 1;

const Sheet Resources::Sheets[1] = {Sheet(Resources::PIECES.name, Resources::PIECES.path)};
