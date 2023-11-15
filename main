adxl_write (0x2d, 0x00);  // reset all bits

adxl_write (0x2d, 0x08);  // measure and wake up 8hz

adxl_write (0x31, 0x01);  // data_format range= +- 4g

void adxl_read_values (uint8_t reg)
{
   HAL_I2C_Mem_Read (&hi2c1, adxl_address, reg, 1, (uint8_t *)data_rec, 6, 100);
}

adxl_read_values (0x32);
x = ((data_rec[1]<<8)|data_rec[0]);  
y = ((data_rec[3]<<8)|data_rec[2]);
z = ((data_rec[5]<<8)|data_rec[4]);

xg = x * .0078;
yg = y * .0078;
zg = z * .0078;

void display_data (float data)
{
    sprintf (x_char, "% 4f", data);
    SSD1306_Puts (x_char, &Font_11x18, 1);
    SSD1306_UpdateScreen ();  // update display
}

SSD1306_GotoXY (16, 1);
SSD1306_Puts ("X: ", &Font_11x18, 1);
SSD1306_GotoXY (32, 1);
display_data (xg);

SSD1306_GotoXY (16, 20);
SSD1306_Puts ("Y: ", &Font_11x18, 1);
SSD1306_GotoXY (32, 20);
display_data (yg);

SSD1306_GotoXY (16, 40);
SSD1306_Puts ("Z: ", &Font_11x18, 1);
SSD1306_GotoXY (32, 40);
display_data (zg);

