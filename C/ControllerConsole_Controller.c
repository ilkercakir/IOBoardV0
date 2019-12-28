/*
 * ControllerConsole_Controller.c
 * 
 * Copyright 2019  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

// compile with gcc -Wall -c "%f" -DIS_RPI -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -g -ftree-vectorize -pipe -DUSE_VCHIQ_ARM -Wno-psabi -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mneon-for-64bits -Wno-deprecated-declarations -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/include -I/usr/lib/jvm/jdk-8-oracle-arm32-vfp-hflt/include/linux

#include <stdio.h>
#include "iochannels.h"
#include "ControllerConsole_Controller.h"

JNIEXPORT jlong JNICALL Java_ControllerConsole_Controller_controller_1open(JNIEnv *env, jobject obj, jint version, jbyte value)
{
	controller *c;

	c = controller_open((controller_type)version, (unsigned char)value);

	return((jlong)(long)c);
}

JNIEXPORT void JNICALL Java_ControllerConsole_Controller_controller_1close(JNIEnv *env, jobject obj, jlong handle)
{
	controller *c = (controller *)(long)handle;

	controller_close(c);
}

JNIEXPORT jint JNICALL Java_ControllerConsole_Controller_ochannel_1add(JNIEnv *env, jobject obj, jlong handle, jstring jname, jint jatype, jint jnumstates)
{
	controller *c = (controller *)(long)handle;
	jboolean iscopy; 
	const char *name;
	int id;

	name = (*env)->GetStringUTFChars(env, jname, &iscopy); 
	id = ochannel_add(c, (char *)name, (actuator_type)jatype, (int)jnumstates);

	return((jint)id);
}

JNIEXPORT jint JNICALL Java_ControllerConsole_Controller_obit_1add(JNIEnv *env, jobject obj, jlong handle, jstring jname)
{
	controller *c = (controller *)(long)handle;
	jboolean iscopy; 
	const char *name;
	int id;

	name = (*env)->GetStringUTFChars(env, jname, &iscopy); 
	id = obit_add(c, (char *)name);

	return((jint)id);
}

JNIEXPORT jint JNICALL Java_ControllerConsole_Controller_opulse_1add(JNIEnv *env, jobject obj, jlong handle, jstring jname)
{
	controller *c = (controller *)(long)handle;
	jboolean iscopy; 
	const char *name;
	int id;

	name = (*env)->GetStringUTFChars(env, jname, &iscopy); 
	id = opulse_add(c, (char *)name);

	return((jint)id);
}

JNIEXPORT jbyte JNICALL Java_ControllerConsole_Controller_ochannel_1get_1value(JNIEnv *env, jobject obj, jlong handle, jint channel)
{
	controller *c = (controller *)(long)handle;
	unsigned char value;

	value = ochannel_get_value(c, (unsigned int)channel);

	return((jbyte)value);
}

JNIEXPORT void JNICALL Java_ControllerConsole_Controller_ochannel_1set_1value(JNIEnv *env, jobject obj, jlong handle, jint channel, jbyte value)
{
	controller *c = (controller *)(long)handle;

	ochannel_set_value(c, (unsigned int)channel, (unsigned char)value);
}

JNIEXPORT jbyte JNICALL Java_ControllerConsole_Controller_controller_1get_1value(JNIEnv *env, jobject obj, jlong handle)
{
	controller *c = (controller *)(long)handle;
	unsigned char value;

	value = controller_get_value(c);

	return((jbyte)value);
}

JNIEXPORT void JNICALL Java_ControllerConsole_Controller_ochannel_1write(JNIEnv *env, jobject obj, jlong handle)
{
	controller *c = (controller *)(long)handle;

	ochannel_write(c);
}

JNIEXPORT jbyte JNICALL Java_ControllerConsole_Controller_obit_1get_1value(JNIEnv *env, jobject obj, jlong handle, jint bit)
{
	controller *c = (controller *)(long)handle;
	unsigned char value;

	value = obit_get_value(c, (unsigned int)bit);

	return((jbyte)value);
}

JNIEXPORT void JNICALL Java_ControllerConsole_Controller_obit_1set_1value(JNIEnv *env, jobject obj, jlong handle, jint bit, jbyte value)
{
	controller *c = (controller *)(long)handle;

	obit_set_value(c, (unsigned int)bit, (unsigned char)value);
}

JNIEXPORT void JNICALL Java_ControllerConsole_Controller_opulse_1out(JNIEnv *env, jobject obj, jlong handle, jint pulse, jint usecs)
{
	controller *c = (controller *)(long)handle;

	opulse_out(c, (unsigned int)pulse, (unsigned int)usecs);
}
