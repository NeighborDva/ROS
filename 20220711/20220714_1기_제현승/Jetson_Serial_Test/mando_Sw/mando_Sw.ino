#define MAX_RECEIVE_DATA 20
#define SIZE_PACKET  9

union
{
    int data ;
    byte  bytedata[2];
} m_int, m_crc;

union
{
    float data ;
    byte  bytedata[4];
} m_float;

char receive_buff[MAX_RECEIVE_DATA] ={0,};
char send_buff[SIZE_PACKET+1] ={0,};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}

//crc 

int crc_cal(int type)
{
  int crc = 0;
  int crc_gen_code=6; // X*2 + X ->CRC발생함수 , 최고차수 2 원래 데이터에 0 2개 추가

  if(type == 0)// int
  {
   crc = (m_int.data<<2) % crc_gen_code;
  }
  else
  {
    crc =((int)(m_float.data)<<2) % crc_gen_code;
  }
  
  return crc;
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

//

void send_int_data(int input)
{
   m_int.data = input;
   send_buff[0] = '#';
   send_buff[1] = 'I';
   send_buff[2] = m_int.bytedata[0];
   send_buff[3] = m_int.bytedata[1];
   send_buff[4] = 0;
   send_buff[5] = 0;
   send_buff[8] = '*';

   m_crc.data= crc_cal(0);
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.write(send_buff[i]);
     send_buff[i] = 0;
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_float_data(float input)
{
   m_float.data = input;
   send_buff[0] = '#';
   send_buff[1] = 'F';
   send_buff[2] = m_float.bytedata[0];
   send_buff[3] = m_float.bytedata[1];
   send_buff[4] = m_float.bytedata[2];
   send_buff[5] = m_float.bytedata[3];
   send_buff[8] = '*';

   m_crc.data= crc_cal(1);
   send_buff[6] = m_crc.bytedata[1];
   send_buff[7] = m_crc.bytedata[0];
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.write(send_buff[i]);
     send_buff[i] = 0;
   }
   Serial.println();  // 보기쉽게 줄바꿈
}


void send_int_data_wrong1(int input)
{
   m_int.data = input;
   send_buff[0] = '#';
   send_buff[1] = 'I';
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
     Serial.write(send_buff[i]);
     send_buff[i] = 0;
   }
   Serial.println();  // 보기쉽게 줄바꿈
}


void send_int_data_wrong2(int input)
{
   m_int.data = input;
   Serial.write("Je########$*");
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
     Serial.write(send_buff[i]);
     send_buff[i] = 0;
   }

   Serial.println();  // 보기쉽게 줄바꿈
}



void loop() {
  // put your main code here, to run repeatedly:
  send_int_data(12);
  //send_float_data(12.34);
  //delay(1000);
  //send_int_data_wrong1(12);
  //delay(1000);

  //send_int_data_wrong2(10);
  //delay(1000);
}
