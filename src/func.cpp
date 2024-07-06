#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

namespace {
const std::string line{"==============================\n"};
}

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
void welcome() {
  std::cout << std::string_view(line) << "Enter your name: ";

  std::string name{};
  std::getline(std::cin, name);

  std::cout << '\n' << "Good evening, " << name << '\n';
}
choices menu(int money) {
  choices user;
  std::cout << std::string_view(line) << '\n'
            << std::string_view(line) << "WELCOME TO VIRTUAL BACCARAT \n"
            << "PUNTO BANCO TABLE\n"
            << std::string_view(line) << "Current balance, " << money
            << " Tokens\n"
            << "1 - BANKER\n"
            << "2 - PLAYER\n";
  int bet{};
  do {
    std::cout << "Choose your bet: ";
    std::cin >> bet;
  } while (bet != 1 & bet != 2);

  user.bet = bet;

  int betAmount{};
  do {
    std::cout << "Place your bet, Tokens: ";
    std::cin >> betAmount;
  } while (betAmount > money);

  user.betAmount = betAmount;

  std::cout << "\n";

  return user;
}

void cardPrinting(cards user, bool userExCard, bool userNatural,
                  std::string_view name) {
  int sum{(user.firstCard + user.secondCard + user.extraCard) % 10};

  std::cout << std::string_view(line) << "       = " << name << " =\n"
            << std::string_view(line) << '\n'
            << " =========\n"
            << " |       |\n"
            << " |   " << sum << "   |\n"
            << " |       |\n"
            << " =========\n";
  if (userNatural) {
    std::cout << "This is a natural win 8/9\n";
  }
  std::cout << " First Card: " << user.firstCard << '\n'
            << "Second Card: " << user.secondCard << '\n';
  if (userExCard) {
    std::cout << " Extra Card: " << user.extraCard << '\n';
  }
}

int win(bool playerWon, bool bankerWon, choices user, int money) {
  std::cout << std::string_view(line) << '\n';

  if (playerWon & bankerWon) {
    std::cout << "TIE, YOU GET YOUR TOKENS BACK!\n"
              << user.betAmount << " Tokens\n"
              << "Current Tokens: " << money << '\n';
    return money;
  }
  if (playerWon) {
    std::cout << "PlAYER WIN, ";
  }
  if (bankerWon) {
    std::cout << "BANKER WIN, ";
  }

  if (playerWon == false & user.bet == 2) {
    std::cout << "YOU LOSE!\n" << user.betAmount << " Tokens\n";
    money -= user.betAmount;
    std::cout << "Current Tokens: " << money << '\n';

    return money;
  } else if (bankerWon == false & user.bet == 1) {
    std::cout << "YOU LOSE!\n" << user.betAmount << " Tokens\n";
    money -= user.betAmount;
    std::cout << "Current Tokens: " << money << '\n';

    return money;
  } else {
    std::cout << "YOU WIN!\n" << user.betAmount << " Tokens\n";
    money += user.betAmount;
    std::cout << "Current Tokens: " << money << '\n';

    return money;
  }
}

bool askIfContinue(int money) {
  char option{};
  do {
    std::cout << "Try Again y/n? ";
    std::cin >> option;
  } while (option != 'y' & option != 'n');

  if (option == 'y' & money > 0) {
    return true;
  }
  if (option == 'n') {
    return false;
  }
  if (money <= 0) {
    std::cout << "You are broke!\n";
    return false;
  }
  return false;
}
} // namespace print

namespace game {
bool checkForNatural(cards user) {
  int sum{(user.firstCard + user.secondCard) % 10};
  if (sum >= 8) {
    return true;
  }
  return false;
}

bool doPlayerTakeExtraCard(cards user) {
  int sum{(user.firstCard + user.secondCard) % 10};
  if (sum <= 5) {
    return true;
  }
  return false;
}

bool doBankerTakeExtraCard(cards banker, int playerExCard) {
  int sum{(banker.firstCard + banker.secondCard) % 10};
  switch (sum) {
  case 2:
    return true;
  case 3:
    if (playerExCard != 8) {
      return true;
    }
    break;
  case 4:
    if (playerExCard >= 2 & playerExCard <= 7) {
      return true;
    }
    break;
  case 5:
    if (playerExCard >= 4 & playerExCard <= 7) {
      return true;
    }
    break;
  case 6:
    if (playerExCard == 6 | playerExCard == 7) {
      return true;
    }
  }

  return false;
}
} // namespace game

int randCard() {
  int card = 1 + rand() % 13;
  if (card >= 10) {
    return 0;
  }
  return card;
}

cards drawCards() {
  cards cards;

  cards.firstCard = randCard();
  cards.secondCard = randCard();
  cards.extraCard = randCard();

  return cards;
}
