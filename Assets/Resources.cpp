

#include "Resources.h"

Balls Resources::BALLS;
Death Resources::DEATH;
Fields Resources::FIELDS;
Kyo_Little_Kick Resources::KYO_LITTLE_KICK;
Kyo_Move_Back Resources::KYO_MOVE_BACK;
Kyo_Move_Forward Resources::KYO_MOVE_FORWARD;
Kyo_Salute Resources::KYO_SALUTE;
Pieces Resources::PIECES;


int Resources::SheetCount = 8;

const Sheet Resources::Sheets[8] = {Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::DEATH.name, Resources::DEATH.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path), Sheet(Resources::KYO_LITTLE_KICK.name, Resources::KYO_LITTLE_KICK.path), Sheet(Resources::KYO_MOVE_BACK.name, Resources::KYO_MOVE_BACK.path), Sheet(Resources::KYO_MOVE_FORWARD.name, Resources::KYO_MOVE_FORWARD.path), Sheet(Resources::KYO_SALUTE.name, Resources::KYO_SALUTE.path), Sheet(Resources::PIECES.name, Resources::PIECES.path)};
