<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
</head>
<jsp:useBean id="user" class="ControllerConsole.User" scope="session"/>
<jsp:useBean id="controller" class="ControllerConsole.Controller" scope="application"/>
<body>
<table align="center" width="90%">
<%
if (user.isLoggedIn())
{
	if (user.isSuperUser())
	{
		ServletContext ctx = request.getSession().getServletContext();
		Map<String, HttpSession> sessions = (Map<String, HttpSession>)ctx.getAttribute("ConsoleSessions");
		Set set = sessions.entrySet();
		Iterator iterator = set.iterator();
		if (iterator.hasNext())
		{
%>
 <tr>
  <td><font style="font-name:Arial;font-size:24pt"><b>Key</b></font></td>
  <td><font style="font-name:Arial;font-size:24pt"><b>Interval</b></font></td>
  <td><font style="font-name:Arial;font-size:24pt"><b>New</b></font></td>
  <td><font style="font-name:Arial;font-size:24pt"><b>User</b></font></td>
 </tr>
<%
		}
		while(iterator.hasNext()) 
		{
			Map.Entry mentry = (Map.Entry)iterator.next();
			HttpSession s = (HttpSession)mentry.getValue();
			ControllerConsole.User u = (ControllerConsole.User)s.getAttribute("user");
			String uname = (u!=null?u.getUserName():"");
			
%>
 <tr>
  <td><%=mentry.getKey()%></td>
  <td><%=s.getMaxInactiveInterval()%></td>
  <td><%=s.isNew()%></td>
  <td><%=uname%></td>
 </tr>
<%
		}
	}
	else
	{
%>
<tr><td align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Need superuser</font></td></tr>
<%
	}
}
else
{
%>
<tr><td align="center"><font style="font-name:Arial;font-size:24pt;width:256px;height:128px;">Invalid credentials</font></td></tr>
<%
}
%>
</table>
</body>
</html>