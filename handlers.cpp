#include "handlers.hpp"

using namespace std;

void handleNormalBlock(bool ans, Game &game){
    if (ans == false){
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