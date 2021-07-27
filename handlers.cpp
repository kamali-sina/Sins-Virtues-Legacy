#include "handlers.hpp"

using namespace std;

void runBlockHandler(bool ans, Game &game) {
    Block *block = game.getBlockAtPlayerLocation();
    switch (block->getID()){
        case NORMALBLOCK:
            handleNormalBlock(ans, game);
            break;
        case HOMEBLOCK:
            handleHomeBlock(ans, game);
            break;
        case SHOPBLOCK:
            handleShopBlock(ans, game);
            break;
        case BLACKSMITHBLOCK:
            handleBlacksmithBlock(ans, game);
            break;
        case CASTLEBLOCK:
            handleCastleBlock(ans, game);
            break;
        default:
            handleDefault();
    }
}

void handleNormalBlock(bool ans, Game &game) {
    if (ans == false) {
        noNormalblockPromptDialog();
        return;
    }
    NormalBlock *normalblock = (NormalBlock*)game.getBlockAtPlayerLocation();
    normalblock->setContainsItem(false);
    normalblock->setHasPrompt(false);
    normalblock->setHasAdjacentDialog(false);
    game.getPlayer()->addItem(normalblock->getItemInside());
    yesNormalblockPromptDialog();
}

void handleHomeBlock(bool ans, Game &game) {
    //TODO: 
    cout<<"Complete home block!"<<endl;
}

void handleShopBlock(bool ans, Game &game) {
    //TODO: 
    cout<<"Complete shop block!"<<endl;
}

void handleBlacksmithBlock(bool ans, Game &game) {
    //TODO: 
    cout<<"Complete blacksmith block!"<<endl;
}

void handleCastleBlock(bool ans, Game &game) {
    //TODO: 
    cout<<"Complete castle block!"<<endl;
}

void handleDefault() {
    _error("There was a problem running the handler. error: DEFAULT");
}

void runItemHandler(Game &game, int inventory_index) {
    UtilityItem* item = (UtilityItem*)game.getPlayer()->getItemAtIndex(inventory_index);
    switch (item->getID()){
        case SHOVEL:
            handleShovel(game, inventory_index);
            break;
        case COMPASS:
            handleCompass(game, inventory_index);
            break;
        case MAP:
            handleMap(game, inventory_index);
            break;
        case STEROID:
            handleSteroid(game, inventory_index);
            break;
        default:
            handleDefault();
    }
}

void handleShovel(Game &game, int inventory_index) {
    game.digHere(inventory_index);    
}

void handleCompass(Game &game, int inventory_index) {
    cout<<game.getMap().compass(game.getPlayer()->getLocation())<<endl;
}

void handleMap(Game &game, int inventory_index) {
    game.getPlayer()->useItem(inventory_index);
    game.getMap().printPartialMap(game.getPlayer()->getVision(), game.getPlayer()->getLocation());    
}

void handleSteroid(Game &game, int inventory_index) {
    game.getPlayer()->useItem(inventory_index);
    int new_max = game.getPlayer()->useSteroid();
    usedSteroidDialog(new_max);
}