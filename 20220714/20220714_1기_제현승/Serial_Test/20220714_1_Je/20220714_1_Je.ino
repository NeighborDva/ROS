
#define MAX_RECEIVE_DATA 20
#define SIZE_PACKET  9

union
{
    short data ;
    char  bytedata[2];    
} m_int, m_crc;

union
{
    float data ;
    char  bytedata[4];    
} m_float;

char receive_buff[MAX_RECEIVE_DATA] ={0,};
char send_buff[SIZE_PACKET+1] ={0,};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
}

int crc_check(void)
{
  int crc=0;
  for(int i=1;i<6;i++)
  {
     send_buff[i];
     crc += send_buff[i];
  }
  return crc;
}
void send_int_data(int input)
{
   m_int.data = input;
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data2(int input)
{
   m_int.data = input;
   Serial.print("#I");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data3(int input)
{
   m_int.data = input;
   Serial.print("#I");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   send_buff[6] = 0x00;
   send_buff[7] = 0x4e;  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data4(int input)
{
   m_int.data = input;
   Serial.print("#I");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data5(int input)
{
   m_int.data = input;
   Serial.print("#***");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   send_buff[7] = 0x4d;
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data6(int input)
{
   m_int.data = input;
   Serial.print("#***");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   send_buff[7] = 0x99;
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data7(int input)
{
   m_int.data = input;
   Serial.print("#***");
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 0;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0]; 
   send_buff[6] = 0x12; 
   send_buff[7] = 0x17;
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data_wrong1(int input)
{
   m_int.data = input;
   send_buff[0] = '#';
   send_buff[1] = 's';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 10;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   m_crc.data= crc_check();
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i],HEX);
     send_buff[i] = 0; 
   }
   
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data_wrong2(int input)
{
   m_int.data = input;
   Serial.print("########$*");
   send_buff[0] = '#';
   send_buff[1] = 's';
   send_buff[2] = m_int.bytedata[1];
   send_buff[3] = m_int.bytedata[0];
   send_buff[4] = 10;
   send_buff[5] = 0;   
   send_buff[8] = '*';
   
   //m_crc.data= crc_check();
   send_buff[6] = 0x00;
   send_buff[7] = 0x4e;  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(send_buff[i]);
     send_buff[i] = 0; 
   }
   
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_test_data(int size_packet )
{

   send_buff[0] = '#';
   send_buff[1] = 's';
      
   for(int i=0;i <size_packet; i++)
   {
      
      Serial.print(send_buff[i]);
     send_buff[i] = 0;     
   }

  
}

int data = 0;

void loop() {
  // put your main code here, to run repeatedly:

  send_int_data(2);
  delay(1000);

  send_int_data2(2);
  delay(1000);

  send_int_data3(2);
  delay(1000);

  send_int_data4(5);
  delay(1000);

  send_int_data5(5);
  delay(1000);

  send_int_data5(5);
  delay(1000);

   send_int_data7(5);
  delay(1000);



  send_int_data(29);
  delay(1000);
  send_int_data3(29);
  delay(1000);

  /*
  send_int_data_wrong1(10);
  delay(1000);

  send_int_data_wrong2(10);
  delay(1000);
  */
}
