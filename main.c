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

/* typedef enum { */
/*   MK_KOSONG, */
/*   MK_AYAM, */
/*   MK_DAGING, */
/*   MK_TENDON, */
/*   MK_AYAM_SP, */
/*   MK_DAGING_SP, */
/*   MK_TENDON_SP, */
/* } MeeKolok; */

/* ******************************** */
/* *      Function Prototypes      * */
/* ******************************** */
void displayMenu();
void displayOptions();
void displayReceipts(Customer *customer, int numOrders);

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
      displayReceipts(&customer, numOrders);
      break;
    case 3: // Finalize order
      running = 0;
      break;
    default: // Any other options besides available
      printf("\nInvalid option\n");
      break;
    }
  }

  printf("You have reached the order limit of 4! Here is your final receipt");
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

void addOrder(Customer *customer, int numOrders) {
  int meeID;
  char char_meeID;
  char meeType = 'R';

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

    addExtras(&customer->meeOrders[numOrders]);
  }

  customer->meeOrders[numOrders].meeID = meeID;
  customer->meeOrders[numOrders].meeType = meeType;
}

void addExtras(MeeKolok *meeOrder) {}

void displayReceipts(Customer *customer, int numOrders) {}
