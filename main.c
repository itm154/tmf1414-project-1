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

/* ******************************** */
/* *        Constant values       * */
/* ******************************** */
#define MAX_ORDERS 4
// Prices for all available purchases
// RG = Regular
// SP = Special
const float MK_KOSONG_RG = 4.50;
const float MK_AYAM_RG = 7.00;
const float MK_DAGING_RG = 8.00;
const float MK_TENDON_RG = 13.00;

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
  char type;     // Mee kolok type (Kosong, Ayam, ...)
  char size;     // Mee kolok size (regular, special)
  int extras[4]; // Int array of extras
  float price;   // Total price of the whole order
} Order;

/* ********************************* */
/* *      Function Prototypes      * */
/* ********************************* */
// Various display functions
// Most of these is just to declutter main()
void displayMenu();
void displayExtras();
void displayOperations();
void displayReceipt(Order order[], int orderCount);

// Responsible for taking user orders
void getOrder(Order *order);

// Calculate the price for all orders in a single session
float getPrice(Order *order);

void updateTransactionsFile(Order order[], int orderCount);

/* **************************** */
/* *      Main Function       * */
/* **************************** */
int main() {
  Order orders[MAX_ORDERS];
  int orderCount = 0;

  int operation;

  do {
    printf("\nOrders available: %d\n", MAX_ORDERS - orderCount);

    displayOperations();

    if (scanf("%d", &operation) != 1) {
      printf("\nInvalid input. Please enter a valid number\n");

      // Clear input buffer
      // Explanation
      // https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c
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
      if (orderCount != 0) {
        displayReceipt(orders, orderCount);
        updateTransactionsFile(orders, orderCount);
        return 0;
      } // Only finalize an order if an order exists

      printf("Please make an order!\n");
      break;
    default: // Any other options besides available
      printf("\nInvalid option, Please choose a valid operation\n");
      break;
    }
  } while (orderCount < MAX_ORDERS);

  // Do the same operation as finalize order when order limit is reached
  displayReceipt(orders, orderCount);
  printf("You have reached your order limit!. Come again another time\n");

  return 0;
}

