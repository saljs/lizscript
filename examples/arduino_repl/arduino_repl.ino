/*
 * Lizscript example REPL.
 * Requires ~3.4 KB static memory, so will NOT run on UNO
 */

#include <lizscript.h>

#define BUFF_LEN 124
char buffer[BUFF_LEN];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("LizScript version 1.01\nCopyright 2023 Salvatore Skare.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("ls> ");
  while (Serial.available() == 0);
  int len = Serial.readBytesUntil('\n', buffer, BUFF_LEN);
  buffer[len] = '\0';
  Serial.println(buffer);
  
  LSParseResult r = lizscript_eval(buffer);
  print_result(r.result);
}

void print_result(LSData res)
{
  switch (res.type) {
    case LS_INVALID_T:
      Serial.println("Invalid command");
      return;
    case LS_INT_T:
      Serial.println(res.ival);
      return;
    case LS_FLOAT_T:
      Serial.println(res.fval);
      return;
    case LS_BOOL_T:
      Serial.println(res.bval);
      return;
    case LS_CHAR_T:
      Serial.println(res.cval);
      return;
    default:
      Serial.println("<Func>");
  }
}
