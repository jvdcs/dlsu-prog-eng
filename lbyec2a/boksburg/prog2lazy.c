#include <stdio.h>
#include <string.h>

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

char displays[10][3000] = {
    "\n| DOKBOK's BOKGER |\n"
    "1) Login\n"
    "2) About\n"
    "3) Exit\n"
    "Your Option: ",

    "\n| ABOUT DOKBOK's |\n"
    "This restaurant is the most authentic\n"
    "Not only do we sell the best burgers!\n"
    "But we also sell hardware, which you can eat\n"
    "...and many more surprises!\n"
    "ENJOY!\n",

    "\ny o u   w i l l   r e g r e t   t h i s ...\n",

    "\n"
    "┌─NUM─NAME───────────────────────────────────PRICE──┬──NUM─NAME───────────"
    "───────────────────────────────────────PRICE─┐\n"
    "│ 000 Quadruple-Patty Bokger Ultra            99 ₱  │  001 Hippopotamus   "
    "                                      1999 ₱ │\n"
    "│ 002 50KG Edible Copper Wire Set             29 ₱  │  003 Horse Burger   "
    "                                       199 ₱ │\n"
    "│ 004 Eagle Burger                          1001 ₱  │  005 Bread Burger   "
    "                                      1002 ₱ │\n"
    "│ 006 Bread Sandwich                           9 ₱  │  007 Bread and Rice "
    "                                        10 ₱ │\n"
    "│ 008 Honey Glazed Chihuahua                2999 ₱  │  009 3kg Industrial "
    "Grad Rootbeer                            1 ₱ │\n"
    "│ 010 A drum of Industrial Grade Lubricant    29 ₱  │  011 Bok's Hot'n "
    "Spicy Ice Cubes                           499 ₱ │\n"
    "│ 012 Mahogany Tree Bark Salad                29 ₱  │  013 Saging'ng "
    "panggising, sinangag at ginisang sinigang  5999 ₱ │\n"
    "│ 014 20 7x2' unstable aluminum alloy nails  799 ₱  │  015 Intel(R) "
    "Core(TM) Ultra 5 125H (8+10)                   1 ₱ │\n"
    "│ 016 Turtle Burger                            9 ₱  │  017 Water Burger   "
    "                                         9 ₱ │\n"
    "│ 018 Cynical Cyanide Cider                  499 ₱  │  019 ???            "
    "                                     99999 ₱ │\n"
    "├───────────────────────────────────────< DOKBOK's >┴< BOKGER "
    ">────────────────────────────────────────────────────────┘\n",

    "│\n"
    "├─MENU\n"
    "1) Edit Order\n"
    "2) Receipt & Check Out\n"
    "3) Log Out\n"
    "Your Option: ",

    "\n"
    "┌─CHECKOUT\n"
    "1) Pay\n"
    "2) Discounts\n"
    "3) Back to Menu (too expensive?)\n"
    "Your Option: ",

    "\n"
    "┌─DISCOUNTS-(i am a ... check all that apply):\n"
    "1) Person with disability"
    "2) Senior Citizen"
    "3) DOK's VIP"
    "4) Back to Checkout (im normal)\n"
    "Your Option: ",
};
int menu_nums[20] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
};
char menu_names[20][80 + 1] = {
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
int menu_prices[20] = {
    99, 1999, 29, 199,  1001, 1002, 9, 10, 2999, 1,
    29, 499,  29, 5999, 799,  1,    9, 9,  499,  99999,
};

// + 1 for the annoying null terminator
char user_names[3][20 + 1] = {
    "tinus_lorvalds",
    "derry_tavis",
    "dok",
};
char user_pass[3][20 + 1] = {
    "WindowsIsUseless",
    "GodsChosenProgrammer",
    "bok",
};
int user_bals[3] = {210945, 68, 99999999};
int user_menus[3][20];
int user_index;
float user_discounts = 0;

void init_user_index(char name[]) {
  for (int i = 0; i < 3; i++) {
    if (strcmp(user_names[i], name) == 0) {
      user_index = i;
      return;
    }
  }
}

// this prevents a lot of bugs
void buffer_clear() {
  int c;
  while ((c = getchar()) != '\n' && c != -1)
    ;
}

void prompt_wait() {
  printf("\n(press enter to continue)");
  buffer_clear();
}

int matches(char c1[], char c2[]) { return strcmp(c1, c2) == 0; }
int isValid_login(char n[], char p[]) {
  int is = 0;
  for (int i = 0; i < 3; i++) {
    int name_match = matches(n, user_names[i]);
    int pass_match = matches(p, user_pass[i]);
    if (name_match && pass_match) {
      is = 1;
      break;
    }
  }
  return is;
}

void display_entry() { printf("%s", displays[0]); }
void display_about() { printf("%s", displays[1]); }
void display_exit() { printf("%s", displays[2]); }
void display_menu() { printf("%s", displays[3]); }
void display_menuOptn() { printf("%s", displays[4]); }
void display_checkoutOptn() { printf("%s", displays[5]); }
int main() {
  int _s = STATE_entry;
  int failed_logins = 0;

  int usr_optn;
  // +1 for the annoying null terminator
  char usr_name[20 + 1];
  char usr_pass[20 + 1];

  while (_s != STATE_exit) {
    switch (_s) {
    case STATE_entry:
      display_entry();
      if (scanf("%d", &usr_optn) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      switch (usr_optn) {
      case 1:
        _s = STATE_login;
        break;
      case 2:
        _s = STATE_about;
        break;
      default:
        _s = STATE_exit;
        break;
      }
      break;

    case STATE_about:
      display_about();
      prompt_wait();
      _s = STATE_entry;
      break;

    case STATE_login: {
      printf("Username: ");
      if (scanf("%20s", usr_name) != 1) {
        _s = STATE_entry;
        break;
      }
      buffer_clear();
      printf("Password: ");
      if (scanf("%20s", usr_pass) != 1) {
        _s = STATE_entry;
        break;
      }
      buffer_clear();
      if (isValid_login(usr_name, usr_pass)) {
        printf("\nLogin Successful!\n");
        init_user_index(usr_name);
        _s = STATE_menu;
      } else {
        printf(
            "\n| INVALID LOGIN, attempts remaining: %d |\n\ns t a y   o u t\n",
            2 - failed_logins);
        failed_logins++;
        _s = STATE_entry;
      }
      if (failed_logins > 2) {
        _s = STATE_exit;
      }
    } break;

    case STATE_menu:
      display_menu();
      display_menuOptn();
      if (scanf("%d", &usr_optn) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      switch (usr_optn) {
      case 1:
        _s = STATE_menu_order;
        break;
      case 2:
        _s = STATE_menu_receipt;
        break;
      default:
        _s = STATE_entry;
        break;
      }
      break;

    case STATE_menu_order: {
      int order_num;
      printf("ENTER | item number (000-019): ");
      if (scanf("%d", &order_num) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (order_num < 0 || order_num > 19) {
        printf("YIKES | That ain't in the menu buddy.\n");
        break;
      }
      int cur_quant = user_menus[user_index][order_num];
      printf("ENTER | change quantity (current: %d): ", cur_quant);
      int new_quant;
      if (scanf("%d", &new_quant) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (new_quant < 1) {
        printf("REMOV | Removing item %s\n", menu_names[order_num]);
        user_menus[order_num][user_index] = 0;
      } else {
        printf("ADDED | %d of %s\n", new_quant, menu_names[order_num]);
        user_menus[order_num][user_index] = new_quant;
      }
      printf("ORDER | edit another item? (yes=1/no=0): ");
      if (scanf("%d", &usr_optn) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (usr_optn == 1) {
        _s = STATE_menu_order;
      } else {
        _s = STATE_menu;
      }
    } break;

    case STATE_menu_receipt: {
      int count_order = 0;
      for (int i = 0; i < 20; i++) {
        if (user_menus[i] > 0) {
          count_order++;
        }
      }
      if (count_order == 0) {
        printf("\nCheckout? Order something first! >:(\n");
        _s = STATE_menu;
        prompt_wait();
      } else {
        printf("\nOrders (%d):\n", count_order);
        int acc_items = 0;
        int acc_price = 0;
        for (int i = 0; i < 20; i++) {
          int quant = user_menus[user_index][i];
          if (quant == 0) {
            continue;
          }
          char name[80 + 1];
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
        printf("\nAccumulated:\n");
        printf("  - Item Count: %d\n", acc_items);
        printf("  - Cost: %d ₱\n", acc_price);
        _s = STATE_menu_checkout;
      }
    } break;

    case STATE_menu_checkout: {
      display_checkoutOptn();
      if (scanf("%d", &usr_optn) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      switch (usr_optn) {
      case 1:
        _s = STATE_menu_checkout_pay;
        break;
      case 2:
        _s = STATE_menu_checkout_discount;
        break;
      default:
        _s = STATE_menu;
        break;
      }
    } break;

    case STATE_menu_checkout_pay: {

    } break;

    case STATE_menu_checkout_discount: {
      if (scanf("%d", &usr_optn) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      switch (usr_optn) {
      case 1:
        user_discounts += 0.10f;
        break;
      case 2:
        user_discounts = 0.15f;
        break;
      case 3:
        user_discounts = 0.98f;
        break;
      default:
        _s = STATE_menu_checkout;
        break;
      }
    } break;

    case STATE_error:
      printf("\n⚠ Uh oh! You made an error ⚠\n");
      _s = STATE_exit;
      break;

    default:
      printf("\nUnknown program state, Exiting.\n");
      _s = STATE_exit;
      break;
    }
  }

  display_exit();
  return 0;
}
