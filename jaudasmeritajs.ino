#include <Adafruit_GFX.h> // Displejam nepieciešamo bibliotēku iekļaušana
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH 128 // OLED ekrāna platums pikseļos
#define SCREEN_HEIGHT 64 // OLED ekrāna augstums pikseļos

// SSD1306 displeja deklarācija savienotam ar I2C (SDA, SCL piniem)
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int lev; // Deklarē mainīgo lev priekš strāvas aprēķināšanas

void setup() {
  // Inicializē seriālo komunikāciju
  Serial.begin(9600);

  // Inicializē OLED displeju
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 inicializācija neizdevās"));
    for (;;); 
  }
  
  display.display();
  delay(2000); // Pauze uz 2 sekundēm
  
  // Notīra buferi
  display.clearDisplay();
}

void loop() {
  // Sprieguma nolasīšana un aprēķināšana
  int level = analogRead(A1);
  float voltage = level * (5.0 / 1023.0);
  float uin = (voltage * 14100) / 2100;
// Strāvas nolasīšana un aprēķināšana
  lev = analogRead(A0);
  float lev1 = lev * (5.0 / 1023.0);
  float current = (lev1 - 2.5) / 0.185;

  // Aprēķina jaudu (P = V * I)
  float power = uin * current;
 

  // Izvada vērtības uz OLED ekrāna, novietojot kursoru trijās rindās (katram lielumam savā)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Spriegums (V): ");
  display.println(uin);

  display.setCursor(0, 16);
  display.print("Strāva (A): ");
  display.println(current);

  display.setCursor(0, 32);
  display.print("Jauda (W): ");
  display.println(power);

  display.display();

  delay(1000); // Pauze
}
