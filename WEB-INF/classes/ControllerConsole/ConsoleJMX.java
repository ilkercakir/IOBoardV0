package ControllerConsole;

import java.lang.management.*;
import java.net.*;
import java.io.*;

import javax.management.InstanceNotFoundException; 
import javax.management.MBeanServer; 
import javax.management.MalformedObjectNameException; 
import javax.management.ObjectName;
import javax.management.ObjectInstance;

public class ConsoleJMX
{

	public int getMaxPostSize(int httpPort)
	{
		int maxPostSize = -1;
		try
		{
    			MBeanServer mbeanServer = ManagementFactory.getPlatformMBeanServer();
    			ObjectName objectName = new ObjectName("Catalina:type=Connector,port=" + httpPort);
    			maxPostSize = (int) mbeanServer.getAttribute(objectName, "maxPostSize");
    		}
    		catch (Exception ex)
    		{
    			ex.printStackTrace();
    		}
    		return (maxPostSize);
	}
	
	public int getActiveSessions()
	{
		int activeSessions = -1;
		try
		{
			MBeanServer mBeanServer = ManagementFactory.getPlatformMBeanServer();
			ObjectName objectName = new ObjectName("Catalina:type=Manager,context=/IOBoardV0,host=localhost");
			activeSessions = (Integer) mBeanServer.getAttribute(objectName, "activeSessions");
    		}
    		catch (Exception ex)
    		{
    			ex.printStackTrace();
    		}
    		return (activeSessions);
	}
}
