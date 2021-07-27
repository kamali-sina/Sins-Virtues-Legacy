#ifndef _HANDLERS_HPP
#define _HANDLERS_HPP

#include "game.hpp"

void runBlockHandler(bool ans, Game &game);
void handleNormalBlock(bool ans, Game &game);
void handleHomeBlock(bool ans, Game &game);
void handleShopBlock(bool ans, Game &game);
void handleBlacksmithBlock(bool ans, Game &game);
void handleCastleBlock(bool ans, Game &game);
void handleDefault();

void runItemHandler(Game &game, int inventory_index);
void handleShovel(Game &game, int inventory_index);
void handleCompass(Game &game, int inventory_index);
void handleMap(Game &game, int inventory_index);
void handleSteroid(Game &game, int inventory_index);

#endif