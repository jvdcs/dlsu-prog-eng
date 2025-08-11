#include <math.h>
#include <stdio.h>

const int STATE_ENTRY = 0;
const int STATE_EXIT  = 1;
const int STATE_ERROR = 2;
const int STATE_PCE   = 3;
const int STATE_CL    = 4;

// coulomb's constant
const double k = 8.9875517923e9;

int currentState = 0;
int currentUserOption;
double currentUserValue;

void display_formulaOptions() {
  printf("Welcome!\n"
         "       ┌─────────────┐\n"
         "       │ CALCULATORS │\n"
         "       │      4      │\n"
         "       │  ENGINEERS  │\n"
         "       └─────────────┘\n"
         "Select an equation:\n"
         "1) Power Consumption Equation\n"
         "2) Coulomb's Law\n"
         "_) Exit Program\n"
         "Option: ");
}
void display_CL() {
  printf("                         Coulomb's Law\n"
         "                      ┌─────────────────┐\n"
         "                      │     k × q₁ × q₂ │\n"
         "                      │ F = ─────────── │\n"
         "                      │          r²     │\n"
         "                      └─────────────────┘\n"
         "Where: F      = Electric force in newtons            (N)\n"
         "       k      = Coulomb's constant                   (8.99 × "
         "10⁹Nm²/C²)\n"
         "       q₁, q₂ = Magnitude of each charge in coulombs (C)\n"
         "       r      = Distance between charges in meters   (m)\n"
         "\n");
}
void display_CLopts() {
  printf("Solve for:\n"
         "1) F\n"
         "2) r\n"
         "3) q₁ or q₂\n"
         "_) BACK\n"
         "Option: ");
}
void display_PCE() {
  printf(" Power Consumption Equation (CMOS Dynamic Power)\n"
         "             ┌────────────────────┐\n"
         "             │ P = a × C × V² × f │\n"
         "             └────────────────────┘\n"
         "Where: P = Power consumption in watts  (W)\n"
         "       a = Activity factor (0 < a ≤ 1) (unitless)\n"
         "       C = Capacitance in farads       (F)\n"
         "       V = Supply voltage in volts     (V)\n"
         "       f = Clock frequency in hertz    (Hz)\n"
         "\n");
}
void display_PCEopts() {
  printf("Solve for:\n"
         "1) P\n"
         "2) a\n"
         "3) C\n"
         "4) V\n"
         "5) f\n"
         "_) BACK\n"
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
void clear_screen() {
  for (int i = 0; i < 100; i++) {
    printf("\n");
  }
}

// when user tpes 1.2abc
// and scanf("%lf", &x) reads 1.2
// "abc\n" remains in the input
// so next scanf calls will take abc...
// clear_buffer will remove the leftovers from
// influencing the scanf call
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
int take_value() {
  if (scanf("%lf", &currentUserValue) != 1) {
    clear_buffer();
    currentState = STATE_ERROR;
    return 1;
  }
  clear_buffer();
  return 0;
}

// === CALCULATOR FUNCTIONS ===
// power consumption equation
int PCE_P() {
  printf("Solving for P\n");
  printf("a: ");
  if (take_value() != 0)
    return 1;
  double a = currentUserValue;

  printf("C: ");
  if (take_value() != 0)
    return 1;
  double C = currentUserValue;

  printf("V: ");
  if (take_value() != 0)
    return 1;
  double V = currentUserValue;

  printf("f: ");
  if (take_value() != 0)
    return 1;
  double f = currentUserValue;

  double P = a * C * pow(V, 2) * f;
  printf("P = %lf watts", P);
  prompt_wait();
  return 0;
}
int PCE_a() {
  printf("Solving for a\n");
  printf("P: ");
  if (take_value() != 0)
    return 1;
  double P = currentUserValue;

  printf("C: ");
  if (take_value() != 0)
    return 1;
  double C = currentUserValue;

  printf("V: ");
  if (take_value() != 0)
    return 1;
  double V = currentUserValue;

  printf("f: ");
  if (take_value() != 0)
    return 1;
  double f = currentUserValue;

  double a = P / (C * pow(V, 2) * f);
  printf("α = %lf (unitless)", a);
  prompt_wait();
  return 0;
}
int PCE_C() {
  printf("Solving for C\n");
  printf("P: ");
  if (take_value() != 0)
    return 1;
  double P = currentUserValue;

  printf("a: ");
  if (take_value() != 0)
    return 1;
  double a = currentUserValue;

  printf("V: ");
  if (take_value() != 0)
    return 1;
  double V = currentUserValue;

  printf("f: ");
  if (take_value() != 0)
    return 1;
  double f = currentUserValue;

  double C = P / (a * pow(V, 2) * f);
  printf("C = %lf farads", C);
  prompt_wait();
  return 0;
}
int PCE_V() {
  printf("Solving for V\n");
  printf("P: ");
  if (take_value() != 0)
    return 1;
  double P = currentUserValue;

  printf("a: ");
  if (take_value() != 0)
    return 1;
  double a = currentUserValue;

  printf("C: ");
  if (take_value() != 0)
    return 1;
  double C = currentUserValue;

  printf("f: ");
  if (take_value() != 0)
    return 1;
  double f = currentUserValue;

  double V = sqrt(P / (a * C * f));
  printf("V = %lf volts", V);
  prompt_wait();
  return 0;
}
int PCE_f() {
  printf("Solving for f\n");
  printf("P: ");
  if (take_value() != 0)
    return 1;
  double P = currentUserValue;

  printf("a: ");
  if (take_value() != 0)
    return 1;
  double a = currentUserValue;

  printf("C: ");
  if (take_value() != 0)
    return 1;
  double C = currentUserValue;

  printf("V: ");
  if (take_value() != 0)
    return 1;
  double V = currentUserValue;

  double f = P / (a * C * pow(V, 2));
  printf("f = %lf hertz", f);
  prompt_wait();
  return 0;
}
// coulomb's law
int CL_F() {
  printf("Solving for F\n");
  printf("q₁: ");
  if (take_value() != 0)
    return 1;
  double q1 = currentUserValue;

  printf("q₂: ");
  if (take_value() != 0)
    return 1;
  double q2 = currentUserValue;

  printf("r: ");
  if (take_value() != 0)
    return 1;
  double r = currentUserValue;

  double F = (k * q1 * q2) / pow(r, 2);
  printf("F = %lf newtons", F);
  prompt_wait();
  return 0;
}
int CL_q() {
  printf("Solving for q\n");
  printf("F: ");
  if (take_value() != 0)
    return 1;
  double F = currentUserValue;

  printf("r: ");
  if (take_value() != 0)
    return 1;
  double r = currentUserValue;

  printf("q₁: ");
  if (take_value() != 0)
    return 1;
  double q1 = currentUserValue;

  double q2 = (F * pow(r, 2)) / (k * q1);
  printf("q₂ = %lf coulombs", q2);
  prompt_wait();
  return 0;
}
int CL_r() {
  printf("Solving for r\n");
  printf("q₁: ");
  if (take_value() != 0)
    return 1;
  double q1 = currentUserValue;

  printf("q₂: ");
  if (take_value() != 0)
    return 1;
  double q2 = currentUserValue;

  printf("F: ");
  if (take_value() != 0)
    return 1;
  double F = currentUserValue;

  double r = sqrt((k * q1 * q2) / F);
  printf("r = %lf meters", r);
  prompt_wait();
  return 0;
}

// === MAIN LOOPS ===
int state_loop() {
  switch (currentState) {
  case STATE_ENTRY: {
    clear_screen();
    display_formulaOptions();
    if (take_option() != 0)
      return 1;
    switch (currentUserOption) {
    case 1:
      currentState = STATE_PCE;
      break;
    case 2:
      currentState = STATE_CL;
      break;
    default:
      currentState = STATE_EXIT;
      break;
    }
  } break;
  case STATE_CL: {
    clear_screen();
    display_CL();
    display_CLopts();
    if (take_option() != 0)
      return 1;
    clear_screen();
    display_CL();
    switch (currentUserOption) {
    case 1:
      if (CL_F() != 0)
        return 1;
      break;
    case 2:
      if (CL_r() != 0)
        return 1;
      break;
    case 3:
      if (CL_q() != 0)
        return 1;
      break;
    default:
      currentState = STATE_ENTRY;
      break;
    }
  } break;
  case STATE_PCE: {
    clear_screen();
    display_PCE();
    display_PCEopts();
    if (take_option() != 0)
      return 1;
    clear_screen();
    display_PCE();
    switch (currentUserOption) {
    case 1:
      if (PCE_P() != 0)
        return 1;
      break;
    case 2:
      if (PCE_a() != 0)
        return 1;
      break;
    case 3:
      if (PCE_C() != 0)
        return 1;
      break;
    case 4:
      if (PCE_V() != 0)
        return 1;
      break;
    case 5:
      if (PCE_f() != 0)
        return 1;
      break;
    default:
      currentState = STATE_ENTRY;
      break;
    }
  } break;
  case STATE_ERROR: {
    display_error();
    prompt_wait();
    currentState = STATE_ENTRY;
  }
  }
  return 0;
}
int main() {
  while (currentState != STATE_EXIT) {
    state_loop();
  }
  display_exit();
  return 0;
}
