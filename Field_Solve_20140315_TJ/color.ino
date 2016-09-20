

void colorInterrupt()
{
  switch(colorStatus)
  {
    case 0:
      colorDarkValue = (float)analogRead(PHOTO);
      digitalWrite(LRED, 1);
      break;
    case 1:
      currentColor.r = colorDarkValue - (float)analogRead(PHOTO);
      digitalWrite(LRED, 0);
      digitalWrite(LGREEN, 1);
      break;
    case 2:
      currentColor.g = colorDarkValue - (float)analogRead(PHOTO);
      digitalWrite(LGREEN, 0);
      digitalWrite(LBLUE, 1);
      break;
    case 3:
      currentColor.b = colorDarkValue - (float)analogRead(PHOTO);
      digitalWrite(LBLUE, 0);
      break;
  }
  colorStatus++;
  colorStatus %= 4;
}


void debugWaitForGo()
{
  pinMode(PHOTO, INPUT);
  delay(100);
  float favg = 0;
  for(int i=0; i<4; i++)
  {
    favg += (float)analogRead(PHOTO);
    delay(50);
  }
  favg /= 4.0;
  int noLight = (int)favg;
  Serial.print("light level: ");
  Serial.println(noLight);
}

void waitForGo()
{
  stopColor();
  //warning, this will block indefinitely
  pinMode(PHOTO, INPUT);
  delay(500);
  float favg = 0;
  for(int i=0; i<10; i++)
  {
    favg += (float)analogRead(PHOTO);
    delay(50);
  }
  favg /= 10.0;
  int noLight = (int)favg;
  
  int goCount = 0;
  while(goCount < 3) //wait for three good reads in a row
  {
    if(abs((int)analogRead(PHOTO) - noLight) > 100)
    {
      goCount++;
    }
    else
    {
      goCount = 0;
    }
    delay(50);
  }
}


void stopColor()
{
  Timer1.detachInterrupt();
  //set LED pins as outputs and low (off)
  pinMode(LRED, 1);
  pinMode(LGREEN, 1);
  pinMode(LBLUE, 1);
  //digitalWrite(LRED, 1);
  //delay(300);
  digitalWrite(LRED, 0);
  //digitalWrite(LGREEN, 1);
  //delay(300);
  digitalWrite(LGREEN, 0);
  //digitalWrite(LBLUE, 1);
  //delay(300);
  digitalWrite(LBLUE, 0);
}
  

void initColor()
{
  //set LED pins as outputs and low (off)
  pinMode(LRED, 1);
  pinMode(LGREEN, 1);
  pinMode(LBLUE, 1);
  //digitalWrite(LRED, 1);
  //delay(300);
  digitalWrite(LRED, 0);
  //digitalWrite(LGREEN, 1);
  //delay(300);
  digitalWrite(LGREEN, 0);
  //digitalWrite(LBLUE, 1);
  //delay(300);
  digitalWrite(LBLUE, 0);

  pinMode(PHOTO, INPUT);
  delay(250);
  Timer1.initialize(250000); //4 times per second
  Timer1.attachInterrupt(colorInterrupt);
}


void debugColor()
{
  RGB currColor = getColor();
  rgbPrint(currColor);
  printColor(whatColor(currColor));
  delay(500);
} 


void printColor(int colorNum)
{
  if(colorNum == -1)
  {
    Serial.println("UNKNOWN");
  }
  else
  {    
    Serial.println(colorNames[colorNum]);
  }
}


int whatColor(RGB currColor)
{
  Serial.println("Running zombie whatColor");
  getsensors();
  int numberOfSetLBits=0;

  if(sensorl1)
    numberOfSetLBits++;
  if(sensorl2)
    numberOfSetLBits++;
  if(sensorl3)
    numberOfSetLBits++;
  if(sensorl4)
    numberOfSetLBits++;
  if(sensorl5)
    numberOfSetLBits++;
  if(numberOfSetLBits>2){
    Serial.println("Zombie whatColor found block. Stepping 600 west");
    stepcount+=600;   
    for(int i=0;i<600;i++)
      west();
    return 3;
  }
  return 1;
  
  /*
  float distance[NUMCOLORS] = {
    0    };
  for(int i=0; i<NUMCOLORS; i++)
  {
    distance[i] = colorDistance(currColor, *correlate[i]);
  }
  int minIndex = 0;
  int minValue = distance[0];
  for(int i=1; i<NUMCOLORS; i++)
  {
    if(distance[i] < minValue)
    {
      minValue = distance[i];
      minIndex = i;
    }
  }
  //Serial.print("distance: ");
  //Serial.println(minValue);
  if(minValue > MAXDISTANCE)
  {
    //bad color read
    return -1;
  }
  return minIndex;
  */
}


float colorDistance(RGB currColor, RGB std)
{
  float r = currColor.r - std.r;
  float g = currColor.g - std.g;
  float b = currColor.b - std.b;
  return sqrt(r*r + g*g + b*b);
}


void rgbPrint(RGB col)
{
  Serial.print(col.r);
  Serial.print("\t");
  Serial.print(col.g);
  Serial.print("\t");
  Serial.println(col.b);
}


RGB getColor()
{
  RGB fooColor;
  fooColor.r = currentColor.r;
  fooColor.g = currentColor.g;
  fooColor.b = currentColor.b;
  return fooColor;
}


