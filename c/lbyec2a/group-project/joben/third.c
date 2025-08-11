#include <stdio.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_NAME_LENGTH 20
#define MAX_FAILED_LOGINS 2
#define MAX_ITEM_COUNT 5

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
#define STATE_PAYMENT 11
// === RUNTIME VARIABLES ===
int currentState = 0;
int currentFailedLogins = 0;
int runtimeInt = 0;
double runtimeDouble = 0;
char currentUserName[MAX_NAME_LENGTH + 1];
char currentUserPassword[MAX_NAME_LENGTH + 1];
int currentUserNumNights = 0;
int currentUserDesiredRoomCount = 0;

char currentUserRoomType[MAX_NAME_LENGTH + 1];
int currentUserRoomTypeIndex;

double discountRate = 0;

// === UNCHANGING VARIABLES ===
char REGISTERED_USERNAMES[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST",
    "ADMIN",
    "CHECKIN",
};
char REGISTERED_PASSWORDS[MAX_USERS][MAX_NAME_LENGTH] = {
    "GUEST",
    "ADMIN",
    "PILLOW",
};

char STORAGE_ROOM_TYPES[MAX_ITEM_COUNT][MAX_NAME_LENGTH + 1] = {
    "Single", "Double", "Suite", "Family", "Deluxe",
};
int STORAGE_ROOM_PRICESPERNIGHT[MAX_ITEM_COUNT] = {2000, 3500, 4700, 5200,
                                                   6300};
int STORAGE_ROOM_MAXGUESTS[MAX_ITEM_COUNT] = {2, 4, 5, 5, 8};
char STORAGE_ROOM_AMENITIES[MAX_ITEM_COUNT][MAX_NAME_LENGTH] = {
    "1 Bed, AC, TV",      // SINGLE ROOM
    "2 Bed, AC, TV",      // DOUBLE ROOM
    "3 bed, Living Room", // suite ROOM
    "Suite + 1 bed",      // FAMILY ROOM
    "Family + Mini-bar",  // Deluxe ROOM
};

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
void display_currentUserBooking() {
  printf("\n"
         "--TYPE-----ID---$/NIGHT---MAXGST---AMENITIES-------------"
         "\n");
  int i = currentUserRoomTypeIndex - 1;
  printf("| %-8s %-4d %-9d %-8d %-20s |\n",
         STORAGE_ROOM_TYPES[i],          //
         i,                              //
         STORAGE_ROOM_PRICESPERNIGHT[i], //
         STORAGE_ROOM_MAXGUESTS[i],      //
         STORAGE_ROOM_AMENITIES[i]       //
  );
  printf("---------------------------------------------------------\n");
}

