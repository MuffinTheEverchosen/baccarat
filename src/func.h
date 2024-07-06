#ifndef FUNCTIONS
#define FUNCTIONS
#include <string_view>
struct choices {
  int bet;
  int betAmount;
};

struct cards {
  int firstCard;
  int secondCard;
  int extraCard;
};

namespace print {
void welcome();
choices menu(int money);
void cardPrinting(cards user, bool userExCard, bool userNatural,
                  std::string_view name);
int win(bool playerWon, bool bankerWon, choices user, int money);
bool askIfContinue(int money);
} // namespace print

namespace game {
bool checkForNatural(cards user);
bool doPlayerTakeExtraCard(cards user);
bool doBankerTakeExtraCard(cards banker, int playerExCard);
} // namespace game

int randCard();
cards drawCards();
#endif // !FUNCTIONS
