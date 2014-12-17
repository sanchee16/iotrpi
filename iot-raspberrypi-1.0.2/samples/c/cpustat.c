/*******************************************************************************
* Copyright (c) 2014 IBM Corporation and other Contributors.
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
*
* Contributors:
*   Sancheeta Kaushal - Initial Contribution
*******************************************************************************/

/*
 * C Program to get the stats for CPU.
 * Currently it gets the CPU temperature and CPU usage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PATHSIZE = 255;
int SIZE = 8;
char sensortemploc[255] = "/sys/bus/w1/devices/28-000003838aa5/w1_slave";
char cpuloadloc[255] = "/proc/loadavg";
char cputemploc[255]="/sys/class/thermal/thermal_zone0/temp";
float getCPUTemp();
float GetCPULoad();

float getCPUTemp() {
	FILE * cputemp = NULL;
	char* buffer;
	char *pch;
	int i=2,j=0;
	float tempinc;
	long tempinmillic;
	char temp[20];
	cputemp  = fopen(sensortemploc, "r");
        if(cputemp==NULL){
		printf("ERROR:couldn't open file\n");
		return -2;
	}
	fseek(cputemp,0,SEEK_END);
	long length=ftell(cputemp);
	fseek(cputemp,0,SEEK_SET);

	 buffer=malloc((length+1)*sizeof(char));
	if(buffer==NULL){
		printf("ERROR:not enough memory to read file\n");
		return -3;
	}
	long offset=0;
	while(!feof(cputemp)&&offset<length){
		offset+=fread(buffer+offset,sizeof(char),length-offset,cputemp);
	}
	buffer[offset]='\0';
	pch=strchr(buffer,'t');
	while(*pch!='\0'){
		*pch=*(pch+i);
		temp[j]=*pch;
		i+=1;
		j+=1;
	}
	tempinmillic = atol(temp);
	tempinc = tempinmillic * 1.0 / 1000.0;

	fclose(cputemp);
	return (tempinc);
}

float GetCPULoad() {
	
	FILE *cpu=NULL;
        char buffer[SIZE];
	long tempinmillic;
	float tempinc;

	memset(buffer,0,sizeof(buffer));
	cpu=fopen(cputemploc,"r");
	fgets(buffer,SIZE,cpu);

	tempinmillic=atol(buffer);
	tempinc=tempinmillic*1.0/1000.0;
	fclose(cpu);
	return tempinc;

}
