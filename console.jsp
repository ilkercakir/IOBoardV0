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
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:switchclick(<%=dev.getDeviceID()%>)"></td>
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
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:switchclick(<%=dev.getDeviceID()%>)"></td>
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
  <td><img src="images/<%=dev.getDeviceTypeIcon()%>" style="cursor:hand" onclick="javascript:switchclick(<%=dev.getDeviceID()%>)"></td>
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
function switchclick(deviceid)
{
	alert(deviceid);
}

</script>