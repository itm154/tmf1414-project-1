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

void writeTrxLogs(Order order[], int orderCount);
void writeTrxInfo(float currentTotal, int currentReceiptNumber);
void readTrxInfo(float *total, int *receiptNumber);

void writeTrxFile();
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
      displayReceipt(orders, orderCount);
      writeTrxLogs(orders, orderCount);
      writeTrxFile();
      break;
    default: // Any other options besides available
      printf("\nInvalid option\n");
      break;
    }
  } while (continueOrder == 1 && orderCount < MAX_ORDERS);

  if (orderCount == MAX_ORDERS) {
    printf("You have reached your order limits!. Come again another time\n");

    displayReceipt(orders, orderCount);
  }
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
  for (int i = 0; i < MAX_ORDERS; i++) {
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

  printf("\n");
  printf("------------------------------------\n");
  printf("            Order receipt           \n");
  printf("------------------------------------\n");
  for (int i = 0; i < orderCount; i++) {
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
    printf("\n");

    totalPrice += order[i].price;
  }
  printf("------------------------------------\n");
  printf("  Grand Total     %10s%6.2f\n", "RM", totalPrice);
  printf("------------------------------------\n");
  printf("\n");
}

void writeTrxLogs(Order order[], int orderCount) {

  FILE *fptr;
  fptr = fopen("logs.dat", "a");

  float prevTotal = 0.0;
  int prevReceiptNumber = 0;

  if (fptr == NULL) {
    printf("Unable to open transactions log file");
    return;
  }

  readTrxInfo(&prevTotal, &prevReceiptNumber);

  float currentTotal = 0.0;
  for (int i = 0; i < orderCount; i++) {
    fprintf(fptr, "%03d         |", prevReceiptNumber + 1);
    switch (order[i].type) {
    case 'a':
      fprintf(fptr, " %-16s |", "Mee Kolok Kosong");
      break;
    case 'b':
      fprintf(fptr, " %-16s |", "Mee Kolok Ayam");
      break;
    case 'c':
      fprintf(fptr, " %-16s |", "Mee Kolok Daging");
      break;
    case 'd':
      fprintf(fptr, " %-16s |", "Mee Kolok Tendon");
      break;
    }

    currentTotal += order[i].price;
    fprintf(fptr, " %-4c |", order[i].size);
    for (int j = 0; j < 4; j++) {
      if (order[i].extras[j] != 0) {
        fprintf(fptr, " %-7d |", order[i].extras[j]);
      } else {
        fprintf(fptr, " %-7s |", "-");
      }
    }
    fprintf(fptr, " RM%6.2f\n", order[i].price);
  }
  writeTrxInfo(currentTotal + prevTotal, prevReceiptNumber + 1);

  fclose(fptr);
}

void writeTrxInfo(float currentTotal, int currentReceiptNumber) {
  FILE *fptr;
  fptr = fopen("info.dat", "w");

  if (fptr == NULL) {
    printf("Unable to save transaction information\n");
    return;
  }

  // Write total on the first line and receipt number on the second line
  fprintf(fptr, "%.2f\n", currentTotal);
  fprintf(fptr, "%d\n", currentReceiptNumber);

  fclose(fptr);
}

void readTrxInfo(float *total, int *receiptNumber) {
  FILE *fptr;
  fptr = fopen("info.dat", "r");

  if (fptr == NULL) {
    // Default values if file does not exist
    *total = 0.0;
    *receiptNumber = 0;
    return;
  }

  // Read total from the first line and receipt number from the second line
  fscanf(fptr, "%f", total);
  fscanf(fptr, "%d", receiptNumber);

  fclose(fptr);
}

void writeTrxFile() {
  FILE *fptr_transactions, *fptr_logs, *fptr_info;
  fptr_transactions = fopen("transactions.dat", "w");
  fptr_logs = fopen("logs.dat", "r");
  fptr_info = fopen("info.dat", "r");

  char ch;
  float total;

  if (fptr_transactions == NULL || fptr_logs == NULL || fptr_info == NULL) {
    printf("Unable to open transaction file\n");
    return;
  }

  printf("Saving transaction details...\n");

  fscanf(fptr_info, "%f", &total);

  fprintf(fptr_transactions,
          "Receipt No. | Mee Kolok        | Type | Chicken | Meat    | Tendon  "
          "| Mee     | Amount (RM)\n");

  // Write transaction logs
  ch = fgetc(fptr_logs);
  while (ch != EOF) {
    /* Write to destination file */
    fputc(ch, fptr_transactions);

    /* Read next character from source file */
    ch = fgetc(fptr_logs);
  }
  fprintf(fptr_transactions, "-------------------------------------------------"
                             "------------------------------------------\n");
  fprintf(fptr_transactions, "%82s%6.2f", "Total:", total);

  fclose(fptr_transactions);
  fclose(fptr_logs);
  fclose(fptr_info);
}
