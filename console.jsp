<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
<link rel="stylesheet" type="text/css" href="css/slidebutton.css">
</head>
<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<jsp:useBean id="devices" class="ControllerConsole.UserDevices" scope="page"/>
<jsp:useBean id="controller" class="ControllerConsole.Controller" scope="application"/>
<body>
<table align="center" width="90%">
<%
byte selectedvalue;
int i;
if (user.isLoggedIn())
{
        Iterator<Device> channelIter = devices.getDevicesOfUser(user, "A", 0, 7).iterator(); 
  
        while (channelIter.hasNext())
	{
		Device dev = channelIter.next();
%>
 <tr>
  <td align="right"><img width="128px" height="128px" src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;"><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></font></td>
  <%selectedvalue=controller.getChannelValue(dev.getDeviceChannel());%>
  <td>
<%
switch(dev.getDeviceType())
{
	case 1: // A_SWITCH
%>
<label class="switch">
  <input type="checkbox" <%if (!dev.getAuthorizationLevel().equals("W")){%>disabled<%}%> id="value<%=dev.getDeviceID()%>" <%if (selectedvalue!=0){%>checked<%}%> onchange="javascript:channelClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>, <%=dev.getDeviceType()%>)">
  <span class="slider round"></span>
</label> 
<%
		break;
	case 2: // A_LEVEL
%>
<select style="font-name:Arial;font-size:64pt;width:200px;height:128px;" <%if (!dev.getAuthorizationLevel().equals("W")){%>disabled<%}%> id="value<%=dev.getDeviceID()%>" onchange="javascript:channelClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>, <%=dev.getDeviceType()%>)"><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select>
<%
		break;
}
%>
  </td>
  <td></td>
 </tr>
<%
        }

        Iterator<Device> bitIter = devices.getDevicesOfUser(user, "A", 8, 9).iterator(); 
  
        while (bitIter.hasNext())
	{
		Device dev = bitIter.next();
%>
 <tr>
  <td align="right"><img width="128px" height="128px" src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;"><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></font></td>
  <%selectedvalue=controller.getBitValue(dev.getDeviceChannel());%>
  <td>
<label class="switch">
  <input type="checkbox" <%if (!dev.getAuthorizationLevel().equals("W")){%>disabled<%}%> id="value<%=dev.getDeviceID()%>" <%if (selectedvalue!=0){%>checked<%}%> onchange="javascript:bitClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>)">
  <span class="slider round"></span>
</label>
  </td> 
  <td></td>
 </tr>
<%
        }

        Iterator<Device> pulseIter = devices.getDevicesOfUser(user, "A", 10, 11).iterator(); 
  
        while (pulseIter.hasNext())
	{
		Device dev = pulseIter.next();
%>
 <tr>
  <td align="right"><img width="128px" height="128px" src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;"><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></font></td>
  <td><img width="128px" height="128px" src="images/<%=dev.getDeviceTypeIcon()%>" <%if (!dev.getAuthorizationLevel().equals("W")){%>disabled<%}else{%>style="cursor:pointer"<%}%> onclick="javascript:pulseClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>, <%=dev.getDeviceInitialValue()%>)"></td>
  <td></td>
 </tr>
<%
        }

	byte value = controller.readChannel();

        Iterator<Device> sensorIter = devices.getDevicesOfUser(user, "S", 0, 7).iterator(); 
  
        while (sensorIter.hasNext())
	{
		Device dev = sensorIter.next();
%>
 <tr>
  <td align="right"><img width="128px" height="128px" src="images/<%=dev.getDeviceIcon()%>" style="cursor:pointer" onclick="javascript:sensorClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>)"></td>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;"><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></font></td>
  <%selectedvalue=controller.getChannelValue(dev.getDeviceChannel());%>
  <td>
<%
switch(dev.getDeviceType())
{
	case 5: // S_SWITCH
%>
<label class="switch">
  <input type="checkbox" disabled id="value<%=dev.getDeviceID()%>" <%if (selectedvalue!=0){%>checked<%}%>>
  <span class="slider round"></span>
</label> 
<%
		break;
	case 6: // S_LEVEL
%>
<select style="font-name:Arial;font-size:64pt;width:200px;height:128px;" disabled id="value<%=dev.getDeviceID()%>"><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select>
<%
		break;
}
%>
  </td>
  <td></td>
 </tr>

<!--
 <tr>
  <td align="right"><img width="128px" height="128px" src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;"><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></font></td>
  <%selectedvalue=controller.getInputChannelValue(dev.getDeviceChannel());%>
  <td><select style="font-name:Arial;font-size:64pt;width:200px;height:128px;" id="value<%=dev.getDeviceID()%>" disabled><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
  <td><img width="128px" height="128px" src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:pointer" onclick="javascript:sensorClick(<%=dev.getDeviceID()%>, <%=dev.getDeviceChannel()%>)"></td>
 </tr>
-->
<%
        }
%>
 <tr>
  <td colspan="4" align="center"><br><form name="logoutform" method="POST" action="ControllerConsole?logout"><input style="font-name:Arial;font-size:36pt;width:256px;height:128px;" type="submit" name="logout" value="Logout"/></form></td>
 </tr>
<%
}
else
{
%>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">User not logged in</font></td>
 </tr>
<%
}
%>
</table>
</body>
</html>

<script type="text/javascript">
function channelCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	document.getElementById('value' + obj.devid).value = obj.value;
}

function channelClick(deviceid, channelid, devicetype)
{
	var value;
	var channelobj = eval('document.getElementById("value' + deviceid + '");');
	switch (devicetype)
	{
		case 1: // A_SWITCH
			if (channelobj.checked)
				value = 1;
			else
				value = 0;
			break;
		case 2:
			value = channelobj.value;
			break;
	}

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			channelCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?channel&id=' + channelid + '&value=' + value + '&devid=' + deviceid;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}

function bitCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	document.getElementById('value' + obj.devid).value = obj.value;
}

function bitClick(deviceid, channelid)
{
	var value;
	var bitobj = eval('document.getElementById("value' + deviceid + '");');

	if (bitobj.checked)
		value = 1;
	else
		value = 0;

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			bitCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?bit&id=' + channelid + '&value=' + value + '&devid=' + deviceid;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}

function pulseCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	//document.getElementById('value' + obj.devid).value = obj.value;
}

function pulseClick(deviceid, channelid, initval)
{
	var pulseobj = eval('document.getElementById("value' + deviceid + '");');
	var value = initval;

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			pulseCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?pulse&id=' + channelid + '&value=' + value + '&devid=' + deviceid;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}
	
function sensorCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	document.getElementById('value' + obj.devid).value = obj.value;
}

function sensorClick(deviceid, channelid)
{
 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			sensorCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?readchannel&id=' + channelid + '&devid=' + deviceid;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}
</script>