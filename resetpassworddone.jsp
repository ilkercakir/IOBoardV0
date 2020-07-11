<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
<link rel="icon" type="image/png" href="images/controller.png">
</head>
<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<body>
<%
int ret = 0;

if (user.isLoggedIn())
{
	ret = user.setPassword(user.getUserName(), request.getParameter("password"));
	if (ret == 1)
	{
%>
<p align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Password reset successful</font></p>
<%
	}
	else
	{
%>
<p align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Password reset failed (error code = <%=ret%>)</font></p>
<%	
	}
}
else
{
%>
<p align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Invalid credentials</font></p>
<%
}
%>
</body>
</html>