//Current file name:sensor_e.ino
#include <ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle  nh;
sensor_msgs::Range range_msg[8];

ros::Publisher ultrasound0("ultrasound0",&range_msg[0]);
ros::Publisher ultrasound1("ultrasound1",&range_msg[1]);
ros::Publisher ultrasound2("ultrasound2",&range_msg[2]);
ros::Publisher ultrasound3("ultrasound3",&range_msg[3]);
ros::Publisher ultrasound4("ultrasound4",&range_msg[4]);
ros::Publisher ultrasound5("ultrasound5",&range_msg[5]);
ros::Publisher ultrasound6("ultrasound6",&range_msg[6]);
ros::Publisher ultrasound7("ultrasound7",&range_msg[7]);

static byte chn = 0;
static byte led = 0;
int Led = 13;
int Trig = 4;
int Echo = 7;
long IntervalTime = 0;
char frameid[] = "/ultrasoundn";

void setup()
{
  pinMode(Led,OUTPUT);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  nh.initNode();
  //for( int i=0;i<8;i++)//存在Bug，将i++转为函数内i=i+1;!!??
  for( int i=0;i<8;)
  {
	//frameid[11] = i+0x30;
	range_msg[i].radiation_type = sensor_msgs::Range::ULTRASOUND;
	//range_msg[i].header.frame_id =  frameid;
	range_msg[i].field_of_view = 0.1;  // fake
	range_msg[i].min_range = 0.0;
	range_msg[i].max_range = 50.00;
	i = i+1;
  };  

	range_msg[0].header.frame_id = "/ultrasound0";
	range_msg[1].header.frame_id = "/ultrasound1";
	range_msg[2].header.frame_id = "/ultrasound2";
	range_msg[3].header.frame_id = "/ultrasound3";
	range_msg[4].header.frame_id = "/ultrasound4";
	range_msg[5].header.frame_id = "/ultrasound5";
	range_msg[6].header.frame_id = "/ultrasound6";
	range_msg[7].header.frame_id = "/ultrasound7";
	nh.advertise(ultrasound0);
	nh.advertise(ultrasound1);
	nh.advertise(ultrasound2);
	nh.advertise(ultrasound3);
	nh.advertise(ultrasound4);
	nh.advertise(ultrasound5);
	nh.advertise(ultrasound6);
	nh.advertise(ultrasound7);
}

void loop()
{
	//转换通道并读取超声数据
	//chn = (chn++)%8;
	if(chn>=8)chn = 0;
    digitalWrite(Trig,HIGH);
	delayMicroseconds(15);
	IntervalTime = pulseIn(Echo,HIGH);
  
	range_msg[chn].range = (float)IntervalTime / 58.00; 
	range_msg[chn].header.stamp = nh.now();
	
	switch(chn){
		case 0x01:
		ultrasound1.publish(&range_msg[chn]);
		break;
		case 0x02:
		ultrasound2.publish(&range_msg[chn]);
		break;
		case 0x03:
		ultrasound3.publish(&range_msg[chn]);
		break;
		case 0x04:
		ultrasound4.publish(&range_msg[chn]);
		break;
		case 0x05:
		ultrasound5.publish(&range_msg[chn]);
		break;
		case 0x06:
		ultrasound6.publish(&range_msg[chn]);
		break;
		case 0x07:
		ultrasound7.publish(&range_msg[chn]);
		break;
		case 0x00:
		ultrasound0.publish(&range_msg[chn]);
		break;
		default:
		break;
	};
	chn = chn+1;
	nh.spinOnce();
  
	if(led != 0){
		led = 0;
		digitalWrite(Led,LOW);
	}
	else {
		led = 1;
		digitalWrite(Led,HIGH);
	};
	delay(100);
}






