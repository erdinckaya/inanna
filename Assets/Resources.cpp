

#include "Resources.h"

Kyo_Salute Resources::KYO_SALUTE;
Pieces Resources::PIECES;
Balls Resources::BALLS;
Death Resources::DEATH;
Fields Resources::FIELDS;
Kyo_Little_Kick Resources::KYO_LITTLE_KICK;


int Resources::SheetCount = 6;

const Sheet Resources::Sheets[6] = {Sheet(Resources::KYO_SALUTE.name, Resources::KYO_SALUTE.path), Sheet(Resources::PIECES.name, Resources::PIECES.path), Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::DEATH.name, Resources::DEATH.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path), Sheet(Resources::KYO_LITTLE_KICK.name, Resources::KYO_LITTLE_KICK.path)};
