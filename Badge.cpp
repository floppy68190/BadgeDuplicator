#include "badge.hpp"

Badge::Badge() : rfid(SS_PIN, RST_PIN)
{
	this->size = sizeof(this->buffer);
	for (byte i = 0; i < 6; i++)
    	this->key.keyByte[i] = 0xFF;   // clé par défaut
}

void  Badge::init()
{
	this->rfid.PCD_Init();
}

void	Badge::write(byte copy[64][16], boolean soundMode)
{
	unsigned long		startTime;
	unsigned long		currentTime;	
	byte 						block_number = 0;
	if (this->rfid.PICC_IsNewCardPresent())
    {
		if (this->rfid.PICC_ReadCardSerial()) {
    		for (byte sector = 0; sector < 16; sector++)
      		{
    			byte firstBlock = sector * 4;
        		this->status = this->rfid.PCD_Authenticate(
        		MFRC522::PICC_CMD_MF_AUTH_KEY_A,
        		firstBlock,
        		&key,
        		&(rfid.uid)
        		);
        		if (this->status != MFRC522::STATUS_OK)
        		{
        			this->status = this->rfid.PCD_Authenticate(
        			MFRC522::PICC_CMD_MF_AUTH_KEY_B,
        			firstBlock,
        			&key,
        			&(this->rfid.uid)
        			);
        			if (this->status != MFRC522::STATUS_OK)
        			{
								digitalWrite(pinError, HIGH);
								delay(200);
								digitalWrite(pinError, LOW);
        				Serial.println("Auth Failed");
        				continue ;
        			}
        		}
        		for (byte block = firstBlock; block < firstBlock + 3; block++)
        		{
        			this->status = this->rfid.MIFARE_Write(block, copy[block_number], sizeof(copy[block_number]));
        			if (this->status == MFRC522::STATUS_OK)
        			{
        				// Serial.print("Write on block: ");
        				// Serial.print(block);
        				// Serial.println(" ok");
        			}
        			else
        			{
        				// Serial.print("write failed on block ");
        				// Serial.println(block);
								digitalWrite(pinError, HIGH);
								delay(200);
								digitalWrite(pinError, LOW);
        			}
        			Serial.println();
        			block_number += 1;
        		}
    		}
		}
		startTime = millis();
		if (soundMode)
			tone(pinBuzz, 500);
    digitalWrite(pinLedValid, HIGH);
		while (1)
		{
			currentTime = millis();
			if (currentTime - startTime >= 500)
				noTone(pinBuzz);
			if (currentTime - startTime >= 2000)
			{
				digitalWrite(pinLedValid, LOW);
				break ;
			}
		}
		this->rfid.PICC_HaltA();
    this->rfid.PCD_StopCrypto1();
	}
}

void	Badge::read(byte copy[64][16], boolean soundMode)
{
	byte						block_number = 0;
	unsigned long		startTime;
	unsigned long		currentTime;
	if (this->rfid.PICC_IsNewCardPresent()) {
    	if (this->rfid.PICC_ReadCardSerial()) {
    		for (byte sector = 0; sector < 16; sector++)
    		{
    			byte firstBlock = sector * 4;
    			this->status = this->rfid.PCD_Authenticate(
    			  MFRC522::PICC_CMD_MF_AUTH_KEY_A,
    			  firstBlock,
    			  &key,
    			  &(this->rfid.uid)
    			);
    			if (this->status != MFRC522::STATUS_OK)
    			{
    				Serial.println("Auth Failed");
    				this->status = this->rfid.PCD_Authenticate(
    				MFRC522::PICC_CMD_MF_AUTH_KEY_B,
    				firstBlock,
    				&key,
    				&(this->rfid.uid)
    				);
    				if (this->status != MFRC522::STATUS_OK)
    				{
							digitalWrite(pinError, HIGH);
							delay(200);
							digitalWrite(pinError, LOW);
    					Serial.println("Auth Failed");
    					continue ;
    				}
    			}
    			for (byte block = firstBlock; block < firstBlock + 4; block++)
    			{
    				this->status = this->rfid.MIFARE_Read(block, buffer, &size);
    				if (this->status == MFRC522::STATUS_OK)
    				{
    					for (byte i = 0; i < 16; i++)
    					{
    						copy[block_number][i] = buffer[i];
    					}
    					Serial.println();
    				}
    				else
    				{
    					// Serial.print("Read failed");
							digitalWrite(pinError, HIGH);
							delay(200);
							digitalWrite(pinError, LOW);
    				}
    				block_number += 1;
    			}
    		}
				startTime = millis();
				if (soundMode)
					tone(pinBuzz, 1000);
        digitalWrite(pinLedValid, HIGH);
				while (1)
				{
					currentTime = millis();
					if (currentTime - startTime >= 1000)
						noTone(pinBuzz);
					if (currentTime - startTime >= 2000)
					{
						digitalWrite(pinLedValid, LOW);
						break ;
					}
				}
    		this->rfid.PICC_HaltA();
    		this->rfid.PCD_StopCrypto1();
    	}
	}
}

Badge::~Badge()
{

}