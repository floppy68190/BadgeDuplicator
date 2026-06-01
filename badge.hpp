#pragma once
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 5
#define pinLedValid 7
#define pinError 9
#define pinBuzz 6

class Badge
{
  public:
    Badge();
  void  init();
    ~Badge();
	void	write(byte copy[64][16], boolean soundMode);
	void	read(byte copy[64][16], boolean soundMode);
  private:
	MFRC522 rfid;
	MFRC522::MIFARE_Key key;
	MFRC522::StatusCode status;
  	byte buffer[18];
  	byte size;
};