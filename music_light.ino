#define MIC_IN  3
#define L1 3
#define L2 5
#define L3 6
#define L4 9
#define L5 10
#define L6 11
#define SMAX 1023
#define MAX 254


const int SAMPLE_WINDOW = 63; // 50ms = 20 hertz;
unsigned long sample = 0;

void lightshow(int, int, int, int);

void setup(){
    Serial.begin(9600);
    analogWrite(L1,0);
    analogWrite(L2,0);
    analogWrite(L3,0);
    analogWrite(L4,0);
    analogWrite(L5,0);
    analogWrite(L6,0);
}

void loop(){
    unsigned long startMillis = millis();
    unsigned int p2p = 0, 
                 sigMax = 0, 
                 sigMin = SMAX;
    int out = 0;
    
    while (millis() - startMillis < SAMPLE_WINDOW)
    {
        sample = analogRead(MIC_IN);
        if (sample <= SMAX){
            if (sample > sigMax)
                sigMax = sample;
            else if (sample < sigMin)
                sigMin = sample;
        }
    }
    p2p = sigMax - sigMin;  //volts = (p2p*5.0)/1024;
    out = map(p2p, 0, SMAX, 0, MAX);

    int cblue = 80, fblue = 40;
    int cred = 1, fred = 0;
    int cwhite = 100, fwhite = 40;
    
    darkshow(L1, cblue, fblue, out);
    lightshow(L2, cred, fred, out);
    lightshow(L3, cred, fred, out);
    lightshow(L4, cred, fred, out);
    lightshow(L5, cred, fred, out);
    flash(L6, cwhite, fwhite, out);

    Serial.println(out);
      
}

void lightshow(int pin, int c, int f, int o){
    double r = 1.34;
    if (o > c)
      analogWrite(pin, o*r);
    else
      analogWrite(pin, f);
}

void darkshow(int pin, int c, int f, int o){
    if (o>c)
      analogWrite(pin,f);
    else
      analogWrite(pin,128);
}

void flash(int pin, int c, int f, int o){
   if(o>c)
      analogWrite(pin,254);
   else
      analogWrite(pin,f);
}
