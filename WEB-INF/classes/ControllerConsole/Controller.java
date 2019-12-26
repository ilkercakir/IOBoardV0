package ControllerConsole;

import java.util.ArrayList;
import java.util.Iterator;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.LogManager;

public class Controller
{
	private long controllerHandle;
	private String libraryPath;
	static Logger logger = LogManager.getLogger(ControllerConsole.Controller.class);

	private native long controller_open(int version, byte initialValue);
	private native long controller_close(long handle);
	private native int ochannel_add(long handle, String name, int type, int numstates);
	private native int obit_add(long handle, String name);
	private native int opulse_add(long handle, String name);
	private native byte ochannel_get_value(long handle, int channel);
	private native void ochannel_set_value(long handle, int channel, byte value);
	private native byte controller_get_value(long handle);
	private native void ochannel_write(long handle);
	private native byte obit_get_value(long handle, int bit);
	private native void obit_set_value(long handle, int bit, byte value);
	private native void opulse_out(long handle, int pulse);

	public Controller()
	{
		controllerHandle = 0;

		logger.debug("init debug messages");
		logger.info("init info messages");
		logger.warn("init warn messages");
		logger.error("init error messages");
		logger.fatal("init fatal messages");

		try
		{
			libraryPath = System.getProperty("java.library.path");
			logger.info("Controller java.library.path = " + libraryPath);
			System.loadLibrary("IOBoardV0");
			logger.info("Native code library loaded");
		}
		catch (UnsatisfiedLinkError e)
		{
      			logger.error("Native code library failed to load" + e);
		}
	}

	public int Open()
	{
		Device dev;
		int id;

		controllerHandle = controller_open(0, (byte)0x00); // Version 0, Default value 0
		logger.info("controller_open() handle " + controllerHandle);

		UserDevices udev = new UserDevices();

		// Channels
        	Iterator<Device> channelIter = udev.getDevices("A", 0, 7).iterator(); 
	        while (channelIter.hasNext())
		{
			dev = channelIter.next();

			id = ochannel_add(controllerHandle, dev.getDeviceText(), dev.getDeviceType(), dev.getDeviceNumStates());
			logger.info("ochannel_add " + dev.getDeviceText() + " db:" + id);
			if (id == dev.getDeviceID())
			{
				ochannel_set_value(controllerHandle, dev.getDeviceID(), (byte)dev.getDeviceInitialValue());
				logger.info("ochannel_set_value " + dev.getDeviceID() + ", initial value " + (byte)dev.getDeviceInitialValue());
			}
			else
			{
				logger.error("ochannel_add " + dev.getDeviceID() + " failed");
				return(-1); // channels init failed
			}
		}

		// Bits
        	Iterator<Device> bitIter = udev.getDevices("A", 8, 9).iterator(); 
	        while (bitIter.hasNext())
		{
			dev = bitIter.next();

			id = obit_add(controllerHandle, dev.getDeviceText());
			logger.info("obit_add " + dev.getDeviceText() + " db:" + id);
			if (id == dev.getDeviceID())
			{
				obit_set_value(controllerHandle, dev.getDeviceID(), (byte)dev.getDeviceInitialValue());
				logger.info("obit_set_value " + dev.getDeviceID() + ", initial value " + (byte)dev.getDeviceInitialValue());
			}
			else
			{
				logger.error("obit_add " + dev.getDeviceID() + " failed");
				return(-2); // bits init failed
			}
		}

		// Pulses
        	Iterator<Device> pulseIter = udev.getDevices("A", 10, 11).iterator(); 
	        while (pulseIter.hasNext())
		{
			dev = pulseIter.next();

			id = opulse_add(controllerHandle, dev.getDeviceText());
			logger.info("opulse_add " + dev.getDeviceText() + " db:" + id);
			if (id == dev.getDeviceID())
			{
				logger.info("opulse " + dev.getDeviceID());
			}
			else
			{
				logger.error("opulse_add " + dev.getDeviceID() + " failed");
				return(-3); // pulses init failed
			}
		}

		logger.info("controller_open() completed");
		return(0);
	}

	public byte getChannelValue(int channel)
	{
		return(ochannel_get_value(controllerHandle, channel));
	}

	public void setChannelValue(int channel, byte value)
	{
		ochannel_set_value(controllerHandle, channel, value);
	}

	public byte getBitValue(int bit)
	{
		return(obit_get_value(controllerHandle, bit));
	}

	public void setBitValue(int bit, byte value)
	{
		obit_set_value(controllerHandle, bit, value);
	}

	public void pulseOut(int pulse)
	{
		opulse_out(controllerHandle, pulse);
	}

	public byte getControllerValue()
	{
		return(controller_get_value(controllerHandle));
	}

	public void writeChannel()
	{
		ochannel_write(controllerHandle);
	}

	public void Close()
	{
		controller_close(controllerHandle);
		controllerHandle = 0;
	}
}