void display_roomSelection_allRooms() {
  printf("\n"
         "--TYPE-----ID---$/NIGHT---MAXGST---AMENITIES------------------"
         "\n");
  for (int i = 0; i < MAX_ITEM_COUNT; i++) {
    printf("| %-8s %-4d %-9d %-8d %-25s |\n",
           STORAGE_ROOM_TYPES[i],          //
           i,                              //
           STORAGE_ROOM_PRICESPERNIGHT[i], //
           STORAGE_ROOM_MAXGUESTS[i],      //
           STORAGE_ROOM_AMENITIES[i]       //
    );
  }
  printf("--------------------------------------------------------------");
}
void display_roomSelectionOpts() {
  printf("\n"
         "------------------------\n"
         "|   ROOM RESERVATION   |\n"
         "------------------------\n"
         "\n"
         "1) Reserve a room\n"
         "2) View all rooms\n"
         "3) Booking summary\n"
         "_) Log out\n"
         "\n"
         "Option: ");
}
void display_roomSelection() {
  printf("Hello, %s! You may now book a room: \n", currentUserName);
  display_roomSelectionOpts();
}
void display_roomSelection_roomTypeOpts() {
  printf("( Unit type: ? ) >> Nights of stay >> Desired Roomcount\n");
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
  printf("Unit type: %s >> ( Nights of stay ) >> Desired Roomcount\n",
         currentUserRoomType);
  printf("\n"
         "- Please enter how many NIGHTS you want to book the rooms\n"
         "\n"
         "Option: ");
}
void display_roomSelection_numRoomsOpts() {
  printf("Unit type: %s >> Nights of stay: %d >> ( Desired Roomcount )\n",
         currentUserRoomType, currentUserNumNights);
  printf("\n"
         "- Please enter how many rooms you want to book\n"
         "\n"
         "Option: ");
}
void display_roomSelection_summary() {
  printf("( Summary of Current Booking )\n"
         "\n"
         "- Unit type                  : %s\n"
         "  Nights of stay             : %d\n"
         "  Rooms reserved             : %d\n",
         currentUserRoomType, currentUserNumNights,
         currentUserDesiredRoomCount);
}
void display_roomSelection_confirmation() {
  display_roomSelection_summary();
  display_currentUserBooking();
  printf("\n"
         "1) Confirm Booking\n"
         "2) Reset Booking details\n"
         "_) Back\n"
         "\n"
         "Option: ");
}
void display_discount_check() {
  printf("\n"
         "( Discounting verification )\n"
         "\n"
         "- What ID to present?\n"
         "Options: \n"
         "1) Senior/PWD (20 %%)\n"
         "2) Loyalty Discount (15 %%)\n"
         "3) No Discount\n"
         "_) Cancel\n"
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
int take_int() {
  if (scanf("%d", &runtimeInt) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}
int take_double() {
  if (scanf("%lf", &runtimeDouble) != 1) {
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
        numRooms <= STORAGE_ROOM_MAXGUESTS[i]) {
      hits++;
    }
  }
  return hits;
}
void reset_user_data() {
  currentUserNumNights = 0;
  currentUserDesiredRoomCount = 0;
  strcpy(currentUserRoomType, "");
  currentUserRoomTypeIndex = 0;
}

// === INTERACTIVE FUNCTIONS ===
int INT_entry() {
  reset_user_data();
  clear_screen();
  display_entryOpts();
  if (take_int() != 0)
    return 1;
  switch (runtimeInt) {
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
    currentFailedLogins++;
    if (currentFailedLogins > MAX_FAILED_LOGINS) {
      printf("\nYou have been warned.\n");
      currentState = STATE_EXIT;
    } else {
      prompt_wait();
      currentState = STATE_ENTRY;
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
  switch (runtimeInt) {
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
  char desiredType[MAX_NAME_LENGTH];
  switch (runtimeInt) {
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
  currentUserRoomTypeIndex = runtimeInt;
  int roomCount = STORAGE_ROOM_MAXGUESTS[runtimeInt - 1];

  clear_screen();
  display_roomSelection_numNightsOpts();
  if (take_int() != 0)
    return 1;
  currentUserNumNights = runtimeInt;

  clear_screen();
  display_roomSelection_numRoomsOpts();
  if (take_int() != 0)
    return 1;
  currentUserDesiredRoomCount = runtimeInt;

  clear_screen();
  display_roomSelection_summary();
  printf("\n  We have %d rooms of type '%s', and you wanted %d.\n", roomCount,
         currentUserRoomType, currentUserDesiredRoomCount);

  if (currentUserDesiredRoomCount > roomCount) {
    printf("\n"
           "- Unfortunately, we currently\n"
           "  don't have rooms satisfying your\n"
           "  criteria, try again next time!\n"
           "\n"
           "- For more information, please \n"
           "  check our list of available rooms at\n"
           "  'Room Reservation >> 2) View all rooms'\n");
  } else {
    printf("  Noted! proceed to receipt\n");
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
  if (currentUserRoomTypeIndex == 0) {
    printf("\nNo booking, please reserve a room\n");
    prompt_wait();
    currentState = STATE_ROOMSELECTION;
    return 0;
  }
  clear_screen();
  display_roomSelection_confirmation();
  if (take_int() != 0)
    return 1;
  switch (runtimeInt) {
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
  return 0;
}
int INT_discount_check() {
  display_discount_check();
  if (take_int() != 0)
    return 1;

  switch (runtimeInt) {
  case 1: {
    char UserId[21], amendedString[21];
    char ControlString[21] = "130155";
    int userIdLength = 0;
    int idLength = 11;
    int verify = 0;
    int i;

    while (1) {
      printf("\n- Enter your ID (11 digits): ");
      fgets(UserId, sizeof(UserId), stdin);
      UserId[strcspn(UserId, "\n")] = 0; // remove newline
      userIdLength = strlen(UserId);

      int allDigits = 1;
      for (i = 0; i < userIdLength; i++) {
        if (UserId[i] < '0' || UserId[i] > '9') {
          allDigits = 0;
          break;
        }
      }

      if (userIdLength != idLength || !allDigits) {
        printf("Invalid input. Please enter the 11-digit ID.\n");
        continue;
      }

      strncpy(amendedString, UserId, 6);
      amendedString[6] = '\0';
      verify = strcmp(ControlString, amendedString);

      if (verify != 0) {
        printf("Entered ID number is not valid. Please try again.\n");
        continue;
      }

      break;
    }

    printf("\n- ID verified. Continuing to payment.");
    discountRate = 0.2;
    currentState = STATE_PAYMENT;
  } break;

  case 2: {
    char UserId[21], amendedString[21];
    char ControlString[21] = "8452";
    int userIdLength = 0;
    int idLength = 9;
    int verify = 0;
    int i;

    while (1) {
      printf("\n- Enter your card no. (9 digits): ");
      fgets(UserId, sizeof(UserId), stdin);
      UserId[strcspn(UserId, "\n")] = 0; // remove newline
      userIdLength = strlen(UserId);

      int allDigits = 1;
      for (i = 0; i < userIdLength; i++) {
        if (UserId[i] < '0' || UserId[i] > '9') {
          allDigits = 0;
          break;
        }
      }

      if (userIdLength != idLength || !allDigits) {
        printf("Invalid input. Please enter the 9-digit card no.\n");
        continue;
      }

      strncpy(amendedString, UserId, 4);
      amendedString[4] = '\0';
      verify = strcmp(ControlString, amendedString);

      if (verify != 0) {
        printf("Entered card number is not valid. Please try again.\n");
        continue;
      }

      break;
    }

    printf("\n- Loyalty card verified. Continuing to payment.");
    discountRate = 0.15;
    currentState = STATE_PAYMENT;
  } break;

  case 3: {
    printf("\n- No discount Applied. Continuing to payment.");
    currentState = STATE_PAYMENT;
  } break;

  default: {
    currentState = STATE_ROOMSELECTION;
  } break;
  }

  prompt_wait();
  return 0;
}
int INT_reset_user_data() {
  reset_user_data();
  printf("\nCleared booking!\n");
  prompt_wait();
  currentState = STATE_ROOMSELECTION_SUMMARY;
  return 0;
}
int INT_payment() {
  clear_screen();

  double total = STORAGE_ROOM_PRICESPERNIGHT[currentUserRoomTypeIndex - 1] *
                 currentUserNumNights * currentUserDesiredRoomCount;
  double discount = total * discountRate;
  double final = total - discount;

  printf("- Total price: %lf\n", total);
  printf("  Discount: %lf\n", discount);
  printf("  Final: %lf\n", final);
  printf("Enter issued cash: ");
  if (take_double() != 0)
    return 1;
  double issuedcash = runtimeDouble;
  if (issuedcash < final) {
    printf("Broke ass, try again\n");
    currentState = STATE_PAYMENT;
    return 0;
  }
  printf("\nThank you for booking! Here is your receipt\n");
  printf("-----------------------------------\n");
  printf("- Customer Name: %s\n", currentUserName);
  printf("  Room type: %s\n", currentUserRoomType);
  printf("  Number of rooms: %d\n", currentUserDesiredRoomCount);
  printf("  Total nights: %d\n", currentUserNumNights);
  printf("  Discount Rate: %.2lf%%\n", discountRate * 1000);
  printf("\n");
  printf("- Total price: %.2lf\n", total);
  printf("  Discount: %.2lf\n", discount);
  printf("  Final: %.2lf\n", final);
  printf("-----------------------------------\n");

  printf("Make another booking?\n"
         "1) yes\n"
         "2) no, exit\n"
         "Option: ");
  if (take_int() != 0)
    return 1;
  switch (runtimeInt) {
  case 1: {
    reset_user_data();
    currentState = STATE_ROOMSELECTION;
    return 0;
  }
  default: {
    currentState = STATE_EXIT;
    return 0;
  }
  }
  prompt_wait();
  currentState = STATE_ROOMSELECTION;
  return 0;
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
  case STATE_PAYMENT: {
    INT_payment();
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
