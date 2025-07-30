#include <stdio.h>
#include <string.h>

// makes my life easier, less copy paste
#define MAX_USERS 3
#define MAX_MENU_ITEMS 20
#define MAX_MENU_ITEMNAME_LENGTH 80
#define MAX_USERNAME_LENGTH 20

// === GLOBAL VARIABLES ===
int Current_state = 0; // states for the main loop
const int STATE_entry = 0;
const int STATE_about = 1;
const int STATE_login = 2;
const int STATE_menu = 3;
const int STATE_exit = 4;
const int STATE_menu_order = 5;
const int STATE_error = 6;
const int STATE_menu_receipt = 7;
const int STATE_menu_checkout = 8;
const int STATE_menu_checkout_pay = 9;
const int STATE_menu_checkout_discount = 10;
const int STATE_menu_checkout_discount_vipverify = 11;
int menu_nums[MAX_MENU_ITEMS] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
};
char menu_names[MAX_MENU_ITEMS][MAX_MENU_ITEMNAME_LENGTH + 1] = {
    "Quadruple-Patty Bokger Ultra",
    "Hippopotamus",
    "50KG Edible Copper Wire Set",
    "Horse Burger",
    "Eagle Burger",
    "Bread Burger",
    "Bread Sandwich",
    "Bread and Rice",
    "Honey Glazed Chihuahua",
    "3kg Industrial Grad Rootbeer",
    "A drum of Industrial Grade Lubricant",
    "Bok's Hot'n Spicy Ice Cubes",
    "Mahogany Tree Bark Salad",
    "Saging'ng panggising, sinangag at ginisang sinigang",
    "20 7x2' unstable aluminum alloy nails",
    "Intel(R) Core(TM) Ultra 5 125H (8+10)",
    "Turtle Burger",
    "Water Burger",
    "Cynical Cyanide Cider",
    "???",
};
int menu_prices[MAX_MENU_ITEMS] = {
    99, 1999, 29, 199,  1001, 1002, 9, 10, 2999, 1,
    29, 499,  29, 5999, 799,  1,    9, 9,  499,  99999,
};
// inventory per user,
// i can login between them
// and their states are saved
// as long as i dont exit progam
char user_names[MAX_USERS][MAX_USERNAME_LENGTH + 1] = {
    //+1 for null terminator
    "tinus_lorvalds",
    "derry_tavis",
    "dok",
};
char user_pass[MAX_USERS][MAX_USERNAME_LENGTH + 1] = {
    "WindowsIsUseless",
    "GodsChosenProgrammer",
    "bok",
};
float user_bals[MAX_USERS] = {310771.0f, 68.9999f, 4201889.0f};
int user_orders[MAX_USERS][MAX_MENU_ITEMS];
int user_orderCount[MAX_USERS];
int user_isPWD[MAX_USERS];
int user_isSRC[MAX_USERS];
int user_isVIP[MAX_USERS];

int Current_userIndex; // user index for tracking inventory
int Current_failedLogins = 0;
int Current_userOption;
char Current_userName[MAX_USERNAME_LENGTH + 1]; //+1 for null terminator
char Current_userPass[MAX_USERNAME_LENGTH + 1];
float Current_priceToPay;
// === GLOBAL VARIABLES END ===

