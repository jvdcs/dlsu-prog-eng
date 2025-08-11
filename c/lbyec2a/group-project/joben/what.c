
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// utility functions. for formatting
int clear(int spaces) { // to print n number of newlines
  for (int yes = 0; yes < spaces; yes++) {
    printf("\n");
  }
}
void input_buffer() { //	equivalent to scanf("%*[^\n]"); which excludes
                      //newline input from what is scanned and avoids null
                      //states
  int yea;
  while ((yea = getchar()) != '\n' && yea != -1)
    ;
}
void input_error() { printf("\nWrong input. Try again\n"); }

// loop variable constants
int current_option;
double current_value;
int initialState = 0;
int getOut = 1;
int error = 2; // if the current state of the program is an error, it will read
               // the error case and return to menu
const int Program1 = 3; // case corresponding to program 1
const int Program2 = 4; // case corresponding to program 2
int loop_control; // to ensure that only the allowed values 1-3 are read as
                  // correct. the do while loop will repeat if it reads
                  // character or not allowed number
int current_state = 0;

// display
void display_menu() {
  printf("Practical Exam 2: math programs\n");
  clear(1);
  printf("Formulas to evaluate:\n");
  printf("1. Solving for Required force to open a rectangular sluice gate\n");
  printf("2. Passive force of Sheet-Pile wall in dry sand.\n");
  printf("3. Exit.\n");
  printf("\nWhat Formula to calculate? ");
}
void display_Program1() {
  printf("\nSolving for Required force to open a rectangular sluice gate\n\n"
         "       Ma = 0:	P(hg) - F(hcp - h_water)\n\n"
         "Where:\n\n"
         "Ma - summation of moment at the hinge point A., lb-ft\n\n"
         "P - horizontal force applied to the gate, lb\n\n"
         "hg - depth of the sluice gate, ft\n\n"
         "F - applied hydrostatic force of the dam to the gate, lb\n\n"
         "hcp - depth of the applied force from the water surface, ft\n\n"
         "h_water - submerged depth of the hinge from the water surface, ft\n\n"
         "Variable selection (Solving for F will also solve for hcp and "
         "vice-versa):\n"
         "Solving for force P will take the computed values of hcp and F.\n");
  printf("1. F\n");
  printf("2. hcp\n");
  printf("3. Solving for force P\n");
  printf("4. return\n");
  printf("\nChoice? ");
}

void display_Program2() {
  printf("\nSolving for Total Active force on Sheet-pile wall in dry sand\n\n"
         "       P = (0.5*(sigma_2)*(L)) + (0.5*(sigma_2)*(L_3))\n\n"
         "Where:\n\n"
         "sigma_2 - lateral earth pressure of dry sand, kN/m^3\n\n"
         "L - depth of sheet pile, m\n\n"
         "L_3 - depth of hinge point from dredge line\n\n"
         "F - applied hydrostatic force of the dam to the gate, lb\n\n"
         "Variable selection :\n"
         "Solving for force P will take the computed values of hcp and F.\n");
  printf("1. sigma_2\n");
  printf("2. L_3\n");
  printf("3. L\n");
  printf("4. Force P");
  printf("\nChoice? ");
}
void display_exit() {
  printf("\nTime to close the program. Thank you so much\n");
}
void display_error_variable() {
  printf("\nWrong input for variable. Returning to menu.\n");
}

const double unit_weight = 62.4;

void pause() { // shorthand function as just adding system("PAUSE") after each
               // variable calculation needs another newline. just makes things
               // easier for me
  clear(1);
  printf("Press any key to continue . . .");
  input_buffer();
}
int input_option() {
  if (scanf("%d", &current_option) != 1) {
    input_buffer();
    current_state = error;
    return 1;
  }
  input_buffer();
  return 0;
}

int input_value() { // returning 1 goes to error state then loop back to main
  if (scanf("%lf", &current_value) != 1) {
    input_buffer();
    current_state = error;
    return 1;
  }
  input_buffer();
  return 0;
}

