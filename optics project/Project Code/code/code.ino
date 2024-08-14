
const int Photodiode_pin = A0; // Photodiode pin number (analog pin A0)
unsigned long timer = 0; // timer variable
unsigned long switch_time = 0; // stores the pulse time that the switch has been pressed
unsigned long  x = 0; // stores the input values of dots and dashes
unsigned long  y = 0; // stores the reverse of input values of dots and dashes

void setup() 
{
  Serial.begin(9600);
  pinMode(Photodiode_pin, INPUT);
}

void loop() 
{
  if( analogRead(Photodiode_pin) ) // if the photodiode receives an IR light
  {
    timer = millis();
    while(1)
    {
      if( !analogRead(Photodiode_pin) ) // if the photodiode doesn't receive an IR light
      {
        timer = millis() - timer;
        break;
      }
    }

    switch_time = timer; // stores the pulse time that the switch has been pressed

    if( (switch_time<300) && (switch_time>50) ) // represent the dot input, generate a number contains 1's and 2's
    {
      if(x==0)
      {
        x+=1;
        Serial.print("Dot input, output is: ");
        Serial.println(x);
        Serial.print("Hold time (ms) : ");
        Serial.println(switch_time);
      }
      else
      {
        x*=10;
        x+=1;
        Serial.print("Dot input, output is: ");
        Serial.println(x);
        Serial.print("Hold time (ms) : ");
        Serial.println(switch_time);
      }
    }
    else if( (switch_time<2000) && (switch_time>300) ) // represent the dash, generate a number contains 1's and 2's
    {
      if(x==0)
      {
        x+=2;
        Serial.print("Dash input, output is: ");
        Serial.println(x);
        Serial.print("Switch hold time (ms) is: ");
        Serial.println(switch_time);
      }
      else
      {
        x*=10;
        x+=2;
        Serial.print("Dash input, output is: ");
        Serial.println(x);
        Serial.print("Switch hold time (ms) is: ");
        Serial.println(switch_time);
      }
    }
    else if( (switch_time>2000) ) // represent the end of inputs
    {
      Serial.println("");
      Serial.print("Detected letter is: ");
      switch(x) // compare input data stored in 'x' with the morse code table
      {
        case 12 : Serial.println("A"); break; 
        case 2111 : Serial.println("B"); break;
        case 2121 : Serial.println("C"); break;
        case 211 : Serial.println("D"); break;
        case 1 : Serial.println("E"); break;
        case 1121 : Serial.println("F"); break;
        case 221 : Serial.println("G"); break;
        case 1111 : Serial.println("H"); break;
        case 11 : Serial.println("I"); break;
        case 1222 : Serial.println("J"); break;
        case 212 : Serial.println("K"); break;
        case 1211 : Serial.println("L"); break;
        case 22 : Serial.println("M"); break;
        case 21 : Serial.println("N"); break;
        case 222 : Serial.println("O"); break;
        case 1221 : Serial.println("P"); break;
        case 2212 : Serial.println("Q"); break;
        case 121 : Serial.println("R"); break;
        case 111 : Serial.println("S"); break;
        case 2 : Serial.println("T"); break;
        case 112 : Serial.println("U"); break;
        case 1112 : Serial.println("V"); break;
        case 122 : Serial.println("W"); break;
        case 2112 : Serial.println("X"); break;
        case 2122 : Serial.println("Y"); break;
        case 2211 : Serial.println("Z"); break;
        case 12222 : Serial.println("1"); break;
        case 11222 : Serial.println("2"); break;
        case 11122 : Serial.println("3"); break;
        case 11112 : Serial.println("4"); break;
        case 11111 : Serial.println("5"); break;
        case 21111 : Serial.println("6"); break;
        case 22111 : Serial.println("7"); break;
        case 22211 : Serial.println("8"); break;
        case 22221 : Serial.println("9"); break;
        case 22222 : Serial.println("0"); break;
        case 121212 : Serial.println("."); break;
        case 221122 : Serial.println(","); break;
        case 112211 : Serial.println("?"); break;

        default: Serial.println("Unknown input"); break; // display for unknown characters
      }

      y = reverse_number(x); // stores the reverse of input values of dots and dashes
      x=0; // resets the input data variable
      
      Serial.print("Reversed input is: ");
      Serial.println(y);
      Serial.println("");

      play_buzzer(y); // play the buzzer sound
      y=0; // resets the reverse of input data variable

    }
  }
}


unsigned long reverse_number(unsigned long a) // creating a function that reverses (returns mirror) number
{
  unsigned long b = 0;
  while(a)
  {
    if(b==0)
    {
      b = a%10;
      a/=10;
    }
    else
    {
      b*=10;
      b = b + a%10;
      a/=10;
    }
  }
  
  return b;
}



void play_buzzer(unsigned long b) // creating a function plays the buzzer
{
  while(b)
  {
    if( b%2 == 1 )
    {
      b/=10;

      tone(4, 1000, 200); // takes pin number, tone frequency, sound pulse duration 
      timer = millis();

      while(1)
      {
        if( (millis()-timer > 1200) ) // -> 1200-200 = 1000 ms stoping between each two tones 
        {
          break;
        }
      }
    }
    else if( b%2 == 0 )
    {
      b/=10;

      tone(4, 1000, 600); // takes pin number, tone frequency, sound pulse duration 
      timer = millis();

      while(1)
      {
        if( (millis()-timer > 1600) ) // -> 1600-600 = 1000 ms stoping between each two tones 
        {
          break;
        }
      }
    }
  }
}
