#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_NAME_LENGTH 20
#define MAX_FAILED_LOGINS 2
#define MAX_ITEM_COUNT 20

#define STATE_ENTRY 0
#define STATE_LOGIN 1
#define STATE_EXIT 2
#define STATE_ERROR 3
#define STATE_ABOUT 4
#define STATE_ROOMSELECTION 5
#define STATE_ROOMSELECTION_SUMMARY 6
#define STATE_ROOMSELECTION_ALLROOMS 7
#define STATE_ROOMSELECTION_RESERVE 8
#define STATE_DISCOUNT_CHECK 9
#define STATE_RESET_USER_DATA 10

// === RUNTIME VARIABLES ===
int currentState = 0;
int currentFailedLogins = 0;
int currentUserInt = 0;
double currentUserDouble = 0;
char currentUserName[MAX_NAME_LENGTH + 1];
char currentUserPassword[MAX_NAME_LENGTH + 1];
char currentUserRoomType[MAX_NAME_LENGTH + 1];
int currentUserNumNights = 0;
int currentUserNumRooms = 0;

// === UNCHANGING VARIABLES ===
char REGISTERED_USERNAMES[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST", "ADMIN",
    // "CHECKIN",
    "k", // < TEMPRARY for convenience
};
char REGISTERED_PASSWORDS[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST", "ADMIN",
    // "PILLOW",
    "k", // < TEMPRARY for convenience
};

