package ControllerConsole;

import java.util.ArrayList;
import java.util.ResourceBundle;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.DriverManager;
import java.sql.SQLException;

public class UserDevices
{
	private ResourceBundle rb;
	private String DBpath;

	public UserDevices()
	{
		rb = ResourceBundle.getBundle("ControllerConsole.Global");
		DBpath = rb.getString("ControllerConsole.DBPATH");
	}

	private Device newDeviceFromRS(ResultSet rs)
	{
		Device dev = new Device();
		try
		{
			dev.setAuthorizationLevel(rs.getString("level"));
			dev.setDeviceID(Integer.parseInt(rs.getString("devid")));
			dev.setDeviceText(rs.getString("dtext"));
			dev.setDeviceType(Integer.parseInt(rs.getString("dtype")));
			dev.setDeviceTypeText(rs.getString("dttext"));
			int dstat = Integer.parseInt(rs.getString("dstat"));
			if (dstat==0)
				dev.setDeviceNumStates(Integer.parseInt(rs.getString("numstates")));
			else
				dev.setDeviceNumStates(Integer.parseInt(rs.getString("dstat")));
			dev.setDeviceInitialValue(Integer.parseInt(rs.getString("initval")));
			dev.setDeviceCategory(rs.getString("categ"));
			dev.setDeviceCategoryText(rs.getString("catxt"));
			dev.setDeviceIcon(rs.getString("dicon"));
			dev.setDeviceTypeIcon(rs.getString("dticon"));
		}
		catch(SQLException sqlex)
		{
        		//throw sqlex;	
		}
		return(dev);
	}

	public ArrayList<Device> getDevicesOfUser(User user, String categ, int fromChannel, int toChannel)
	{
		ArrayList<Device> devices = new ArrayList<Device>();

		Connection conn = null;
		ResultSet rs = null;
		Statement stat = null;
	
		try
		{
			Class.forName("org.sqlite.JDBC");
		}
		catch (ClassNotFoundException ex)
		{
			//throw ex;
		}

		try
		{
			conn = DriverManager.getConnection("jdbc:sqlite:" + DBpath);
			stat = conn.createStatement();
			if (user.isSuperUser()) // superuser
				rs = stat.executeQuery("select 'W' as level, devices.devid, devices.dtext, devices.chnnl, devices.dtype, devicetypes.dtext as dttext, devices.numstates, devices.initval, devicetypes.dstat, devicetypes.categ, devcat.catxt, devices.dicon, devicetypes.dicon as dticon from devices inner join devicetypes on devicetypes.dtype = devices.dtype inner join devcat on devcat.categ = devicetypes.categ where devicetypes.categ = '" + categ + "' and devices.chnnl >= " + fromChannel + " and devices.chnnl <= " + toChannel + ";");
			else
				rs = stat.executeQuery("select authorizations.level, devices.devid, devices.dtext, devices.chnnl, devices.dtype, devicetypes.dtext as dttext, devices.numstates, devices.initval, devicetypes.dstat, devicetypes.categ, devcat.catxt, devices.dicon, devicetypes.dicon as dticon from users inner join authorizations on authorizations.username = users.username inner join devices on devices.devid = authorizations.devid inner join devicetypes on devicetypes.dtype = devices.dtype inner join devcat on devcat.categ = devicetypes.categ where devicetypes.categ = '" + categ + "' and users.username = '" + user.getUserName() + "' and devices.chnnl >= " + fromChannel + " and devices.chnnl <= " + toChannel + ";");
			while (rs.next()) 
			{
				Device dev = newDeviceFromRS(rs);
				devices.add(dev);
			}
			rs.close();
			stat.close();
			conn.close();
		}
		catch(SQLException sqlex)
		{
        		//throw sqlex;	
		}
		return(devices);
	}

	public ArrayList<Device> getDevices(String categ, int fromChannel, int toChannel)
	{
		ArrayList<Device> devices = new ArrayList<Device>();

		Connection conn = null;
		ResultSet rs = null;
		Statement stat = null;
	
		try
		{
			Class.forName("org.sqlite.JDBC");
		}
		catch (ClassNotFoundException ex)
		{
			//throw ex;
		}

		try
		{
			conn = DriverManager.getConnection("jdbc:sqlite:" + DBpath);
			stat = conn.createStatement();
			rs = stat.executeQuery("select 'W' as level, devices.devid, devices.dtext, devices.chnnl, devices.dtype, devicetypes.dtext as dttext, devices.numstates, devices.initval, devicetypes.dstat, devicetypes.categ, devcat.catxt, devices.dicon, devicetypes.dicon as dticon from devices inner join devicetypes on devicetypes.dtype = devices.dtype inner join devcat on devcat.categ = devicetypes.categ where devicetypes.categ = '" + categ + "' and devices.chnnl >= " + fromChannel + " and devices.chnnl <= " + toChannel + ";");
			while (rs.next()) 
			{
				Device dev =  newDeviceFromRS(rs);
				devices.add(dev);
			}
			rs.close();
			stat.close();
			conn.close();
		}
		catch(SQLException sqlex)
		{
        		//throw sqlex;	
		}
		return(devices);
	}
}
