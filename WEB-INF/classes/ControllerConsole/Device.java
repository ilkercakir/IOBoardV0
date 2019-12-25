package ControllerConsole;

public class Device
{
	private String level;
	private int devid;
	private String dtext;
	private int dtype;
	private String dttext;
	private int numstates;
	private int initval;
	private String categ;
	private String catxt;
	private String dicon;
	private String dticon;

	public Device()
	{
	}

	public String getAuthorizationLevel()
	{
		return level;
	}

	public void setAuthorizationLevel(String authLevel)
	{
		level = authLevel;
	}

	public int getDeviceID()
	{
		return devid;
	}

	public void setDeviceID(int deviceID)
	{
		devid = deviceID;
	}

	public String getDeviceText()
	{
		return dtext;
	}

	public void setDeviceText(String deviceText)
	{
		dtext = deviceText;
	}

	public int getDeviceType()
	{
		return dtype;
	}

	public void setDeviceType(int deviceType)
	{
		dtype = deviceType;
	}

	public String getDeviceTypeText()
	{
		return dttext;
	}

	public void setDeviceTypeText(String deviceTypeText)
	{
		dttext = deviceTypeText;
	}

	public int getDeviceNumStates()
	{
		return numstates;
	}

	public void setDeviceNumStates(int numStates)
	{
		numstates = numStates;
	}

	public int getDeviceInitialValue()
	{
		return initval;
	}

	public void setDeviceInitialValue(int initVal)
	{
		initval = initVal;
	}

	public String getDeviceCategory()
	{
		return categ;
	}

	public void setDeviceCategory(String deviceCat)
	{
		categ = deviceCat;
	}

	public String getDeviceCategoryText()
	{
		return catxt;
	}

	public void setDeviceCategoryText(String deviceCatxt)
	{
		catxt = deviceCatxt;
	}

	public String getDeviceIcon()
	{
		return dicon;
	}

	public void setDeviceIcon(String deviceIcon)
	{
		dicon = deviceIcon;
	}

	public String getDeviceTypeIcon()
	{
		return dticon;
	}

	public void setDeviceTypeIcon(String deviceTypeIcon)
	{
		dticon = deviceTypeIcon;
	}
}