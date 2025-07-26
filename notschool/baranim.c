#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main() {
  struct timeval timevalue;
  gettimeofday(&timevalue, NULL);

  long ms = (timevalue.tv_sec * 1000 + timevalue.tv_usec / 1000);

  const char msg[] =
      "It'sbeenayeardaddyIreallyreallymissyoumommysaysyouwentto"
      "thestoretogetsomemilkanywaysimfailingallmyclassesandmommy"
      "hitsmeveryfrequentlyandshechangedmynametotickletipson"
      "anywaysdaddyiforgiveyouforabusingmepleasecomeback";
  int frame = (ms / 200) % strlen(msg); // 150ms per character

  printf("%c\n", msg[frame]);
  return 0;
}