// === FUNCTIONS ===
void buffer_clear() { // this prevents a lot of bugs with scanf
  int c;
  while ((c = getchar()) != '\n' && c != -1)
    ;
}
void prompt_wait() {
  printf("\n(press enter to continue)");
  buffer_clear();
}
int matches(char c1[], char c2[]) { return strcmp(c1, c2) == 0; }
void init_user_vars(char name[]) {
  for (int i = 0; i < MAX_USERS; i++) {
    if (matches(user_names[i], name)) {
      Current_userIndex = i;
      return;
    }
  }
}
void clear_user_orders() {
  for (int i = 0; i < MAX_MENU_ITEMS; i++) {
    user_orders[Current_userIndex][i] = 0;
  }
}
void error2menu() {
  buffer_clear();
  Current_state = STATE_menu;
  printf("\nBAD input! returning to MENU...\n");
  prompt_wait();
}
void error2entry() {
  buffer_clear();
  Current_state = STATE_entry;
  printf("\nBAD input! returning to ENTRY...\n");
  prompt_wait();
}
int is_valid_login(char n[], char p[]) {
  int is = 0;
  for (int i = 0; i < MAX_USERS; i++) {
    int name_match = matches(n, user_names[i]);
    int pass_match = matches(p, user_pass[i]);
    if (name_match && pass_match) {
      is = 1;
      break;
    }
  }
  return is;
}
void screen_clear() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}
void display_entryOptn() {
  printf("\n  W E L C O M E   T O\n"
         "\n-={ DOKBOK's BOKGER }=-\n\n"
         "1) Login\n"
         "2) About\n"
         "3) Exit\n"
         "Option Number: ");
}
void display_aboutMsg() {
  printf("\n| ABOUT DOKBOK's |\n"
         "This restaurant is the most authentic\n"
         "Not only do we sell the best burgers!\n"
         "But we also sell hardware, which you can eat!\n"
         "And many more *surprises*...\n"
         "ENJOY!\n");
}
void display_exitMsg() { printf("\nSee you next time...\n"); }
void display_menuUI() {
  printf("┌─NUM─NAME─────────────────────────────PRICE─┬─NUM─NAME─────────────"
         "──────────────────────────────────────PRICE─┐\n");
  for (int i = 0; i < 10; i++) {
    printf("│ %03d %-30s %5d ₱ │", menu_nums[i], menu_names[i], menu_prices[i]);
    printf(" %03d %-52s %5d ₱ │\n", menu_nums[i + 10], menu_names[i + 10],
           menu_prices[i + 10]);
  }
  printf("├────────────────────────────────[ DOKBOK's ]┴[ BOKGER "
         "]────────────────────────────────────────────────────────┘\n");
}
void display_menuOptn() {
  printf("├─[BALANCE] %f ₱\n", user_bals[Current_userIndex]);
  printf("├─[MENU]\n"
         "1) Edit Order\n"
         "2) Receipt & Check Out\n"
         "3) Log Out\n"
         "Option Number: ");
}
void display_checkoutOptn() {
  printf("├─[BALANCE] %f ₱\n", user_bals[Current_userIndex]);
  printf("├─[CHECKOUT]\n"
         "1) Pay\n"
         "2) Discounts\n"
         "3) Back to Menu (too expensive?)\n"
         "Option Number: ");
}
void display_paymentOptn() {
  printf("├─[PAID]\n"
         "1) Order again\n"
         "2) Bye bye\n"
         "Option Number: ");
}
void display_receipt() {
  printf("\nOrders (%d):\n", user_orderCount[Current_userIndex]);
  int acc_items = 0;
  int acc_price = 0;
  for (int i = 0; i < MAX_MENU_ITEMS; i++) {
    int quant = user_orders[Current_userIndex][i];
    if (quant == 0) {
      continue;
    }
    char name[MAX_MENU_ITEMNAME_LENGTH + 1];
    strcpy(name, menu_names[i]);
    int price = menu_prices[i];
    int tprice = price * quant;
    printf("  - %d x ", quant);
    printf("%s ", name);
    printf("(%d ₱) | ", price);
    printf("Total: %d ₱\n", tprice);
    acc_price += tprice;
    acc_items += quant;
  }
  float discount = 0.0f;
  if (user_isPWD[Current_userIndex]) {
    discount += 0.08f;
  }
  if (user_isSRC[Current_userIndex]) {
    discount += 0.10f;
  }
  if (user_isVIP[Current_userIndex] > 0) {
    discount += 0.80f;
  } else if (user_isVIP[Current_userIndex] < 0) {
    discount -= 0.80f;
  }
  printf("\nAccumulated:\n");
  printf("  - Item Count: %d\n", acc_items);
  printf("  - Cost: %d ₱\n", acc_price);
  printf("  - Discount: %2f ₱\n", (acc_price * discount));
  Current_priceToPay = acc_price - (acc_price * discount);
  printf("\n┌─[FINAL COST] %2f ₱\n", Current_priceToPay);
}
void display_discounts() {
  printf("\n┌─DISCOUNTS-[I am a... (check all that apply)]\n1) ");
  if (user_isPWD[Current_userIndex]) {
    printf("✓ Person with disability +8%%");
  } else {
    printf("Person with disability");
  }
  printf(" \n2) ");
  if (user_isSRC[Current_userIndex]) {
    printf("✓ Senior Citizen +10%%");
  } else {
    printf("Senior Citizen");
  }
  printf(" \n3) ");
  if (user_isVIP[Current_userIndex] > 0) {
    printf("✓ DOK's VIP +80%%");
  } else if (user_isVIP[Current_userIndex] < 0) {
    printf("! DOK's VIP -80%%");
  } else {
    printf("DOK's VIP");
  }
  printf(" \n4) "
         "Back to checkout\n"
         "Toggle Option: ");
}
void state_loop() {
  switch (Current_state) {
  case STATE_entry:
    screen_clear();
    display_entryOptn();
    if (scanf("%d", &Current_userOption) != 1) {
      error2entry();
      break;
    }
    buffer_clear();
    switch (Current_userOption) {
    case 1:
      Current_state = STATE_login;
      break;
    case 2:
      Current_state = STATE_about;
      break;
    default:
      Current_state = STATE_exit;
      break;
    }
    break;

  case STATE_about:
    screen_clear();
    display_aboutMsg();
    prompt_wait();
    Current_state = STATE_entry;
    break;

  case STATE_login: {
    printf("Username: ");
    if (scanf("%20s", Current_userName) != 1) {
      error2entry();
      break;
    }
    buffer_clear();
    printf("Password: ");
    if (scanf("%20s", Current_userPass) != 1) {
      error2entry();
      break;
    }
    buffer_clear();
    if (is_valid_login(Current_userName, Current_userPass)) {
      init_user_vars(Current_userName);
      Current_state = STATE_menu;
    } else {
      printf("\n| INVALID LOGIN, attempts remaining: %d |\ns t a y   o u t\n",
             2 - Current_failedLogins);
      Current_failedLogins++;
      prompt_wait();
      if (Current_failedLogins > 2) {
        Current_state = STATE_exit;
      } else {
        Current_state = STATE_entry;
      }
    }
  } break;

  case STATE_menu:
    screen_clear();
    display_menuUI();
    display_menuOptn();
    if (scanf("%d", &Current_userOption) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    switch (Current_userOption) {
    case 1:
      printf("└─────┐\n");
      Current_state = STATE_menu_order;
      break;
    case 2:
      Current_state = STATE_menu_receipt;
      break;
    default:
      Current_state = STATE_entry;
      break;
    }
    break;

  case STATE_menu_order: {
    printf("ENTER │ item number (000-019): ");
    int order_num;
    if (scanf("%d", &order_num) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    if (order_num < 0 || order_num > MAX_MENU_ITEMS - 1) {
      printf("YIKES │ That ain't in the menu buddy.\n");
      break;
    }
    int cur_quant = user_orders[Current_userIndex][order_num];
    printf("ENTER │ change quantity of '%s' (current: %d): ",
           menu_names[order_num], cur_quant);
    int new_quant;
    if (scanf("%d", &new_quant) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    if (new_quant < 1) {
      if (cur_quant < 1) {
        printf("YIKES │ Already at 0 buddy.\n");
      } else {
        printf("REMOV │ Removing order %s\n", menu_names[order_num]);
      }
      user_orders[Current_userIndex][order_num] = 0;
    } else {
      printf("ADDED │ Order of %d of %s\n", new_quant, menu_names[order_num]);
      user_orders[Current_userIndex][order_num] = new_quant;
    }
    printf("ORDER │ edit another item? (yes=1/no=0): ");
    if (scanf("%d", &Current_userOption) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    if (Current_userOption == 1) {
      Current_state = STATE_menu_order;
    } else {
      Current_state = STATE_menu;
    }
  } break;

  case STATE_menu_receipt: {
    screen_clear();
    user_orderCount[Current_userIndex] = 0;
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
      if (user_orders[Current_userIndex][i] > 0) {
        user_orderCount[Current_userIndex]++;
      }
    }
    if (user_orderCount[Current_userIndex] == 0) {
      printf("\nCheckout? Order something first! >:(\n");
      prompt_wait();
      Current_state = STATE_menu;
    } else {
      Current_state = STATE_menu_checkout;
    }
  } break;

  case STATE_menu_checkout: {
    screen_clear();
    display_receipt();
    display_checkoutOptn();
    if (scanf("%d", &Current_userOption) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    switch (Current_userOption) {
    case 1:
      Current_state = STATE_menu_checkout_pay;
      break;
    case 2:
      Current_state = STATE_menu_checkout_discount;
      break;
    default:
      Current_state = STATE_menu;
      break;
    }
  } break;

  case STATE_menu_checkout_pay: {
    screen_clear();
    if (user_bals[Current_userIndex] < Current_priceToPay) {
      printf("\nYou're broke :( Change your order!\n");
      prompt_wait();
      Current_state = STATE_menu_checkout;
      break;
    } else {
      float old_bal = user_bals[Current_userIndex];
      user_bals[Current_userIndex] -= Current_priceToPay;
      printf("\nSuccesfully Paid! Thank you for buying at DOKBOK's BOKGER\n");
      printf("\n┌─[OLD BALANCE] %f ₱\n", old_bal);
      printf("├─[NEW BALANCE] %f ₱\n", user_bals[Current_userIndex]);
      display_paymentOptn();
      if (scanf("%d", &Current_userOption) != 1) {
        error2menu();
        break;
      }
      buffer_clear();
      clear_user_orders();
      if (Current_userOption == 1) {
        Current_state = STATE_menu;
      } else {
        Current_state = STATE_exit;
      }
    }
  } break;

  case STATE_menu_checkout_discount: {
    screen_clear();
    display_discounts();
    if (scanf("%d", &Current_userOption) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    switch (Current_userOption) {
    case 1:
      user_isPWD[Current_userIndex] = !user_isPWD[Current_userIndex];
      break;
    case 2:
      user_isSRC[Current_userIndex] = !user_isSRC[Current_userIndex];
      break;
    case 3:
      if (user_isVIP[Current_userIndex] > 0) {
        user_isVIP[Current_userIndex] = !user_isVIP[Current_userIndex];
      } else {
        Current_state = STATE_menu_checkout_discount_vipverify;
      }
      break;
    default:
      Current_state = STATE_menu_checkout;
      break;
    }
  } break;

  case STATE_menu_checkout_discount_vipverify: {
    printf("\nProve yourself.\n");
    printf("What is dok's favorite bok?: ");
    char sec[4];
    if (scanf("%3s", sec) != 1) {
      error2menu();
      break;
    }
    buffer_clear();
    if (matches(sec, "bok")) {
      printf("\nWelcome home, King.\n");
      user_isVIP[Current_userIndex] = 1;
    } else {
      printf("\n⚠ Liar and fraud detected, added negative discount >:(\n");
      user_isVIP[Current_userIndex] = -1;
    }
    prompt_wait();
    Current_state = STATE_menu_checkout_discount;
  } break;
  }
}
int main() {
  while (Current_state != STATE_exit) {
    state_loop();
  }
  display_exitMsg();
  return 0;
}