// === CALCULATOR FUCNTIONS ===
int sigma_2() {
  printf("\nSomehow the variables didn't update so I cannot solve it sadly.");
  pause();
  return 0;
}
int L_3() {
  printf("\nSomehow the variables does not update so I cannot solve it sadly.");
  pause();
  return 0;
}
int DepthL() {
  printf("\nSomehow the variables does not update so I cannot solve it sadly.");
  pause();
  return 0;
}
int Force_P() {
  printf("\nSomehow the variables does not update so I cannot solve it sadly.");
  pause();
  return 0;
}

// Program 1:
int hydroF() {
  double hydroF;
  double hcp;
  double forceP;

  printf("Solving F\n");
  clear(2);
  printf("	F = Unit weight of water * (hcg)(Area of gate)\n\n");
  printf("Additional formulas needed:\n\n");
  printf("	hcg = h_water + 0.5*depth of the gate\n\n");
  printf("Area of gate = depth of gate * width of gate\n\n");
  pause();
  // input parameters
  printf("Depth : ");
  if (input_value() != 0) {
    return 1;
  }
  double hg = current_value;
  printf("\n%f\n", hg);

  printf("Width of gate: : ");
  if (input_value() != 0) {
    return 1;
  }
  double gate_width = current_value;

  printf("\ndepth of water to the hinge: ");
  if (input_value() != 0) {
    return 1;
  }
  double h_water = current_value;

  hydroF = unit_weight * (h_water + (0.5 * hg)) * (gate_width * hg);
  printf("\nComputed hydrostatic force F = %.2f lbs", hydroF);
  pause();
  return 0;
}
int h_cp() {
  printf("\nSomehow the variables didn't update so I cannot solve it sadly.");
  pause();
  return 0;
}
int force() {
  printf("\nSomehow the variables didn't update so I cannot solve it sadly.");
  pause();
  return 0;
}

// main loop
int loop() {
  switch (current_state) {
  case 0: {
    clear(50);
    display_menu();
    do {
      while ((scanf("%d", &current_option)) == 0 || current_option < 0) {
        input_buffer();
        input_error();
        clear(1);
        printf("What operation to calculate? ");
      }
      if (current_option == 1 || current_option == 2 || current_option == 3) {
        loop_control = 1;
        printf("\nCorrect input");
        clear(2);
      } else { // this statement will make the loop repeat to the top so that
               // the only numbers accepted in the program are 1-3
        loop_control = 0;
        printf("wrong input.\n");
        current_option =
            -1; // choice is overwritten to -1 to trigger the first a
        printf("\nWhat operation to calculate? ");
      }

    } while (loop_control == 0);
    switch (current_option) {
    case 1:
      current_state = Program1;
      break;
    case 2:
      current_state = Program2;
      break;
    default:
      current_state = getOut;
      break;
    }
  } break;
  case Program1: { // program 1
    clear(50);
    display_Program1();
    if (input_option() != 0)
      return 1;
    switch (current_option) {
    case 1:
      if (hydroF() != 0)
        return 1;
      break;
    case 2:
      if (h_cp() != 0)
        return 1;
      break;
    case 3:
      if (force() != 0)
        return 1;
      break;
    default:
      current_state = initialState;
      break;
    }
  } break;
  case 4: { // program 2
    clear(50);
    display_Program2();
    if (input_option() != 0)
      return 1;
    switch (current_option) {
    case 1:
      if (sigma_2() != 0)
        return 1;
      break;
    case 2:
      if (L_3() != 0)
        return 1;
      break;
    case 3:
      if (DepthL() != 0)
        return 1;
      break;
    case 4:
      if (Force_P() != 0)
        return 1;
      break;
    }
    break;
  case 2: { // error state
    display_error_variable();
    current_state = initialState;
    system("PAUSE");
  }
  default: {
    current_state = initialState;
    break;
  }
  }
  }
  return 0;
}
int main() {
  while (current_state != getOut) {
    loop();
  }
  display_exit();
  return 0;
}
