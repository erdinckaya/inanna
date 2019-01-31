

#include "Resources.h"

Pieces Resources::PIECES;
Balls Resources::BALLS;
Death Resources::DEATH;
Fields Resources::FIELDS;
Kyo_Crouch Resources::KYO_CROUCH;
Kyo_Jump Resources::KYO_JUMP;
Kyo_Little_Fist Resources::KYO_LITTLE_FIST;
Kyo_Little_Kick Resources::KYO_LITTLE_KICK;
Kyo_Move_Forward Resources::KYO_MOVE_FORWARD;
Kyo_Move_Back Resources::KYO_MOVE_BACK;
Kyo_Idle Resources::KYO_IDLE;
Kyo_Salute Resources::KYO_SALUTE;


int Resources::SheetCount = 12;

const Sheet Resources::Sheets[12] = {Sheet(Resources::PIECES.name, Resources::PIECES.path), Sheet(Resources::BALLS.name, Resources::BALLS.path), Sheet(Resources::DEATH.name, Resources::DEATH.path), Sheet(Resources::FIELDS.name, Resources::FIELDS.path), Sheet(Resources::KYO_CROUCH.name, Resources::KYO_CROUCH.path), Sheet(Resources::KYO_JUMP.name, Resources::KYO_JUMP.path), Sheet(Resources::KYO_LITTLE_FIST.name, Resources::KYO_LITTLE_FIST.path), Sheet(Resources::KYO_LITTLE_KICK.name, Resources::KYO_LITTLE_KICK.path), Sheet(Resources::KYO_MOVE_FORWARD.name, Resources::KYO_MOVE_FORWARD.path), Sheet(Resources::KYO_MOVE_BACK.name, Resources::KYO_MOVE_BACK.path), Sheet(Resources::KYO_IDLE.name, Resources::KYO_IDLE.path), Sheet(Resources::KYO_SALUTE.name, Resources::KYO_SALUTE.path)};
