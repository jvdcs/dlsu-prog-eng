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

char displays[6][3000] = {
    "\n| DOKBOK's BOKGER |\n"
    "1)  Login\n"
    "2)  About\n"
    "... Exit\n"
    "Your Option: ",

    "\n| ABOUT DOKBOK's |\n"
    "This restaurant is the most authentic\n"
    "Not only do we sell the best burgers!\n"
    "But we also sell hardware, which you can eat\n"
    "...and many more surprises!\n"
    "ENJOY!\n",

    "\ny o u   w i l l   r e g r e t   t h i s ...\n",

    "\n"
    "┌─NUM─NAME───────────────────────────────────PRICE──┬──NUM─NAME──────────────────────────────────────────────────PRICE─┐\n"
    "│ 001 Quadruple-Patty Bokger Ultra            99 ₱  │  002 Hippopotamus                                         1999 ₱ │\n"
    "│ 003 50KG Edible Copper Wire Set             29 ₱  │  004 Horse Burger                                          199 ₱ │\n"
    "│ 005 Eagle Burger                          1001 ₱  │  006 Bread Burger                                         1002 ₱ │\n"
    "│ 007 Bread Sandwich                           9 ₱  │  008 Bread and Rice                                         10 ₱ │\n"
    "│ 009 Honey Glazed Chihuahua                2999 ₱  │  010 3kg Industrial Grad Rootbeer                            1 ₱ │\n"
    "│ 011 A drum of Industrial Grade Lubricant    29 ₱  │  012 Bok's Hot'n Spicy Ice Cubes                           499 ₱ │\n"
    "│ 013 Mahogany Tree Bark Salad                29 ₱  │  014 Saging'ng panggising, sinangag at ginisang sinigang  5999 ₱ │\n"
    "│ 015 20 7x2' unstable aluminum alloy nails  799 ₱  │  016 Intel(R) Core(TM) Ultra 5 125H (8+10)                   1 ₱ │\n"
    "│ 017 Turtle Burger                            9 ₱  │  018 Water Burger                                            9 ₱ │\n"
    "│ 019 Cynical Cyanide Cider                  499 ₱  │  020 ???                                                 99999 ₱ │\n"
    "├──────────────────────────────────────────────M──E─┴─N──U─────────────────────────────────────────────────────────────┘\n",

    "│\n"
    "├─OPTIONS─>\n"
    "1)  Back to menu\n"
    "2)  Take Order\n"
    "3)  Log Out\n"
    "4)  View Receipt\n"
    "... Exit\n"
    "Your Option: ",
};
char menu_nums[20][3 + 1] = {
    "001", "002", "003", "004", "005", "006", "007", "008", "009", "010",
    "011", "012", "013", "014", "015", "016", "017", "018", "019", "020",
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

// USERS 
// + 1 for null terminator
char names[3][20 + 1] = {
    "tinus_lorvalds",
    "derry_tavis",
    "lazy",
};
char pass[3][20 + 1] = {
    "WindowsIsUseless",
    "GodsChosenProgrammer",
    "pass",
};
int balance[3] = {
  2158,
  200,
  99999999
};

// PROGRAM 
void display_entry() { printf("%s", displays[0]); }
void display_about() { printf("%s", displays[1]); }
void display_exit() { printf("%s", displays[2]); }
void display_menu() { printf("%s", displays[3]); }
void display_menuOptions() { printf("%s", displays[4]); }

// this prevents a lot of bugs 
void buffer_clear(){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void prompt_wait() {
  printf("\n(press enter to continue)");
  buffer_clear();
}

int matches(char c1[], char c2[]) { return strcmp(c1, c2) == 0; }
int isValid_login(char n[], char p[]) {
  int is = 0;
  for (int i = 0; i < 3; i++) {
    int name_match = matches(n, names[i]);
    int pass_match = matches(p, pass[i]);
    if (name_match && pass_match) {
      is = 1;
      break;
    }
  }
  return is;
}
int isValid_orderNum (char num[]) {
  int is = 0;
  for (int i = 0; i < 20; i++) {
    int num_match = matches(num, menu_nums[i]);
    if (num_match) {
      is = 1;
      break;
    }
  }
  return is;
}

int get_itemIndex(char num[]){
  for (int i = 0; i <= 20; i++) {
    if (matches(menu_nums[i], num)){
      return i;
    }
  }
  return 0;
}

// because I'm not allowed to use malloc :(, the user is limited to 1000 orders
char user_orderNums[1000][3 + 1];
int user_orderQuants[1000];
int user_orderCount = 0;
void order_add(char num[], int quant){
  for (int i = 0; i < 1000; i++) {
    if (user_orderNums[i][0] == 0) {
      strncpy(user_orderNums[i], num, 3 + 1);
      user_orderQuants[i] = quant;
      user_orderCount++;
      break;
    }
  }
}

int main() {
  int _s = STATE_entry;
  int failed_logins = 0;

  // +1 for the annoying null terminator 
  char option[1 + 1];
  char usname[20 + 1];
  char uspass[20 + 1];

  while (_s != STATE_exit) {
    switch (_s) {
    case STATE_entry:
      display_entry();
      if (scanf("%1s", option) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (matches("1", option)) {
        _s = STATE_login;
      } else if (matches("2", option)) {
        _s = STATE_about;
      } else {
        _s = STATE_exit;
      }
      break;


    case STATE_about:
      display_about();
      prompt_wait();
      _s = STATE_entry;
      break;


    case STATE_login: {
      printf("Username: ");
      if (scanf("%20s", usname) != 1) {
        _s = STATE_entry;
        break;
      }
      buffer_clear();
      printf("Password: ");
      if (scanf("%20s", uspass) != 1) {
        _s = STATE_entry;
        break;
      }
      buffer_clear();

      if (isValid_login(usname, uspass)) {
        printf("\nLogin Successful!\n");
        _s = STATE_menu;
      } else {
        printf("\n| INVALID LOGIN, attempts remaining: %d |"
               "\n"
               "\ns t a y   o u t"
               "\n",
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
      display_menuOptions();
      if (scanf("%1s", option) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (matches("1", option)) {
        _s = STATE_menu;
      } else if (matches("2", option)) {
        _s = STATE_menu_order;
      } else if (matches("3", option)) {
        _s = STATE_entry;
      } else if (matches("4", option)) {
        _s = STATE_menu_receipt;
      } else {
        _s = STATE_exit;
      }
     break;

     
    case STATE_menu_order: {
      // +1 for null terminator
      char order_num[3 + 1];
      int quant = 0;
      int order_again = 0;
      printf("ENTER | order number: ");
      if (scanf("%3s", order_num) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (!isValid_orderNum(order_num)){
        printf("YIKES | That ain't in the menu buddy.\n");
        break;
      }
      printf("ENTER | quantity: ");
      if (scanf("%d", &quant) != 1) {
        _s = STATE_error;
        break;
      }
      if (quant < 1){
        printf("YIKES | Learn how to count buddy.\n");
        break;
      }
      order_add(order_num, quant);
      printf("ADDED | %d of %s\n", quant, menu_names[get_itemIndex(order_num)]);
      buffer_clear();
      printf("ORDER | another item? (y/n): ");
      if (scanf("%1s", option) != 1) {
        _s = STATE_error;
        break;
      }
      buffer_clear();
      if (matches(option, "y")) {
        _s = STATE_menu_order;
      } else {
        _s = STATE_menu;
      }
      // ...
      } break;

      
    case STATE_menu_receipt:
      if (user_orderCount == 0) {
        printf("\nReceipt? Order something first! >:(\n");
      } else {
        printf("\nItems (%d):\n", user_orderCount);
        for (int i = 0; i < user_orderCount; i++) {
          int item_i = get_itemIndex(user_orderNums[i]);
          printf("Quantity: %d\n", user_orderQuants[i]);
          printf("%s | ", menu_names[item_i]);
          printf("%d₱ | \n", menu_prices[item_i]);
        }
      }
      _s = STATE_menu;
      prompt_wait();
      break;

      
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
