<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
<link rel="icon" type="image/png" href="images/controller.png">
</head>
<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<body>
<form name="resetpasswordform" method="POST" action="resetpassworddone.jsp">
<table align="center" width="90%">
<%
if (user.isLoggedIn())
{
%>
 <tr>
  <td colspan="2" align="center"><img width="128px" height="128px" src="images/controller.png"/></td>
 </tr>
 <tr>
  <td colspan="2" align="center"><font style="font-name:Arial;font-size:36pt;"><b>IOBoard V0 Controller Console</b></font></td>
 </tr>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt"><b>User</b></font></td>
  <td><font style="font-name:Arial;font-size:24pt"><%=user.getUserName()%></font></td>
 </tr>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt"><b>Password</b></font></td>
  <td><input style="font-name:Arial;font-size:24pt;" type="password" name="password" /></td>
 </tr>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt"><b>Re-type Password</b></font></td>
  <td><input style="font-name:Arial;font-size:24pt;" type="password" name="password2" /></td>
 </tr>
 <tr>
  <td></td>
  <td><br><input style="font-name:Arial;font-size:36pt;width:256px;height:128px;" type="button" name="reset" value="Reset" onclick="javascript:click_reset()"/></td>
 </tr>
<%
}
else
{
%>
<tr><td align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Invalid credentials</font></td></tr>
<%
}
%>
</table>
</form>
</body>
</html>

<script type="text/javascript">
function click_reset()
{
	if (resetpasswordform.password.value == resetpasswordform.password2.value)
		resetpasswordform.submit();
	else
		alert("Passwords do not match");
}
</script>