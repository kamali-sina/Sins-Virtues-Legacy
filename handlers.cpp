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
    cout<<"Complete home block!"<<endl;
}

void handleShopBlock(bool ans, Game &game) {
    cout<<"Complete shop block!"<<endl;
}

void handleBlacksmithBlock(bool ans, Game &game) {
    cout<<"Complete blacksmith block!"<<endl;
}

void handleCastleBlock(bool ans, Game &game) {
    cout<<"Complete castle block!"<<endl;
}

void handleDefault() {
    _error("There was a problem running the handler. error: DEFAULT");
}
