#include <stdio.h>
#include <string.h>

const int STATE_ENTRY = 0;
const int STATE_ABOUT = 1;
const int STATE_LOGIN = 2;
const int STATE_MENU = 3;
const int STATE_EXIT = 4;

char displays[4][1000] = {
    "\n[ DOKBOK's BOKGER ]\n"
    ": l      > Login\n"
    ": a      > About\n"
    ": ...    > Exit\n"
    "Your Option: ",

    "\n[ ABOUT DOKBOK's ]\n"
    ": This restaurant is the most authentic\n"
    ": Not only do we sell the best burgers!\n"
    ": But we also sell hardware, which you can eat.\n"
    ": ...And many more surprises!\n"
    ": ENJOY!\n",

    "\ny o u   w i l l   r e g r e t   t h i s ...\n",
};
char menuCodes[20][4] = {
    "001", "002", "003", "004", "005", "006", "007", "008", "009", "010",
    "011", "012", "013", "014", "015", "016", "017", "018", "019", "020",
};
int menuPrices[20] = {
    99, 1999, 29, 199,  1001, 1002, 9, 10, 2999, 1,
    29, 499,  29, 5999, 799,  1,    9, 9,  499,  99999,
};
char menuItems[20][100] = {
    "Quadruple-Patty Bokger Ultra",
    "Hippopotamus",
    "50KG Edible Copper Wire Set",
    "Horse Burger",
    "Eagle Burger",
    "Bread Burger",
    "Bread Sandwich",
    "Bread and Rice",
    "Honey Glazed Chihuahua",
    "3kg Industrial Grade Rootbeer",
    "A drum of Industrial Grade Lubricant",
    "Bok's Hot'n Spicy Ice Cubes",
    "Mahogany Tree Bark Salad",
    "Saging na panggising at sinangag na may ginisang sinigang",
    "20 7x2' unstable aluminum alloy nails",
    "Intel(R) Core(TM) Ultra 5 125H (8+10)",
    "Turtle Burger",
    "Water Burger",
    "Cynical Cyanide Cider",
    "???",
};

int digitCount(int n) {
  if (n == 0) {
    return 1;
  } else {
    int count = 0;
    while (n != 0) {
      n /= 10;
      count++;
    }
    return count;
  }
}

void menuDisplay() {
  printf("\n[ M E N U ]\n\n");

  for (int i = 0; i < 20; i += 2) {
    int len1 = strlen(menuCodes[i]) + 1 + strlen(menuItems[i]) + 1 +
               digitCount(menuPrices[i]);
    printf("%s %s %d", menuCodes[i], menuItems[i], menuPrices[i]);

    int distfromlongest = 3;
    int padding = 60 - len1;
    if (padding < 1)
      padding = 1;

    for (int j = 0; j < padding; j++)
      putchar(' ');

    printf("%s %s %d\n", menuCodes[i + 1], menuItems[i + 1], menuPrices[i + 1]);
  }
}

char names[3][20] = {
    "tinus_lorvalds",
    "derry_tavis",
    "parkus_mersson",
};
char pass[3][20] = {
    "WindowsIsUseless",
    "GodsChosenProgrammer",
    "DepressedBillionaire",
};
int nameCount = sizeof(names) / sizeof(names[0]);

void entryDisplay() { printf("%s", displays[0]); }
void aboutDisplay() { printf("%s", displays[1]); }
void exitDisplay() { printf("%s", displays[2]); }
void waitPrompt() {
  printf("\n(press enter to continue)");
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
  }
}

int readInput(char buffer[]) {
  if (scanf("%s", buffer) == -1) {
    buffer[0] = '\0';
    return 0;
  }
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
  return 1;
}

int matches(char c1[], char c2[]) { return strcmp(c1, c2) == 0; }
int isValidLogin(char n[], char p[]) {
  int is = 0;
  for (int i = 0; i < nameCount; i++) {
    int nameMatch = matches(n, names[i]);
    int passMatch = matches(p, pass[i]);
    if (nameMatch && passMatch) {
      is = 1;
      break;
    }
  }
  return is;
}

int main() {
  int _s = STATE_ENTRY;
  int failedLogins = 0;

  char opt_buffer[1];
  char username_buffer[20];
  char password_buffer[20];

  while (_s != STATE_EXIT) {
    switch (_s) {
    case STATE_ENTRY:
      // asdfs
      menuDisplay();
      // asdfs
      entryDisplay();
      if (!readInput(opt_buffer)) {
        _s = STATE_EXIT;
        break;
      }

      if (matches("l", opt_buffer)) {
        _s = STATE_LOGIN;
      } else if (matches("a", opt_buffer)) {
        _s = STATE_ABOUT;
      } else {
        _s = STATE_EXIT;
      }
      break;

    case STATE_ABOUT:
      aboutDisplay();
      waitPrompt();
      _s = STATE_ENTRY;
      break;

    case STATE_LOGIN: {
      printf("Username: ");
      if (!readInput(username_buffer)) {
        _s = STATE_ENTRY;
        break;
      }
      if (strlen(username_buffer) == 0) {
        _s = STATE_ENTRY;
        break;
      }

      printf("Password: ");
      if (!readInput(password_buffer)) {
        _s = STATE_ENTRY;
        break;
      }
      if (strlen(password_buffer) == 0) {
        _s = STATE_ENTRY;
        break;
      }

      if (isValidLogin(username_buffer, password_buffer)) {
        printf("\nLogin Successful!\n");
        _s = STATE_MENU;
      } else {
        printf("\n[ INVALID LOGIN, attempts remaining: %d ]"
               "\n"
               "\ns t a y   o u t"
               "\n",
               2 - failedLogins);
        failedLogins++;
        _s = STATE_ENTRY;
      }

      if (failedLogins > 2) {
        _s = STATE_EXIT;
        break;
      }
    } break;

    case STATE_MENU:
      menuDisplay();
      waitPrompt();
      _s = STATE_ENTRY;
      break;

    default:
      printf("Unknown program state, Exiting.\n");
      _s = STATE_EXIT;
      break;
    }
  }

  exitDisplay();
  return 0;
}
