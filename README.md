# Floating_point_numbers: An investigation

For many of us these numbers remain rather mysterious long after we have got used to their integer equivalents.

Two projects are provided here which I hope will provide illumination for anyone interested.  There is no intention to
compete with standard library functions however, just to illustrate the steps that must be taken.   The first project 
looks at numbers like 123.456 and converts then to floating point.

The second puts the first in a subroutine.  It then takes numbers like 123.456e10 and deals with them in the following stages:
	Converts the number to 1.234567e12
	Converts the 1.23456 to floating point
	Uses repeated multiplication or division to amalgamate the exponent
Arithmetic can be performed at this stage and finally the number is reconverted back to a string.

A short introduction is also provided in the .pdf document which outlines the theory in simple terms.

Note:
1.	This project follows on from the Project Floating point display for the UNO posted on 23, May 2021 which gives some useful links.
The following link which gives an IEEE-754 Floating Point Converter is also recommended:
https://www.h-schmidt.net/FloatConverter/IEEE754.html

2.	When using the IEEEE converter rmember that the second project provides bettery accurracy.  For example it is more sensible to convert 8e-5 than 0.00008.
