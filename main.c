// Requirements
// - Display menu for user to take orders ++
// - Allow maximum of 4 packs of MK per order ++
// - Display details of MK orders made by each customer
// - Display the calculated total price in a single receipt
// - Take order continuously from customers until user choose to exit ++
// - Display the transaction details at anytime when it is needed
// - Save all the order transaction to a file
// - Error handling for inputs

#include <stdio.h>

/* ******************************** */
/* *        Constant values       * */
/* ******************************** */
#define MAX_ORDER 4

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
  int meeID;       // ID for mee kolok, 0-3 mapped to kosong -> tendon
  char meeType;    // Either R for regular or S for special
  int extrasID[4]; // ID for extras mapped
  int extrasQty[4];
} MeeKolok;

typedef struct {
  MeeKolok meeOrders[MAX_ORDER];
} Customer;

/* ******************************** */
/* *      Function Prototypes      * */
/* ******************************** */
void displayMenu();
void displayOptions();
void displayReceipts(Customer customer, int numOrders);

void addOrder(Customer *customer, int numOrders);
void addExtras(MeeKolok *meeOrder);

/* **************************** */
/* *      Main Function       * */
/* **************************** */
int main() {
  // Initialize a struct variable named customer
  Customer customer;

  // Initialize variable to keep track of program status
  int numOrders = 0;
  int running = 1;
  int option;

  while (numOrders < MAX_ORDER && running != 0) {
    displayMenu();
    printf("Orders available: %d\n", MAX_ORDER - numOrders);
    displayOptions();
    scanf("%d", &option);

    switch (option) {
    case 1: // Add orders
      addOrder(&customer, numOrders);
      numOrders++;
      break;
    case 2: // Display current receipt
      displayReceipts(customer, numOrders);
      break;
    case 3: // Finalize order
      running = 0;
      break;
    default: // Any other options besides available
      printf("\nInvalid option\n");
      break;
    }
  }

  displayReceipts(customer, numOrders);
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
  printf(
      "+================================================================+ \n");
}

void displayOptions() {
  printf("Choose an operation:\n");
  printf("1. Add an order\n");
  printf("2. Display current receipt\n");
  printf("3. Finalize order\n");
  printf("(1-3): ");
}

void displayReceipts(Customer customer, int numOrders) {
  const char *meeTypes[] = {
      "Mee Kolok Kosong", // ID 0
      "Mee Kolok Ayam",   // ID 1
      "Mee Kolok Daging", // ID 2
      "Mee Kolok Tendon"  // ID 3
  };

  const float regularPrices[] = {4.50, 7.00, 8.00, 13.00};
  const float specialPrices[] = {0.00, 9.00, 10.00, 16.00};
  const float extraPrices[] = {1.50, 2.00, 2.50, 3.00};

  float grandTotal = 0.0;

  printf("\n");
  printf("------------------------------------------\n");
  printf("               Order receipt             \n");
  printf("------------------------------------------\n");
  printf("  Total orders: %d\n", numOrders);
  for (int i = 0; i < numOrders; i++) {
    MeeKolok order = customer.meeOrders[i];
    const char *type = (order.meeType == 'R') ? "Regular" : "Special";

    // Calculate noodle price
    float noodlePrice = (order.meeType == 'R') ? regularPrices[order.meeID]
                                               : specialPrices[order.meeID];

    printf("\n  Order #%d: \n", i + 1);
    printf("    %-16s %7s  %5s %2.2f\n", meeTypes[order.meeID], type, "RM",
           noodlePrice);
    float extrasTotal = 0.0;
    const char *extraNames[] = {"Mee", "Chicken", "Meat", "Tendon"};
    for (int j = 0; j < 4; j++) {
      if (order.extrasID[j]) {
        float extraCost = extraPrices[j] * order.extrasQty[j];
        printf("    - %s: %d x RM %.2f       RM %.2f\n", extraNames[j],
               order.extrasQty[j], extraPrices[j], extraCost);
        extrasTotal += extraCost;
      }
    }
    grandTotal += noodlePrice + extrasTotal;
  }
  printf("------------------------------------------\n");
  printf("  Grand Total %26.2f\n", grandTotal);
  printf("------------------------------------------\n");
}

void addOrder(Customer *customer, int numOrders) {
  int meeID = 0;      // Default mee kolok type
  char char_meeID;    // Because user input is a char
  char meeType = 'R'; // Default mee kolok type

  printf("Choose one of our famous Mee Kolok (e.g. a): ");
  scanf(" %c", &char_meeID);

  // We can find out the index/ID of the mee by utilizing ascii codes as
  // integers
  // Example:
  // b - a = 1 is equivalient to
  // 98 - 97 = 1
  // Reference:
  // https://www.ibm.com/docs/en/sdse/6.4.0?topic=configuration-ascii-characters-from-33-126
  // Map meeID to 0, 1, 2, 3
  meeID = char_meeID - 'a';

  if (meeID != 0) {
    printf("Choose a type (R for regular, S for special): ");
    scanf(" %c", &meeType);
  }

  addExtras(&customer->meeOrders[numOrders]);

  customer->meeOrders[numOrders].meeID = meeID;
  customer->meeOrders[numOrders].meeType = meeType;
}

void addExtras(MeeKolok *meeOrder) {
  int extrasID;
  int extrasQty;
  char char_extrasID;

  while (1) {
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
    printf("Add extras for your Mee Kolok Order\n");
    printf("(To stop or if you do  not want to add an extra, press S): ");
    scanf(" %c", &char_extrasID);
    extrasID = char_extrasID - 'a';
    if (char_extrasID == 'S') {
      printf("Order is successful!\n");
      return;
    } else if (extrasID < 0 || extrasID > 3) {
      printf("Invalid choice, please choose a valid extras\n");
    } else {
      break;
    }
  }

  while (1) {
    printf("Enter quantity: ");
    scanf("%d", &extrasQty);
    if (extrasQty < 0) {
      printf("Invalid amount");
    } else {
      break;
    }
  }

  meeOrder->extrasID[extrasID] = 1;
  meeOrder->extrasQty[extrasID] = extrasQty;
}