/* *********************************** */
/* *      Function Definitions       * */
/* *********************************** */
void displayMenu() {
  printf("\n");
  printf("+================================================================"
         "+\n");
  printf("|                         Mi Kolok Menu                          "
         "|\n");
  printf("+=====================+=============+=============+=============="
         "+\n");
  printf("|       Package       | Regular (R) | Special (S) |    Extras    "
         "|\n");
  printf("|                     |    (RM)     |     (RM)    |     (RM)     "
         "|\n");
  printf("+---------------------+-------------+-------------+--------------"
         "|\n");
  printf("| a) Mi Kolok Kosong  | 4.50        | -           | Mee/1.50     "
         "|\n");
  printf("| b) Mi Kolok Ayam    | 7.00        | 9.00        | Chicken/2.00 "
         "|\n");
  printf("| c) Mi Kolok Daging  | 8.00        | 10.00       | Meat/2.50    "
         "|\n");
  printf("| d) Mi Kolok Tendon  | 13.00       | 16.00       | Tendon/3.00  "
         "|\n");
  printf("+================================================================"
         "+\n");
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

void displayOperations() {
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
  char meeType;

  do {
    printf("Select Mee type (a/b/c/d): ");
    scanf(" %c", &meeType);
    meeType = tolower(meeType); // Make input case insensitive
    if (meeType < 'a' || meeType > 'd') {
      printf("Invalid input. PLease select a valid meeType (a/b/c/d)\n");
    }
  } while (meeType < 'a' || meeType > 'd');
  order->type = meeType;

  if (meeType != 'a') {
    do {
      printf("Select size (R for Regular, S for Special): ");
      scanf(" %c", &order->size);
      order->size = toupper(order->size); // Make input case insensitive
      if (order->size != 'R' && order->size != 'S') {
        printf("Invalid input. Please select a valid size (R/S).\n");
      }
    } while (order->size != 'R' && order->size != 'S');
  } else {
    order->size = 'R'; // Defaults type 'a' (Kosong) to regular
  }

  // -------------- //
  // Extras section //
  // -------------- //
  char addExtras;
  int extraQty;
  char extraType;

  // Set initial values of all extras to 0
  for (int i = 0; i < MAX_ORDERS; i++) {
    order->extras[i] = 0;
  }

  do {
    printf("Do you want extras? (y/n): ");
    scanf(" %c", &addExtras);
    addExtras = tolower(addExtras); // Make input case insensitive
    if (addExtras != 'y' && addExtras != 'n') {
      printf("Invalid input. Please enter 'y' or 'n'\n");
    }
  } while (addExtras != 'y' && addExtras != 'n');

  if (addExtras == 'y') {
    do {
      displayExtras();
      do {
        printf("Select an extra (a/b/c/d) or 'q' to quit: ");
        scanf(" %c", &extraType);
        extraType = tolower(extraType); // Make input case insensitive
        if (extraType < 'a' || extraType > 'd') {
          printf("Invalid input. PLease select a valid extras (a/b/c/d)\n");
        }
      } while ((extraType < 'a' || extraType > 'd') && extraType != 'q');

      if (extraType >= 'a' && extraType <= 'd') {
        do {
          printf("Enter quantity: ");
          // scanf() returns 1 if it is able to scan/assign a valid value
          if (scanf("%d", &extraQty) != 1 || extraQty < 0) {
            printf("Invalid quantity. Please enter a non-negative number\n");

            // See Line 90 for explanation
            while (getchar() != '\n')
              ;
            extraQty = -1;
          }
        } while (extraQty < 0);

        order->extras[extraType - 'a'] += extraQty;
      }
    } while (extraType != 'q');
  }

  order->price = getPrice(order);
}

float getPrice(Order *order) {
  float price = 0.0;

  switch (order->type) {
  case 'a':               // Mi Kolok Kosong
    price = MK_KOSONG_RG; // Special not available
    break;
  case 'b': // Mi Kolok Ayam
    price = (order->size == 'R') ? MK_AYAM_RG : MK_AYAM_SP;
    break;
  case 'c': // Mi Kolok Daging
    price = (order->size == 'R') ? MK_DAGING_RG : MK_DAGING_SP;
    break;
  case 'd': // Mi Kolok Tendon
    price = (order->size == 'R') ? MK_TENDON_RG : MK_TENDON_SP;
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

  printf("\n");
  printf("------------------------------------\n");
  printf("            Order receipt           \n");
  printf("------------------------------------\n");
  for (int i = 0; i < orderCount; i++) {
    printf("  Order #%d: \n", i + 1);
    switch (order[i].type) {
    case 'a':
      printf("  Mi Kolok Kosong %10s%6.2f\n", "RM", MK_KOSONG_RG);
      break;
    case 'b':
      printf("  Mi Kolok Ayam   %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_AYAM_RG : MK_AYAM_SP);
      break;
    case 'c':
      printf("  Mi Kolok Daging %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_DAGING_RG : MK_DAGING_SP);
      break;
    case 'd':
      printf("  Mi Kolok Tendon %10s%6.2f\n", "RM",
             order[i].size == 'R' ? MK_TENDON_RG : MK_TENDON_SP);
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
    printf("\n");

    totalPrice += order[i].price;
  }
  printf("------------------------------------\n");
  printf("  Total           %10s%6.2f\n", "RM", totalPrice);
  printf("------------------------------------\n");
  printf("\n");
}

void updateTransactionsFile(Order order[], int orderCount) {
  FILE *fptr;
  fptr = fopen("transactions.dat", "r+");
  if (fptr == NULL) {
    fptr = fopen("transactions.dat", "w+");

    if (fptr == NULL) {
      printf("Unable to open or create transactions file\n");
      return;
    }
    fprintf(fptr, "0 0.0\n");

    fprintf(fptr, "\nNo.  Mee Kolok Type    Size  Chicken  Meat     Tendon  "
                  " Mee      Amount (RM)\n");

    rewind(fptr);
  }

  int latestReceiptNumber = 0;
  float totalSales = 0.0;

  fscanf(fptr, "%d %f", &latestReceiptNumber, &totalSales);

  fseek(fptr, 0, SEEK_END);

  float totalPrice = 0.0;
  for (int i = 0; i < orderCount; i++) {
    fprintf(fptr, "%03d ", latestReceiptNumber + 1);
    switch (order[i].type) {
    case 'a':
      fprintf(fptr, " %-16s ", "Mee Kolok Kosong");
      break;
    case 'b':
      fprintf(fptr, " %-16s ", "Mee Kolok Ayam");
      break;
    case 'c':
      fprintf(fptr, " %-16s ", "Mee Kolok Daging");
      break;
    case 'd':
      fprintf(fptr, " %-16s ", "Mee Kolok Tendon");
      break;
    }

    fprintf(fptr, " %-4c ", order[i].size);

    for (int j = 0; j < 4; j++) {
      if (order[i].extras[j] != 0) {
        fprintf(fptr, " %-7d ", order[i].extras[j]);
      } else {
        fprintf(fptr, " %-7s ", "-");
      }
    }

    fprintf(fptr, " RM%6.2f\n", order[i].price);

    totalPrice += order[i].price;
  }

  totalSales += totalPrice;

  rewind(fptr);
  fprintf(fptr, "%d %-6.2f\n", latestReceiptNumber + 1, totalSales);

  fclose(fptr);
}
