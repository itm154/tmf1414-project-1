// Requirements
// - Display menu for user to take orders ++
// - Allow maximum of 4 packs of MK per order ++
// - Display details of MK orders made by each customer ++
// - Display the calculated total price in a single receipt ++
// - Take order continuously from customers until user choose to exit ++
// - Display the transaction details at anytime when it is needed ++
// - Save all the order transaction to a file
// - Error handling for inputs ++

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* ******************************** */
/* *        Constant values       * */
/* ******************************** */
#define MAX_ORDERS 4

const float MK_KOSONG = 4.50;
const float MK_AYAM = 7.00;
const float MK_DAGING = 8.00;
const float MK_TENDON = 13.00;

const float MK_AYAM_SP = 9.00;
const float MK_DAGING_SP = 10.00;
const float MK_TENDON_SP = 16.00;

const float EX_MEE = 1.50;
const float EX_CHICKEN = 2.00;
const float EX_MEAT = 2.50;
const float EX_TENDON = 3.00;

/* ******************************* */
/* *      Type Definitions       * */
/* ******************************* */
typedef struct {
  char type;
  char size;
  int extras[4];
  float price;
} Order;

/* ********************************* */
/* *      Function Prototypes      * */
/* ********************************* */
void displayMenu();
void displayOptions();
void displayReceipt(Order order[], int orderCount);

void getOrder(Order *order);
float getPrice(Order *order);

/* **************************** */
/* *      Main Function       * */
/* **************************** */
int main() {
  Order orders[4];
  int orderCount = 0;

  int operation;
  char continueOrder = 1;

  do {
    printf("\nOrders available: %d\n", MAX_ORDERS - orderCount);

    displayOptions();

    if (scanf("%d", &operation) != 1) {
      printf("\nInvalid input. Please enter a valid number.\n");
      while (getchar() != '\n')
        ;
      continue;
    }
    switch (operation) {
    case 1: // Add orders
      getOrder(&orders[orderCount]);
      orderCount++;
      break;
    case 2: // Display current receipt
      displayReceipt(orders, orderCount);
      break;
    case 3: // Finalize order
      continueOrder = 0;
      break;
    default: // Any other options besides available
      printf("\nInvalid option\n");
      break;
    }
  } while (continueOrder == 1 && orderCount < 4);

  return 0;
}

/* *********************************** */
/* *      Function Definitions       * */
/* *********************************** */
void displayMenu() {
  printf("\n");
  printf(
      "+================================================================+\n");
  printf(
      "|                         Mi Kolok Menu                          |\n");
  printf(
      "+=====================+=============+=============+==============+\n");
  printf(
      "|       Package       | Regular (R) | Special (S) |    Extras    |\n");
  printf(
      "|                     |    (RM)     |     (RM)    |     (RM)     |\n");
  printf(
      "+---------------------+-------------+-------------+--------------|\n");
  printf(
      "| a) Mi Kolok Kosong  | 4.50        | -           | Mee/1.50     |\n");
  printf(
      "| b) Mi Kolok Ayam    | 7.00        | 9.00        | Chicken/2.00 |\n");
  printf(
      "| c) Mi Kolok Daging  | 8.00        | 10.00       | Meat/2.50    |\n");
  printf(
      "| d) Mi Kolok Tendon  | 13.00       | 16.00       | Tendon/3.00  |\n");
  printf("+================================================================+ "
         "\n");
}

void displayExtras() {
  printf("\n");
  printf("+=================+\n");
  printf("|      Extras     |\n");
  printf("|       (RM)      |\n");
  printf("+-----------------+\n");
  printf("| a) Mee 1.50     |\n");
  printf("| b) Chicken 2.00 |\n");
  printf("| c) Meat 2.50    |\n");
  printf("| d) Tendon 3.00  |\n");
  printf("+=================+\n");
}

void displayOptions() {
  printf("Choose an operation:\n");
  printf("1. Add an order\n");
  printf("2. Display current receipt\n");
  printf("3. Finalize order\n");
  printf("(1-3): ");
}