// NOTE: Room values may not be realistic. For academic purposes only (and comic
// relief)
char STORAGE_ROOM_TYPES[MAX_ITEM_COUNT][MAX_NAME_LENGTH + 1] = {
    "Single", "Double", "Double", "Suite",  "Family", "Deluxe", "Double", //
    "Double", "Family", "Family", "Double", "Double", "Deluxe", "Suite",  //
    "Single", "Single", "Suite",  "Single", "Double", "Family",           //
};
int STORAGE_ROOM_NUMROOMS[MAX_ITEM_COUNT] = {
    1, 2, 1, 3, 6, 1, 1, 2, 3, 1, //
    2, 5, 1, 3, 2, 4, 1, 2, 5, 1  //
};
int STORAGE_ROOM_PRICESPERNIGHT[MAX_ITEM_COUNT] = {
    99, 1999, 29, 199,  1001, 1002, 9, 10, 2999, 1,     //
    29, 499,  29, 5999, 799,  1,    9, 9,  499,  99999, //
};
int STORAGE_ROOM_MAXGUESTS[MAX_ITEM_COUNT] = {
    2, 1, 3, 2, 1, 1, 2, 3, 1, 1, //
    2, 1, 4, 2, 3, 1, 5, 2, 1, 6  //
};
char STORAGE_ROOM_AMENITIES[MAX_ITEM_COUNT][MAX_NAME_LENGTH] = {
    "WiFi, TV",
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
void display_entryOpts() {
  printf("Welcome!\n"
         "\n"
         "---------------\n"
         "| Hotel  Room |\n"
         "|   Booking   |\n"
         "---------------\n"
         "\n"
         "1) Login\n"
         "2) About\n"
         "3) Exit\n"
         "\n"
         "Option: ");
}
void display_exit() {
  printf("\n"
         "Exited the program.\n");
}
void display_error() {
  printf("\n"
         "Be careful of erroneous inputs! Returning to entry.\n");
}
void display_about() {
  printf("\n"
         "WELCOME TO HOTEL ROOM BOOKING\n");
}
void display_roomSelection_allRooms() {
  printf("\n"
         "--TYPE-----ID---ROOMS---$/NIGHT---MAXGST---AMENITIES-------------"
         "-TYPE-----ID---ROOMS---$/NIGHT---MAXGST---AMENITIES-------------"
         "\n");
  for (int i = 0; i < MAX_ITEM_COUNT / 2; i++) {
    printf("| %-8s %-4d %-7d %-9d %-8d %-20s |",
           STORAGE_ROOM_TYPES[i],          //
           i,                              //
           STORAGE_ROOM_NUMROOMS[i],       //
           STORAGE_ROOM_PRICESPERNIGHT[i], //
           STORAGE_ROOM_MAXGUESTS[i],      //
           STORAGE_ROOM_AMENITIES[i]       //
    );
    int j = i + 10;
    printf(" %-8s %-4d %-7d %-9d %-8d %-20s |\n",
           STORAGE_ROOM_TYPES[j],          //
           j,                              //
           STORAGE_ROOM_NUMROOMS[j],       //
           STORAGE_ROOM_PRICESPERNIGHT[j], //
           STORAGE_ROOM_MAXGUESTS[j],      //
           STORAGE_ROOM_AMENITIES[j]       //
    );
  }
  printf("-----------------------------------------------------------------");
  printf("----------------------------------------------------------------\n");
}
void display_roomSelectionOpts() {
  printf("\n"
         "------------------------\n"
         "|   ROOM RESERVATION   |\n"
         "------------------------\n"
         "\n"
         "1) Reserve a room\n"
         "2) View all rooms\n"
         "3) Proceed to booking summary\n"
         "_) Log out\n"
         "\n"
         "Option: ");
}
void display_roomSelection() {
  printf("Hello, %s! You may now book a room: \n", currentUserName);
  display_roomSelectionOpts();
}
void display_roomSelection_roomTypeOpts() {
  printf("( Room type: ? ) >> Nights of stay >> Reserved rooms\n");
  printf("\n"
         "1) Single\n"
         "2) Double\n"
         "3) Suite\n"
         "4) Deluxe\n"
         "5) Family\n"
         "_) Cancel\n"
         "\n"
         "Option: ");
}
void display_roomSelection_numNightsOpts() {
  printf("Room type: %s >> ( Nights of stay ) >> Reserved rooms\n",
         currentUserRoomType);
  printf("\n"
         "- Please enter how many NIGHTS you want to book the rooms\n"
         "\n"
         "Option: ");
}
void display_roomSelection_numRoomsOpts() {
  printf("Room type: %s >> Nights of stay: %d >> ( Reserved rooms )\n",
         currentUserRoomType, currentUserNumNights);
  printf("\n"
         "- Please enter how many ROOMS you want to book\n"
         "\n"
         "Option: ");
}
void display_roomSelection_summary() {
  printf("( Summary of Current Booking )\n"
         "\n"
         "- Room type: %s\n"
         "  Nights of stay: %d\n"
         "  Reserved rooms: %d\n\n"
         "Options:\n"
         "1) Confirm Booking\n"
         "2) Reset Booking details\n\n"
         "Option: ",
         currentUserRoomType, currentUserNumNights, currentUserNumRooms);
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
int take_int() {
  if (scanf("%d", &currentUserInt) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}
int take_double() {
  if (scanf("%lf", &currentUserDouble) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}

// === PASSWORD CHECKING ===
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
  return is; // RETURNING ZERO
}

int get_desiredType_quantity(char type[], int numRooms) {
  int hits = 0;
  for (int i = 0; i < MAX_ITEM_COUNT; i++) {
    if (streq(type, STORAGE_ROOM_TYPES[i]) &&
        numRooms <= STORAGE_ROOM_NUMROOMS[i]) {
      hits++;
    }
  }
  return hits;
}

// === INTERACTIVE FUNCTIONS ===
int INT_entry() {
  clear_screen();
  display_entryOpts();
  if (take_int() != 0)
    return 1;
  switch (currentUserInt) {
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
  if (scanf("%20s", currentUserName) != 1) { // get username
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  printf("Password: ");
  if (scanf("%20s", currentUserPassword) != 1) { // get password
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();

  if (!check_valid_login(currentUserName, currentUserPassword)) { // if
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
  display_roomSelection();
  if (take_int() != 0)
    return 1;
  switch (currentUserInt) {
  case 1:
    currentState = STATE_ROOMSELECTION_RESERVE;
    break;
  case 2:
    currentState = STATE_ROOMSELECTION_ALLROOMS;
    break;
  case 3:
    currentState = STATE_ROOMSELECTION_SUMMARY;
    break;
  default:
    currentState = STATE_ENTRY;
    break;
  }
  return 0;
}
int INT_roomSelection_reserve() {
  clear_screen();
  display_roomSelection_roomTypeOpts();
  if (take_int() != 0)
    return 1;

  char desiredType[MAX_NAME_LENGTH]; // if I press 1-5, it will copy the desired
                                     // type to set options
  switch (currentUserInt) {
  case 1:
    strcpy(desiredType, "Single");
    break;
  case 2:
    strcpy(desiredType, "Double");
    break;
  case 3:
    strcpy(desiredType, "Suite");
    break;
  case 4:
    strcpy(desiredType, "Deluxe");
    break;
  case 5:
    strcpy(desiredType, "Family");
    break;
  default:
    currentState = STATE_ROOMSELECTION;
    return 0;
    break;
  }
  strcpy(currentUserRoomType, desiredType);

  clear_screen();
  display_roomSelection_numNightsOpts();
  if (take_int() != 0)
    return 1;
  currentUserNumNights = currentUserInt;

  clear_screen();
  display_roomSelection_numRoomsOpts();
  if (take_int() != 0)
    return 1;
  currentUserNumRooms = currentUserInt;
  int count = get_desiredType_quantity(desiredType, currentUserInt);
  int maxcount = get_desiredType_quantity(desiredType, 0);
  clear_screen();
  display_roomSelection_summary();
  if (count < 1) {
    printf("\n"
           "- Unfortunately, we currently\n"
           "  don't have rooms satisfying your\n"
           "  criteria, try again next time!\n"
           "\n"
           "- For more information, please \n"
           "  check our list of available rooms at\n"
           "  'Room Reservation >> 2) View all rooms'\n");
  } else {
    printf("\n"
           "- Noted! We have %d of '%s' rooms, and %d of them have at least %d "
           "rooms\n\n"
           "- Please proceed to the Booking summary for payment and "
           "confirmation.\n",
           maxcount, desiredType, count, currentUserInt);
  }
  prompt_wait();
  currentState = STATE_ROOMSELECTION;
  return 0;
}
int INT_roomSelection_allRooms() {
  clear_screen();
  display_roomSelection_allRooms();
  prompt_wait();
  currentState = STATE_ROOMSELECTION;
  return 0;
}
int INT_roomSelection_summary() {
  clear_screen();
  display_roomSelection_summary();
  if (take_int() != 0)
    return 1;
  switch (currentUserInt) {
  case 1:
    currentState = STATE_DISCOUNT_CHECK;
    break;
  case 2:
    currentState = STATE_RESET_USER_DATA;
    break;
  default:
    currentState = STATE_ROOMSELECTION;
    break;
  }
  printf("%d", currentUserNumRooms);
  prompt_wait();
  return 0;
}
int INT_discount_check() {
  clear_screen();
  prompt_wait();

  currentState = STATE_ROOMSELECTION_SUMMARY;
  return 0;
}
int INT_reset_user_data() {
  clear_screen();
  currentUserNumNights = 0;
  printf("\nnumnights: %d", currentUserNumNights);
  currentUserNumRooms = 0;
  printf("\nnumrooms: %d", currentUserNumRooms);
  strcpy(currentUserRoomType, " ");
  printf("\nroom type: '%s'", currentUserRoomType);
  prompt_wait();

  currentState = STATE_ROOMSELECTION_SUMMARY;
  return 1;
}
int INT_error() {
  display_error();
  prompt_wait();
  currentState = STATE_ENTRY;
  return 0;
}

// === TOP-LEVEL FUNCTIONS ===
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
  case STATE_ROOMSELECTION_RESERVE: {
    INT_roomSelection_reserve();
  } break;
  case STATE_ROOMSELECTION_ALLROOMS: {
    INT_roomSelection_allRooms();
  } break;
  case STATE_ROOMSELECTION_SUMMARY: {
    INT_roomSelection_summary();
  } break;
  case STATE_ERROR: {
    INT_error();
  } break;
  case STATE_DISCOUNT_CHECK: {
    INT_discount_check();
  } break;
  case STATE_RESET_USER_DATA: {
    INT_reset_user_data();
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
