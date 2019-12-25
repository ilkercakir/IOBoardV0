<%@ page language="java" contentType="text/html; charset=ISO-8859-9" pageEncoding="utf-8" %>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-9" />
<link rel="icon" type="image/png" href="images/controller.png">
</head>

<body onload="javascript:load()">
<form name="loginform" method="POST" action="ControllerConsole?login">
<table align="center">
 <tr>
  <td colspan="2" align="center"><img src="images/controller.png"/></td>
 </tr>
 <tr>
  <td colspan="2" align="center"><b>IOBoard V0 Controller Console</b></td>
 </tr>
 <tr>
  <td>User name</td>
  <td><input type="text" name="username" /></td>
 </tr>
 <tr>
  <td>Password</td>
  <td><input type="password" name="password" /></td>
 </tr>
 <tr>
  <td></td>
  <td><input type="submit" name="login" value="Login" /></td>
 </tr>
</table>
</form>
</body>
</html>

<script type="text/javascript">
function load()
{
 loginform.username.focus();
}
</script>