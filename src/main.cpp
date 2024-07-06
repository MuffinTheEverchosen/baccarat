#include "func.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>

int main() {
  srand(time(NULL));
  // initialize variables
  int money{10000};
  choices user;
  bool playerWon{};
  bool bankerWon{};
  bool playerExtraCard{};
  bool bankerExtraCard{};
  bool playerNatural{};
  bool bankerNatural{};
  bool playing{true};

  // start of printing
  print::welcome();
  // drawingCards
  do {
    user = print::menu(money);

    cards player = drawCards();
    cards banker = drawCards();

    // check neutrals
    playerWon = game::checkForNatural(player);
    bankerWon = game::checkForNatural(banker);
    playerNatural = playerWon;
    bankerNatural = bankerWon;

    // was extra card drawn?
    playerExtraCard = game::doPlayerTakeExtraCard(player);
    if (playerExtraCard) {
      bankerExtraCard = game::doBankerTakeExtraCard(banker, player.extraCard);
    } else {
      bankerExtraCard = game::doPlayerTakeExtraCard(banker);
    }

    // check for winner if no neutrals
    if (!playerExtraCard) {
      player.extraCard = 0;
    }
    if (!bankerExtraCard) {
      banker.extraCard = 0;
    }

    if (!playerWon & !bankerWon) {
      int playerSum{(player.firstCard + player.secondCard + player.extraCard) %
                    10};
      int bankerSum{(banker.firstCard + banker.secondCard + banker.extraCard) %
                    10};

      if (playerSum > bankerSum) {
        playerWon = true;
      }
      if (bankerSum > playerSum) {
        bankerWon = true;
      }
      if (bankerSum == playerSum) {
        playerWon = true;
        bankerWon = true;
      }
    }
    // card printing
    print::cardPrinting(banker, bankerExtraCard, bankerNatural, "BANKER");
    print::cardPrinting(player, playerExtraCard, playerNatural, "PLAYER");

    // declare winner
    money = print::win(playerWon, bankerWon, user, money);

    playing = print::askIfContinue(money);
  } while (playing);
}
