#define ECHO 49
#define TRIGGER 53
//TIMEOUT = maximum distance in meters / 340 * microsecondsInASecond
#define TIMEOUT 5000 


void setup()
{
  usonicInit();
  Serial.begin(115200);
}

void loop()
{
  Serial.println(usonicAvg());
}

void usonicInit()
{
  pinMode(TRIGGER, 1);
  digitalWrite(TRIGGER, 0);
  pinMode(ECHO, 0);
  digitalWrite(ECHO, 0);


}

int usonicAvg() 
{
  int times[16];
  for(int i=0; i<16; i++)
  {
    times[i] = usonicRead();
    delay(2);
  }
  qsort(times, 16, sizeof(int), compare_ints);
  float avg = 0;
  for(int i=4; i<12; i++)
    avg += times[i];
  avg /= 8.0;

  return (int)avg;
}


int compare_ints(const void *a, const void *b)
{
  const int *da = (const int *)a;
  const int *db = (const int *)b;
  return (*da>*db)-(*da<*db);
}


int usonicRead()
{
  delayMicroseconds(TIMEOUT);
    digitalWrite(TRIGGER, 1);
    delayMicroseconds(5);
    digitalWrite(TRIGGER, 0);
    delayMicroseconds(5);
    digitalWrite(TRIGGER, 1);
    delayMicroseconds(5);
    digitalWrite(TRIGGER, 0);
    
    int distance = pulseIn(31, 1, TIMEOUT);
    if(distance == 0)
      distance = TIMEOUT;

    return distance;
}
