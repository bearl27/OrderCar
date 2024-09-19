//セグメント
#define SEG_G 8
#define SEG_F 9
#define SEG_E 10
#define SEG_D 11
#define SEG_A 12
#define SEG_B 13
#define SEG_C 7
#define SEG_DP 15

//可変抵抗
const int analogInputPin = 1;
//表示する数字
int order = 10;

#include <DynamixelWorkbench.h>
#include <OLLO.h>
OLLO myOLLO;

#if defined(__OPENCM904__)
#define DEVICE_NAME "1"
#elif defined(__OPENCR__)
#define DEVICE_NAME ""
#endif

#define BAUDRATE 1000000

//モーターID
#define DXL_ID 1
#define DXL_ID_2 2
#define DXL_ID_3 3
#define DXL_ID_4 4

DynamixelWorkbench dxl_wb;

void setup()
{
  // while(!Serial);
  //  input回すやつ
  pinMode(analogInputPin, INPUT_ANALOG);
  Serial.begin(115200);

  // セグメント
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  // button
  pinMode(23, INPUT_PULLDOWN);
  pinMode(BOARD_LED_PIN, OUTPUT);

  // moter
  uint8_t dxl_id = DXL_ID;
  uint8_t dxl_id_2 = DXL_ID_2;
  uint8_t dxl_id_3 = DXL_ID_3;
  uint8_t dxl_id_4 = DXL_ID_4;
  uint16_t model_number = 0;

  // moterのために必要なもの(initやping)
  const char *log;
  bool result = false;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);
  }

  result = dxl_wb.ping(dxl_id, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.ping(dxl_id_2, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id_2);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.ping(dxl_id_3, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id_3);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.ping(dxl_id_4, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id_4);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.wheelMode(dxl_id, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }

  result = dxl_wb.wheelMode(dxl_id_2, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }

  result = dxl_wb.wheelMode(dxl_id_3, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }

  result = dxl_wb.wheelMode(dxl_id_4, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change wheel mode");
  }
}

void loop()
{
  int value = analogRead(analogInputPin);
  int buttonState = digitalRead(BOARD_BUTTON_PIN);

//可変抵抗と数字のリンク
  if (value < 102)
  {
    number(1);
    order = 1;
  }
  else if (value < 204)
  {
    number(2);
    order = 2;
  }
  else if (value < 306)
  {
    number(3);
    order = 3;
  }
  else if (value < 408)
  {
    number(4);
    order = 4;
  }
  else if (value < 510)
  {
    number(5);
    order = 5;
  }
  else if (value < 612)
  {
    number(6);
    order = 6;
  }
  else if (value < 714)
  {
    number(7);
    order = 7;
  }
  else if (value < 816)
  {
    number(8);
    order = 8;
  }
  else if (value < 918)
  {
    number(9);
    order = 9;
  }
  else
  {
    number(0);
    order = 0;
  }

  //ボタンを押した時
  if (buttonState == HIGH)
  {
    //Serial.println(value);
    //表示している数字に場合分け
    switch (order)
    {
    case 1:
      move();
      break;
    case 2:
      back();
      break;
    case 3:
      right();
      break;
    case 4:
      left();
      break;
    case 5:
      right_back();
      break;
    case 6:
      left_back();
      break;
    case 7:
      right_arm();
      break;
    case 8:
      left_arm();
      break;
    case 9:
      arms();
      break;
    case 0:
      dancing();
      break;
    }
  }
}

//セグメント表示
void number(int num)
{
  switch (num)
  {
  case 0:
    digitalWrite(SEG_G, HIGH);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 1:
    digitalWrite(SEG_G, HIGH);
    digitalWrite(SEG_F, HIGH);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, HIGH);
    digitalWrite(SEG_A, HIGH);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 2:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, HIGH);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, HIGH);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 3:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, HIGH);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 4:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, HIGH);
    digitalWrite(SEG_A, HIGH);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 5:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, HIGH);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 6:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, HIGH);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 7:
    digitalWrite(SEG_G, HIGH);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, HIGH);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 8:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, LOW);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  case 9:
    digitalWrite(SEG_G, LOW);
    digitalWrite(SEG_F, LOW);
    digitalWrite(SEG_E, HIGH);
    digitalWrite(SEG_D, LOW);
    digitalWrite(SEG_A, LOW);
    digitalWrite(SEG_B, LOW);
    digitalWrite(SEG_C, LOW);
    digitalWrite(SEG_DP, HIGH);
    break;
  }
}

// 1　前進
void move()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)-500);
  delay(3000);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 2　後退
void back()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)-500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)500);
  delay(3000);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 3　右向け右
void right()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)-500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)-500);
  delay(660);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 4　左向け左
void left()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)500);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)500);
  delay(660);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 5　回れ右
void right_back()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)-500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)-500);
  delay(1320);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 6　回れ左
void left_back()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)500);
  delay(1320);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 7　右腕を振る
void right_arm()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)-500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)-500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 8　左腕を振る
void left_arm()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)-500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)-500);
  delay(500);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 9　両腕を振る
void arms()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  for(int i = 0; i < 2; i++){
    dxl_wb.goalVelocity(DXL_ID_3, (int32_t)500);
    dxl_wb.goalVelocity(DXL_ID_4, (int32_t)500);
    delay(500);
    dxl_wb.goalVelocity(DXL_ID_3, (int32_t)-500);
    dxl_wb.goalVelocity(DXL_ID_4, (int32_t)-500);
    delay(500);
  }
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}

// 0　踊る（両腕を振りながら回転）
void dancing()
{
  digitalWrite(BOARD_LED_PIN, LOW);
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)500);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)500);
  for(int i = 0; i < 3; i++){
    dxl_wb.goalVelocity(DXL_ID_3, (int32_t)500);
    dxl_wb.goalVelocity(DXL_ID_4, (int32_t)500);
    delay(500);
    dxl_wb.goalVelocity(DXL_ID_3, (int32_t)-500);
    dxl_wb.goalVelocity(DXL_ID_4, (int32_t)-500);
    delay(500);
  }
  dxl_wb.goalVelocity(DXL_ID_2, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID_3, (int32_t)0);
  dxl_wb.goalVelocity(DXL_ID_4, (int32_t)0);
  digitalWrite(BOARD_LED_PIN, HIGH);
}
