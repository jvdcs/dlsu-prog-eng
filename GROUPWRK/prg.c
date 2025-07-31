#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_NAME_LENGTH 20
#define MAX_FAILED_LOGINS 2
#define MAX_ITEM_COUNT 20

#define STATE_ENTRY  0
#define STATE_LOGIN  1
#define STATE_EXIT  2
#define STATE_ERROR  3
#define STATE_ABOUT  4
#define STATE_ROOMSELECTION  5

int currentState = 0;
int currentFailedLogins = 0;
int currentUserOption = 0;
double currentUserValue = 0;
char currentUserName[MAX_NAME_LENGTH + 1]; //+1 for null terminator
char currentUserPassword[MAX_NAME_LENGTH + 1];

char REGISTERED_USERNAMES[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST",
    "ADMIN",
    "CHECKIN",
};
char REGISTERED_PASSWORDS[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST",
    "ADMIN",
    "CHECKIN",
};
char STORAGE_ROOM_TYPES[MAX_ITEM_COUNT][MAX_NAME_LENGTH + 1] = {
    "Single", "Double", "Double", "Suite",  "Family", "Deluxe", "Double",
    "Double", "Family", "Family", "Double", "Double", "Deluxe", "Suite",
    "Single", "Single", "Suite",  "Single", "Double", "Family",
};
int STORAGE_ROOM_NUMROOMS[MAX_ITEM_COUNT] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};
int STORAGE_ROOM_PRICESPERNIGHT[MAX_ITEM_COUNT] = {
    99, 1999, 29, 199,  1001, 1002, 9, 10, 2999, 1,
    29, 499,  29, 5999, 799,  1,    9, 9,  499,  99999,
};
int STORAGE_ROOM_MAXGUESTS[MAX_ITEM_COUNT] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};
char AMENITIES[MAX_ITEM_COUNT][MAX_NAME_LENGTH] = {"WiFi, TV",
                                                   "WiFi, TV, Mini-bar",
                                                   "AC, WiFi",
                                                   "TV",
                                                   "Mini-bar, Gym",
                                                   "WiFi, AC, TV",
                                                   "AC, TV",
                                                   "WiFi",
                                                   "WiFi, TV, AC, Gym",
                                                   "TV, Mini-bar",
                                                   "WiFi, Mini-bar",
                                                   "AC, WiFi, TV",
                                                   "TV, Gym",
                                                   "Mini-bar",
                                                   "WiFi, TV, AC",
                                                   "WiFi, TV, Gym",
                                                   "WiFi, AC, Mini-bar",
                                                   "AC, Mini-bar, TV",
                                                   "WiFi, TV, Spa",
                                                   "TV, AC, Balcony"};

// === DISPLAY FUNCTIONS ===
void display_entry() {
  printf("Welcome!\n"
         "       .-------------.\n"
         "       | Hotel  Room |\n"
         "       |   Booking   |\n"
         "       .-------------.\n"
         "1) Login\n"
         "2) About\n"
         "_) Exit\n"
         "Option: ");
}
void display_exit() {
  printf("\n"
         "Exited The Program.\n");
}
void display_error() {
  printf("\n"
         "Error! Returning to entry.\n");
}
void display_about() {
  printf("\n"
         "WELCOME TO HOTEL ROOM BOOKING\n");
}
void display_rooms() {
  printf("\n.-TYPE-ID--NROOMS--PRICEPERNIGHT--MAXGUESTS---AMENITIES--┬-TYPE-NUM--------------------PRI"
         "CE-.\n");

  for (int i = 0; i < MAX_ITEM_COUNT / 2; i++) {
    printf("| %-10s %d %5d ₱ %5d %5d |", STORAGE_ROOM_TYPES[i], i,
           STORAGE_ROOM_PRICESPERNIGHT[i], STORAGE_ROOM_NUMROOMS[i],
           STORAGE_ROOM_MAXGUESTS[i]);
    printf(" %-10s %d %5d ₱ %5d %5d |\n", STORAGE_ROOM_TYPES[i + 10], i + 10,
           STORAGE_ROOM_PRICESPERNIGHT[i + 10], STORAGE_ROOM_NUMROOMS[i + 10],
           STORAGE_ROOM_MAXGUESTS[i + !0]);
  }

  // printf("├-----------[ DOKBOK's ]┴[ BOKGER "
  //        "]--------------.\n");
}
void display_roomselection() {
  printf("Hello, %s!", currentUserName);
  display_rooms();
  printf("       .-------------------.\n"
         "       |   SELECT A ROOM   |\n"
         "       .-------------------.\n"
         "1) -\n"
         "2) -\n"
         "_) Exit\n"
         "Option: ");
}
void clear_screen() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}

// === UTIL FUNCTIONS ===
void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != -1)
    ;
}
void prompt_wait() {
  printf("\n(press enter to continue)");
  clear_buffer();
}
int take_option() {
  if (scanf("%d", &currentUserOption) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}
int take_double() {
  if (scanf("%lf", &currentUserValue) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}
int streq(char s1[], char s2[]) { return strcmp(s1, s2) == 0; }
int check_valid_login(char name[], char password[]) {
  int is = 0;
  for (int i = 0; i < MAX_USERS; i++) {
    if (streq(name, REGISTERED_USERNAMES[i]) &&
        streq(password, REGISTERED_PASSWORDS[i])) {
      is = 1;
      break;
    }
  }
  return is;
}

// === INTERACTIVE FUNCTIONS ===
int INT_entry() {
  clear_screen();
  display_entry();
  if (take_option() != 0)
    return 1;
  switch (currentUserOption) {
  case 1:
    currentState = STATE_LOGIN;
    break;
  case 2:
    currentState = STATE_ABOUT;
    break;
  default:
    currentState = STATE_EXIT;
    break;
  }
  return 0;
}
int INT_login() {
  printf("Username: ");
  if (scanf("%20s", currentUserName) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  printf("Password: ");
  if (scanf("%20s", currentUserPassword) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();

  if (!check_valid_login(currentUserName, currentUserPassword)) {
    printf("\nInvalid Login, attempts left: %d\n",
           MAX_FAILED_LOGINS - currentFailedLogins);
    currentState = STATE_ENTRY;
    currentFailedLogins++;
    if (currentFailedLogins > MAX_FAILED_LOGINS) {
      printf("\nYou have been warned.\n");
      currentState = STATE_EXIT;
    } else {
      prompt_wait();
    }
  } else {
    currentState = STATE_ROOMSELECTION;
  }
  return 0;
}
int INT_about() {
  clear_screen();
  display_about();
  prompt_wait();
  currentState = STATE_ENTRY;
  return 0;
}
int INT_roomselection() {
  clear_screen();
  display_roomselection();
  prompt_wait();
  return 0;
}
int INT_error() {
  display_error();
  prompt_wait();
  currentState = STATE_ENTRY;
  return 0;
}

// === TOP-LEVEL FUNCTIONs ===
void state_loop() {
  switch (currentState) {
  case STATE_ENTRY: {
    INT_entry();
  } break;
  case STATE_LOGIN: {
    INT_login();
  } break;
  case STATE_ABOUT: {
    INT_about();
  } break;
  case STATE_ROOMSELECTION: {
    INT_roomselection();
  } break;
  case STATE_ERROR: {
    INT_error();
  } break;
  }
}
int main() {
  while (currentState != STATE_EXIT) {
    state_loop();
  }
  display_exit();
  return 0;
}