void getOrder(Order *order) {
  displayMenu();

  // ------------- //
  // Order section //
  // ------------- //
  char type;

  do {
    printf("Select Mee type (a/b/c/d): ");
    scanf(" %c", &type);
    type = tolower(type); // Make input case insensitive
    if (type != 'a' && type != 'b' && type != 'c' && type != 'd') {
      printf("Invalid input. PLease select a valid type (a/b/c/d)\n");
    }
  } while (type != 'a' && type != 'b' && type != 'c' && type != 'd');
  order->type = tolower(type);

  if (type != 'a') {
    do {
      printf("Select size (R for Regular, S for Special): ");
      scanf(" %c", &order->size);
      order->size = toupper(order->size); // Make input case insensitive
      if (order->size != 'R' && order->size != 'S') {
        printf("Invalid input. Please select a valid size (R/S).\n");
      }
    } while (order->size != 'R' && order->size != 'S');
  } else {
    order->size = 'R';
  }

  // -------------- //
  // Extras section //
  // -------------- //
  int extraQty;
  char addExtras;
  char option;

  // Set initial values of all extra to 0
  for (int i = 0; i < 4; i++) {
    order->extras[i] = 0;
  }

  do {
    printf("Do you want extras? (y/n): ");
    scanf(" %c", &addExtras);
    addExtras = tolower(addExtras); // Make input case insensitive
    if (addExtras != 'y' && addExtras != 'n') {
      printf("Invalid input. Please enter 'y' or 'n'.\n");
    }
  } while (addExtras != 'y' && addExtras != 'n');

  if (addExtras == 'y') {
    do {
      displayExtras();
      do {
        printf("Select extra (a/b/c/d) or 'q' to stop: ");
        scanf(" %c", &option);
        option = tolower(option);
      } while ((option < 'a' || option > 'd') && option != 'q');

      if (option >= 'a' && option <= 'd') {
        do {
          printf("Enter quantity: ");
          if (scanf("%d", &extraQty) != 1 || extraQty < 0) {
            printf("Invalid quantity. Please enter a non-negative number.\n");
            while (getchar() != '\n')
              extraQty = -1;
          }
        } while (extraQty < 0);
        order->extras[option - 'a'] += extraQty;
      }
    } while (option != 'q');
  }

  order->price = getPrice(order);
}

float getPrice(Order *order) {
  float price = 0.0;

  switch (order->type) {
  case 'a':            // Mi Kolok Kosong
    price = MK_KOSONG; // Special not available
    break;
  case 'b': // Mi Kolok Ayam
    price = (order->size == 'R') ? MK_AYAM : MK_AYAM_SP;
    break;
  case 'c': // Mi Kolok Daging
    price = (order->size == 'R') ? MK_DAGING : MK_DAGING_SP;
    break;
  case 'd': // Mi Kolok Tendon
    price = (order->size == 'R') ? MK_TENDON : MK_TENDON_SP;
    break;
  }

  price += order->extras[0] * EX_MEE;
  price += order->extras[1] * EX_CHICKEN;
  price += order->extras[2] * EX_MEAT;
  price += order->extras[3] * EX_TENDON;

  return price;
}

void displayReceipt(Order order[], int orderCount) {
  float totalPrice = 0.0;
  for (int i = 0; i < orderCount; i++) {
    printf("------------------------------------\n");
    printf("            Order receipt           \n");
    printf("------------------------------------\n");
    printf("  Order #%d: \n", i + 1);
    switch (order[i].type) {
    case 'a':
      printf("  Mi Kolok Kosong %10s%6.2f\n", "RM", MK_KOSONG);
      break;
    case 'b':
      printf("  Mi Kolok Ayam   %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_AYAM : MK_AYAM_SP);
      break;
    case 'c':
      printf("  Mi Kolok Daging %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_DAGING : MK_DAGING_SP);
      break;
    case 'd':
      printf("  Mi Kolok Tendon %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_TENDON : MK_TENDON_SP);
      break;
    }

    if (order[i].extras[0] > 0)
      printf("    Mee x %-2d      %10s%6.2f\n", order[i].extras[0], "RM",
             order[i].extras[0] * EX_MEE);
    if (order[i].extras[1] > 0)
      printf("    Chicken x %-2d  %10s%6.2f\n", order[i].extras[1], "RM",
             order[i].extras[1] * EX_CHICKEN);
    if (order[i].extras[2] > 0)
      printf("    Meat x %-2d     %10s%6.2f\n", order[i].extras[2], "RM",
             order[i].extras[2] * EX_MEAT);
    if (order[i].extras[3] > 0)
      printf("    Tendon x %-2d   %10s%6.2f\n", order[i].extras[3], "RM",
             order[i].extras[3] * EX_TENDON);

    totalPrice += order[i].price;
  }
  printf("------------------------------------\n");
  printf("  Grand Total     %10s%6.2f\n", "RM", totalPrice);
  printf("------------------------------------\n");
  printf("\n");
}
