int getNL(int sensorPin, int irPin)
{
	int ret=0;
	digitalWrite(irPin,0);
	/*for(int i=0;i<=2;i++)
	{
		delay(2);
		ret+=analogRead(irPin-2);
	}
	digitalWrite(irPin,1);
	return ret/3;*/
	delay(2);
	ret=analogRead(sensorPin);
	digitalWrite(irPin,1);
	return ret;
}

void getData(int sensorPin, int irPin)
{
	boolean ifchange = 0;
	int NL,Ave=0,tem,old=-1;
	int Sample[20],Range[20];
	NL = getNL(sensorPin, irPin);
			
	for (int i=0;i<=19;i++)
	{
		delay(50);
		Sample[i]=NL-analogRead(sensorPin);
		Ave+=Sample[i];
	}
	
	
	
	Ave = Ave/20;
	for (int i=0;i<=19;i++)   
	{
		Sample[i]=abs(Sample[i]-Ave);
		Range[i]=Sample[i];
	}


	for (int x=0;x<=18;x++)
	{
		ifchange = 0;
		for (int y=0;y<=18;y++)
		{
			if(Range[y] < Range[y+1])
			{
				tem = Range[y];
				Range[y] = Range[y+1];
				Range[y+1] = tem;
				ifchange = 1;
			}
		}
		if (!ifchange) break;
	}
	
 
	for (int x=0;x<=19;x++)
	{
		if (old!=Range[x])
		{
			for (int y=0;y<=19;y++)
			{
				if(Sample[y]==Range[x])  
				{
				Serial.print(Range[x]);
				Serial.print(" ");
				}
				else  Serial.print("  ");
			}
			Serial.println("");
			old=Range[x];
		}
	}
	Serial.println("");
	Serial.print("average: ");
	Serial.print(Ave);
	Serial.print("   max: ");
	Serial.print(Range[0]);
	Serial.println();
	Serial.println("----------------------------------------------");
	
}

void setup()
{
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	Serial.begin(9600);
}

void loop()
{

	getData(2, 6);
	digitalWrite(4, 0);
	delay(1);
	Serial.print("***********************");
	Serial.println("***********************");

	delay(100);
}
