<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
</head>

<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<jsp:useBean id="devices" class="ControllerConsole.UserDevices" scope="page"/>

<jsp:useBean id="controller" class="ControllerConsole.Controller" scope="page"/>


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
  <%selectedvalue=controller.getChannelValue(dev.getDeviceID())%>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (int i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
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
  <%selectedvalue=controller.getBitValue(dev.getDeviceID())%>
  <td><select id="value<%=dev.getDeviceID()%>"><%for (int i=0;i<dev.getDeviceNumStates();i++){%><option value="<%=i%>"<%if (i==selectedvalue){%> selected<%}%>><%=i%></option><%}%></select></td>
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
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:pulseClick(<%=dev.getDeviceID()%>)"></td>
 </tr>
<%
        }
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
	alert(responseText);
 	var obj = JSON.parse(responseText);
	var id = obj.id;
	var value = obj.value;
	
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
 	xmlHttp.open('GET', '/controller?channel&id=' + deviceid + '&value=' + value, true); // asynchronous 
 	xmlHttp.send(null);
}

function bitClick(deviceid)
{
}

function pulseClick(deviceid)
{
}
</script>
