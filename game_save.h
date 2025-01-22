#pragma once
#include "orzel1.h"
#include "licznikpunktow.h"
#include <fstream>

class GameSave {
public:
    static void saveGame(const orzel& o, const licznikpunktow& score, float elapsedTime, const std::string& filename);
    static bool loadGame(orzel& o, licznikpunktow& score, float& elapsedTime, const std::string& filename);
};

