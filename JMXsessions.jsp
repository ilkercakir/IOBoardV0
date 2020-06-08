<%@ page import ="java.util.*" %>
<%@ page import ="ControllerConsole.*" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
</head>
<jsp:useBean id="jmx" class="ControllerConsole.ConsoleJMX" scope="page"/>
<body>
maxPostSize(8080) = <%=jmx.getMaxPostSize(8080)%><br/>
activeSessions() = <%=jmx.getActiveSessions()%><br/>
</body>
</html>