
#ifndef IOT_H_
#define IOT_H_

/* This is structure for the JSON */

  struct json {
	  char myname[100];
	  float cputemp;
	  float sine;
	  float sensortemp;
  };

  /* This is the short hand for json */
  typedef struct json JsonMessage;

//constants
#define MAXBUF 100

//config properties
//#define MSPROXY_URL "tcp://messaging.quickstart.internetofthings.ibmcloud.com:1883"
#define MSPROXY_URL "tcp://46.16.189.243:1883"
#define MSPROXY_URL_SSL "ssl://46.16.189.242:8883"
#define EVENTS_INTERVAL 1
#define DEVICE_NAME "myPi"
//Logging level for the syslog
//Default is INFO-6. Other possible values - ERROR-3, INFO-6, DEBUG-7
#define LOGLEVEL 6

extern int connected;

#endif /* IOT_H_ */
