// Requirements
// - Display menu for user to take orders
// - Allow maximum of 4 packs of MK per order
// - Display details of MK orders made by each customer
// - Display the calculated total price in a single receipt
// - Take order continuously from customers until user choose to exit
// - Display the transaction details at anytime when it is needed
// - Save all the order transaction to a file

#include <stdio.h>

/* ******************************** */
/* *        Constant values       * */
/* ******************************** */
const int MAX_ORDER = 4;

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

/* ********************************** */
void displayMenu();
void displayOptions();
void executeOption(int *option);

/* **************************** */
/* *      Main Function       * */
/* **************************** */
int main() {
  int order = 0;
  int option;

  while (order < MAX_ORDER) {
    displayMenu();
    printf("Orders available: %d\n", MAX_ORDER - order);
    displayOptions();
    scanf("%d", &option);

    switch (option) {
    case 1:
      order++;
      break;
    case 2:
      order++;
      break;
    case 3:
      order++;
      break;
    default:
      printf("Invalid option\n");
      break;
    }
  }
  return 0;
}

/* *********************************** */
/* *      Function Definitions       * */
/* *********************************** */
void displayMenu() {
  printf("\n");
  printf(
      "==================================================================\n");
  printf(
      "|                         Mi Kolok Menu                          |\n");
  printf(
      "==================================================================\n");
  printf(
      "|       Package       | Regular (R) | Special (S) | Extra (RM)   |\n");
  printf(
      "|                     |    (RM)     |     (RM)    |              |\n");
  printf(
      "------------------------------------------------------------------\n");
  printf(
      "| a) Mi Kolok Kosong  | 4.50        | -           | Mee/1.50     |\n");
  printf(
      "| b) Mi Kolok Ayam    | 7.00        | 9.00        | Chicken/2.00 |\n");
  printf(
      "| c) Mi Kolok Daging  | 8.00        | 10.00       | Meat/2.50    |\n");
  printf(
      "| d) Mi Kolok Tendon  | 13.00       | 16.00       | Tendon/3.00  |\n");
  printf(
      "==================================================================\n");
}

void displayOptions() {
  printf("Choose an operation:\n");
  printf("1. Add an order\n");
  printf("2. Display current receipt\n");
  printf("3. Finalize order\n");
  printf("(1-3): ");
}
