/*
 * Author: Kiran Kumar Lekkala
 * Created: 3 April 2017
 */

//For now image is a 3 dimensional vector
uniform vec3 image[3];

//Brightness value set by the vertex shader
varying lowp float brightness;
varying lowp float value;

void main()
{
	// Increase brightness if positive value
	// Decrease brightness if negative value
	image = image + value;
}
