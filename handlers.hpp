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

/*
    TODO:
class Shovel(UtilityItem):
    def use(self, game, inventory_index):
        game.dig_here(inventory_index)

class Compass(UtilityItem):
    def use(self, game, inventory_index):
        print(game.map.compass(game.player.location))

class Map(UtilityItem):
    def use(self, game, inventory_index):
        MAP_VISION = 2
        game.player.use_utility(inventory_index)
        game.map.print_partial_map(game.player.location, MAP_VISION)

class Steroid(UtilityItem):
    def use(self, game, inventory_index):
        game.player.use_utility(inventory_index)
        game.player.use_steroid(inventory_index)
        print(f'max hp is now {colored(game.player.max_hp, "red")}')
*/

#endif