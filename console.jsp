<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
</head>

<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<jsp:useBean id="devices" class="ControllerConsole.UserDevices" scope="page"/>

<jsp:useBean id="controller" class="ControllerConsole.Controller" scope="application"/>


<body>
<table align="center">
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
<!-- <br/><%=dev.getAuthorizationLevel()%>, <%=dev.getDeviceID()%>, <%=dev.getDeviceText()%>, <%=dev.getDeviceType()%>, <%=dev.getDeviceTypeText()%>, <%=dev.getDeviceNumStates()%>, <%=dev.getDeviceCategory()%>, <%=dev.getDeviceCategoryText()%> -->
 <tr>
  <td><img src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></td>
  <%selectedvalue=controller.getChannelValue(dev.getDeviceChannel());%>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:channelClick(<%=dev.getDeviceID()%>)"></td>
 </tr>
<%
        }

        Iterator<Device> bitIter = devices.getDevicesOfUser(user, "A", 8, 9).iterator(); 
  
        while (bitIter.hasNext())
	{
		Device dev = bitIter.next();
%>
<!-- <br/><%=dev.getAuthorizationLevel()%>, <%=dev.getDeviceID()%>, <%=dev.getDeviceText()%>, <%=dev.getDeviceType()%>, <%=dev.getDeviceTypeText()%>, <%=dev.getDeviceNumStates()%>, <%=dev.getDeviceCategory()%>, <%=dev.getDeviceCategoryText()%> -->
 <tr>
  <td><img src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></td>
  <%selectedvalue=controller.getBitValue(dev.getDeviceChannel());%>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:bitClick(<%=dev.getDeviceID()%>)"></td>
 </tr>
<%
        }

        Iterator<Device> pulseIter = devices.getDevicesOfUser(user, "A", 10, 11).iterator(); 
  
        while (pulseIter.hasNext())
	{
		Device dev = pulseIter.next();
%>
<!-- <br/><%=dev.getAuthorizationLevel()%>, <%=dev.getDeviceID()%>, <%=dev.getDeviceText()%>, <%=dev.getDeviceType()%>, <%=dev.getDeviceTypeText()%>, <%=dev.getDeviceNumStates()%>, <%=dev.getDeviceCategory()%>, <%=dev.getDeviceCategoryText()%> -->
 <tr>
  <td><img src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></td>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (i=1;i<=10;i++){%><option value="<%=i%>"><%=i%></option><%}%></select></td>
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:pulseClick(<%=dev.getDeviceID()%>)"></td>
 </tr>
<%
        }

        Iterator<Device> sensorIter = devices.getDevicesOfUser(user, "S", 0, 7).iterator(); 
  
        while (sensorIter.hasNext())
	{
		Device dev = sensorIter.next();
%>
<!-- <br/><%=dev.getAuthorizationLevel()%>, <%=dev.getDeviceID()%>, <%=dev.getDeviceText()%>, <%=dev.getDeviceType()%>, <%=dev.getDeviceTypeText()%>, <%=dev.getDeviceNumStates()%>, <%=dev.getDeviceCategory()%>, <%=dev.getDeviceCategoryText()%> -->
 <tr>
  <td><img src="images/<%=dev.getDeviceIcon()%>"></td>
  <td><b><%=dev.getDeviceText()%></b><br><i><%=dev.getDeviceCategoryText()%>, <%=dev.getDeviceTypeText()%></i></td>
  <%selectedvalue=controller.getInputChannelValue(dev.getDeviceChannel());%>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:sensorClick(<%=dev.getDeviceID()%>)"></td>
 </tr>
<%
        }
%>
 <tr>
  <td colspan="4" align="center"><form name="logoutform" method="POST" action="ControllerConsole?logout"><input type="submit" name="logout" value="Logout"/></form></td>
 </tr>
<%
}
else
{
%>
 <tr>
  <td>User not logged in</td>
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
	document.getElementById('value' + obj.id).value = obj.value;
}

function channelClick(deviceid)
{
	var channelobj = eval('document.getElementById("value' + deviceid + '");');
	var value = channelobj.value;

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			channelCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?channel&id=' + deviceid + '&value=' + value;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}

function bitCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	document.getElementById('value' + obj.id).value = obj.value;
}

function bitClick(deviceid)
{
	var bitobj = eval('document.getElementById("value' + deviceid + '");');
	var value = bitobj.value;

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			bitCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?bit&id=' + deviceid + '&value=' + value;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}

function pulseCallback(responseText)
{
 	var obj = JSON.parse(responseText);
	//document.getElementById('value' + obj.id).value = obj.value;
}

function pulseClick(deviceid)
{
	var pulseobj = eval('document.getElementById("value' + deviceid + '");');
	var value = pulseobj.value * 100000;

 	var xmlHttp = new XMLHttpRequest();
	xmlHttp.onreadystatechange = function() { 
 		if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
			pulseCallback(xmlHttp.responseText);
	}
	var url = 'ControllerConsole?pulse&id=' + deviceid + '&value=' + value;
 	xmlHttp.open('GET', url, true); // asynchronous 
 	xmlHttp.send(null);
}
	
function sensorClick(deviceid)
{
}
</script>
