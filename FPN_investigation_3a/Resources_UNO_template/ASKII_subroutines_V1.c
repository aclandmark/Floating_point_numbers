
/*


Enter digits echo and save them 

scan string:  	If E then read and save exponent
				Convert E to null

scan string for a dp
	while previous_digit
	inc dp_counter shift digit one place left to ovewrite dp
	



*/

/**********************************************************************************************/
char isCharavailable (int m){int n = 0;										//For m = 1 waits a maximun of 7.8mS
while (!(Serial.available())){n++;											//before returning zero
if (n>4000) {m--; n = 0;}if (m == 0)return 0;}								//Returns 1 immediately that a char is received
return 1;}



char waitforkeypress(void){
while (!(Serial.available()));
return Serial.read();}


/***************************************************************************************************************************************/
char decimal_digit (char data){
if (((data > '9') || (data < '0')) )return 0;
else return 1;}


/***************************************************************************************************************************************/
char wait_for_return_key(void){  											//Returns keypress
char keypress, temp;														//but converts \r\n, \r or \n to \r
while (!(Serial.available())); 
keypress = Serial.read();
if((keypress == '\r') || (keypress == '\n')){
if (isCharavailable(1)){temp = Serial.read();}keypress = '\r';}
return keypress;}



/***************************************************************************************************************************************/
char Scientific_num_from_KBD(char* array, char* sign){     					//Acquires an integer string from the keyboard and returns the binary equivalent
char keypress;
char array_ptr;
char dp_ptr;
char E_ptr;

dp_ptr = 0;
array_ptr = 0;
E_ptr = 0;

for(int n = 0; n<=14; n++) array[n] = 0;                           			//Clear the buffer used for the string

do
{while (!(Serial.available())); 											//Wait for keypress
keypress = Serial.read();} 
while ((!(decimal_digit(keypress)))
&& (keypress != '-'));														//Ignore illegal keypresses

Serial.write(keypress); 													//Echo keypress

if (keypress == '-') *sign = negative;
else array[array_ptr++] = keypress;											//Save keypress to buffer
 
while(1){																	//continue statement brings program flow back here 
if ((keypress = wait_for_return_key())  =='\r')break;               		//Detect return key press (i.e \r or\r\n)

if ((decimal_digit(keypress)) || (keypress == '.')							//Acceptable keypresses
|| (keypress == '\b') || (keypress == '-')
|| (keypress == 'E') || (keypress == 'e'))

{if(keypress == '\b'){array[--array_ptr] = 0; Serial.write('\b');			//Del key pressed
continue;}																	//Go straight to top of while loop															

{if (keypress == '.'){dp_ptr = array_ptr;									//Save location of decimal point
array[array_ptr++] = '.'; Serial.write('.');continue;}

if ((keypress == 'E') || (keypress == 'e')){
if(!(dp_ptr)){array[array_ptr] = '.'; dp_ptr = array_ptr;
array_ptr += 1;}
E_ptr = array_ptr;}

array[array_ptr++] = keypress;}												//Save keypress to string

Serial.write(keypress);}}                                                   //Update display includes "cr_keypress"                                                 

//if(!(dp_ptr))dp_ptr = 14;	///see next line								//Tells the "main" routine that an integer number has been entered.			
if(!(dp_ptr)){array[array_ptr] = '.'; dp_ptr = array_ptr;}					//CHECK WITH FPN_INVESTIGATION_2!!!!!!!!!!!!!!!!!!!!


Serial.write('\t');
return E_ptr;}																//Return location of the first decimal place




/**************************************************************************************************************************/



