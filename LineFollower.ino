// Sensör pinleri
const int sensorS1 = 2; // En sol sensör (S1)
const int sensorS2 = 3; // Orta sol sensör (S2)
const int sensorS3 = 4; // Orta sağ sensör (S3)
const int sensorS4 = 5; // En sağ sensör (S4)

// Motor pinleri
const int in1 = 10; // Sol motor IN1
const int in2 = 9;  // Sol motor IN2
const int in3 = 8;  // Sağ motor IN3
const int in4 = 7;  // Sağ motor IN4
const int enA = 11; // Sol motor PWM
const int enB = 6;  // Sağ motor PWM

void setup() {
  Serial.begin(9600); // Seri iletişimi başlat

  // Sensör pinlerini giriş olarak ayarla
  pinMode(sensorS1, INPUT);
  pinMode(sensorS2, INPUT);
  pinMode(sensorS3, INPUT);
  pinMode(sensorS4, INPUT);

  // Motor pinlerini çıkış olarak ayarla
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  // Sensör değerlerini oku
  int s1 = digitalRead(sensorS1);
  int s2 = digitalRead(sensorS2);
  int s3 = digitalRead(sensorS3);
  int s4 = digitalRead(sensorS4);

  // Sensör durumlarına göre motorları kontrol et
  if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1) {
    // Siyah çizgi en sağda
    setMotorSpeeds(255, 0); // Sol tam hız (255), sağ dur (0)
  } else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 1) {
    // Siyah çizgi sağda iki sensörde
    setMotorSpeeds(255, 76); // Sol tam hız (255), sağ %30 hız (76)
  } else if (s1 == 0 && s2 == 0 && s3 == 1 && s4 == 0) {
    // Siyah çizgi sağ orta sensörde
    setMotorSpeeds(255, 153); // Sol tam hız (255), sağ %60 hız (153)
  } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 0) {
    // Siyah çizgi tam ortada
    setMotorSpeeds(255, 255); // Her iki motor tam hız (255)
  } else if (s1 == 0 && s2 == 1 && s3 == 0 && s4 == 0) {
    // Siyah çizgi sol orta sensörde
    setMotorSpeeds(153, 255); // Sol %60 hız (153), sağ tam hız (255)
  } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0) {
    // Siyah çizgi solda iki sensörde
    setMotorSpeeds(76, 255); // Sol %30 hız (76), sağ tam hız (255)
  } else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 0) {
    // Siyah çizgi en solda
    setMotorSpeeds(0, 255); // Sol dur (0), sağ tam hız (255)
  } else {
    // Hiçbir sensör algılamıyorsa
    stopMotors(); // Her iki motoru durdur
  }

  // Sensör durumlarını seri monitörde göster
  Serial.print("S1: "); Serial.print(s1);
  Serial.print(" S2: "); Serial.print(s2);
  Serial.print(" S3: "); Serial.print(s3);
  Serial.print(" S4: "); Serial.println(s4);

  delay(100); // Kısa bir bekleme süresi
}

// Motor hızlarını ayarlayan fonksiyon
void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  // Sol motor ileri
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Sağ motor ileri
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // PWM ile hız ayarı
  analogWrite(enA, leftSpeed);  // Sol motor PWM
  analogWrite(enB, rightSpeed); // Sağ motor PWM
}

// Motorları durduran fonksiyon
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, 0); // Sol motor durdur
  analogWrite(enB, 0); // Sağ motor durdur
}
