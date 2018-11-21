

#include "Resources.h"

Pieces Resources::PIECES;


int Resources::SheetCount = 1;

static const std::string TMP_Sheets[] = {Resources::PIECES.name};
const std::string* Resources::Sheets = TMP_Sheets;
