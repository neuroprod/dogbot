

void setup() {

  Serial.begin(115200);
}

void loop() {
 
  int i0 = analogRead(A0);
  int i1 = analogRead(A1);
  int i3 = analogRead(A3);
  int i4 = analogRead(A4);
  int i5 = analogRead(A5);//batery

  Serial.print(i0);
  Serial.print(" ");
  Serial.print(i1);
  Serial.print(" ");
  Serial.print(i3);
  Serial.print(" ");
  Serial.print(i4);
  Serial.print(" ");
  Serial.println(i5);

  delay(2);
}
